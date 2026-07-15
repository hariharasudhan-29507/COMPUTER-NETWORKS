#include <stdio.h>
#include <string.h>

char binary[1000];


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

// Bit Stuffing
void bitStuffing()
{
    char input[100];
    char stuffed[2000];
    int i, j = 0, count = 0;

    printf("Enter a string: ");
    scanf("%s", input);

    stringToBinary(input);
    for(i = 0; binary[i] != '\0'; i++)
    {
        stuffed[j++] = binary[i];
        if(binary[i] == '1')
        {
            count++;
            if(count == 5)
            {
                stuffed[j++] = '0';
                count = 0;
            }
        }
        else
        {
            count = 0;
        }
    }

    stuffed[j] = '\0';
    printf("\nBit Stuffed Data:\n%s\n", stuffed);
}

// Bit Destuffing
void bitDestuffing()
{
    char stuffed[2000], destuffed[2000];
    int i, j = 0, count = 0;

    printf("Enter Stuffed Binary Data:\n");
    scanf("%s", stuffed);

    for(i = 0; stuffed[i] != '\0'; i++)
    {
        if(stuffed[i] == '1')
        {
            count++;
            destuffed[j++] = stuffed[i];
            if(count == 5)
            {
                i++; // Skip stuffed 0
                count = 0;
            }
        }
        else
        {
            count = 0;
            destuffed[j++] = stuffed[i];
        }
    }

    destuffed[j] = '\0';
    printf("\nDestuffed Binary:\n%s\n", destuffed);
}

int main()
{
    int choice;

    do
    {
        printf("\n====================================");
        printf("\n   FRAMING PROTOCOL IMPLEMENTATION");
        printf("\n====================================");
        printf("\n1. Bit Stuffing");
        printf("\n2. Bit Destuffing");
        printf("\n3. Exit");
        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                bitStuffing();
                break;

            case 2:
                bitDestuffing();
                break;

            case 3:
                printf("\nExiting Program...\n");
                break;

            default:
                printf("\nInvalid Choice!\n");
        }

    } while(choice != 5);

    return 0;
}
