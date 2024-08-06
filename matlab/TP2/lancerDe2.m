alea = randi(6, [20, 10^8]);
s = cumsum(alea, 1);
f = (s>=20);
[valeur_max,position_max] = max(f, [], 1);
r = position_max;
hist(r, 3:18)
xlim([3 10])