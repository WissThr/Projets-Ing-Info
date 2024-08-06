X = dlmread('seeds_dataset.txt');
[n p] = size(X);
Y = X(:,p);
p = p - 1;
X = X(:,1:p);
mu = mean(X);
st = std(X);
v1 = ones(n,1);
Xcr = (X - mu(v1,:))./st(v1,:);
disp(Xcr);
echelle = repmat([floor(min(Xcr(:))) ceil(max(Xcr(:)))], 1, 2);
for i = 1:p
      for j = 1:p
            subplot(p,p,(i-1)*p+j);
            plot(Xcr(:,i),Xcr(:,j),'.');
            axis(echelle);
            grid;
      endcorrcoef(X)
end
figure;
