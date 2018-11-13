#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    FILE * fp;
    fp = fopen("lena.txt", "r");
    int grayness[512][512];
    for (int i=0; i < 512; i++) {
        for (int j=0; j < 512; j++) {
            int a, b = 0;
            fscanf(fp, "%i", &a);
            fscanf(fp, "%i", &b);
            fscanf(fp, "%i", &grayness[a][b]);
            printf("%i %i %i\n", a, b, grayness[a][b]);
        }
    }
}