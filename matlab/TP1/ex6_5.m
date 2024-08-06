n=input("Entrez la largeur de la matrice:");
m=input("Entrez la hauteur de la matrice:");
A=rand(n,m);
disp(A);
if n>m
  B=A(1:m,m);
else
  B=A(n,1:n);
end
disp(B);