#include <stdio.h>
#include <string.h>

#define FLAG_BIN "01111110"
#define ESC_BIN  "01111101"

char raw_binary[100][9];
char stuffed_binary[500][9];
char destuffed_binary[100][9];

void charToBinaryStr(char character, char binary_str[]) {
    int bit_index;
    for(bit_index = 7; bit_index >= 0; bit_index--) {
        binary_str[7 - bit_index] = ((character >> bit_index) & 1) + '0';
    }
    binary_str[8] = '\0';
}

char binaryStrToChar(char binary_str[]) {
    int bit_index, decimal_sum = 0;
    for(bit_index = 0; bit_index < 8; bit_index++) {
        decimal_sum = decimal_sum * 2 + (binary_str[bit_index] - '0');
    }
    return (char)decimal_sum;
}


void byteStuffing() {
    char input[100];
    int i, total_bytes = 0, len;

    printf("Enter a string: ");
    scanf("%s", input);
    len = strlen(input);


    printf("\nASCII to Binary Conversion:\n");
    for(i = 0; i < len; i++) {
        charToBinaryStr(input[i], raw_binary[i]);
        printf("%c = %s\n", input[i], raw_binary[i]);
    }

    strcpy(stuffed_binary[total_bytes++], FLAG_BIN);

    for(i = 0; i < len; i++) {
        if(strcmp(raw_binary[i], FLAG_BIN) == 0 || strcmp(raw_binary[i], ESC_BIN) == 0) {
            strcpy(stuffed_binary[total_bytes++], ESC_BIN);
        }
        strcpy(stuffed_binary[total_bytes++], raw_binary[i]);
    }


    strcpy(stuffed_binary[total_bytes++], FLAG_BIN);


    printf("\nByte Stuffed Frame (Binary Blocks):\n");
    for(i = 0; i < total_bytes; i++) {
        printf("%s ", stuffed_binary[i]);
    }
    printf("\n\nContinuous Bitstream:\n");
    for(i = 0; i < total_bytes; i++) {
        printf("%s", stuffed_binary[i]);
    }
    printf("\n");
}


void byteDestuffing() {
    int total_blocks, i;
    int destuffed_count = 0;
    char restored_text[100];

    printf("Enter the number of binary blocks in the stuffed frame: ");
    if (scanf("%d", &total_blocks) != 1) return;

    printf("Enter the %d space-separated binary blocks:\n", total_blocks);
    for(i = 0; i < total_blocks; i++) {
        scanf("%s", stuffed_binary[i]);
    }

   for(i = 1; i < total_blocks - 1; i++) {
       if(strcmp(stuffed_binary[i], ESC_BIN) == 0) {
            i++;
       }
        strcpy(destuffed_binary[destuffed_count++], stuffed_binary[i]);
    }


    printf("\n--- Destuffed Data ---\n");
    for(i = 0; i < destuffed_count; i++) {
        restored_text[i] = binaryStrToChar(destuffed_binary[i]);
        printf("Block %s -> %c\n", destuffed_binary[i], restored_text[i]);
    }
    restored_text[destuffed_count] = '\0';

    printf("\nFinal Restored Text: %s\n", restored_text);
}

int main() {
    int choice;
    do {
        printf("\n   FRAMING PROTOCOL IMPLEMENTATION (BINARY STUFFING)\n\n");
        printf("1. Byte Stuffing\n");
        printf("2. Byte Destuffing\n");
        printf("3. Exit\n");
        printf("\nEnter your choice: ");
        if (scanf("%d", &choice) != 1) break;

        switch(choice) {
            case 1:
                byteStuffing();
                break;
            case 2:
                byteDestuffing();
                break;
            case 3:
                printf("\nExiting Program...\n");
                break;
            default:
                printf("\nInvalid Choice!\n");
        }
    } while(choice != 3);

    return 0;
}
