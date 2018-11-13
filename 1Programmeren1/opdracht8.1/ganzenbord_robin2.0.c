#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int throwDice() { // Functie om dobbelstenen te werpen
    int valueDice = rand() % 6 + 1; // Bepaal een willekeurige waarde
    return valueDice; // Geef het totaal aantal ogen terug
}

int calculateDice(int amountDices) {
    int total = 0;
    if (amountDices == 2) { // Als er twee dobbelstenen worden geworpen
        int temp1 = throwDice(), temp2 = throwDice(); // Werp tweemaal
        printf("Je gooide %i en %i, dus %i totaal.\n", temp1, temp2, temp1+temp2); // Geef output
        total += temp1 + temp2; // Verschuif de speler
    } else { // Als er een dobbelsteen wordt geworpen
        int temp1 = throwDice(); // Sla de waarde op
        printf("Je gooide %i.\n", temp1); // Geef output
        total += temp1;
    }
    return total;
}

bool doubleSpot(int x) {
    for (int i = 0; i < 6; i++) {
        if (x == (i*9)) {
            return true;
        }
    }
    for (int j = 0; j < 7; j++) {
        if (x == ((j*9)-4)) {
            return true;
        }
    }
    return false;
}

int checkWell(int x, int y[]) {
    for(int i = 0; i < x; i++) {
        if (y[i] == 31) {
            return i;
        } 
    }
    return -1;
}

int checkPrison(int x, int y[]) {
    for(int i = 0; i < x; i++) {
        if (y[i] == 52) {
            return i;
        } 
    }
    return -1;
}

int main() {

    // Intializeren van de variabelen
    int amountSpots = 64, gameEnded = 0, amountPlayers, amountDices;

    // Het introduceren van de spelers
    printf("Een hele goedendag! Mag ik u vragen hoeveel spelers we vandaag hebben? Helaas hebben we slechts 6 stukken.\n");
    scanf("%i", &amountPlayers); // Vraag het aantal spelers en sla dat op in onze integer
    while (amountPlayers > 6 || amountPlayers <= 1) { // Controleer of het aantal spelers geldig is
        printf("Het spijt me, met zoveel spelers kan ik niet veel. Dit spel is geschikt voor 2-6 spelers.\n");
        scanf("%i", &amountPlayers); // Sla het aantal spelers opnieuw op
    }
    
    // Intializeren van spelerdata
    char playerDatabase[amountPlayers][11]; // Maak een array waar alle namen in staan vermeld
    int playerSpots[amountPlayers]; // Plaats van speler
    int playerEffect[amountPlayers]; // Effect in werking?

    // Zet elke waarde van de vakjes standaard op 0 en sla de namen van de spelers op
    printf("%i spelers dus. Dat is prachtig. Welkom aan bord! Snap je hem? Ganzen-BORD?\nAhum. Sorry, we gaan verder.\nMag ik van elke speler de naam?\n", amountPlayers);
    for (int a = 0; a < amountPlayers; a++) { // Voor elke speler
        printf("Welkom speler %i, wat is uw naam?\n", a+1);
        scanf("%s", &playerDatabase[a]); // Sla de naam van de speler op in de array
        playerSpots[a] = 0; // Startplaatsen definieren als we toch bezig zijn
        playerEffect[a] = 0;
    }
    printf("Super! Nu dat uit de weg is, denk ik dat het tijd is om te gaan spelen!\n");

    // Hier begint het spel
    while(gameEnded == 0) {
        for (int playerNow = 0; playerNow < amountPlayers; playerNow++) { // Ga door de spelers heen
            if (playerEffect[playerNow] == 0) {
                printf("Het is de beurt aan %s om te gooien. Wil je met 1 of 2 dobbelstenen gooien? Je staat nu op plaats %i.\n", playerDatabase[playerNow], playerSpots[playerNow]);
                scanf("%i", &amountDices); // Vraag het aantal te werpen dobbelstenen
                while (amountDices < 1 || amountDices > 2) { // Controleer of dit aantal geldig is
                    printf("Sorry, maar je mag slechts met 1 of 2 dobbelstenen gooien. Waw wordt het?\n");
                    scanf("%i", &amountDices); // Vraag het aantal te werpen dobbelstenen opnieuw
                }
                int totalDice = calculateDice(amountDices); // Gooi de dobbelsteen echt
                playerSpots[playerNow] += totalDice;

                // Controleer waar de speler op terecht is gekomen
                printf("%s staat nu op vakje %i\n", playerDatabase[playerNow], playerSpots[playerNow]); // Status-update
                if (doubleSpot(playerSpots[playerNow]) == true) {
                    printf("Je staat op %i, je aantal ogen mag je nog een keer vooruit.\n", playerSpots[playerNow]);
                    playerSpots[playerNow] += totalDice;
                    printf("Hierdoor sta je nu op plaats %i.\n", playerSpots[playerNow]);
                } else if (playerSpots[playerNow] == 6) {
                    printf("Je bent op de brug beland! Als gevolg hiervan kun je een gedeelte overslaan en sta je nu op vakje 12.\n");
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
                        printf("Daar stond al iemand! Gelukkig zeg. Daar help je %s maar mooi mee.\n", playerDatabase[status]);
                        playerEffect[status] = 0;
                    }
                } else if (playerSpots[playerNow] == 42) {
                    printf("Het magische getal! 42! Gefeliciteerd! Je verwacht iets moois, maar helaas raak je snel verdwaald tijdens je zoektocht. Je komt verdwaasd terug op plaats 39.\n");
                    playerSpots[playerNow] = 39;
                } else if (playerSpots[playerNow] == 52) {
                    int status = checkPrison(amountPlayers, playerEffect);
                    if (status == -1) {
                        printf("De gevangenis? Serieus? Hoe ben je daar nu weer terecht gekomen? Dat wordt wachten totdat er iemand langskomt die als advocaat kan dienen. Succes.\n");
                    playerEffect[playerNow] = 52;
                    } else {
                        printf("Daar stond al iemand! Gelukkig zeg. Daar help je %s maar mooi mee.\n", playerDatabase[status]);
                        playerEffect[status] = 0;
                    }
                } else if (playerSpots[playerNow] == 58) {
                    printf("DAT MEEN JE NIET. Je was zo dichtbij! Je bent helaas overleden. Niks aan te doen man. Balen. Gelukkig hebben we hier reincarnatie. Je begint dus opnieuw. Succes man.\n");
                    playerSpots[playerNow] = 0;
                } else if (playerSpots[playerNow] == 63) {
                    printf("BAM! Dat is hoe we dat doen! Je hebt gewonnen! Gefeliciteerd!\n");
                }
            } else if (playerEffect[playerNow] == 19) {
                printf("Lekker geslapen in de herberg? De volgende beurt ben je weer gereed om te gaan. Rust nog even uit, %s.\n", playerDatabase[playerNow]);
                playerEffect[playerNow] = 0;
            } else if (playerEffect[playerNow] == 31) {
                printf("Lijkt erop dat je nog steeds in de put staat. Nog even langer wachten dus, %s.\n", playerDatabase[playerNow]);
            } else if (playerEffect[playerNow] == 52) {
                printf("Nog steeds geen advocaat langsgeweest? Ik zal nog eens bellen. Hou vol, %s!\n", playerDatabase[playerNow]);
            }
        }
    }
}