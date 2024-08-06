r=ones(1000,1);
for i=1:10000
lancer = 0;
somme=0;
while somme<20
somme = somme+randi(6,1);
lancer = lancer+1;
end
r(i) = lancer;
end

hist(r,1:1:20);
xlim([3,10]);