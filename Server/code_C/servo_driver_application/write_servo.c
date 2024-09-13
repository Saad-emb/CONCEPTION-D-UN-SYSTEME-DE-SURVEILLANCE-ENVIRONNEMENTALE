#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s [number]\n", argv[0]);
        return 1;
    }
    int number = atoi(argv[1]);
    if (number < 0 || number > 90) {
        printf("Invalid number. Please enter a number between 0 and 90.\n");
        return 1;
    }
    char command[100];
     // stock dans le buffer la commande qui sert a  ecrire dans le fichier  driver qu on a charger avec insmod 	
    sprintf(command, "echo \"%d\" > /dev/servo_motor", number);
    // execution de la commande	
    system(command);
    return 0;
}

