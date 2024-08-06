function puissance(x,n){
    if(n===0){
        return 1;
    }
    else
        return x*puissance(x,n-1);
}

console.log("puissance(3,3)="+puissance(3,3));