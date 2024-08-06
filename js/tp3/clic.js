window.addEventListener('load', () => {
    const titre = document.getElementById('description');
    const image = document.getElementById('imagefilm');

    titre.addEventListener('click', function() {
        image.classList.toggle("arrondi"); // Correction: retirer le point de ".arrondi"
    });
    

    titre.addEventListener("mouseover", (e) => {
        image.src = "images/brighter2.png";
    });

    titre.addEventListener("mouseout", (e) => {
        image.src = "images/brighter1.png";
    });
});
