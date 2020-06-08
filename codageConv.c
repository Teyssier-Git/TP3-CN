#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct couple {
    int out1;
    int out2;
};

int ut_1 = 0;
int ut_2 = 0;

struct couple code (int in) {
    int out1 = (in + ut_1 + ut_2)%2;
    int out2 = (in + ut_2)%2;
    ut_2 = ut_1;
    ut_1 = in;
    return (struct couple){out1,out2};
}

int main (int argc, char * argv[]) {

    if (argc != 2) {
        printf("./codageConv <sequence in bit to code>\n");
        return 1;
    }

    char *sequence = argv[1];
    int size = strlen(sequence);

    int finalCode[2*size];

    for (int i=0; i<size; i++) {
        int in = (int)sequence[i]-'0';
        if (in < 0 || in > 1) {
            printf("Error : %d at pos %d, only 0,1 allowed\n",in,i);
            return 1;
        }

        struct couple res = code(in);
        finalCode[2*i] = res.out1;
        finalCode[2*i+1] = res.out2;
    }

    printf("Result :");
    for (int i=0; i<size; i++) {
        printf(" %d", finalCode[2*i]);
        printf("%d", finalCode[2*i+1]);
    }
    printf("\n");
}
