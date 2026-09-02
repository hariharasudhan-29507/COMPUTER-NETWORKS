#include <stdio.h>
#include <string.h>

#define MAX 10
#define INF 999

int n;
char name[MAX][20];
int cost[MAX][MAX];
int nextHop[MAX][MAX];

void displayTable(int i)
{
    printf("\nRouting Table of Router %s\n", name[i]);
    printf("%-12s%-12s%-12s\n", "Destination", "Cost", "NextHop");
    for (int j = 0; j < n; j++)
    {
        if (i == j) continue;
        printf("%-12s", name[j]);
        if (cost[i][j] >= INF)
            printf("%-12s%-12s\n", "INF", "-");
        else
            printf("%-12d%-12s\n", cost[i][j], name[nextHop[i][j]]);
    }
}

void displayAllTables()
{
    for (int i = 0; i < n; i++)
        displayTable(i);
}

void displayMatrix(const char *title)
{
    printf("\n================ %s ================\n\n", title);
    printf("%-14s", "Info Stored");
    for (int j = 0; j < n; j++)
        printf("%-6s", name[j]);
    printf("\n");
    for (int i = 0; i < n; i++)
    {
        printf("%-14s", name[i]);
        for (int j = 0; j < n; j++)
        {
            if (cost[i][j] >= INF)
                printf("%-6s", "INF");
            else
                printf("%-6d", cost[i][j]);
        }
        printf("\n");
    }
}

void readInput()
{
    printf("Enter number of nodes: ");
    scanf("%d", &n);
    printf("Enter node names:\n");
    for (int i = 0; i < n; i++)
        scanf("%s", name[i]);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cost[i][j] = (i == j) ? 0 : INF;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            int link, c;
            printf("Is there a link between %s and %s? (1-Yes, 0-No): ", name[i], name[j]);
            scanf("%d", &link);
            if (link == 1)
            {
                printf("Enter cost: ");
                scanf("%d", &c);
                cost[i][j] = c;
                cost[j][i] = c;
            }
            else
            {
                cost[i][j] = INF;
                cost[j][i] = INF;
            }
        }
    }
}

void initTables()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                nextHop[i][j] = i;
            else if (cost[i][j] < INF)
                nextHop[i][j] = j;
            else
                nextHop[i][j] = -1;
        }
    }
}

void runDistanceVector()
{
    int updated = 1;
    while (updated)
    {
        updated = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (i == j || cost[i][j] >= INF)
                    continue;
                for (int k = 0; k < n; k++)
                {
                    if (i == k) continue;
                    if (cost[j][k] < INF &&
                        cost[i][j] + cost[j][k] < cost[i][k])
                    {
                        cost[i][k] = cost[i][j] + cost[j][k];
                        nextHop[i][k] = j;
                        updated = 1;
                    }
                }
            }
        }
    }
}

int main()
{
    readInput();
    initTables();
    displayMatrix("INITIAL ROUTING TABLE");
    runDistanceVector();
    int choice;
    do
    {
        printf("\n----- MENU -----\n");
        printf("1. Display final table of one router\n");
        printf("2. Display final tables of all routers\n");
        printf("3. Display final routing table (matrix form)\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        if (choice == 1)
        {
            char rname[20];
            printf("Enter router name: ");
            scanf("%s", rname);
            int idx = -1;
            for (int i = 0; i < n; i++)
                if (strcmp(name[i], rname) == 0) { idx = i; break; }
            if (idx == -1)
                printf("Invalid router name!\n");
            else
                displayTable(idx);
        }
        else if (choice == 2)
        {
            displayAllTables();
        }
        else if (choice == 3)
        {
            displayMatrix("FINAL ROUTING TABLE");
        }
    } while (choice != 4);
    printf("\nProgram terminated. Final result displayed above.\n");
    return 0;
}
