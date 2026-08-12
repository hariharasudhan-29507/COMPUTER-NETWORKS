#include <stdio.h>
#include <string.h>

int onescomplementadd(char *sum, char *segment, int segsize) {
    int i, carry;
    carry = 0;

    for (i = segsize - 1; i >= 0; i--) {
        int a = sum[i] - '0';
        int b = segment[i] - '0';
        int total = a + b + carry;

        if (total == 0) {
            sum[i] = '0';
            carry = 0;
        } else if (total == 1) {
            sum[i] = '1';
            carry = 0;
        } else if (total == 2) {
            sum[i] = '0';
            carry = 1;
        } else {
            sum[i] = '1';
            carry = 1;
        }
    }

    return carry;
}

void char_to_binary(char ch, char *binary) {
   int i ;
   for ( i = 7; i >= 0; i--) {
        binary[7 - i] = ((ch >> i) & 1) ? '1' : '0';
    }
    binary[8] = '\0';
}

int main() {
    char input[100];
    char data[1000]; // increased size to hold binary representation
    char segments[20][20], sum[20], checksum[20], complement[20];
    char codeword[1000], received[1000];
    int datalen, segsize, numsegs, i, j, carry, choice, errorpos, codelen;
    int num_errors, k;

    printf("Enter data as a string: ");
    scanf("%s", input);

    // Convert each character to 8-bit binary
    datalen = strlen(input);
    int total_bits = datalen * 8;
    int pos = 0;
    for (i = 0; i < datalen; i++) {
        char binary[9];
        char_to_binary(input[i], binary);
        for (j = 0; j < 8; j++) {
            data[pos++] = binary[j];
        }
    }
    data[pos] = '\0';
    datalen = total_bits;

    printf("Binary representation: %s\n", data);

    printf("Enter segment size (number of bits per segment): ");
    scanf("%d", &segsize);

    numsegs = datalen / segsize;

    for (i = 0; i < numsegs; i++) {
        for (j = 0; j < segsize; j++) {
            segments[i][j] = data[i * segsize + j];
        }
        segments[i][segsize] = '\0';
    }

    printf("\n--- Sender Side ---\n");
    printf("Data bits: %s\n", data);
    printf("Segments:\n");
    for (i = 0; i < numsegs; i++) {
        printf("Segment %d: %s\n", i + 1, segments[i]);
    }

    for (i = 0; i < segsize; i++) {
        sum[i] = '0';
    }
    sum[segsize] = '\0';

    for (i = 0; i < numsegs; i++) {
        carry = onescomplementadd(sum, segments[i], segsize);
        if (carry == 1) {
            for (j = segsize - 1; j >= 0; j--) {
                if (sum[j] == '1') {
                    sum[j] = '0';
                } else {
                    sum[j] = '1';
                    break;
                }
            }
        }
    }

    printf("Sum: %s\n", sum);

    for (i = 0; i < segsize; i++) {
        if (sum[i] == '0') {
            checksum[i] = '1';
        } else {
            checksum[i] = '0';
        }
    }
    checksum[segsize] = '\0';

    printf("Checksum generated: %s\n", checksum);

    strcpy(codeword, data);
    strcat(codeword, checksum);
    codelen = strlen(codeword);

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

    int recvsegs = codelen / segsize;
    char recvsegments[20][20];

    for (i = 0; i < recvsegs; i++) {
        for (j = 0; j < segsize; j++) {
            recvsegments[i][j] = received[i * segsize + j];
        }
        recvsegments[i][segsize] = '\0';
    }

    for (i = 0; i < segsize; i++) {
        sum[i] = '0';
    }
    sum[segsize] = '\0';

    for (i = 0; i < recvsegs; i++) {
        carry = onescomplementadd(sum, recvsegments[i], segsize);
        if (carry == 1) {
            for (j = segsize - 1; j >= 0; j--) {
                if (sum[j] == '1') {
                    sum[j] = '0';
                } else {
                    sum[j] = '1';
                    break;
                }
            }
        }
    }

    printf("Sum at receiver: %s\n", sum);

    for (i = 0; i < segsize; i++) {
        if (sum[i] == '0') {
            complement[i] = '1';
        } else {
            complement[i] = '0';
        }
    }
    complement[segsize] = '\0';

    printf("Complement: %s\n", complement);

    int iszero = 1;
    for (i = 0; i < segsize; i++) {
        if (complement[i] != '0') {
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
