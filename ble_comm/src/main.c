#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>

#include "main.h"

enum APP_MODE read_app_mode(void) {
    char buffer[32];
    int number;

    while(true) {
        printf("What mode? (0) Send, (1) Receive: ");

        if (fgets(buffer, sizeof(buffer), stdin)) {
            if (
                sscanf(buffer, "%d", &number) == 1 &&
                (number == APP_RECV || number == APP_SEND)
            ) {
                return (enum APP_MODE) number;
            } else {
                printf("Invalid mode.\n");
            }
        }
    }
}

int main(void) {

    enum APP_MODE mode;

    mode = read_app_mode();

    printf("You entered: %d\n", mode);

    return 0;
}