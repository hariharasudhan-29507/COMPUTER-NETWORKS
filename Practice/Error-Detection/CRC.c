#include <stdio.h>
#include <string.h>

int main() {
    char data[50], generator[20], codeword[50], received[50];
    char remainder[20], temp[50];
    int datalen, genlen, codelen, i, j, choice, errorpos;

    printf("Enter data bits as a binary string: ");
    scanf("%s", data);

    printf("Enter generator (divisor) bits as a binary string: ");
    scanf("%s", generator);

    datalen = strlen(data);
    genlen = strlen(generator);
    codelen = datalen + genlen - 1;

    for (i = 0; i < datalen; i++) {
        temp[i] = data[i];
    }
    for (i = 0; i < genlen - 1; i++) {
        temp[datalen + i] = '0';
    }
    temp[datalen + genlen - 1] = '\0';

    for (i = 0; i < genlen; i++) {
        remainder[i] = temp[i];
    }
    remainder[genlen] = '\0';

    for (i = 0; i <= codelen - genlen; i++) {
        if (remainder[0] == '1') {
            for (j = 0; j < genlen; j++) {
                if (remainder[j] == generator[j]) {
                    remainder[j] = '0';
                } else {
                    remainder[j] = '1';
                }
            }
        }

        for (j = 0; j < genlen - 1; j++) {
            remainder[j] = remainder[j + 1];
        }

        if (i + genlen < codelen) {
            remainder[genlen - 1] = temp[i + genlen];
        } else {
            remainder[genlen - 1] = '\0';
        }
    }

    remainder[genlen - 1] = '\0';

    printf("\n--- Sender Side ---\n");
    printf("Data bits: %s\n", data);
    printf("Generator: %s\n", generator);
    printf("CRC remainder: %s\n", remainder);

    for (i = 0; i < datalen; i++) {
        codeword[i] = data[i];
    }
    for (i = 0; i < genlen - 1; i++) {
        codeword[datalen + i] = remainder[i];
    }
    codeword[datalen + genlen - 1] = '\0';

    printf("Transmitted codeword: %s\n", codeword);

    strcpy(received, codeword);

    printf("\nDo you want to introduce an error during transmission? (1 for yes, 0 for no): ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Enter bit position to flip (0 to %d): ", codelen - 1);
        scanf("%d", &errorpos);
        if (received[errorpos] == '0') {
            received[errorpos] = '1';
        } else {
            received[errorpos] = '0';
        }
    }

    printf("\n--- Receiver Side ---\n");
    printf("Received codeword: %s\n", received);

    for (i = 0; i < codelen; i++) {
        temp[i] = received[i];
    }
    temp[codelen] = '\0';

    for (i = 0; i < genlen; i++) {
        remainder[i] = temp[i];
    }
    remainder[genlen] = '\0';

    for (i = 0; i <= codelen - genlen; i++) {
        if (remainder[0] == '1') {
            for (j = 0; j < genlen; j++) {
                if (remainder[j] == generator[j]) {
                    remainder[j] = '0';
                } else {
                    remainder[j] = '1';
                }
            }
        }

        for (j = 0; j < genlen - 1; j++) {
            remainder[j] = remainder[j + 1];
        }

        if (i + genlen < codelen) {
            remainder[genlen - 1] = temp[i + genlen];
        } else {
            remainder[genlen - 1] = '\0';
        }
    }

    remainder[genlen - 1] = '\0';

    printf("Remainder after division: %s\n", remainder);

    int iszero = 1;
    for (i = 0; i < genlen - 1; i++) {
        if (remainder[i] != '0') {
            iszero = 0;
        }
    }

    if (iszero == 1) {
        printf("Result: No error detected\n");
    } else {
        printf("Result: Error detected in received data\n");
    }

    return 0;
}