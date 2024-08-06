n=0;
for i=0:1000
balle = randi(20); %randi(20) permet de piocher un entier entre 1 et 20
if(balle >= 2 && balle <= 4)
disp 'Balle bleue';
n++;
end
end

disp(n);
disp(20*n/1000);