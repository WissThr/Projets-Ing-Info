DROP TABLE F_Rôle;
DROP TABLE MES;
DROP TABLE Personne;
DROP TABLE Film;

CREATE TABLE Personne(
    PID NUMBER NOT NULL,
    Prenom VARCHAR(100) NOT NULL,
    Nom VARCHAR(100) NOT NULL,
    PRIMARY KEY(PID)
);

CREATE TABLE Film(
    FID NUMBER NOT NULL,
    Titre VARCHAR(100) NOT NULL,
    An NUMBER NOT NULL,
    Duree INT NOT NULL,
    Rang INT NOT NULL,
    PRIMARY KEY(FID)
);

CREATE TABLE F_Rôle(
    FID NUMBER NOT NULL,
    PID NUMBER NOT NULL,
    Nom VARCHAR(50) NOT NULL,
    CONSTRAINT ffid FOREIGN KEY(FID) REFERENCES Film(FID) ON DELETE CASCADE,
    CONSTRAINT fpid FOREIGN KEY(PID) REFERENCES Personne(PID) ON DELETE CASCADE,
    PRIMARY KEY(FID, PID, Nom)
);

CREATE TABLE MES(
    FID NUMBER NOT NULL,
    PID NUMBER NOT NULL,
    CONSTRAINT fffid FOREIGN KEY(FID) REFERENCES Film(FID)ON DELETE CASCADE,
    CONSTRAINT ffpid FOREIGN KEY(PID) REFERENCES Personne(PID)ON DELETE CASCADE,
    PRIMARY KEY(FID, PID)
);

ALTER TABLE Film ADD CONSTRAINT check_annee CHECK (An > 1900);
ALTER TABLE Film DROP CONSTRAINT check_annee;
ALTER TABLE Film ADD CONSTRAINT check_annee CHECK (An > 1900);

INSERT INTO Film (FID, Titre, An, Duree, Rang) VALUES (3000, 'Kind_Hearts_and_Coronets', 1949, 106, 99);
INSERT INTO Film (FID, Titre, An, Duree, Rang) VALUES(2174, 'Butch_Cassidy_and_the_Sundance_Kid', 1969, 110, 175);
INSERT INTO Film (FID, Titre, An, Duree, Rang) VALUES(2096, 'The_Sting', 1973, 129, 97);
INSERT INTO Film (FID, Titre, An, Duree, Rang) VALUES(2324, 'All_the_PresidentJs_Men', 1976, 125, 325);
INSERT INTO Film (FID, Titre, An, Duree, Rang) VALUES(2101, 'Monty_Python_and_the_Holy_Grail', 1975, 91, 102);
INSERT INTO Film (FID, Titre, An, Duree, Rang) VALUES(2189, 'Life_of_Brian', 1979, 94, 190);
INSERT INTO Film (FID, Titre, An, Duree, Rang) VALUES(2180, 'Annie_Hall', 1977, 93, 181);
INSERT INTO Film (FID, Titre, An, Duree, Rang) VALUES(2295, 'Manhattan', 1979, 96, 296);
INSERT INTO Film (FID, Titre, An, Duree, Rang) VALUES(2432, 'Ordinary_People', 1980, 124, 433);
INSERT INTO Film (FID, Titre, An, Duree, Rang) VALUES(2568, 'Match_Point', 2005, 126, 569);
INSERT INTO Film (FID, Titre, An, Duree, Rang) VALUES(2340, 'Hannah_and_Her_Sisters', 1986, 103, 341);
INSERT INTO Film (FID, Titre, An, Duree, Rang) VALUES(2609, 'Midnight_in_Paris', 2011, 94, 610);
INSERT INTO Film (FID, Titre, An, Duree, Rang) VALUES(2602, 'La_mome', 2007, 140, 603);
INSERT INTO Film (FID, Titre, An, Duree, Rang) VALUES(2034, 'The_Dark_Knight_Rises', 2012, 165, 35);
INSERT INTO Film (FID, Titre, An, Duree, Rang) VALUES(2798, 'De_rouille_et_d_os', 2012, 120, 799);

INSERT INTO Personne (PID, Prenom, Nom) VALUES (2330, 'Woody', 'Allen');
INSERT INTO Personne (PID, Prenom, Nom) VALUES (1281, 'Robert', 'Redford');
INSERT INTO Personne (PID, Prenom, Nom) VALUES (6572, 'Robert', 'De Niro');
INSERT INTO Personne (PID, Prenom, Nom) VALUES (1280, 'Paul', 'Newman');
INSERT INTO Personne (PID, Prenom, Nom) VALUES (26, 'Diane', 'Keaton');
INSERT INTO Personne (PID, Prenom, Nom) VALUES (7148, 'Olivier', 'Dahan');
INSERT INTO Personne (PID, Prenom, Nom) VALUES (4033, 'Alan J.', 'Pakula');
INSERT INTO Personne (PID, Prenom, Nom) VALUES (1279, 'George Roy', 'Hill');
INSERT INTO Personne (PID, Prenom, Nom) VALUES (165, 'Marion', 'Cotillard');
INSERT INTO Personne (PID, Prenom, Nom) VALUES (1340, 'Terry', 'Jones');
INSERT INTO Personne (PID, Prenom, Nom) VALUES (1339, 'Terry', 'Gilliam');
INSERT INTO Personne (PID, Prenom, Nom) VALUES (181, 'Alec', 'Guinness');
INSERT INTO Personne (PID, Prenom, Nom) VALUES (11001, 'Robert', 'Hamer');
INSERT INTO Personne (PID, Prenom, Nom) VALUES (11002, 'Actrice', 'Robert');
INSERT INTO Personne (PID, Prenom, Nom) VALUES (798, 'Scarlett', 'Johansson');
INSERT INTO Personne (PID, Prenom, Nom) VALUES (6764, 'Jonathan', 'Rhys');
INSERT INTO Personne (PID, Prenom, Nom) VALUES (2042, 'Emily', 'Mortimer');
INSERT INTO Personne (PID, Prenom, Nom) VALUES (42, 'Christopher', 'Nolan');
INSERT INTO Personne (PID, Prenom, Nom) VALUES (4761, 'Jacques', 'Audiard');
INSERT INTO Personne (PID, Prenom, Nom) VALUES (48, 'Julie', 'Andrews');


INSERT INTO F_Rôle (FID, PID, Nom) VALUES (2295, 26, 'Mary');
INSERT INTO F_Rôle (FID, PID, Nom) VALUES (2609, 165, 'Adriana');
INSERT INTO F_Rôle (FID, PID, Nom) VALUES (2609, 11002, 'Ghost');
INSERT INTO F_Rôle (FID, PID, Nom) VALUES (2340, 2330, 'Mickey');
INSERT INTO F_Rôle (FID, PID, Nom) VALUES (2340, 11002, 'Mickey');
INSERT INTO F_Rôle (FID, PID, Nom) VALUES (2180, 26, 'Annie_Hall');
INSERT INTO F_Rôle (FID, PID, Nom) VALUES (2180, 11002, 'Jones');
INSERT INTO F_Rôle (FID, PID, Nom) VALUES (3000, 181, 'General_d_Ascoyne');
INSERT INTO F_Rôle (FID, PID, Nom) VALUES (2602, 165, 'Edith_Piaf');
INSERT INTO F_Rôle (FID, PID, Nom) VALUES (2602, 48, 'Mary');
INSERT INTO F_Rôle (FID, PID, Nom) VALUES (2295, 2330, 'Isaac');
INSERT INTO F_Rôle (FID, PID, Nom) VALUES (2295, 11002, 'Mary');
INSERT INTO F_Rôle (FID, PID, Nom) VALUES (2174, 1281, 'The_Sundance_Kid');
INSERT INTO F_Rôle (FID, PID, Nom) VALUES (3000, 181, 'Reverend_d_Ascoyne');
INSERT INTO F_Rôle (FID, PID, Nom) VALUES (2174, 1280, 'Butch_Cassidy');
INSERT INTO F_Rôle (FID, PID, Nom) VALUES (2096, 1281, 'Johnny_Hooker');
INSERT INTO F_Rôle (FID, PID, Nom) VALUES (2324, 1281, 'Bob_Woodward');
INSERT INTO F_Rôle (FID, PID, Nom) VALUES (2101, 1340, 'DennisJs_Mother');
INSERT INTO F_Rôle (FID, PID, Nom) VALUES (2101, 1339, 'Patsy');
INSERT INTO F_Rôle (FID, PID, Nom) VALUES (2189, 1340, 'Mandy_Cohen');
INSERT INTO F_Rôle (FID, PID, Nom) VALUES (3000, 181, 'Lord_d_Ascoyne');
INSERT INTO F_Rôle (FID, PID, Nom) VALUES (3000, 181, 'Lady_d_Ascoyne');
INSERT INTO F_Rôle (FID, PID, Nom) VALUES (2568, 6764, 'Chris_Wilton');
INSERT INTO F_Rôle (FID, PID, Nom) VALUES (2568, 11002, 'Old_Lady');
INSERT INTO F_Rôle (FID, PID, Nom) VALUES (2568, 2042, 'Chloe_Hewett_Wilton');
INSERT INTO F_Rôle (FID, PID, Nom) VALUES (2568, 798, 'Nola_Rice');
INSERT INTO F_Rôle (FID, PID, Nom) VALUES (2798, 165, 'Stephanie');
INSERT INTO F_Rôle (FID, PID, Nom) VALUES (2034, 165, 'Miranda');

INSERT INTO MES (FID, PID) VALUES (2096, 1279);
INSERT INTO MES (FID, PID) VALUES (2174, 1279);
INSERT INTO MES (FID, PID) VALUES (2101, 1340);
INSERT INTO MES (FID, PID) VALUES (2101, 1339);
INSERT INTO MES (FID, PID) VALUES (2189, 1340);
INSERT INTO MES (FID, PID) VALUES (2189, 1339);
INSERT INTO MES (FID, PID) VALUES (2180, 2330);
INSERT INTO MES (FID, PID) VALUES (2295, 2330);
INSERT INTO MES (FID, PID) VALUES (2340, 2330);
INSERT INTO MES (FID, PID) VALUES (2609, 2330);
INSERT INTO MES (FID, PID) VALUES (2568, 2330);
INSERT INTO MES (FID, PID) VALUES (2602, 7148);
INSERT INTO MES (FID, PID) VALUES (2324, 4033);
INSERT INTO MES (FID, PID) VALUES (2432, 1281);
INSERT INTO MES (FID, PID) VALUES (2798, 4761);
INSERT INTO MES (FID, PID) VALUES (2034, 42);







