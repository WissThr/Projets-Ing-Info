#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

#define couleur(param) printf("\033[%sm", param)
#define clrscr() printf("\033[H\033[2J")

#define LIGNE 6
#define COLONNE 7

enum Etat
{
    Vide = -1,
    Jaune,
    Rouge,
};

typedef struct
{
    int8_t **tab;
    int8_t tour;
    int8_t fin;
    int8_t mode;
} partie;

typedef struct liste
{
    int8_t **tab;
    int32_t score;
    struct liste *l;
} liste;

partie *initialisation_partie();
int8_t **initialisation_tableau();

void menu(partie *p);

void deroulement(partie *p);
void deroulementIA(partie *p);
void deroulement2IA(partie *p);

int8_t demande_colonne(partie *p);
void poser_jeton(partie *p, int8_t jeu);
void finalite(partie *p);

void partie_pvp(partie *p);
void partie_pve(partie *p);
void partie_eve(partie *p);

int32_t score_case(int8_t **tab, int8_t c, int8_t l);
int32_t score_diag1(int8_t **tab, int8_t c, int8_t l);
int32_t score_diag2(int8_t **tab, int8_t c, int8_t l);
int32_t score_colonne(int8_t **tab, int8_t c, int8_t l);
int32_t score_ligne(int8_t **tab, int8_t c, int8_t l);
int32_t resultat(int8_t j, int8_t r, int8_t vide);
int32_t score(liste *Li);

int32_t MinMax(liste *Li, uint8_t n);
int32_t max(liste *Li);
int32_t min(liste *Li);

int8_t verif(int8_t **tab, int8_t c, int8_t l);
void afficher(int8_t **tab);
void free_liste(liste *Li);
bool liste_est_feuille(liste *Li);
void free_tableau(int8_t **tab);
void free_partie(partie *p);

int main()
{

    // initialisation de la partie
    partie *p = initialisation_partie();

    // choix mode et déroulement de la partie

    menu(p);
    if (p->mode == 1)
    {
        partie_pvp(p);
    }
    else if (p->mode == 2)
    {
        partie_pve(p);
    }
    else
    {
        partie_eve(p);
    }
    free_partie(p);
    return EXIT_SUCCESS;
}

partie *initialisation_partie()
{

    partie *p = (partie *)malloc(sizeof(partie));

    // initialisation tableau
    p->tab = initialisation_tableau();

    // initialiser les autres valeurs
    p->fin = 0;
    p->tour = 0;

    return p;
}

int8_t **initialisation_tableau()
{
    int8_t **tab = (int8_t **)malloc(LIGNE * sizeof(int8_t *));
    for (int i = 0; i < LIGNE; i++)
    {
        tab[i] = (int8_t *)malloc(COLONNE * sizeof(int8_t));
    }
    for (int i = 0; i < LIGNE; i++)
    {
        for (int j = 0; j < COLONNE; j++)
        {
            tab[i][j] = -1;
        }
    }
    return tab;
}

void menu(partie *p)
{

    printf("Si vous voulez jouer en pvp tapez 1 mais si vous voulez jouer en pve taper 2. \nTapez autre chose pour que 2 IA s'affrontent.\n");
    scanf("%hhd", &p->mode);

}

void partie_pvp(partie *p)
{
    deroulement(p);
    finalite(p);
}

void deroulement(partie *p)
{
	
    while (p->fin == 0)
    {
	
        int8_t jeu = demande_colonne(p);
		system("clear");
        if (p->fin != -1)
        {
            poser_jeton(p, jeu);
        }
    }
}

void deroulementIA(partie *p)
{
    while (p->fin == 0)
    {
        int8_t jeu=0;
        if (p->tour % 2 == 0)
        {
            jeu = demande_colonne(p);
        }
        else
        {

            liste *Li = (liste *)malloc(sizeof(liste));
            Li->tab = initialisation_tableau();
            for (int i = 0; i < LIGNE; i++)
            {
                for (int j = 0; j < COLONNE; j++)
                {
                    Li->tab[i][j] = p->tab[i][j];
                }
            }
            Li->score = MinMax(Li, 0);
            for (int i = 0; i < COLONNE; i++)
            {
                printf("score du coup %d: %d\n", i, Li->l[i].score);

                if (Li->score == Li->l[i].score)
                {
                    if (p->tab[LIGNE - 1][i] != Vide)
                    {
                        while (p->tab[LIGNE - 1][i] != Vide && i != -1)
                        {
                            Li->l[i].score = -999999;
                            Li->score = max(Li);
                            i = -1;
                        }
                    }
                    else
                    {
                        jeu = i;
                    }
                }
            }
            free_tableau(Li->tab);
            free_liste(Li);
            free(Li);
            system("clear");
            printf("\ncoup joué en %d\n", jeu + 1);
        }

        if (p->fin != -1)
        {
            poser_jeton(p, jeu);
        }
    }
}

void deroulement2IA(partie *p)
{
    while (p->fin == 0)
    {
        int8_t jeu=0;

        if (p->tour == 0)
        {
            srand(time(NULL));
            jeu = rand() % COLONNE;
        }
        else
        {
            liste *Li = (liste *)malloc(sizeof(liste));
            Li->tab = initialisation_tableau();
            for (int i = 0; i < LIGNE; i++)
            {

                for (int j = 0; j < COLONNE; j++)
                {
                    Li->tab[i][j] = p->tab[i][j];
                }
            }
            Li->score = MinMax(Li, 0);
            for (int i = 0; i < COLONNE; i++)
            {

                if (Li->score == Li->l[i].score)
                {
                    if (p->tab[LIGNE - 1][i] != Vide)
                    {
                        while (p->tab[LIGNE - 1][i] != Vide && i != -1)
                        {
                            Li->l[i].score = -999999;
                            Li->score = max(Li);
                            i = -1;
                        }
                    }
                    else
                    {
                        jeu = i;
                    }
                }
            }
            free_tableau(Li->tab);
            free_liste(Li);
            free(Li);
            printf("\ncoup joué en %d\n", jeu + 1);
        }

        if (p->fin != -1)
        {
            poser_jeton(p, jeu);
        }
    }
}

int8_t demande_colonne(partie *p)
{
    if (p->tour % 2 == Jaune)
    {
        couleur("33"); // orange
        printf("Jaune: ");
        couleur("37"); // blanc
    }
    if (p->tour % 2 == Rouge)
    {
        couleur("31"); // rouge
        printf("Rouge: ");
        couleur("37"); // blanc
    }
    printf("Entrez le numéro de la colonne (entre 1 à %d) dans laquelle vous voulez placez votre jeton:\n", COLONNE);
    char j;
    scanf(" %c", &j);
    int8_t jeu = j - '0';

    if (jeu == 9)
    {
        p->fin = -1;
    }
    else
    {
        int8_t num_entre_valide = 0;
        while (num_entre_valide == 0)
        {
            if (jeu < 1 || jeu > COLONNE)
            {
                printf("Le nombre ne correspond pas. \nEntrez le numéro de la colonne (entre 1 à %d) dans laquelle vous voulez placez votre jeton\n", COLONNE);
                scanf(" %c", &j);
                jeu = j - '0';
            }
            else if (p->tab[LIGNE - 1][jeu - 1] != Vide)
            {
                printf("La colonne est pleine. \nRéessayez-en une autre.");
                scanf(" %c", &j);
                jeu = j - '0';
            }
            else
            {
                num_entre_valide = 1;
            }
        }
        jeu--; // ici on fait jeu-- car pour l'utilisateur les colonnes vont de 1 à n mais pour nous elles vont de 0 à n-1
    }
    return jeu;
}

void poser_jeton(partie *p, int8_t jeu)
{
    int i = 0;
    while (i <= LIGNE && p->tab[i][jeu] != Vide)
    { // recherche de la hauteur ou le jeton doit être posé dans la colonne demandée
        i++;
    }
    if (p->tour % 2 == Jaune)
    {
        p->tab[i][jeu] = Jaune;
    }
    if (p->tour % 2 == Rouge)
    {
        p->tab[i][jeu] = Rouge;
    }

    afficher(p->tab);
    p->fin = verif(p->tab, jeu, i);
    p->tour++;
}

void finalite(partie *p)
{
    if (p->fin == 2)
    {
        printf("Il y'a Egalité, bien joué à vous 2");
    }
    else if (p->fin == -1)
    {
        printf("fin demandée\n");
    }
    else
    {
        if (p->tour % 2 == Rouge)
        {
            couleur("33");              // orange
            printf("Jaune a gagné!\n"); // car le tour est augmenté dans tous les cas
            couleur("37");              // blanc
        }
        if (p->tour % 2 == Jaune)
        {
            couleur("31");              // rouge
            printf("Rouge a gagné!\n"); // de même
            couleur("37");              // blanc
        }
    }
}

void partie_pve(partie *p)
{
    deroulementIA(p);
    finalite(p);
}

void partie_eve(partie *p)
{
    deroulement2IA(p);
    finalite(p);
}

int32_t score_case(int8_t **tab, int8_t c, int8_t l)
{
    int32_t score = score_colonne(tab, c, l) + score_diag1(tab, c, l) + score_diag2(tab, c, l) + score_ligne(tab, c, l);
    return score;
}

int32_t score_diag1(int8_t **tab, int8_t c, int8_t l)
{
    int8_t j = 0, r = 0, vide = 0, compteur = 0;
    while (l < LIGNE && c >= 0 && compteur < 4)
    {
        if (tab[l][c] == Rouge)
            r++;
        if (tab[l][c] == Jaune)
            j++;
        if (tab[l][c] == Vide)
            vide++;

        compteur++;
        l++;
        c--;
    }
    return resultat(j, r, vide);
}

int32_t score_diag2(int8_t **tab, int8_t c, int8_t l)
{
    int8_t j = 0, r = 0, vide = 0, compteur = 0;
    while (l < LIGNE && c < COLONNE && compteur < 4)
    {
        if (tab[l][c] == Rouge)
            r++;
        if (tab[l][c] == Jaune)
            j++;
        if (tab[l][c] == Vide)
            vide++;

        compteur++;
        l++;
        c++;
    }
    return resultat(j, r, vide);
}

int32_t score_colonne(int8_t **tab, int8_t c, int8_t l)
{
    int8_t j = 0, r = 0, vide = 0, compteur = 0;
    while (l < LIGNE && compteur < 4)
    {
        if (tab[l][c] == Rouge)
            r++;
        if (tab[l][c] == Jaune)
            j++;
        if (tab[l][c] == Vide)
            vide++;

        compteur++;
        l++;
    }
    return resultat(j, r, vide);
}

int32_t score_ligne(int8_t **tab, int8_t c, int8_t l)
{
    int8_t j = 0, r = 0, vide = 0, compteur = 0;
    while (c < COLONNE && compteur < 4)
    {
        if (tab[l][c] == Rouge)
            r++;
        if (tab[l][c] == Jaune)
            j++;
        if (tab[l][c] == Vide)
            vide++;

        compteur++;
        c++;
    }
    return resultat(j, r, vide);
}

int32_t resultat(int8_t j, int8_t r, int8_t vide)
{
    if (r == 4)
        return 100;
    else if (j == 4)
        return -95;
    else if (r == 3 && vide == 1)
        return 5;
    else if (j == 3 && vide == 1)
        return -4;
    else if (r == 2 && vide == 2)
        return 2;
    else if (j == 2 && vide == 2)
        return -1;
    else
        return 0;
}

int8_t verif(int8_t **tab, int8_t c, int8_t l)
{
    int8_t victoire = 0;
    
    // vertical
    int8_t v = 0;
    int8_t lb = l;
    int8_t cb = 0;
    int8_t couleur = tab[l][c];
    while (lb >= 0 && tab[lb][c] == couleur)
    {
        v++;
        lb--;
    }
    if (v >= 4)
    {
        return victoire = 1;
    }
    lb = l;

    // horizontal
    int8_t h = 0;
    while (cb < COLONNE)
    {
        if (tab[l][cb] == couleur)
            h++;
        else
            h = 0;
        if (h == 4)
            return victoire = 1;
        cb++;
    }
    cb = c;

    // diag 1
    while (cb != 0 && lb != 0)
    {
        cb--;
        lb--;
    }
    int8_t d = 0;
    while (cb < COLONNE && lb < LIGNE)
    {
        if (tab[lb][cb] == couleur)
            d++;
        else
            d = 0;
        if (d == 4)
            return victoire = 1;
        cb++;
        lb++;
    }
    cb = c;
    lb = l;

    // diag 2

    while (cb != 0 && lb != LIGNE - 1)
    {
        cb--;
        lb++;
    }
    d = 0;
    while (cb < COLONNE && lb >= 0)
    {
        if (tab[lb][cb] == couleur)
            d++;
        else
            d = 0;
        if (d == 4)
            return victoire = 1;
        cb++;
        lb--;
    }

    // égalité
    lb = LIGNE - 1;
    cb = 0;
    while (cb < COLONNE && tab[lb][cb] != -1)
    {
        cb++;
    }
    if (cb == COLONNE)
        return victoire = 2;
    return victoire = 0;
}

void afficher(int8_t **tab)
{   
    srand(time(NULL));
    int32_t sus = rand()%10;
    printf("\n");
    printf(" 1 2 3 4 5 6 7 \n");
    couleur("4");
    for (int i = LIGNE - 1; i >= 0; i--)
    {
        for (int j = 0; j < COLONNE; j++)
        {
            printf("|");
            if (tab[i][j] == Vide)
            {
                printf("_");
            }
            else if (tab[i][j] == Jaune)
            {
                couleur("33"); // orange
                if(sus==0)
                    printf("ඞ");
                else
                    printf("O");
                couleur("37"); // blanc
            }
            else
            {
                couleur("31"); // rouge
                 if(sus==0)
                    printf("ඞ");
                else
                    printf("O");
                couleur("37"); // blanc
            }
        }
        printf("|\n");
    }
    couleur("0");
    printf(" 1 2 3 4 5 6 7 \n\n");
    if (sus==0)
    	printf("INVASION D'AMONG US!!\n");
}

void free_liste(liste *Li)
{
    for (int i = 0; i < COLONNE; i++)
    {
        free_tableau(Li->l[i].tab);
    }
    free(Li->l);
}

void free_tableau(int8_t **tab)
{
    for (int i = 0; i < LIGNE; i++)
    {
        free(tab[i]);
    }
    free(tab);
}

void free_partie(partie *p)
{
    free_tableau(p->tab);
    free(p);
}

int32_t MinMax(liste *Li, uint8_t n)
{
    // double boucle pour verifier qu'un des joueurs a gagner et uil ne faut donc pas créer de fils
    int8_t verif_win = 0;
    for (int i = 0; i < LIGNE; i++)
    {
        for (int j = 0; j < COLONNE; j++)
        {
            if (Li->tab[i][j] != Vide)
            {
                if (verif_win != 1 && verif(Li->tab, j, i) != 0)
                    verif_win = 1;
            }
        }
    }
    if (n == 6 || verif_win == 1)
    {

        return -1 * score(Li);
    }
    else 
    {

        Li->l = (liste *)malloc(COLONNE * sizeof(liste));
        for (int i = 0; i < COLONNE; i++)
        {
            Li->l[i].tab = initialisation_tableau();
        }
        int8_t **tableau = initialisation_tableau();
        for (int i = 0; i < LIGNE; i++)
        {
            for (int j = 0; j < COLONNE; j++)
            {
                tableau[i][j] = Li->tab[i][j];
            }
        }
        for (int k = 0; k < COLONNE; k++)
        {
            for (int i = 0; i < LIGNE; i++)
            {
                for (int j = 0; j < COLONNE; j++)
                {
                    Li->l[k].tab[i][j] = tableau[i][j];
                }
            }
        }
        if (n == 0)

            for (int i = 0; i < COLONNE; i++)
            {

                int j = 0;
                while (j < LIGNE && Li->l[i].tab[j][i] != Vide)
                { // recherche de la hauteur ou le jeton doit être posé dans la colonne demandée
                    j++;
                }
                if (Li->l[i].tab[LIGNE - 1][i] != Vide)
                {
                    if (i < COLONNE - 1)
                        i++;
                }
                else
                {
                    if (n % 2 == Jaune)
                    {
                        Li->l[i].tab[j][i] = Jaune;
                    }
                    if (n % 2 == Rouge)
                    {
                        Li->l[i].tab[j][i] = Rouge;
                    }
                }
            }

        for (int i = 0; i < COLONNE; i++)
        {
            Li->l[i].score = MinMax(&Li->l[i], n + 1);
        }
        if (n % 2 == 0)
        {
            int32_t scoreF = max(Li);
            if (n != 0)
            {
                free_liste(Li);
            }
            free_tableau(tableau);
            return scoreF;
        }
        else
        {
            int32_t scoreF = min(Li);

            free_liste(Li);
            free_tableau(tableau);
            return scoreF;
        }
    }
}

int32_t max(liste *Li)
{
    int32_t m = -999999;
    for (int i = 0; i < COLONNE; i++)
    {
        if (Li->l[i].score > m)
            m = Li->l[i].score;
    }
    return m;
}

int32_t min(liste *Li)
{
    int32_t m = 999999;
    for (int i = 0; i < COLONNE; i++)
    {
        if (Li->l[i].score < m)
            m = Li->l[i].score;
    }
    return m;
}

int32_t score(liste *Li)
{
    int32_t s = 0;
    // vertical
    for (int i = 0; i < LIGNE; i++)
    {
        for (int j = 0; j < COLONNE; j++)
        {
            s = s + score_case(Li->tab, j, i);
        }
    }
    return s;
}
