X = dlmread('seeds_dataset.txt');
[n p] = size(X);
Y = X(:,p);
p = p - 1;
X = X(:,1:p);
X2=X
 for i = unique(Y)
   X2(i,:) =mean(X(Y==i),:)
 endfor
cov(X)
corrcoef(X)
[n p] = size(X);
vect1 = ones(n,1);
mu = mean(X);
st = std(X);
Xcr = (X - mu(vect1,:))./st(vect1,:);
disp(Xcr);
[V lambda] = eig(corrcoef(X));
Xacp = Xcr * V(:,diag(lambda) >= 1);
[n k] = size(Xacp);
figure
for i = 1:k
        for j = 1:k
                subplot(k,k,(i-1)*k+j);
                hold on;
                plot(Xacp(Y == 1,i),Xacp(Y == 1,j),'o');
                hold on; polar((0:(atan(1)*8/99):(atan(1)*8))',ones(100,1));
                plot(Xacp(Y == 2,i),Xacp(Y == 2,j),'dk');
                hold on; polar((0:(atan(1)*8/99):(atan(1)*8))',ones(100,1));
                plot(Xacp(Y == 3,i),Xacp(Y == 3,j),'+r');
                hold on; polar((0:(atan(1)*8/99):(atan(1)*8))',ones(100,1));
                grid;
        end
end

l = diag(lambda);
i_tot= sum(l);
prop= l / i_tot;

S1=Xcr*V(:,6);
S2=Xcr*V(:,7);
figure;
hold on
for i=1:7
  m1=corrcoef(Xcr(:,i),S1)
  m2=corrcoef(Xcr(:,i),S2)
  plot([0,m1(2,1)],[0,m2(2,1)],'-');
 end
 axis equal;
 polar((0:(atan(1)*8/99):(atan(1)*8))',ones(100,1));
 legend("area A","perimeter P","compactness C ","length of kernel","width of kernel","asymmetry coefficient","length of kernel groove");
 
 
 
