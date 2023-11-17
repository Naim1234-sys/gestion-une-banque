#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Client {
    char *numero_de_compte;
    char *nom;
    char *prenom;
} Client;

#define longueur_tableau(arr) sizeof(arr) / sizeof(Client)

Client *ajouterClient(Client *, int *);
Client *supprimerClient(Client *, int *);
Client *modifierClient(Client *, int);
void afficherClients(Client *, int);

int main() {
    int choix;
    int nombreClients = 5;
    Client *tableauClients = (Client *)malloc(nombreClients * sizeof(Client));

    printf("Entrez les details pour 5 clients : \n");
    for (int i = 0; i < nombreClients; i++) {
        tableauClients[i].numero_de_compte = (char *)malloc(50 * sizeof(char));
        tableauClients[i].nom = (char *)malloc(50 * sizeof(char));
        tableauClients[i].prenom = (char *)malloc(50 * sizeof(char));

        printf("Entrez le numero de compte pour le client %d : ", i + 1);
        scanf("%s", tableauClients[i].numero_de_compte);
        printf("Entrez le nom pour le client %d : ", i + 1);
        scanf("%s", tableauClients[i].nom);
        printf("Entrez le prenom pour le client %d : ", i + 1);
        scanf("%s", tableauClients[i].prenom);
    }

    do {
        printf("\nChoisissez une option :\n 1. Ajouter un nouveau client \n 2. Supprimer un client \n 3. Modifier les informations d'un client\n 4. Quitter\n");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                tableauClients = ajouterClient(tableauClients, &nombreClients);
                break;
            case 2:
                tableauClients = supprimerClient(tableauClients, &nombreClients);
                break;
            case 3:
                tableauClients = modifierClient(tableauClients, nombreClients);
                break;
            case 4:
                break; // Quitter la boucle
            default:
                printf("Choix invalide. Veuillez entrer une option valide.\n");
        }
    } while (choix != 4);

    afficherClients(tableauClients, nombreClients);

    // Liberer la memoire allouee
    for (int i = 0; i < nombreClients; i++) {
        free(tableauClients[i].numero_de_compte);
        free(tableauClients[i].nom);
        free(tableauClients[i].prenom);
    }
    free(tableauClients);

    return 0;
}

Client *ajouterClient(Client *clients, int *nombreClients) {
    (*nombreClients)++;
    clients = (Client *)realloc(clients, (*nombreClients) * sizeof(Client));

    clients[*nombreClients - 1].numero_de_compte = (char *)malloc(50 * sizeof(char));
    clients[*nombreClients - 1].nom = (char *)malloc(50 * sizeof(char));
    clients[*nombreClients - 1].prenom = (char *)malloc(50 * sizeof(char));

    printf("Entrez le numero de compte du nouveau client : ");
    scanf("%s", clients[*nombreClients - 1].numero_de_compte);
    printf("Entrez le nom du nouveau client : ");
    scanf("%s", clients[*nombreClients - 1].nom);
    printf("Entrez le prenom du nouveau client : ");
    scanf("%s", clients[*nombreClients - 1].prenom);

    return clients;
}

Client *supprimerClient(Client *clients, int *nombreClients) {
    char numeroCompte[50];
    printf("Entrez le numero de compte du client que vous souhaitez supprimer : ");
    scanf("%s", numeroCompte);

    int indexASupprimer = -1;
    for (int i = 0; i < *nombreClients; i++) {
        if (strcmp(numeroCompte, clients[i].numero_de_compte) == 0) {
            indexASupprimer = i;
            break;
        }
    }

    if (indexASupprimer != -1) {
        free(clients[indexASupprimer].numero_de_compte);
        free(clients[indexASupprimer].nom);
        free(clients[indexASupprimer].prenom);

        for (int i = indexASupprimer; i < *nombreClients - 1; i++) {
            clients[i] = clients[i + 1];
        }

        (*nombreClients)--;
        clients = (Client *)realloc(clients, (*nombreClients) * sizeof(Client));
    } else {
        printf("Client non trouve.\n");
    }

    return clients;
}

Client *modifierClient(Client *clients, int nombreClients) {
    char numeroCompte[50];
    printf("Entrez le numero de compte du client que vous souhaitez modifier : ");
    scanf("%s", numeroCompte);

    int indexAModifier = -1;
    for (int i = 0; i < nombreClients; i++) {
        if (strcmp(numeroCompte, clients[i].numero_de_compte) == 0) {
            indexAModifier = i;
            break;
        }
    }

    if (indexAModifier != -1) {
        int choix;
        char nouvelleValeur[50];

        printf("Que voulez-vous changer :\n 1. Le numero de compte\n 2. Le nom\n 3. Le prenom\n Entrez le nouveau choix et la nouvelle valeur : ");
        scanf("%d %s", &choix, nouvelleValeur);

        switch (choix) {
            case 1:
                clients[indexAModifier].numero_de_compte = strdup(nouvelleValeur);
                break;
            case 2:
                clients[indexAModifier].nom = strdup(nouvelleValeur);
                break;
            case 3:
                clients[indexAModifier].prenom = strdup(nouvelleValeur);
                break;
            default:
                printf("Choix invalide. Veuillez entrer une option valide.\n");
        }
    } else {
        printf("Client non trouve.\n");
    }

    return clients;
}

void afficherClients(Client *clients, int nombreClients) {
    for (int i = 0; i < nombreClients; i++) {
        printf("%s: %s %s\n", clients[i].numero_de_compte, clients[i].nom, clients[i].prenom);
    }
}
