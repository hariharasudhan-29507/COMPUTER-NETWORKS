#include <stdio.h>
#include <string.h>

int main() {
    char databits[20];
    int senderdata[20], receiverdata[20];
    int n, i, count, paritybit, paritytype, errorpos, choice;

    printf("Enter data bits as a binary string (e.g. 1011): ");
    scanf("%s", databits);

    n = strlen(databits);

    for (i = 0; i < n; i++) {
        senderdata[i] = databits[i] - '0';
    }

    printf("Choose parity type (1 for Even parity, 2 for Odd parity): ");
    scanf("%d", &paritytype);

    count = 0;
    for (i = 0; i < n; i++) {
        if (senderdata[i] == 1) {
            count = count + 1;
        }
    }

    if (paritytype == 1) {
        if (count % 2 == 0) {
            paritybit = 0;
        } else {
            paritybit = 1;
        }
    } else {
        if (count % 2 == 0) {
            paritybit = 1;
        } else {
            paritybit = 0;
        }
    }

    senderdata[n] = paritybit;

    printf("\n--- Sender Side ---\n");
    printf("Data bits: ");
    for (i = 0; i < n; i++) {
        printf("%d ", senderdata[i]);
    }
    printf("\nParity bit generated: %d\n", paritybit);
    printf("Transmitted codeword: ");
    for (i = 0; i <= n; i++) {
        printf("%d ", senderdata[i]);
    }
    printf("\n");

    for (i = 0; i <= n; i++) {
        receiverdata[i] = senderdata[i];
    }

    printf("\nDo you want to introduce an error during transmission? (1 for yes, 0 for no): ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Enter bit position to flip (0 to %d): ", n);
        scanf("%d", &errorpos);
        if (receiverdata[errorpos] == 0) {
            receiverdata[errorpos] = 1;
        } else {
            receiverdata[errorpos] = 0;
        }
    }

    printf("\n--- Receiver Side ---\n");
    printf("Received codeword: ");
    for (i = 0; i <= n; i++) {
        printf("%d ", receiverdata[i]);
    }
    printf("\n");

    count = 0;
    for (i = 0; i <= n; i++) {
        if (receiverdata[i] == 1) {
            count = count + 1;
        }
    }

    if (paritytype == 1) {
        if (count % 2 == 0) {
            printf("Result: No error detected\n");
        } else {
            printf("Result: Error detected in received data\n");
        }
    } else {
        if (count % 2 != 0) {
            printf("Result: No error detected\n");
        } else {
            printf("Result: Error detected in received data\n");
        }
    }

    return 0;
}