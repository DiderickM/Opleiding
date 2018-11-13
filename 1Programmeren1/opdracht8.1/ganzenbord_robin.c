#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int throwDice() { // Functie om dobbelstenen te werpen
    int valueDice = rand() % 6 + 1; // Bepaal een willekeurige waarde
    return valueDice; // Geef het totaal aantal ogen terug
}

int main() {

    // Intializeren van de variabelen
    int amountSpots = 64, gameEnded = 0, amountPlayers, amountDices, temp1, temp2;

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
    bool playerEffect[amountPlayers]; // Effect in werking?

    // Zet elke waarde van de vakjes standaard op 0 en sla de namen van de spelers op
    printf("%i spelers dus. Dat is prachtig. Welkom aan bord! Snap je hem? Ganzen-BORD?\nAhum. Sorry, we gaan verder.\nMag ik van elke speler de naam?\n", amountPlayers);
    for (int a = 0; a < amountPlayers; a++) { // Voor elke speler
        printf("Welkom speler %i, wat is uw naam?\n", a+1);
        scanf("%s", &playerDatabase[a]); // Sla de naam van de speler op in de array
        playerSpots[a] = 0; // Startplaatsen definieren als we toch bezig zijn
        playerEffect[a] = false;
    }
    printf("Super! Nu dat uit de weg is, denk ik dat het tijd is om te gaan spelen!\n");

    // Hier begint het spel
    while(gameEnded == 0) {
        for (int playerNow = 0; playerNow < amountPlayers; playerNow++) { // Ga door de spelers heen
            printf("Het is de beurt aan %s om te gooien. Wil je met 1 of 2 dobbelstenen gooien?\n", playerDatabase[playerNow]);
            scanf("%i", &amountDices); // Vraag het aantal te werpen dobbelstenen
            while (amountDices < 1 || amountDices > 2) { // Controleer of dit aantal geldig is
                printf("Sorry, maar je mag slechts met 1 of 2 dobbelstenen gooien. Waw wordt het?\n");
                scanf("%i", &amountDices); // Vraag het aantal te werpen dobbelstenen opnieuw
            }
            if (amountDices == 2) { // Als er twee dobbelstenen worden geworpen
                int temp1 = throwDice(), temp2 = throwDice(); // Werp tweemaal
                printf("Je gooide %i en %i, dus %i totaal.\n", temp1, temp2, temp1+temp2); // Geef output
                playerSpots[playerNow] += temp1 + temp2; // Verschuif de speler
            } else { // Als er een dobbelsteen wordt geworpen
                int temp1 = throwDice(); // Sla de waarde op
                printf("Je gooide %i.\n", temp1); // Geef output
                playerSpots[playerNow] += temp1; // Verschuif de speler
            }
            printf("%s staat nu op vakje %i\n", playerDatabase[playerNow], playerSpots[playerNow]); // Status-update
        }
    }
}