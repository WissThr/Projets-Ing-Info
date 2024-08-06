n=5;
v=1:n;
B=repmat(v,n,n);
C=B';
A=rand(n,n);
A(B<C)=0;
disp(A);