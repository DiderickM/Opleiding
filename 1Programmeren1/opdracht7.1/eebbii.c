#include <stdio.h>

//#define DEBUG_write
//#define DEBUG_avg
//#define DEBUG_ascii

/**
 * Function takes a 2D array and writes the values to a file
 */
void writeToFile(int arr[300][300]) {
    FILE *OUTPUTFILE_;
    OUTPUTFILE_ = fopen("Output.txt", "w+");

    for(int ROW = 0; ROW < 300; ROW++) {
        for(int COL = 0; COL < 300; COL++) {
            fprintf(OUTPUTFILE_, "%d \n", arr[ROW][COL]);

#ifdef DEBUG_write
    printf("%d ", arr[ROW][COL]);
#endif

        }
    }

    fclose(OUTPUTFILE_);
}


/**
 * Function calculates and returns the average "pixel value" of a 2D array
 */
float calcAvgPixel(int arr[300][300]) {
    float avgResult = 0;

    for(int ROW = 0; ROW < 300; ROW++) {
        for(int COL = 0; COL < 300; COL++) {
            avgResult += arr[ROW][COL];
        }
    }

#ifdef DEBUG_avg
    printf("%d ", avgResult);
#endif

    avgResult /= 90000.0;
    return avgResult;
}


/**
 * Function takes a 2D array and prints values as pixel values to console using ASCII
 */
void writeConsoleASCII(int arr[300][300]) {
    char seq[20] = {' ', '.', ',', ':', '"', ';', '-', '<', '>','=', '+', '*', 'v', 'x', 'X', 'N', '#', 'M', '%', '@'};

    int pixelValue;

    for(int ROW = 0; ROW < 300; ROW+=10) {
        for(int COL = 0; COL < 300; COL+=5) { 
            pixelValue = arr[ROW][COL] / 13;

#ifdef DEBUG_ascii
    printf("%d ", pixelValue);
#endif

            printf("%c", seq[pixelValue]);
        }
        printf("\n");
    }
}


int main() {
    FILE *lena;

    int readArr[512][512];
    int subArr[300][300];

    lena = fopen("LENA.txt", "r");

    int readValue;
    
    for(int ROW = 0; ROW < 512; ROW++) {
        for(int COL = 0; COL < 512; COL++) {
            fscanf(lena, "%d%d%d", &readValue, &readValue, &readArr[ROW][COL]);
        }
    }

    for(int ROW = 0; ROW < 300; ROW++) {
        for(int COL = 0; COL < 300; COL++) {
            subArr[ROW][COL] = readArr[ROW + 100][COL + 100];
        }
    }
    writeToFile(subArr);

    printf("\nAverage pixel value: %.2f \n\n", calcAvgPixel(subArr));

    writeConsoleASCII(subArr);

    fclose(lena);
}