#include <stdio.h>

void printbits(int arr[], int len)
{
    int i;
    for(i=0;i<len;i++)
        printf("%d", arr[i]);
    printf("\n");
}

int main()
{
    int a[100], b[300], c[300], d[300], e[300];
    int n, i, j, k, count;
    int stufflen, translen, destufflen;
    int parity, rparity;
    int numerrors, pos;

    printf("Enter number of bits in original data: ");
    scanf("%d", &n);
    printf("Enter the bits (0 or 1) one by one:\n");
    for(i=0;i<n;i++)
        scanf("%d", &a[i]);

    j=0;
    count=0;
    for(i=0;i<n;i++)
    {
        b[j]=a[i];
        j++;
        if(a[i]==1)
        {
            count++;
            if(count==5)
            {
                b[j]=0;
                j++;
                count=0;
            }
        }
        else
        {
            count=0;
        }
    }
    stufflen=j;

    parity=0;
    for(i=0;i<stufflen;i++)
    {
        c[i]=b[i];
        parity=parity^b[i];
    }
    c[stufflen]=parity;
    translen=stufflen+1;

    for(i=0;i<translen;i++)
        d[i]=c[i];

    printf("Enter number of bit errors to introduce (0 for none): ");
    scanf("%d", &numerrors);
    for(k=0;k<numerrors;k++)
    {
        printf("Enter position of error bit (0 to %d): ", translen-1);
        scanf("%d", &pos);
        if(pos>=0 && pos<translen)
            d[pos]=1-d[pos];
    }

    rparity=0;
    for(i=0;i<stufflen;i++)
        rparity=rparity^d[i];

    j=0;
    count=0;
    for(i=0;i<stufflen;i++)
    {
        if(count==5)
        {
            count=0;
            continue;
        }
        e[j]=d[i];
        j++;
        if(d[i]==1)
            count++;
        else
            count=0;
    }
    destufflen=j;

    printf("\nOriginal data:      ");
    printbits(a, n);

    printf("Stuffed frame:      ");
    printbits(b, stufflen);

    printf("Transmitted frame:  ");
    printbits(c, translen);

    printf("Received frame:     ");
    printbits(d, translen);

    printf("Destuffed data:     ");
    printbits(e, destufflen);

    printf("\nComputed parity at receiver: %d\n", rparity);
    printf("Parity bit received:         %d\n", d[stufflen]);

    if(rparity!=d[stufflen])
        printf("Error detection status: ERROR detected in transmission\n");
    else
        printf("Error detection status: No error detected, data received correctly\n");

    return 0;
}
