function saisirNbr(msg){
    let n=prompt(msg);
    while(n<0){
        alert("bzr");
        n=prompt(msg);
    }
    return n;
}

function calcMoy(){
    let n=parseInt(prompt("cmb de nbr à entrer?"));
    let res =0;
    for(let i=0;i<n;i++){
        let a=parseInt(saisirNbr("entre nbr"));
        document.write("Entier "+i+" = "+a+"<br>");
        res=res+a;
    }
    document.write("Moyenne ="+(res/n));
}
calcMoy();