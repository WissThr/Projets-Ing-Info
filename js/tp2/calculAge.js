function calculAge(yb,m,j){
    let date=new Date();
    if(m>date.getMonth()+1 || j>date.getDate() )
        return date.getFullYear()-yb-1;
    else
        return date.getFullYear()-yb;
}

function askAge(){
    let jour= prompt("Quelle est ton jour de naissance?");
    let mois= prompt("Quelle est ton mois de naissance?");
    let annee= prompt("Quelle est ton année de naissance?");
    while(!anneeCorrect(annee)&& !moisCorrect(mois) && !jourCorrect(jour)){
        alert("La valeur entrée n'est pas valide, réessayez.");
        if(!anneeCorrect(annee))
            annee= prompt("Quelle est ton année de naissance?");
        if(!moisCorrect(mois))
            mois= prompt("Quelle est ton mois de naissance?");
        if(!jourCorrect(jour))
            jour= prompt("Quelle est ton jour de naissance?");
    }
    document.write("J'ai "+ calculAge(annee,mois,jour)+" ans");
}
function anneeCorrect(y){
    let date=new Date();
    return date.getFullYear()>y;
}
function moisCorrect(m){
    return m<12&&m>0;
}
function moisCorrect(j){
    return j<31&&j>0;
}
askAge();