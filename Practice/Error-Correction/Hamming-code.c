#include <stdio.h>
#include <string.h>

int main() {
    char data[50];
    int datalen, r, codelen, i, j, k, pos;
    int codeword[50], received[50];
    int choice, errorpos;

    printf("Enter data bits as a binary string: ");
    scanf("%s", data);

    datalen = strlen(data);

    r = 0;
    while ((1 << r) < datalen + r + 1) {
        r = r + 1;
    }

    codelen = datalen + r;

    j = 0;
    for (i = 1; i <= codelen; i++) {
        if ((i & (i - 1)) == 0) {
            codeword[i] = -1;
        } else {
            codeword[i] = data[j] - '0';
            j = j + 1;
        }
    }

    for (i = 0; i < r; i++) {
        pos = 1 << i;
        int count = 0;
        for (j = pos; j <= codelen; j = j + 1) {
            if (((j / pos) % 2) == 1) {
                if (codeword[j] == 1) {
                    count = count + 1;
                }
            }
        }
        if (count % 2 == 0) {
            codeword[pos] = 0;
        } else {
            codeword[pos] = 1;
        }
    }

    printf("\n--- Sender Side ---\n");
    printf("Data bits: %s\n", data);
    printf("Number of parity bits: %d\n", r);
    printf("Transmitted codeword: ");
    for (i = 1; i <= codelen; i++) {
        printf("%d", codeword[i]);
    }
    printf("\n");

    for (i = 1; i <= codelen; i++) {
        received[i] = codeword[i];
    }

    printf("\nDo you want to introduce an error during transmission? (1 for yes, 0 for no): ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Enter bit position to flip (1 to %d): ", codelen);
        scanf("%d", &errorpos);
        if (received[errorpos] == 0) {
            received[errorpos] = 1;
        } else {
            received[errorpos] = 0;
        }
    }

    printf("\n--- Receiver Side ---\n");
    printf("Received codeword: ");
    for (i = 1; i <= codelen; i++) {
        printf("%d", received[i]);
    }
    printf("\n");

    int syndrome = 0;
    for (i = 0; i < r; i++) {
        pos = 1 << i;
        int count = 0;
        for (j = pos; j <= codelen; j = j + 1) {
            if (((j / pos) % 2) == 1) {
                if (received[j] == 1) {
                    count = count + 1;
                }
            }
        }
        if (count % 2 != 0) {
            syndrome = syndrome + pos;
        }
    }

    printf("Syndrome (error position): %d\n", syndrome);

    if (syndrome == 0) {
        printf("Result: No error detected\n");
    } else {
        printf("Result: Error detected at position %d\n", syndrome);
        if (received[syndrome] == 0) {
            received[syndrome] = 1;
        } else {
            received[syndrome] = 0;
        }
        printf("Corrected codeword: ");
        for (i = 1; i <= codelen; i++) {
            printf("%d", received[i]);
        }
        printf("\n");
    }

    j = 0;
    char correcteddata[50];
    for (i = 1; i <= codelen; i++) {
        if ((i & (i - 1)) != 0) {
            correcteddata[j] = received[i] + '0';
            j = j + 1;
        }
    }
    correcteddata[j] = '\0';

    printf("Extracted data bits: %s\n", correcteddata);

    return 0;
}