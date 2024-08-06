window.addEventListener('load', () => {
    const sources = ['images/diapo1.jpg', 'images/diapo2.jpg', 'images/diapo3.jpg', 'images/diapo4.jpg', 'images/diapo5.jpg', 'images/diapo6.jpg', 'images/diapo7.jpg', 'images/diapo8.jpg', 'images/diapo9.jpg', 'images/diapo10.jpg'];
    let i = 0;
    const img = document.getElementById("photo");

    img.addEventListener('click', (e) => {
        i = (i + 1) % sources.length; // Incrémentation de i et gestion de la boucle
        img.src = sources[i]; // Utilisation de i pour accéder à la prochaine source d'image
    });
});
