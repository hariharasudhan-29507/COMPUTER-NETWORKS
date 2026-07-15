#include <stdio.h>
#include <string.h>

char binary[1000];

// Function to convert string into binary (ASCII)
void stringToBinary(char str[])
{
    int i, j, k = 0;

    printf("\nASCII Values:\n");
    for(i = 0; str[i] != '\0'; i++)
        printf("%c = %d\n", str[i], str[i]);

    printf("\nBinary Representation:\n");

    for(i = 0; str[i] != '\0'; i++)
    {
        for(j = 7; j >= 0; j--)
        {
            binary[k++] = ((str[i] >> j) & 1) + '0';
            printf("%c", binary[k - 1]);
        }
    }

    binary[k] = '\0';
    printf("\n");
}

void byteStuffing()
{
    char input[100];
    char stuffed[500];
    char FLAG = 'F';
    char ESC = 'E';
    int i, j = 0;

    printf("Enter a string: ");
    scanf("%s", input);

    stuffed[j++] = FLAG;

    for(i = 0; input[i] != '\0'; i++)
    {
        if(input[i] == FLAG || input[i] == ESC)
            stuffed[j++] = ESC;

        stuffed[j++] = input[i];
    }
    stuffed[j++] = FLAG;
    stuffed[j] = '\0';

    printf("\nByte Stuffed Frame:\n%s\n", stuffed);
    printf("\nBinary Form of Stuffed Frame:\n");
    stringToBinary(stuffed);
}

// Byte Destuffing
void byteDestuffing()
{
    char frame[500], destuffed[500];
    char FLAG = 'F';
    char ESC = 'E';
    int i, j = 0;
    int len;

    printf("Enter Stuffed Frame:\n");
    scanf("%s", frame);
    len = strlen(frame);

    for(i = 1; i < len - 1; i++)
    {
        if(frame[i] == ESC)
            i++;
        destuffed[j++] = frame[i];
    }
    destuffed[j] = '\0';

    printf("\nDestuffed Data:\n%s\n", destuffed);
    printf("\nBinary Form of Destuffed Data:\n");
    stringToBinary(destuffed);
}
int main()
{
    int choice;
    do{ 
        printf("\n   FRAMING PROTOCOL IMPLEMENTATION\n\n");
        printf("\n1. Byte Stuffing");
        printf("\n2. Byte Destuffing");
        printf("\n3. Exit");
        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {   
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
