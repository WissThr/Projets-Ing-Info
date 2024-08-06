max_total = 0;
max_prose = 0;
max_pbleu=0;

for p_rose=0:100
for p_bleu=0:100
if(p_rose + p_bleu <=100) %On exclue les valeur de proba impossible
p_vert = 100 - p_rose - p_bleu;
Bonbons = rand(1000, 15)*100;
nombre_rose = sum(Bonbons<p_rose, 2);
nombre_bleu = sum(Bonbons>=p_rose & Bonbons < p_rose + p_bleu, 2);
nombre_vert = sum(Bonbons >= p_rose + p_bleu, 2);
Nombre_Bonbon = [nombre_rose nombre_bleu nombre_vert];
total = sum(ismember(Nombre_Bonbon, [4 5 6], 'rows')) +sum(ismember(Nombre_Bonbon, [3 4 8], 'rows')) +sum(ismember(Nombre_Bonbon, [7 2 6], 'rows')) +sum(ismember(Nombre_Bonbon, [5 3 7], 'rows')) +sum(ismember(Nombre_Bonbon, [6 3 6], 'rows'));

if( total > max_total)
max_total = total;
max_prose = p_rose;
max_pbleu = p_bleu;
end

end
end
end