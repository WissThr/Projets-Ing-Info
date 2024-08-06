clear
Bonbons = rand(1000,15)*100; %%rand() genere des nombres aleatoires dans [0;1],
%on multiplie le resultat par 100 pour avoir des nombres dans [0;100]
Est_Rose = (Bonbons < 45);
nombre_rose = sum(Est_Rose, 2);
nombre_bleu = sum(Bonbons>=45 & Bonbons < 80, 2);
nombre_vert = sum(Bonbons >= 80, 2);
Nombre_Bonbon = [nombre_rose nombre_bleu nombre_vert];
C = ismember(Nombre_Bonbon, [4 5 6], 'rows');
n = sum(C);
total = sum(ismember(Nombre_Bonbon, [4 5 6], 'rows')) +sum(ismember(Nombre_Bonbon, [3 4 8], 'rows')) +sum(ismember(Nombre_Bonbon, [7 2 6], 'rows')) +sum(ismember(Nombre_Bonbon, [5 3 7], 'rows')) +sum(ismember(Nombre_Bonbon, [6 3 6], 'rows'));
