#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>

int z=1;
int* pz=&z; // Pointeur vers z pour pouvoir le modifier dans le gestionnaire de signal

// Gestionnaire de signal pour SIGINT (Ctrl+C) et SIGTSTP (Ctrl+Z)
void signal_handler(int signum) {
    if (signum == SIGINT || signum == SIGTSTP)
        *pz=0; // Mettre z à 0 pour arrêter la boucle
}

char* connexion(char tab[]);
char* discussion(char tab[]);



int main() {
    char aux[100];
    char auxp[100];
    char*idp=connexion(aux);	// Appel de la fonction de connexion pour obtenir l'ID de l'utilisateur
    while(idp==NULL){
    	idp=connexion(aux);		// Tant que l'ID est NULL, demander à nouveau à l'utilisateur
    }
	int ilen= strlen(idp);
	DIR *dir;
	dir = opendir("partage");
	if (!dir) {
		if (mkdir("partage", 0777) == -1) {// Code pour la création du dossier 'partage' s'il n'existe pas
        	perror("Erreur lors de la création du dossier");
        	return EXIT_FAILURE;
    	}
    }
    char*idd=discussion(auxp);// Appel de la fonction de discussion pour choisir un interlocuteur
    while(idd==NULL){
    	idd=discussion(auxp);
    }
    int jlen= strlen(idd);
    
    // Création des chemins des fichiers de conversation
    char nvChemin[100];
    char nvCheminS[100];
    snprintf(nvChemin, sizeof(nvChemin), "%s/%s.txt", idp,idd);
    snprintf(nvCheminS, sizeof(nvCheminS), "%s/%s.txt", idd, idp);
    
    if(strcmp(idd,"partage")==0){// Si l'interlocuteur est 'partage', modifier les chemins
    	snprintf(nvChemin, sizeof(nvChemin), "%s/partage.txt", idp);
    	snprintf(nvCheminS, sizeof(nvCheminS), "partage/partage.txt");
    }
    
    // Création des fichiers de conversation
    FILE *fichier = fopen(nvChemin, "a");
    FILE *gichier = fopen(nvCheminS, "a");
    fclose(fichier);
    fclose(gichier);
    
    // Cryptage de l'ID de l'utilisateur utile pour plus tard
    char idpB[20];
       strcpy(idpB,idp);
       for(int i=0;i<strlen(idpB);i++){
		if (idpB[i] >= 'a' && idpB[i] <= 'z') {
       	    idpB[i] = 'a' + (idpB[i] - 'a' + 7) % 26;
       	}
       	if (idpB[i] >= 'A' && idpB[i] <= 'Z') {
       	    idpB[i] = 'A' + (idpB[i] - 'A' + 7) % 26;
       	}
    }
    
    
    // Configuration du gestionnaire de signal
    struct sigaction act;
    act.sa_handler = signal_handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGINT, &act, NULL);
    sigaction(SIGTSTP, &act, NULL);
    
    
    // Création du processus fils pour la communication en temps réel
	pid_t pid = fork();
    if (pid < 0) {
        // Erreur lors de la création du processus fils
        perror("Erreur lors de la création du processus fils");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
    	sleep(2);
        // Code exécuté par le processus fils	Boucle pour saisir et envoyer les messages
        while (1) {
            char donnee[100];
            scanf("\n");
            fgets(donnee, sizeof(donnee), stdin);
            
             // Si l'utilisateur entre "-1" ou si le signal SIGINT ou SIGTSTP est reçu, quitter la boucle
            if (strcmp(donnee, "-1\n") == 0 || !z) {
                FILE *aux = fopen("aux.txt", "w");
                fprintf(aux, "%s a quitté la conv.\n", idp);
                fclose(aux);
                exit(EXIT_SUCCESS);
                break; 
            } 
            
            else {//cryptage du message
            for(int i=0;i<strlen(donnee);i++){
				if (donnee[i] >= 'a' && donnee[i] <= 'z') {
       	     	donnee[i] = 'a' + (donnee[i] - 'a' + 7) % 26;
       			}
       			if (donnee[i] >= 'A' && donnee[i] <= 'Z') {
       	     	donnee[i] = 'A' + (donnee[i] - 'A' + 7) % 26;
       			}
       		}
       		
                // Ouvrir les historiques en mode ajout
                FILE *fichier = fopen(nvChemin, "a");
                FILE *gichier = fopen(nvCheminS, "a");
                //Et le transmetteur en mode écriture
                FILE *aux = fopen("aux.txt", "w");
                if (fichier == NULL||gichier==NULL) {
                    perror("Erreur lors de l'ouverture du fichier");
                    exit(EXIT_FAILURE);
                }
               
                // Écrire dans les fichiers de conversation
                fprintf(fichier, "%s kpa: %s", idpB, donnee);
                fprintf(gichier, "%s kpa: %s", idpB, donnee);
                fprintf(aux, "%s kpa: %s", idpB, donnee);
                // Fermer les fichiers
                fclose(fichier);
                fclose(gichier);
                fclose(aux);
				
                sleep(2);
            }
        }
    } else {
        // Code exécuté par le processus parent 	Boucle pour afficher les messages reçus
        char buffer[100];
        struct stat st;
        int last_modification_time = 0;
        system("clear");
        FILE *affiche;
        if(strcmp(idd,"partage")==0)
			affiche = fopen(nvCheminS, "r");
		else
			affiche = fopen(nvChemin, "r");
		while (fgets(buffer, sizeof(buffer), affiche) != NULL) {
		// decryptage de l'historique pour l'afficher
				for(int i=0;i<strlen(buffer);i++){
					if (buffer[i] >= 'a' && buffer[i] <= 'z') {
		            	buffer[i] = 'a' + (buffer[i] - 'a' - 7 + 26) % 26;
		       		}
		       		if (buffer[i] >= 'A' && buffer[i] <= 'Z') {
		            	buffer[i] = 'A' + (buffer[i] - 'A' - 7+ 26) % 26;
		       		}
		       	}
        	printf("%s", buffer);
            fflush(stdout);
        }
		fclose(affiche);
		FILE *efface = fopen("aux.txt", "w");
		fclose(efface);

        while (waitpid(pid, NULL, WNOHANG) == 0) {
            // Vérifier la dernière modification du fichier
            if(strcmp(idd,"partage")==0)
            	stat(nvCheminS, &st);
            else
            	stat(nvChemin, &st);
            int current_modification_time = st.st_mtime;
			
            if (current_modification_time > last_modification_time) {
                // Le fichier a été modifié, lire et afficher les nouvelles données;
                FILE *fichier = fopen("aux.txt", "r");
                if (fichier == NULL) {
                    perror("Erreur lors de l'ouverture du fichier");
                    exit(EXIT_FAILURE);
                }
				
              		  // Lire à partir du fichier
              		  printf("\r"); // Revenir au début de la ligne et effacer "idd:"
              		  for(int i=0;i<jlen;i++){
              		  		printf(" ");
              		  }
              		  printf("\r");
              		  while (fgets(buffer, sizeof(buffer), fichier) != NULL && strncmp(buffer, idpB, ilen) != 0) {
              		  for(int i=0;i<strlen(buffer);i++){
					if (buffer[i] >= 'a' && buffer[i] <= 'z') {
		            	buffer[i] = 'a' + (buffer[i] - 'a' - 7 + 26) % 26;
		       		}
		       		if (buffer[i] >= 'A' && buffer[i] <= 'Z') {
		            	buffer[i] = 'A' + (buffer[i] - 'A' - 7+ 26) % 26;
		       		}
		       	}
        	printf("%s", buffer);
            fflush(stdout);
        }
              		  // Fermer le fichier
              		  fclose(fichier);
		
              		  // Mettre à jour le temps de dernière modification
              		  last_modification_time = current_modification_time;
              		  printf("%s:", idp);
              		  fflush(stdout);
            }

            // Pause de quelques secondes avant de vérifier à nouveau
            sleep(2);
        }
    }

    printf("byebye\n");
    return EXIT_SUCCESS;
}





// Fonction pour l'inscription ou la connexion de l'utilisateur
char* connexion(char tab[]){
    printf("Bonjour, tape 0 pour t'inscrire ou autre chose pour te connecter:");
    fflush(NULL);
    char choix;
    scanf("%s",&choix); // Demande à l'utilisateur de choisir entre inscription et connexion

    // Si l'utilisateur choisit l'inscription
    if(choix=='0'){						
        printf("rentre l'ID de ton choix: (en 20 caracteres max)");
        fflush(NULL);
        char id[50];
        scanf("\n");
        fgets(id, sizeof(id), stdin); // Demande à l'utilisateur de saisir un ID

        // Vérifie la longueur de l'ID
        while(strlen(id)>20){
            fgets(id, sizeof(id), stdin); // Demande à nouveau si l'ID est trop long
            printf("en 20 caracteres max:");
        }
        id[strcspn(id, "\n")] = '\0'; // Supprime le caractère de nouvelle ligne

        // Crée un dossier avec l'ID de l'utilisateur
        if (mkdir(id, 0777) == -1) {
            perror("Erreur lors de la création du dossier");
            return NULL; // Retourne NULL en cas d'erreur
        }

        printf("maintenant entre un mot de passe de ton choix d'");
        fflush(NULL);
        char mdp[100];
        int x=0;
        // Demande à l'utilisateur de saisir un mot de passe d'au moins 4 caractères
        while(!x){    
            printf("au moins 4 caractères:");
            fgets(mdp, sizeof(mdp), stdin);
            mdp[strcspn(mdp, "\n")] = '\0'; // Supprime le caractère de nouvelle ligne
            if (strlen(mdp) >= 4) 
                x++;
        }
        
        // Cryptage du mot de passe
        for(int i=0;i<strlen(mdp);i++){
            if (mdp[i] >= 'a' && mdp[i] <= 'z') {
                mdp[i] = 'a' + (mdp[i] - 'a' + 7) % 26;
            }
            if (mdp[i] >= 'A' && mdp[i] <= 'Z') {
                mdp[i] = 'A' + (mdp[i] - 'A' + 7) % 26;
            }
        }
        
        // Chemin du fichier contenant le mot de passe
        char nv_chemin[100];
        snprintf(nv_chemin, sizeof(nv_chemin), "%s/mdp.txt", id);
        FILE* f=fopen(nv_chemin,"w");
        if (f == NULL) {
           perror("Erreur lors de l'ouverture du fichier");
           exit(EXIT_FAILURE);
        }
        fprintf(f,"%s",mdp); // Écrit le mot de passe dans le fichier
        fclose(f);
        printf("compte créé\n");
        strcpy(tab,id); // Copie l'ID dans tab
        return tab; // Retourne l'ID
    }
    
    else{ // Si l'utilisateur choisit la connexion
        printf("Entre ton id:");
        char id[20];
        scanf("\n");
        fgets(id, sizeof(id), stdin); // Demande à l'utilisateur de saisir son ID
        id[strcspn(id, "\n")] = '\0'; // Supprime le caractère de nouvelle ligne

        // Vérifie si le dossier avec cet ID existe
        DIR *dir;
        dir = opendir(id);
        if (dir) {
            closedir(dir);
            // Chemin du fichier contenant le mot de passe
            char nv_chemin[100];
            snprintf(nv_chemin, sizeof(nv_chemin), "%s/mdp.txt", id);
            FILE* f=fopen(nv_chemin,"r");
            printf("Entre ton mdp:");
            int x=0, cpt=3;
            // Demande à l'utilisateur de saisir son mot de passe, avec un maximum de 3 essais
            while(!x){
                char mdp[100],t[100];
                fgets(mdp, sizeof(mdp), f); // Lit le mot de passe depuis le fichier
                
                mdp[strcspn(mdp, "\n")] = '\0'; // Supprime le caractère de nouvelle ligne

                // Décryptage du mot de passe
                for(int i=0;i<strlen(mdp);i++){
                    if (mdp[i] >= 'a' && mdp[i] <= 'z') {
                        mdp[i] = 'a' + (mdp[i] - 'a' - 7 + 26) % 26;
                    }
                    if (mdp[i] >= 'A' && mdp[i] <= 'Z') {
                        mdp[i] = 'A' + (mdp[i] - 'A' - 7+ 26) % 26;
                    }
                }
                fgets(t, sizeof(t), stdin); // Lit le mot de passe saisi par l'utilisateur
                t[strcspn(mdp, "\n")] = '\0'; // Supprime le caractère de nouvelle ligne
                
                // Vérifie si le mot de passe est correct
                if(strcmp(mdp,t)==0){
                    x++;
                    printf("Bienvenue %s \n", id);
                    strcpy(tab,id); // Copie l'ID dans tab
                    return tab; // Retourne l'ID
                }
                else{
                    printf("mdp incorrect. Réessayez:");
                    cpt--;
                    // Si l'utilisateur dépasse le nombre d'essais, retourne NULL pour revenir au début du programme
                    if(cpt==0){
                        printf("Trop d'essais retournez à l'accueil\n");
                        return NULL; 
                    }
                }
            }
        }
        else {
            printf("L'ID \"%s\" n'existe pas.\n", id);
            return NULL; // Retourne NULL si l'ID n'existe pas
        }
    }
    return tab; // Retourne l'ID
}





// Fonction pour choisir un interlocuteur avec qui discuter
char* discussion(char tab[]){
    printf("Avec qui souhaitez vous parler?\n");

    // Ouvre le répertoire courant pour lister les interlocuteurs disponibles
    DIR *directory;
    struct dirent *entry;
    directory = opendir("."); 

    // Vérifie si l'ouverture du répertoire a réussi
    if (directory == NULL) {
        perror("Erreur lors de l'ouverture du répertoire");
        return NULL;
    }

    // Affiche les noms des dossiers (interlocuteurs) disponibles dans le répertoire courant
    while ((entry = readdir(directory)) != NULL) {
        struct stat fileStat;
        // Vérifie le type du fichier
        if (stat(entry->d_name, &fileStat) < 0) {
            continue;
        }
        // Si c'est un dossier, affiche son nom
        if (S_ISDIR(fileStat.st_mode)) {
            printf("%s\n", entry->d_name); 
        }
    }
    closedir(directory); // Ferme le répertoire

    char id[20];
    DIR *dir;

    // Boucle pour demander à l'utilisateur de choisir un interlocuteur
    do{ 
        scanf("\n");
        fgets(id, sizeof(id), stdin); // Saisie de l'interlocuteur
        id[strcspn(id, "\n")] = '\0'; // Supprime le caractère de nouvelle ligne

        dir = opendir(id); // Ouvre le dossier de l'interlocuteur
        if (dir) {
            strcpy(tab,id); // Copie l'interlocuteur choisi dans tab
            return tab; // Retourne l'interlocuteur choisi
        }
        else{
            printf("Cet ID n'existe pas, réessayez:\n");
        }
    } while(!dir); // Continue tant que l'interlocuteur choisi n'existe pas

    return tab; // Retourne l'interlocuteur choisi
}

		




















