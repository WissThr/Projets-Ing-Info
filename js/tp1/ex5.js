let multipli4=creerMulti(4);
console . log ( " Test : creerMultiplicateur (4) (3) = " + creerMulti2(5,6) ) ;

function creerMulti(n){
    return (x)=>x*n;
}

function creerMulti2(x,n){
    let multiX=creerMulti(n);
    return multiX(x);
}