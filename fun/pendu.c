#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void clear_terminal() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int main() {
    char a[50];
    printf("Entrez un mot ici: ");
    scanf("%s", a);

    int erreurs = 0;
    int taille = strlen(a);
    int i = 0;
    int estTrouve = 0;

    clear_terminal();

    char rep[50];
    for (int j = 0; j < taille; j++) {
        rep[j] = '_';
    }
    rep[taille] = '\0'; // Ajoutez une terminaison de chaîne

    while (erreurs < 3 && !estTrouve) {
        char b;
        printf("\nMot actuel: %s\n", rep);
        printf("Entrez une lettre: ");
        scanf(" %c", &b);

        int essai = 0;
        for (int j = 0; j < taille; j++) {
            if (a[j] == b) {
                rep[j] = b;
                essai++;
            }
        }
        if (essai == 0) {
            erreurs++;
        }

        // Vérifier si le mot est complètement trouvé
        int verif = 0;
        for (int j = 0; j < taille; j++) {
            if (rep[j] == '_') {
                verif++;
            }
        }
        if (verif == 0) {
            estTrouve = 1;
        }
    }

    if (estTrouve) {
        printf("\nFélicitations ! Vous avez trouvé le mot : %s\n", rep);
    } else {
        printf("\nVous avez perdu. Le mot était : %s\n", a);
    }

    printf("Fin de la partie.\n");

    return 0;
}

