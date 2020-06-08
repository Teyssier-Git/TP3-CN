#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MESSAGE_SIZE 8

//ecrire des defines pour les transitions, plus simple

int time = 0

struct way {
    int message[MESSAGE_SIZE];
    int size; // size -1 : any way which come to the state
    int weight;
};

struct ways {
    struct way way[4];
};

struct ways chemins;

void init() {
    for (int i =0; i<4; i++) {
        chemins.way[i].size = -1;
        chemins.way[i].weight = 0;
    }
    chemins.way[0].size = 0;
}

void treatment () {
    struct ways temp = chemin;
    for (int i=0; i<4; i++) {
        if (chemins.way[i].size > -1) {
            // traiter en fonction de comment c'est

            // compare avec le poid chemin final
        }
    }
}


int main (int argc, char * argv[]) {
    if (argc != 2) {
        printf("./decodageConv <sequence in bit to deccode>\n");
        return 1;
    }

    char *sequence = argv[1];
    int size = strlen(sequence);

    if (size%2 != 0) {
        printf("Error : Sequence only pair\n");
    }

    init();

    // Traiter la séquence 8 par 8
    // Reinitialiser a la fin de 8 temps la structure goblale 
}
