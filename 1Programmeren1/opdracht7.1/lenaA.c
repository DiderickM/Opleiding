#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    FILE * fp;
    fp = fopen("LENA.txt", "r");
    int grayness[512][512];
    for (int i=0; i < 511; i++) {
        for (int j=0; j < 511; j++) {
            int a, b = 0;
            fscanf(fp, "%i", &a);
            fscanf(fp, "%i", &b);
            fscanf(fp, "%i", &grayness[a][b]);
            printf("%i %i %i\n", a, b, grayness[a][b]);
        }
    }
}