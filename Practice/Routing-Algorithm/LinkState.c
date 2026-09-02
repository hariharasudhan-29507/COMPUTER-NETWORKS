#include <stdio.h>
#include <string.h>

#define MAX 10
#define INF 999

int n;
char name[MAX][20];
int cost[MAX][MAX];
int dist[MAX][MAX];
int nextHop[MAX][MAX];

void displayLSP()
{
    printf("\n================ LINK STATE PACKETS (Direct Links) ================\n");
    for (int i = 0; i < n; i++)
    {
        printf("\nLSP of Router %s\n", name[i]);
        printf("%-12s%-12s\n", "Neighbor", "Cost");
        for (int j = 0; j < n; j++)
        {
            if (i == j) continue;
            if (cost[i][j] < INF)
                printf("%-12s%-12d\n", name[j], cost[i][j]);
        }
    }
}

void displayTable(int i)
{
    printf("\nRouting Table of Router %s\n", name[i]);
    printf("%-12s%-12s%-12s\n", "Destination", "Cost", "NextHop");
    for (int j = 0; j < n; j++)
    {
        if (i == j) continue;
        printf("%-12s", name[j]);
        if (dist[i][j] >= INF)
            printf("%-12s%-12s\n", "INF", "-");
        else
            printf("%-12d%-12s\n", dist[i][j], name[nextHop[i][j]]);
    }
}

void displayAllTables()
{
    for (int i = 0; i < n; i++)
        displayTable(i);
}

void displayMatrix(const char *title, int mat[MAX][MAX])
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
            if (mat[i][j] >= INF)
                printf("%-6s", "INF");
            else
                printf("%-6d", mat[i][j]);
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

void dijkstra(int s)
{
    int visited[MAX] = {0};
    for (int i = 0; i < n; i++)
    {
        dist[s][i] = cost[s][i];
        if (i != s && cost[s][i] < INF)
            nextHop[s][i] = i;
        else
            nextHop[s][i] = -1;
    }
    dist[s][s] = 0;
    nextHop[s][s] = s;
    visited[s] = 1;
    for (int count = 1; count < n; count++)
    {
        int u = -1, minDist = INF;
        for (int i = 0; i < n; i++)
        {
            if (!visited[i] && dist[s][i] < minDist)
            {
                minDist = dist[s][i];
                u = i;
            }
        }
        if (u == -1) break;
        visited[u] = 1;
        for (int v = 0; v < n; v++)
        {
            if (!visited[v] && cost[u][v] < INF &&
                dist[s][u] + cost[u][v] < dist[s][v])
            {
                dist[s][v] = dist[s][u] + cost[u][v];
                nextHop[s][v] = (u == s) ? v : nextHop[s][u];
            }
        }
    }
}

void runLinkState()
{
    for (int i = 0; i < n; i++)
        dijkstra(i);
}

int main()
{
    readInput();
    displayLSP();
    displayMatrix("INITIAL ROUTING TABLE", cost);
    runLinkState();

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
            displayMatrix("FINAL ROUTING TABLE", dist);
        }
    } while (choice != 4);
    printf("\nProgram terminated. Final result displayed above.\n");
    return 0;
}
