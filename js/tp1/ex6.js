function creerSequence(init, step){
    let i = init;
    return () => {
        let result = i;  // Stocker la valeur actuelle de i
         i += step;  // Incrémenter i par step
        return result;  // Retourner la valeur stockée
    };
}

let seq43 = creerSequence(4, 3);
let seq21 = creerSequence(2, 1); 
console.log ( " Test : creerSequence (4 , 3) appel 1 : " + seq43() ) ; // 4
console.log ( " Test : creerSequence (2 , 1) appel 1 : " + seq21() ) ; // 2
console.log ( " Test : creerSequence (4 , 3) appel 2 : " + seq43() ) ; // 7
console.log ( " Test : creerSequence (4 , 3) appel 3 : " + seq43() ) ; // 10
console.log ( " Test : creerSequence (2 , 1) appel 2 : " + seq21() ) ; // 3