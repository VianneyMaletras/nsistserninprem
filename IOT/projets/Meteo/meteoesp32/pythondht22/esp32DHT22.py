from machine import *
import network
import utime
from vitta_server import SERVER
import gc
import esp

ESP32_IP = ''
SERVER_PORT = 80
esp.osdebug(None)
gc.collect()

station = None
accessPoint = None
server = SERVER()
# Servo on p12
p12 = PWM(Pin(12), freq=50, duty=26)

def connect_station(ssid='', password='', ip='', mask='', gateway='', dhcp_hostname=''):
  global station
  station = network.WLAN(network.STA_IF)
  if station.isconnected():
    if station.config('essid') is ssid:
      print("Already connected on ssid: '%s'" % station.config('essid'))
      return
    else:
      disconnect_station()
  print("\nTrying to connect to '%s' ..." % ssid)
  if len(ip) is not 0:
    if len(gateway) == 0:
      gateway = ip.split('.')[0] + '.' + ip.split('.')[1] + '.' + ip.split('.')[2] + '.1'
    if len(mask) == 0:
      mask = '255.255.255.0'
    station.ifconfig([ip, mask, gateway, gateway])
  if not station.active():
    station.active(True)
  if len(dhcp_hostname) != 0:
    station.config(dhcp_hostname=dhcp_hostname)
  station.connect(ssid, password)
  while not station.isconnected():
    pass
  print("Station connected !")

def disconnect_station():
  if station is not None and station.isconnected():
    ssid = station.config('essid')
    station.disconnect()
    for retry in range(100):
      connected = station.isconnected()
      if not connected:
        break
      utime.sleep(0.1)
    if not connected:
      station.active(False)
      utime.sleep(0.2)
      print("Disconnected from '%s'\n" %ssid)
    else:
      print("Disconnection from '%s' failed.\n" %ssid)
  else:
    print("Station already disconnected.\n")

def setServoAngle(pin, angle):
  if (angle >= 0 and angle <= 180):
    pin.duty(int(0.025*1023 + (angle*0.1*1023)/180))
  else:
    raise ValueError("Servomotor angle have to be set between 0 and 180")

connect_station(ssid='', password='', ip=ESP32_IP)
server.start(sta=station, ip=ESP32_IP, port=SERVER_PORT)
valeur_angle = 0
setServoAngle(p12, valeur_angle)

while True:
  if station.isconnected():
    server.html_page = """
      <!DOCTYPE HTML>
      <html>
      <head>
      <meta charset="UTF-8" name="viewport" content="width=device-width, initial-scale=1">
      </head>
      <body>
        <h1 class="police" style="color:#22b573;">""" + 'Piloter un servomoteur' + """</h1>
        <h3 class="police" style="color:#999999;">""" + 'depuis une page web' + """</h3>
        <span class="police" style="color:#c3c3c3;font-size:""" + str(0.8*15) + """px;margin-bottom:""" + str(0.15*15) + """px;">""" + str(15) + """</span>
        <input type="range" min='""" + str(15) + """' max='""" + str(165) + """' value='""" + server.getValueById('Commande-Rotation', default=(165-15)/2) + """' class="slider slider_""" + 'Commande-Rotation' + """" id='""" + 'Commande-Rotation' + """'>
        <span class="police" style="color:#c3c3c3;font-size:""" + str(0.8*15) + """px;margin-bottom:""" + str(0.15*15) + """px;">""" + str(165) + """</span>
      </body>
      </html>"""

    server.sendHtmlPage(False)
  valeur_angle = int(float(server.getValueById('Commande-Rotation')))
  setServoAngle(p12, valeur_angle)
  server.closeClient(True)