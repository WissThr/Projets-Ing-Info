function minimum(a,b){
    if(a>b)
        return b;
    else
        return a;
}
function maximum(a,b){
    if(a<b)
        return b;
    else
        return a;
}

console . log ( " minimum (75 ,93) = " + minimum (75 ,93) ) ; // affiche minimum (75 ,93) = 75
console . log ( " minimum (54 ,35) = " + minimum (54 ,35) ) ; // affiche minimum (54 ,35) = 35
console . log ( " maximum (75 ,93) = " + maximum (75 ,93) ) ; // affiche maximum (75 ,93) = 93