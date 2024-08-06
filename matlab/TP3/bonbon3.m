M = zeros(101,101);
for p_rose=0:100
for p_bleu=0:100
if(p_rose + p_bleu <=100) %On exclue les valeur de proba impossible
p_vert = 100 - p_rose - p_bleu
Bonbons = rand(1000, 15)*100;
nombre_rose = sum(Bonbons<p_rose, 2);
nombre_bleu = sum(Bonbons>=p_rose & Bonbons < p_rose + p_bleu, 2);
nombre_vert = sum(Bonbons >= p_rose + p_bleu, 2);
Nombre_Bonbon = [nombre_rose nombre_bleu nombre_vert];
total = sum(ismember(Nombre_Bonbon, [4 5 6], 'rows')) +sum(ismember(Nombre_Bonbon, [3 4 8], 'rows')) +sum(ismember(Nombre_Bonbon, [7 2 6], 'rows')) +sum(ismember(Nombre_Bonbon, [5 3 7], 'rows')) +sum(ismember(Nombre_Bonbon, [6 3 6], 'rows'));
M(p_rose+1, p_bleu+1) = total;
end
end
end
prose = 0:100;
pbleu = 0:100;
surf(0:100, 0:100, M); %Attention, le premier axe represente l'axe des x, donc les
%colonnes, donc pbleu
%surf utilise une representation x,y tandis que M a ete remplie avec une
%representation
%ligne,colonne
xlabel('pbleu');
ylabel('prose');