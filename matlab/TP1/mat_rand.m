n=input("Entrez le nombre de lignes n: ")
m=input("Entrez le nombre de colonne m: ")
M=rand(n,m);
M*=100;
disp(M);
disp("\n")
N=M(2:2:n,2:2:m);
disp(N);

