#include <stdio.h> // pour les printf
#include <stdbool.h> // pour les boolean
#include <string.h> // permet la manipulation des chaines de caractères (strlen par exemple)
#include <ctype.h> // Fonctions de traitements de caractères (utilisé ici pour vérifier la catégorie d'un caractère (utilisé ici pour isalpha))

// Généré par l'IA 
#include <stdlib.h> // Utilisé pour générer aléatoirement un mot (rand()) 
#include <time.h> // Manipuler des timers, date, temps, intervals
#define MAX_WORDS 835
#define MAX_LENGTH 50
// Fin de génération d'IA

void drawHangman(int step) {
    switch (step) {
        case 1:
            printf("          \n");
            printf("|         \n");
            printf("|         \n");
            printf("|         \n");
            printf("|         \n");
            printf("|         \n");
            printf("|         \n");
            printf("+---------+\n");
            break;
        case 2:
            printf("+---------+\n");
            printf("|         |\n");
            printf("|         \n");
            printf("|         \n");
            printf("|         \n");
            printf("|         \n");
            printf("|         \n");
            printf("+---------+\n");
            break;
        case 3:
            printf("+---------+\n");
            printf("|         |\n");
            printf("|         O\n");
            printf("|         \n");
            printf("|         \n");
            printf("|         \n");
            printf("|         \n");
            printf("+---------+\n");
            break;
        case 4:
            printf("+---------+\n");
            printf("|         |\n");
            printf("|         O\n");
            printf("|        /|\n");
            printf("|         \n");
            printf("|         \n");
            printf("|         \n");
            printf("+---------+\n");
            break;
        case 5:
            printf("+---------+\n");
            printf("|         |\n");
            printf("|         O\n");
            printf("|        /|\\\n");
            printf("|         \n");
            printf("|         \n");
            printf("|         \n");
            printf("+---------+\n");
            break;
        case 6:
            printf("+---------+\n");
            printf("|         |\n");
            printf("|         O\n");
            printf("|        /|\\\n");
            printf("|        /\n");
            printf("|         \n");
            printf("|         \n");
            printf("+---------+\n");
            break;
        case 7:
            printf("+---------+\n");
            printf("|         |\n");
            printf("|         O\n");
            printf("|        /|\\\n");
            printf("|        / \\\n");
            printf("|         \n");
            printf("|         \n");
            printf("+---------+\n");
            break;
        case 8:
            printf("+---------+\n");
            printf("|         |\n");
            printf("|         O\n");
            printf("|        /|\\\n");
            printf("|        / \\\n");
            printf("|     Game Over\n");
            printf("|         \n");
            printf("+---------+\n");
            break;
        default:
            break;
    }
}

bool verifyChar(char c) {
    if (!isalpha(c)) {
        return false;
    }

    return true;
}

bool letterTried(char letter, char letterUsed[], int size) {
    for (int i = 0; i < size; i++) {
        if (letterUsed[i] == letter) {
            return true;
        }
    }

    return false;
}

int main() {

    while (true) {
        // ======= Généré par l'IA =======

        char words[MAX_WORDS][MAX_LENGTH]; // Tableau pour stocker tous les mots du fichier
        int nbWords = 0; // Compter le nombre de mots lus
        char wordToFind[MAX_LENGTH];

        FILE *file = fopen("C:\\Users\\duval\\Documents\\GitHub\\Jeu-du-Pendu\\words.txt", "r"); // Ouverture du fichier en mode lecture
        if (file == NULL) {
            printf("Erreur lors de l'ouverture du fichier.\n");
            return 1;
        }

        // Lecture du fichier et stockage des mots dans le tableau
        while (fgets(words[nbWords], MAX_WORDS, file)) { // fgets utilisé pour lire chaque ligne du fichier
            words[nbWords][strcspn(words[nbWords], "\n")] = '\0'; // la fonction strcspn supprime le caractère de saut de ligne \n si présent
            nbWords++;
        }

        fclose(file); // Fermeture du fichier

        srand(time(NULL)); // Initialise le générateur de mots aléatoires avec l'horloge système pour garantir des résultats différents à chaque exécution (autrement dit : fait en sorte qu'il n'y ait pas 2 fois le même mot)

        int randomIndex = rand() % nbWords; // rand() génère un nombre aléatoire
        strcpy(wordToFind, words[randomIndex]); // on récupère le mot associé au nombre et ce sera notre mot wordToFind

        // ======= Fin de génération d'IA =======

        char playerName[50];
        int wordLength = strlen(wordToFind);
        char hiddenWord[wordLength + 1]; // + 1 pour le caractère nul

        char letterUsed[26]; // Tableau pour stocker les letters déjà données
        int nbletterUsed = 0;

        printf("Bienvenue au jeu du pendu ! \n");
        printf("===========================\n");
        printf("Veuillez entrer votre pseudonyme :\n");
        scanf("%s", &playerName); // On récupère le nom du joueur
        printf("Nom enregistré : %s \n", playerName);

        printf("Voici le mot à deviner, vous avez 8 tentatives pour le trouver.\n");
        printf("Bonne chance !\n\n");

        for (int i = 0; i < wordLength; i++) {
            hiddenWord[i] = '_'; // On remplace les letters du mot par des ____
        }
        hiddenWord[strlen(wordToFind)] = '\0'; // Rajout du caractère nul à la fin

        printf("Mot : %s\n", hiddenWord);

        int nbErrors = 0;
        while(nbErrors < 8 && strcmp(hiddenWord, wordToFind) != 0) {
            char charChoosen[10];
            char letter;
    
            printf("Choisis un caractère de A à Z:\n");
            fgets(charChoosen, sizeof(charChoosen), stdin);

            if (strlen(charChoosen) == 2 && verifyChar(charChoosen[0])) { // strlen(charChoosen) == 2 car 1 caractère acceptée + le caractère nul
                letter = tolower(charChoosen[0]);
            } else {
                printf("Erreur : vous devez entrer une seule lettre.\n");
                printf("Mot : %s\n\n", hiddenWord);
                continue;
            }

            if (letterTried(letter, letterUsed, nbletterUsed)) {
                printf("Erreur : vous avez déjà essayé la lettre '%c'.\n", letter);
                printf("Mot : %s\n\n", hiddenWord);
                continue;
            } else {
                letterUsed[nbletterUsed++] = letter;
            }

            bool letterFind = false;

            for (int i = 0; i < strlen(wordToFind); i++) {
                if (tolower(wordToFind[i]) == letter) {
                hiddenWord[i] = wordToFind[i];
                    letterFind = true;
                }
            }

            if (letterFind) {

                if (strcmp(hiddenWord, wordToFind) == 0) { // strcmp compare si hiddenWord et wordToFind sont égaux ou non
                    printf("Bravo, vous avez trouver le mot qui était %s ! \n\n\n", hiddenWord);
                    continue;
                } else {
                printf("Bravo, %c est une bonne lettre\n", letter);
                printf("Mot : %s\n\n", hiddenWord);
                }
            } else {
                printf("Dommage, %c n'est pas une bonne lettre\n", letter);
                nbErrors++;
                drawHangman(nbErrors);
                printf("Mot : %s\n\n", hiddenWord);

                if ((8 - nbErrors) > 0) {
                    printf("Nombre de vies restantes : %d\n\n", 8 - nbErrors);
                } else {
                    printf("Vous avez perdu car vous n'avez plus de vie\n");
                    printf("Le mot était : %s \n\n\n", wordToFind);
                }
            }
        }
    }

    return 0;
}