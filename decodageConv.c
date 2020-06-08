#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define BUFFER_SIZE 8

struct way {
    int message[BUFFER_SIZE];
    int size; // size -1 : any way which come to the state
    int weight;
};

struct ways {
    struct way way[4];
};

struct ways chemins;

struct couple {
    int out1;
    int out2;

    int state;

    int sortie;
};

struct couple trans[4][2];

void init() {
    for (int i =0; i<4; i++) {
        chemins.way[i].size = 0;
        chemins.way[i].weight = 4*BUFFER_SIZE;
    }
    chemins.way[0].weight = 0;
}

void copy(struct way *dest, struct way *src) {
    for (int i=0; i<src->size; i++) {
        dest->message[i] = src->message[i];
    }
}

void treatment (int b1, int b2) {
    struct ways temp = chemins;
    for (int i=0; i<4; i++) {
        struct way w1, w2;


        struct couple c = trans[i][0];
        copy(&w1,&temp.way[c.state]);
        int weight = 0;
        if (b1 != c.out1) {
            weight++;
        }
        if (b2 != c.out2) {
            weight++;
        }
        w1.weight = weight + temp.way[c.state].weight;
        w1.message[temp.way[c.state].size] = c.sortie;
        w1.size = temp.way[c.state].size + 1;


        c = trans[i][1];
        copy(&w2,&temp.way[c.state]);
        weight = 0;
        if (b1 != c.out1) {
            weight++;
        }
        if (b2 != c.out2) {
            weight++;
        }
        w2.weight = weight + temp.way[c.state].weight;
        w2.message[temp.way[c.state].size] = c.sortie;
        w2.size = temp.way[c.state].size + 1;


        if (w1.weight > w2.weight) {
            chemins.way[i] = w2;
        } else {
            chemins.way[i] = w1;
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

    trans[0][0] = (struct couple){0,0,0,0};
    trans[0][1] = (struct couple){1,1,1,0};
    trans[1][0] = (struct couple){1,0,2,0};
    trans[1][1] = (struct couple){0,1,3,0};
    trans[2][0] = (struct couple){1,1,0,1};
    trans[2][1] = (struct couple){0,0,1,1};
    trans[3][0] = (struct couple){0,1,2,1};
    trans[3][1] = (struct couple){1,0,3,1};


    int finalDecode[size/2];
    for (int i=0; i<size/2; i++) {
        finalDecode[i] = 0;
    }

    int i = 0;
    for (; i<size; i+=2) {
        if (i%(BUFFER_SIZE*2) == 0) {
            if (i != 0) {
                struct way temp = chemins.way[0];
                for (int j=1; j<4; j++) {
                    if (chemins.way[j].weight < temp.weight) {
                        temp = chemins.way[j];
                    }
                }

                if (temp.weight >= 3) {
                    printf("Error : more than 3 error detect at the position %d to %d\n",i/2-BUFFER_SIZE, i/2);
                    return 1;
                }

                for (int j=0; j<BUFFER_SIZE; j++) {
                    finalDecode[i/2-BUFFER_SIZE+j] = temp.message[j];
                }
            }
            init();
        }

        treatment((int)(sequence[i]-'0'), (int)(sequence[i+1]-'0'));
    }

    struct way temp = chemins.way[0];
    for (int j=1; j<4; j++) {
        if (chemins.way[j].weight < temp.weight) {
            temp = chemins.way[j];
        }
    }

    if (temp.weight >= 3) {
        printf("Error : more than 3 error detect at the position %d the end\n",i/2-BUFFER_SIZE);
        return 1;
    }

    for (int j=0; j<temp.size; j++) {
        finalDecode[i/2-BUFFER_SIZE+j] = temp.message[j];
    }



    printf("Message : ");
    for (int i = 0; i<size/2; i++) {
        printf("%d",finalDecode[i]);
    }
    printf("\n");
}
