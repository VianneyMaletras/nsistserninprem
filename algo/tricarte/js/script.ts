// Fonction pour mélanger un tableau d'éléments
function shuffle<T>(array: T[]): T[] {
    for (let i = array.length - 1; i > 0; i--) {
        const j = Math.floor(Math.random() * (i + 1));
        [array[i], array[j]] = [array[j], array[i]];
    }
    return array;
}

// Fonction pour mélanger un tableau d'éléments sans remplacement
function shuffleWithoutReplacement<T>(array: T[]): T[] {
    let currentIndex = array.length;
    let temporaryValue: T;
    let randomIndex: number;

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

// Fonction pour dupliquer la ligne
function duplicateRow() {
    const originalRow = document.querySelector<HTMLDivElement>("#initial-cards");
    const clonedRow = originalRow.cloneNode(true) as HTMLDivElement;
    const stepNumber = document.querySelectorAll<HTMLDivElement>(".cards-container").length + 1;
    const shuffledCards = ["10.png", "valet.png", "dame.png", "roi.png", "as.png"];
    shuffleWithoutReplacement(shuffledCards);
    clonedRow.childNodes.forEach((card, index) => {
        const cardElement = card as HTMLElement;
        cardElement.id = `card-${index}-${stepNumber}`;
        cardElement.setAttribute("data-index", index.toString());
        cardElement.innerHTML = `<img src="${shuffledCards[index]}" alt="${shuffledCards[index]}">`;
        cardElement.draggable = true;
        cardElement.ondragstart = drag;
    });
    clonedRow.childNodes.forEach((card) => {
        const cardElement = card as HTMLElement;
        cardElement.innerHTML += ` (étape ${stepNumber})`;
    });
    document.querySelector<HTMLDivElement>(".container").appendChild(clonedRow);
}

// Liste des noms de fichiers des cartes
const cardFiles: string[] = ["10.png", "valet.png", "dame.png", "roi.png", "as.png"];

// Fonction pour charger aléatoirement une carte dans chaque zone de drop, en excluant la première zone
function loadRandomCards() {
    const dropZones = document.querySelectorAll<HTMLDivElement>('.drop-zone');
    const uniqueCards = shuffle(cardFiles.slice()); // Copie de la liste des cartes pour éviter de la modifier directement
    // Commencer à partir de la deuxième zone de drop pour exclure la première zone
    for (let i = 1; i < dropZones.length; i++) {
        const randomIndex = Math.floor(Math.random() * uniqueCards.length);
        const cardFileName = uniqueCards.splice(randomIndex, 1)[0]; // Retirer la carte sélectionnée de la liste des cartes uniques
        const img = document.createElement('img');
        img.src = cardFileName;
        img.alt = cardFileName.split('.')[0];
        dropZones[i].appendChild(img);
    }
}

// Charger les cartes aléatoires au démarrage
loadRandomCards();

// Fonction pour réorganiser les cartes
function reshuffleCards() {
    // Supprimer les cartes actuelles de toutes les zones de drop
    const dropZones = document.querySelectorAll<HTMLDivElement>('.drop-zone');
    dropZones.forEach((zone) => {
        zone.innerHTML = ''; // Supprimer tout le contenu de la zone de drop
    });

    // Recharger les cartes aléatoires
    loadRandomCards();
}

// Fonction pour autoriser le drop
function allowDrop(event: DragEvent) {
    event.preventDefault();
}

// Fonction pour lancer le drag
function drag(event: DragEvent) {
    const target = event.target as HTMLElement;
    event.dataTransfer.setData("text", target.id);
}

// Variable pour garder une trace de la source de la carte
let draggedFromTopZone = false;

// Fonction pour gérer le drop
function drop(event: DragEvent) {
    event.preventDefault();
    const id = event.dataTransfer.getData("text");
    console.log("ID de l'élément à déplacer :", id);
    const target = event.target as HTMLElement;
    const sourceZone = document.getElementById("drop-zone")!;
    if (target) {
        if (id.startsWith("card-")) {
            // Si l'élément vient d'une des cartes initiales
            const selectedCard = document.getElementById(id)!;
            // Vérifier si la carte provient de la zone du haut
            draggedFromTopZone = (selectedCard.parentElement!.id === "drop-zone");
            // Supprimer la carte existante dans la zone de drop
            target.innerHTML = '';
            // Ajouter la carte dans la nouvelle zone de drop
            target.appendChild(selectedCard.cloneNode(true));
            // Vider la zone d'origine si la carte est déplacée depuis la zone du bas
            if (!draggedFromTopZone && target !== sourceZone) {
                sourceZone.innerHTML = '';
            }
        } else {
            // Si l'élément vient d'un glisser-déposer depuis le système de fichiers
            const img = document.createElement("img");
            img.src = id;
            img.alt = id;
            // Supprimer la carte existante dans la zone de drop
            target.innerHTML = '';
            // Ajouter l'image dans la nouvelle zone de drop
            target.appendChild(img);
        }
    }
}
