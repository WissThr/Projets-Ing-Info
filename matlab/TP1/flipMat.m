n=input("Entrez la largeur de la matrice:");
m=input("Entrez la hauteur de la matrice:");
A=randi([1,10],n,m);
disp(A);
disp("\n");
l=1:n;
c=m:-1:1;
B=A(l,c);
disp(B);