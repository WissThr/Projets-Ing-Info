function puissance(x,n){
    rep=1;
    for(let i=0;i<n;i++){
        rep*=x;
    }
    return rep;
}

console.log("puissance(3,3)="+puissance(3,3));