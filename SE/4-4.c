#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main() {
    // Ouvrir ou créer le fichier pour la sortie d'erreur
    int fichier_erreur = open("fichier_erreur", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fichier_erreur == -1) {
        perror("Erreur lors de l'ouverture du fichier d'erreur");
        exit(EXIT_FAILURE);
    }

    // Dupliquer le descripteur de fichier pour la sortie d'erreur
    int dup_result = dup2(fichier_erreur, STDERR_FILENO);
    if (dup_result == -1) {
        perror("Erreur lors de la duplication du descripteur de fichier");
        exit(EXIT_FAILURE);
    }

    // Fermer le descripteur de fichier dupliqué
    close(fichier_erreur);

    // Tester la redirection en écrivant dans la sortie d'erreur
    fprintf(stderr, "Ceci est un test de redirection de la sortie d'erreur vers fichier_erreur.\n");

    return 0;
}

