#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Initializeren van de variabelen (global)
int amountSpots = 64, gameEnded = 0, amountDices, amountPlayers, playerSpots[6], playerEffect[6], playerFound[6] = {0,0,0,0,0,0};
char playerNames[6][10]; // Maak een array waar alle namen in staan vermeld

/* REKENKUNDIGE FUNCTIES HIERONDER */

// Deze functie controleert of iets in een array is aangetroffen
int isvalueinarray(int val, int arr[], int size){
    for (int i=0; i < size; i++) {
        if (arr[i] == val){
            if (playerFound[i] != 1) {  // Als de speler nog niet eerder gevonden is
                playerFound[i] = 1;
                return i;               // Geef de gevonden waarde terug
            }
        }
    }
    return -1;
}

// Deze functie geeft een random waarde terug
int throwDice() {
    int valueDice = rand() % 6 + 1; // Bepaal een willekeurige waarde
    return valueDice; // Geef het totaal aantal ogen terug
}

// Deze functie gooit de dobbelstenen en geeft output
int calculateDice(int amountDices) {
    int total = 0;
    if (amountDices == 2) {                                                                     // Als er twee dobbelstenen worden geworpen
        int temp1 = throwDice(), temp2 = throwDice();                                           // Werp tweemaal
        printf("Je hebt %i en %i gegooid, dat wordt totaal %i.\n", temp1, temp2, temp1+temp2);  // Geef output
        total += temp1 + temp2;                                                                 // Verschuif de speler
    } else {                                                                                    // Als er een dobbelsteen wordt geworpen
        int temp1 = throwDice();                                                                // Sla de waarde op
        printf("Je gooide %i.\n", temp1);                                                       // Geef output
        total += temp1;
    }
    return total;                                                                                //geef waarde terug
}

// Deze functie controleert of een speler recht heeft om zijn geworpen aantal nogmaals te lopen
bool doubleSpot(int x) {
    for (int i = 0; i < 6; i++) { //staat de speler op een plaats van een meervoud van 9
        if (x == (i*9)) {
            return true;
        }
    }
    for (int j = 0; j < 7; j++) { //staat de speler op een plaats van een meervoud van 9 - 4
        if (x == ((j*9)-4)) {
            return true;
        }
    }
    return false;
}

// Deze functie controleert of een speler terecht is gekomen op plaats 31, de put
int checkWell(int x, int y[]) {
    for(int i = 0; i < x; i++) {
        if (y[i] == 31) {
            return i;
        } 
    }
    return -1;
}

// Deze functie controleert of een speler terecht is gekomen op plaats 52, de gevangenis
int checkPrison(int x, int y[]) {
    for(int i = 0; i < x; i++) {
        if (y[i] == 52) {
            return i;
        } 
    }
    return -1;
}

/* REKENKUNDIGE FUNCTIES HIERBOVEN */

/* ASCII OUTPUT HIERONDER */

// Deze functie reset de array playerFound
void resetFound() {
    for (int i = 0; i < 6; i++) {
        playerFound[i] = 0;
    }
}

// Deze functie toont een rij met tekens, zoals deze tussendoor vaak nodig is
void eightTimesLine() {
    for (int i = 0; i < 8; i++) {
        printf("+----------");
    }   
    printf("+\n");
}

// Deze rij toont de nummers van de vakken en plaatst er spelers in
void printNumber1(int x, int y) {
    for (int j = x; j < y; j++)  {
        printf("|    %i    ", j);   //laat het nummer van het vakje zien
        if (j < 10) {
            printf(" ");
        }
    }
    printf("|\n");
    eightTimesLine();
    for (int l = 0; l < amountPlayers; l++) {
        int o = x;
        for (int k = 0; k < 8; k++) {
            int gevonden = isvalueinarray(o, playerSpots, 6);
            if (gevonden != -1) {
                printf("|%-10s", playerNames[gevonden]); //laat de naam zien van de speler, als deze op dit vakje staat
            } else {
                printf("|          ");
            }
            o++;
        }
        printf("|\n");
    }
    resetFound();
}

// Deze rij toont de nummers van de vakken en plaatst er spelers in, achterstevoren
void printNumber2(int x, int y) {
    int j = x;
    for (int j = x; j > y; j--)  {
        printf("|    %i    ", j); //laat het nummer van het vakje zien
        if (j < 10) {
            printf(" ");
        }
    }
    printf("|\n");
    eightTimesLine();
    for (int l = 0; l < amountPlayers; l++) {
        int o = x;
        for (int k = 0; k < 8; k++) {
            int gevonden = isvalueinarray(o, playerSpots, 6);
            if (gevonden != -1) {
                printf("|%-10s", playerNames[gevonden]); //laat de naam zien van de speler, als deze op dit vakje staat
            } else {
                printf("|          ");
            }
            o--;
        }
        printf("|\n");
    }
    resetFound();
}

// Deze functie koppelt de ASCII onderdelen aan elkaar en toont de output
void displayStatus() {
    eightTimesLine();
    printNumber1(0, 8);
    eightTimesLine();
    printNumber2(15, 7);
    eightTimesLine();
    printNumber1(16, 24);
    eightTimesLine();
    printNumber2(31, 23);
    eightTimesLine();
    printNumber1(32, 40);
    eightTimesLine();
    printNumber2(47, 39);
    eightTimesLine();
    printNumber1(48, 56);
    eightTimesLine();
    printNumber2(63, 55);
    eightTimesLine();
}

/* EINDE ASCII OUTPUT */

/* ZORG DAT JE ALLEEN INT KAN INVOEREN*/
int input(){

    char *p, s[100];
    int n;

    while (fgets(s, sizeof(s), stdin)) {
        n = strtol(s, &p, 10);
        if (p == s || *p != '\n') {
            printf("Voer alstublieft een nummer in: ");
        } else break;
    }
    return n;
}
/* EINDE INVOER CONTROLE*/

/* BEGIN VAN DE MAIN */

int main() {

    // Het introduceren van de spelers
    printf("Welkom bij ons ganzenbord! Met hoeveel spelers zijn we vandaag?\n");
    amountPlayers = input(); // Vraag het aantal spelers en sla dat op in onze integer
    while (amountPlayers > 6 || amountPlayers <= 1) { // Controleer of het aantal spelers geldig is
        printf("Het spijt me, zoveel spelers kan dit bord niet aan. Dit spel is geschikt voor 2-6 spelers.\n");
        amountPlayers = input(); // Sla het aantal spelers opnieuw op
    }

    // Zet elke waarde van de vakjes standaard op 0 en sla de namen van de spelers op
    printf("%i spelers dus. Dat is prachtig.\nMag ik van elke speler de naam?\nHelaas kunnen wij geen namen accepteren die langer zijn dan 9 karakters!\nIs de door jouw ingevoerde naam wel langer? Dan wordt het overige deel vergeten :(\n", amountPlayers);
    for (int a = 0; a < amountPlayers; a++) {               // Voor elke speler
        printf("Welkom speler %i, wat is uw naam?\n", a+1);
        int c;
        scanf("%9s", playerNames[a]);                       // Sla de naam van de speler op in de array
        while ((c = fgetc(stdin)) != '\n' && c != EOF);     /* Flush stdin */
        playerSpots[a] = 0;                                 // Startplaatsen definieren als we toch bezig zijn
        playerEffect[a] = 0;
    }
    printf("Super! Nu we alle namen weten kunnen we beginnen met het spel\n");

    displayStatus(); //laat het bord zien
    
    // Hier begint het spel
    while(gameEnded == 0) {
        for (int playerNow = 0; playerNow < amountPlayers; playerNow++) { // Ga door de spelers heen
            if (playerEffect[playerNow] == 0) {
                printf("\nHet is de beurt aan %s om te gooien. Wil je met 1 of 2 dobbelstenen gooien? Je staat nu op plaats %i.\n", playerNames[playerNow], playerSpots[playerNow]);
                amountDices = input(); // Vraag het aantal te werpen dobbelstenen
                while (amountDices < 1 || amountDices > 2) { // Controleer of dit aantal geldig is
                    printf("Sorry, maar je mag slechts met 1 of 2 dobbelstenen gooien. Wat wordt het?\n");
                    amountDices = input(); // Vraag het aantal te werpen dobbelstenen opnieuw
                }
                int totalDice = calculateDice(amountDices); // Gooi de dobbelsteen echt
                if ((playerSpots[playerNow] + totalDice) > 63) {
                    int tempSpot = totalDice - (63-playerSpots[playerNow]);
                    printf("%s dreigt nu boven de 63 uit te komen. Je moet nu %d plaatsen teruglopen!\n", playerNames[playerNow], tempSpot);
                    playerSpots[playerNow] = 63 - tempSpot;
                } else {
                    playerSpots[playerNow] += totalDice;
                }

                // Controleer waar de speler op terecht is gekomen
                printf("%s staat nu op vakje %i\n", playerNames[playerNow], playerSpots[playerNow]); // Status-update
                if (doubleSpot(playerSpots[playerNow]) == true) {
                    printf("Omdat %i een speciaal plekje is mag je het gegooide aantal ogen nog een keer gooien!\n", playerSpots[playerNow]);
                    playerSpots[playerNow] += totalDice;
                    printf("Hierdoor sta je nu op plaats %i.\n", playerSpots[playerNow]);
                } else if (playerSpots[playerNow] == 6) {
                    printf("Wat een geluk! Er is hier een brug die je direct naar plek 12 brengt.\n");
                    playerSpots[playerNow] = 12;
                } else if (playerSpots[playerNow] == 19) {
                    printf("Welkom in de herberg! Vannacht is de eerste nacht gratis. Je blijft slapen en slaat een beurt over.\n");
                    playerEffect[playerNow] = 19;
                } else if (playerSpots[playerNow] == 31) {
                    int status = checkWell(amountPlayers, playerEffect);
                    if (status == -1) {
                        printf("Ah, val je nou zo in de put? Dat wordt wachten totdat er iemand langskomt. Succes man.\n");
                        playerEffect[playerNow] = 31;
                    } else {
                        printf("Daar stond al iemand! Gelukkig zeg. Daar help je %s maar mooi mee.\n", playerNames[status]);
                        playerEffect[status] = 0;
                    }
                } else if (playerSpots[playerNow] == 42) {
                    printf("Het magische getal! 42! Maar tijdens je zoetocht naar dit nummer kom je terecht op plaats 39, helaas.\n");
                    playerSpots[playerNow] = 39;
                } else if (playerSpots[playerNow] == 52) {
                    int status = checkPrison(amountPlayers, playerEffect);
                    if (status == -1) {
                        printf("De gevangenis? Serieus? Hoe ben je daar nu weer terecht gekomen? Dat wordt wachten totdat er iemand langskomt die als advocaat kan dienen. Succes.\n");
                    playerEffect[playerNow] = 52;
                    } else {
                        printf("Daar stond al iemand! Gelukkig zeg. Daar help je %s maar mooi mee.\n", playerNames[status]);
                        playerEffect[status] = 0;
                    }
                } else if (playerSpots[playerNow] == 58) {
                    printf("Wat overkomt jouw nu? Je sterft ter plekken. Je begint dus opnieuw. Succes man.\n");
                    playerSpots[playerNow] = 0;
                } else if (playerSpots[playerNow] == 63) {
                    printf("Gefeliciteerd! De winnaar van vandaag is %s. Applaudiseert u even alstublieft!\n", playerNames[playerNow]);
                    displayStatus();
                    exit(1);
                }
            } else if (playerEffect[playerNow] == 19) {
                printf("Lekker geslapen in de herberg? De volgende beurt ben je weer gereed om te gaan. Rust nog even uit, %s.\n", playerNames[playerNow]);
                playerEffect[playerNow] = 0;
            } else if (playerEffect[playerNow] == 31) {
                printf("Lijkt erop dat je nog steeds in de put staat. Nog even langer wachten dus, %s.\n", playerNames[playerNow]);
            } else if (playerEffect[playerNow] == 52) {
                printf("Nog steeds niemand langs geweest? Ik ga iemand bellen. Hou vol, %s!\n", playerNames[playerNow]);
            }
                displayStatus();
        }
    }
    return 0;
}
