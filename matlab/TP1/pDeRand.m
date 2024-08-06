a=rand(3000,3000);
b=a(find(a>0.5));
p=(numel(b)/numel(a))*100;
disp(p);