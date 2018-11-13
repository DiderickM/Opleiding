#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(void)
{
    FILE * fp;
    fp = fopen("LENA.txt", "r");
    int grayness[512][512];
    int i,j;
    printf("OK");
    for (i=0; i < 511; i++) {
        for (j=0; j < 511; j++) {
            int a, b = 0;
            fscanf(fp, "%i", &a);
            fscanf(fp, "%i", &b);
            fscanf(fp, "%i", &grayness[a][b]);
        }
    }
    printf("OK");
    fclose(fp);

    FILE *outputfp;
    outputfp = fopen("test.txt", "w");
    for (i = 100; i < 400; i++) {
        for (j = 100; j < 400; j++) {
            fprintf (outputfp, "%d\t%d\t%d\n", i,j,grayness[i][j]);
        }
    }
    fclose(outputfp);
    

}