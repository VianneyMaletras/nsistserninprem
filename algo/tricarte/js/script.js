function shuffle(array) {
    for (var i = array.length - 1; i > 0; i--) {
        var j = Math.floor(Math.random() * (i + 1));
        [array[i], array[j]] = [array[j], array[i]];
    }
    return array;
}
function shuffleWithoutReplacement(array) {
    var currentIndex = array.length, temporaryValue, randomIndex;

    // Tant qu'il reste des éléments à mélanger
    while (currentIndex !== 0) {
        // Sélectionner un élément restant
        randomIndex = Math.floor(Math.random() * currentIndex);
        currentIndex -= 1;

        // Échanger avec l'élément courant
        temporaryValue = array[currentIndex];
        array[currentIndex] = array[randomIndex];
        array[randomIndex] = temporaryValue;
    }

    return array;
}

function duplicateRow() {
    var originalRow = document.querySelector("#initial-cards");
    var clonedRow = originalRow.cloneNode(true);
    var stepNumber = document.querySelectorAll(".cards-container").length + 1;
    var shuffledCards = ["10.png", "valet.png", "dame.png", "roi.png", "as.png"];
    shuffleWithoutReplacement(shuffledCards);
    clonedRow.childNodes.forEach(function(card, index) {
        card.id = "card-" + index + "-" + stepNumber;
        card.setAttribute("data-index", index);
        card.innerHTML = `<img src="${shuffledCards[index]}" alt="${shuffledCards[index]}">`;
        card.draggable = true;
        card.ondragstart = drag;
    });
    clonedRow.childNodes.forEach(function(card) {
        card.innerHTML += " (étape " + stepNumber + ")";
    });
    document.querySelector(".container").appendChild(clonedRow);
}

// Liste des noms de fichiers des cartes
var cardFiles = ["10.png", "valet.png", "dame.png", "roi.png", "as.png"];

// Fonction pour charger aléatoirement une carte dans chaque zone de drop, en excluant la première zone
function loadRandomCards() {
    var dropZones = document.querySelectorAll('.drop-zone');
    var uniqueCards = shuffle(cardFiles.slice()); // Copie de la liste des cartes pour éviter de la modifier directement
    // Commencer à partir de la deuxième zone de drop pour exclure la première zone
    for (var i = 1; i < dropZones.length; i++) {
        var randomIndex = Math.floor(Math.random() * uniqueCards.length);
        var cardFileName = uniqueCards.splice(randomIndex, 1)[0]; // Retirer la carte sélectionnée de la liste des cartes uniques
        var img = document.createElement('img');
        img.src = "./images/"+cardFileName;
        img.alt = cardFileName.split('.')[0];
        dropZones[i].appendChild(img);
    }
}

// Charger les cartes aléatoires au démarrage
loadRandomCards();

function reshuffleCards() {
    // Supprimer les cartes actuelles de toutes les zones de drop
    var dropZones = document.querySelectorAll('.drop-zone');
    dropZones.forEach(function(zone) {
        zone.innerHTML = ''; // Supprimer tout le contenu de la zone de drop
    });

    // Recharger les cartes aléatoires
    loadRandomCards();
}
function allowDrop(event) {
    event.preventDefault();
}

function drag(event) {
    event.dataTransfer.setData("text", event.target.id);
}
/* ce drop ajoute à coté
function drop(event) {
    event.preventDefault();
    var id = event.dataTransfer.getData("text");
    console.log("ID de l'élément à déplacer :", id);
    var target = event.target.closest(".drop-zone");
    if (target) {
        if (id.startsWith("card-")) {
            // Si l'élément vient d'une des cartes initiales
            var selectedCard = document.getElementById(id);
            if (selectedCard) {
                // Ajouter la carte dans la nouvelle zone de drop
                target.appendChild(selectedCard.cloneNode(true));
            }
        } else {
            // Si l'élément vient d'un glisser-déposer depuis le système de fichiers
            var img = document.createElement("img");
            img.src = id;
            img.alt = id;
            // Ajouter l'image dans la nouvelle zone de drop
            target.appendChild(img);
        }
    }

}*/
// Variable pour garder une trace de la source de la carte
var draggedFromTopZone = false;

function allowDrop(event) {
    event.preventDefault();
}

function drag(event) {
    event.dataTransfer.setData("text", event.target.id);
    // Vérifier si la carte est glissée depuis la zone du haut
    draggedFromTopZone = (event.target.parentElement.id === "drop-zone");
}

function drop(event) {
    event.preventDefault();
    var id = event.dataTransfer.getData("text");
    console.log("ID de l'élément à déplacer :", id);
    var target = event.target.closest(".drop-zone");
    var sourceZone = document.getElementById("drop-zone");
    if (target) {
        if (id.startsWith("card-")) {
            // Si l'élément vient d'une des cartes initiales
            var selectedCard = document.getElementById(id);
            if (selectedCard) {
                // Vider la zone du haut si la carte provient de là
                if (draggedFromTopZone) {
                    sourceZone.innerHTML = '';
                }
                // Supprimer la carte existante dans la zone de drop
                target.innerHTML = '';
                // Ajouter la carte dans la nouvelle zone de drop
                target.appendChild(selectedCard.cloneNode(true));
            }
        } else {
            // Si l'élément vient d'un glisser-déposer depuis le système de fichiers
            var img = document.createElement("img");
            img.src = id;
            img.alt = id;
            // Supprimer la carte existante dans la zone de drop
            target.innerHTML = '';
            // Ajouter l'image dans la nouvelle zone de drop
            target.appendChild(img);
        }
    }
}
