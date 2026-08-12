#include <stdio.h>
#include <string.h>

void char_to_binary(char ch, char *binary) {
    int i;
    for (i = 7; i >= 0; i--) {
        binary[7 - i] = ((ch >> i) & 1) ? '1' : '0';
    }
    binary[8] = '\0';
}

int main() {
    char input[50];
    char data[1000]; // increased size for binary representation
    char generator[20], codeword[1000], received[1000];
    char remainder[20], temp[1000];
    int datalen, genlen, codelen, i, j, choice, errorpos;
    int num_errors, k;

    printf("Enter data as a string: ");
    scanf("%s", input);

    // Convert each character to 8-bit binary
    int input_len = strlen(input);
    int total_bits = input_len * 8;
    int pos = 0;
    for (i = 0; i < input_len; i++) {
        char binary[9];
        char_to_binary(input[i], binary);
        for (j = 0; j < 8; j++) {
            data[pos++] = binary[j];
        }
    }
    data[pos] = '\0';
    datalen = total_bits;

    printf("Binary representation: %s\n", data);

    printf("Enter generator (divisor) bits as a binary string: ");
    scanf("%s", generator);

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
        printf("Enter number of bit errors to introduce: ");
        scanf("%d", &num_errors);

        for (k = 0; k < num_errors; k++) {
            printf("Enter bit position %d to flip (0 to %d): ", k + 1, codelen - 1);
            scanf("%d", &errorpos);
            if (received[errorpos] == '0') {
                received[errorpos] = '1';
            } else {
                received[errorpos] = '0';
            }
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
