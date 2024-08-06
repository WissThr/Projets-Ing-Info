function fibonacci(init, step){
    let i = 0;
    let j=1;
    return () => {
        let result = i+j;  // Stocker la valeur actuelle de i
         i = j;
         j=result;  // Incrémenter i par step
        return result;  // Retourner la valeur stockée
    };
}

let fibolapins = fibonacci (1 , 1) ;
console . log ( " fibolapins appel 1 : " + fibolapins () ) ; // affiche 2
console . log ( " fibolapins appel 2 : " + fibolapins () ) ; // affiche 3
console . log ( " fibolapins appel 3 : " + fibolapins () ) ; // affiche 5
console . log ( " fibolapins appel 4 : " + fibolapins () ) ; // affiche 8
console . log ( " fibolapins appel 1 : " + fibolapins () ) ; // affiche 2
console . log ( " fibolapins appel 2 : " + fibolapins () ) ; // affiche 3
console . log ( " fibolapins appel 3 : " + fibolapins () ) ; // affiche 5
console . log ( " fibolapins appel 4 : " + fibolapins () ) ; // affiche 8