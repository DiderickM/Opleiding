#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int throwDice() { // Functie om dobbelstenen te werpen
    int valueDice = rand() % 6 + 1; // Bepaal een willekeurige waarde
    return valueDice; // Geef het totaal aantal ogen terug
}

int movepice(int Player, int Steps, int PlayerSpots[], int Spots){
    PlayerSpots[Player] += Steps;
    if(PlayerSpots[Player] > Spots){
        int ToMany = PlayerSpots[Player] - Spots;
        PlayerSpots[Player] = Spots - ToMany;
        printf("Je bent verder dan %d, Je moet nu %d stappen terug\n", Spots, ToMany);
    }
}

bool isvalueinarray(int val, int arr[], int size){
    int i;
    for (i=0; i < size; i++) {
        if (arr[i] == val){
            return true;
        }
    }
    return false;
}

int SetEffect(int Player, int PlayerSpots[], int PlayerEffect[]){
    printf("Je staat op een speciale plek!\n");
    if(PlayerSpots[Player] == 6){
        printf("Je staat op de brug, mag gelijk door naar 12!\n");
        PlayerSpots[Player] = 12;
    }
    if(PlayerSpots[Player] == 19){
        printf("Je bent aangekomen bij de herberg, Je slaat daarom een beurt over!\n");
        PlayerEffect[Player] = 1;
    }
    if(PlayerSpots[Player] == 31){
        printf("Je bent in de put beland!, Je moet wachten tot dat iemand je komt redden!\n");
        //TODO: Hier moet de functie voor de put
    }
    if(PlayerSpots[Player] == 42){
        printf("Je bent in het doolhof beland, De uitgang was alleen bij plaats 39\n");
        PlayerSpots[Player] = 39;
    }
    if(PlayerSpots[Player] == 52){
        printf("Je bent in de put beland!, Je moet wachten tot dat iemand je komt redden!\n");
        //TODO: Hier moet de functie voor de put
    }
    if(PlayerSpots[Player] == 58){
        printf("Je bent helaas dood :(, Je moet opnieuw beginnen\n");
        PlayerSpots[Player] = 0;
    }
    
}

int main(){
    int PlayerAmount;
    
    printf("Welkom bij het ganzenbord spel!\n");
    printf("Met hoeveel spelers spelen we vandaag?\n");
    scanf("%i", &PlayerAmount);
    while(PlayerAmount < 2 || PlayerAmount > 6){
        printf("Dit spel kan worden gespeeld door 2 tot 6 spelers, geef een nieuw aantal spelers op\n");
        scanf("%i", &PlayerAmount);
    }

    char PlayerNames[PlayerAmount][20];
    int PlayerSpots[PlayerAmount];
    int SpecialSpots[] = {6,19,31,42,52,58,63};
    int DoubleSpots[] = {5,9,14,18,23,27,32,36,42,45,50,54,59};
    int PlayerEffect[PlayerAmount];

    printf("Ik zou graag de namen willen weten van de verschillende spelers\n");
    for (int a = 0; a < PlayerAmount; a++) { // Voor elke speler
        printf("Welkom speler %i, wat is uw naam?\n", a+1);
        scanf("%s", &PlayerNames[a]); // Sla de naam van de speler op in de array
        PlayerSpots[a] = 0; // Startplaatsen definieren als we toch bezig zijn
    }

    bool doorgaan = true;
    int DiceAmount;
    int Spots = 64;
    while(doorgaan){
        for(int b = 0; PlayerAmount > b; b++){
            if(PlayerEffect[b] == 1){
                PlayerEffect[b] = 0;
                printf("Jammer %s je moest een beurt oversaan! de volgende ronde doe je weer mee.\n", PlayerNames[b]);
            }else{
                printf("%s is aan de beurt\nJe staat op %d\n", PlayerNames[b], PlayerSpots[b]);
                printf("Met hoeveel dobbelstenen wil je gooien?\n");
                scanf("%i", &DiceAmount);
                while(DiceAmount == 0 || DiceAmount > 2){
                    printf("Je mag maximaal met 2 dobbelstenen gooien! geef een nieuw aantal op\n");
                    scanf("%i", &DiceAmount);
                }
                int valueDices = 0;
                for(int c = 1; DiceAmount + 1 > c; c++){
                    int valueDice = throwDice();
                    valueDices += valueDice;
                    printf("%de keer gooien geeft waarde: %d\n", c, valueDice);
                    movepice(b, valueDice, PlayerSpots, Spots);
                }
                printf("Je staat nu op plaats %d\n", PlayerSpots[b]);
                while(isvalueinarray(PlayerSpots[b],DoubleSpots,sizeof(DoubleSpots)/sizeof(DoubleSpots[0]))){
                    printf("Je bent beland op een verdubbel plaats, je mag het gegooide ogen nogeen keer lopen!\n");
                    movepice(b, valueDices, PlayerSpots, Spots);
                    printf("Je staat nu op plaats %d\n", PlayerSpots[b]);
                }
                if(isvalueinarray(PlayerSpots[b],SpecialSpots,sizeof(SpecialSpots)/sizeof(SpecialSpots[0]))){
                    SetEffect(b, PlayerSpots, PlayerEffect);
                }
                //printf("Je staat nu op plaats %d\n", PlayerSpots[b]);

                if(PlayerSpots[b] == Spots){
                    doorgaan = false;
                    printf("%d heeft het spel gewonnen!", PlayerNames[b]);
                    break;
                }
            }
        }
    }
}