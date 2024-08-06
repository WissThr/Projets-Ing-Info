for(let i =0; i<=100; i++){
    console.log(i + div3(i)+ div5(i)+ville(i));
}


function div3(x){
    if(x%3===0){
        return " est divisible par 3";
    }
    else   
        return "";
}

function div5(x){
    if(x%5===0){
        return " est divisible par 5";
    }
    else
        return "";
}

function ville(x){
    if(x===13)
        return " C'est Marseille bb!";
    else if(x===93)
        return " 93 c'est la Champions League";
    else
        return "";
}

