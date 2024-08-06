#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define FILENAME "testfile"

int main() {
    // Partie 1
    int fd = open(FILENAME, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    // Positionner la tête de lecture/écriture sur le 10 000e octet
    off_t offset = lseek(fd, 9999, SEEK_SET);
    if (offset == -1) {
        perror("Erreur lors du positionnement de l'offset");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Ecrire un caractère à cette position
    char ch = 'X';
    ssize_t bytes_written = write(fd, &ch, sizeof(ch));
    if (bytes_written == -1) {
        perror("Erreur lors de l'écriture dans le fichier");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Fermer le fichier
    close(fd);

    // Partie 2
    // Ouvrir le fichier en lecture
    fd = open(FILENAME, O_RDONLY);
    if (fd == -1) {
        perror("Erreur lors de l'ouverture du fichier en lecture");
        exit(EXIT_FAILURE);
    }

    // Lire l'offset courant
    offset = lseek(fd, 0, SEEK_CUR);
    if (offset == -1) {
        perror("Erreur lors de la récupération de l'offset courant");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("L'offset courant du fichier est : %ld\n", offset);

    // Fermer le fichier
    close(fd);

    return 0;
}

