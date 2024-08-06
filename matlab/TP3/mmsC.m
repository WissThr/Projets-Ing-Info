Bonbons = rand(1000,42)*100; %%rand() genere des nombres aleatoires dans [0;1],
%on multiplie le resultat par 100 pour avoir des nombres dans [0;100]
Est_rouge = (Bonbons < 40);
nombre_rouge = sum(Est_rouge, 2);
nombre_jaune = sum(Bonbons>=40 & Bonbons < 75, 2);
nombre_bleu = sum(Bonbons >= 75, 2);
Nombre_Bonbon = [nombre_rouge nombre_jaune nombre_bleu];
C = ismember(Nombre_Bonbon, [17 11 14], 'rows');
n = sum(C);


Bonbonst = rand(1000,42)*100; %%rand() genere des nombres aleatoires dans [0;1],
%on multiplie le resultat par 100 pour avoir des nombres dans [0;100]
Est_rouget = (Bonbonst < 40);
nombre_rouget = sum(Est_rouget, 2);
nombre_jaunet = sum(Bonbonst>=40 & Bonbonst < 75, 2);
nombre_bleut = sum(Bonbonst >= 75, 2);
Nombre_Bonbont = [nombre_rouget nombre_jaunet nombre_bleut];
Ct = ismember(Nombre_Bonbont, [17 11 14], 'rows');
nt = sum(Ct);

disp(max(n,nt));