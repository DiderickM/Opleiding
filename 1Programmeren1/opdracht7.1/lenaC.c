  #include <stdio.h>
#include <stdlib.h>
#include <string.h>

int grayness[512][512];

void loadFile(char* fileName) {
    FILE * fp;
    fp = fopen(fileName, "r");
    for (int i=0; i < 511; i++) {
        for (int j=0; j < 511; j++) {
            int a, b = 0;
            fscanf(fp, "%i", &a);
            fscanf(fp, "%i", &b);
            
            fscanf(fp, "%i", &grayness[a][b]);
            //printf("%i %i %i\n", a, b, grayness[a][b]);
        }
    }
}

void outputASCII(int newArray[][512]) {
    for (int i=100; i < 400; i= i + 10) {
        for (int j=100; j < 400; j= j + 5) {
            /*
                @%#*+=-:.
            */
           if (newArray[i][j] <= 27) {
               printf("@");
           } else if (newArray[i][j] <= 54) {
               printf("%%");
           } else if (newArray[i][j] <= 81) { 
               printf("#");
           } else if (newArray[i][j] <= 108) {
               printf("*");
           } else if (newArray[i][j] <= 135) {
               printf("+");
           } else if (newArray[i][j] <= 162) {
               printf("=");
           } else if (newArray[i][j] <= 189) {
               printf("-");
           } else if (newArray[i][j] <= 216) {
               printf(":");
           } else {
               printf(" .");
           }
        }
        printf("\n");
    }
}

void storeFile(int newArray[][512], char* fileName) {
    FILE *fp2;
    fp2 = fopen(fileName, "w+");
    for (int i=100; i <= 400; i++) {
        for (int j=100; j <= 400; j++) {
            fprintf(fp2, "%i %i %i\n", i, j, newArray[i][j]);
        }
    }
    fclose(fp2);
}

void calculateAverage(int newArray[][512]) {
    int d, e = 0;
    for (int i=100; i < 400; i++) {
        for (int j=100; j <= 400; j++) {
            d += newArray[i][j];
            e++;
        }
    }
    int average = d / e;
    printf("Average: %i\n", average);
}

int main()
{
    loadFile("LENA.txt"); // Opdracht 1
    storeFile(grayness, "newlena.txt"); // Opdracht 2
    calculateAverage(grayness); // Opdracht 3
    outputASCII(grayness); // Opdracht 4
}