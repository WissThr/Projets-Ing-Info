function formatter(numero_initial){
    let n=numero_initial;
    return (X) => "msg "+ n++ +": "+X;
}

function logger(f , c){
    return c(f);
}

let f= formatter(1);
logger(f("wsh"),console.log);
