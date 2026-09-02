#include <stdio.h>
#include <string.h>

#define MAX 10
#define INF 999

int n;
char name[MAX][20];
int cost[MAX][MAX];
int linkCost[MAX][MAX];
int nextHop[MAX][MAX];
int pathCount;

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
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            linkCost[i][j] = cost[i][j];
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

void resetCost()
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cost[i][j] = linkCost[i][j];
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

void changeEdgeCost()
{
    char u[20], v[20];
    int newCost;
    printf("Enter first node: ");
    scanf("%s", u);
    printf("Enter second node: ");
    scanf("%s", v);
    int idx1 = -1, idx2 = -1;
    for (int i = 0; i < n; i++)
    {
        if (strcmp(name[i], u) == 0) idx1 = i;
        if (strcmp(name[i], v) == 0) idx2 = i;
    }
    if (idx1 == -1 || idx2 == -1 || idx1 == idx2)
    {
        printf("Invalid node names!\n");
        return;
    }
    if (linkCost[idx1][idx2] >= INF)
        printf("Current cost between %s and %s: INF (no direct link)\n", name[idx1], name[idx2]);
    else
        printf("Current cost between %s and %s: %d\n", name[idx1], name[idx2], linkCost[idx1][idx2]);
    printf("Enter new cost: ");
    scanf("%d", &newCost);
    linkCost[idx1][idx2] = newCost;
    linkCost[idx2][idx1] = newCost;
    resetCost();
    initTables();
    runDistanceVector();
    printf("Edge cost updated and routing table recalculated.\n");
    displayMatrix("FINAL ROUTING TABLE");
}

void dropEdge()
{
    char u[20], v[20];
    printf("Enter first node: ");
    scanf("%s", u);
    printf("Enter second node: ");
    scanf("%s", v);
    int idx1 = -1, idx2 = -1;
    for (int i = 0; i < n; i++)
    {
        if (strcmp(name[i], u) == 0) idx1 = i;
        if (strcmp(name[i], v) == 0) idx2 = i;
    }
    if (idx1 == -1 || idx2 == -1 || idx1 == idx2)
    {
        printf("Invalid node names!\n");
        return;
    }
    linkCost[idx1][idx2] = INF;
    linkCost[idx2][idx1] = INF;
    resetCost();
    initTables();
    runDistanceVector();
    printf("Edge dropped and routing table recalculated.\n");
    displayMatrix("FINAL ROUTING TABLE");
}

void printShortestPathBetweenNodes()
{
    char sname[20], dname[20];
    printf("Enter source router: ");
    scanf("%s", sname);
    printf("Enter destination router: ");
    scanf("%s", dname);
    int src = -1, dest = -1;
    for (int i = 0; i < n; i++)
    {
        if (strcmp(name[i], sname) == 0) src = i;
        if (strcmp(name[i], dname) == 0) dest = i;
    }
    if (src == -1 || dest == -1)
    {
        printf("Invalid router name(s)!\n");
        return;
    }
    if (src == dest)
    {
        printf("Source and destination are the same: %s\n", name[src]);
        return;
    }
    if (cost[src][dest] >= INF)
    {
        printf("No path exists from %s to %s\n", name[src], name[dest]);
        return;
    }
    printf("Shortest path from %s to %s (cost %d): ", name[src], name[dest], cost[src][dest]);
    int cur = src;
    printf("%s", name[cur]);
    while (cur != dest)
    {
        cur = nextHop[cur][dest];
        if (cur == -1)
        {
            printf(" -> [no path]");
            break;
        }
        printf(" -> %s", name[cur]);
    }
    printf("\n");
}

void findAllPathsUtil(int u, int dest, int visited[], int path[], int pathLen)
{
    visited[u] = 1;
    path[pathLen] = u;
    pathLen++;
    if (u == dest)
    {
        pathCount++;
        for (int i = 0; i < pathLen; i++)
        {
            printf("%s", name[path[i]]);
            if (i < pathLen - 1) printf(" -> ");
        }
        printf(" (cost: ");
        int totalCost = 0;
        for (int i = 0; i < pathLen - 1; i++)
            totalCost += linkCost[path[i]][path[i+1]];
        printf("%d)\n", totalCost);
    }
    else
    {
        for (int v = 0; v < n; v++)
        {
            if (!visited[v] && linkCost[u][v] < INF && u != v)
                findAllPathsUtil(v, dest, visited, path, pathLen);
        }
    }
    visited[u] = 0;
}

void printAllPathsBetweenNodes()
{
    char sname[20], dname[20];
    printf("Enter source router: ");
    scanf("%s", sname);
    printf("Enter destination router: ");
    scanf("%s", dname);
    int src = -1, dest = -1;
    for (int i = 0; i < n; i++)
    {
        if (strcmp(name[i], sname) == 0) src = i;
        if (strcmp(name[i], dname) == 0) dest = i;
    }
    if (src == -1 || dest == -1)
    {
        printf("Invalid router name(s)!\n");
        return;
    }
    if (src == dest)
    {
        printf("Source and destination are the same: %s\n", name[src]);
        return;
    }
    int visited[MAX] = {0};
    int path[MAX];
    pathCount = 0;
    printf("All possible paths from %s to %s:\n", name[src], name[dest]);
    findAllPathsUtil(src, dest, visited, path, 0);
    if (pathCount == 0)
        printf("No paths found.\n");
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
        printf("4. Change cost of an edge\n");
        printf("5. Drop an edge\n");
        printf("6. Print shortest path between two nodes\n");
        printf("7. Print all possible paths between two nodes\n");
        printf("8. Exit\n");
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
        else if (choice == 4)
        {
            changeEdgeCost();
        }
        else if (choice == 5)
        {
            dropEdge();
        }
        else if (choice == 6)
        {
            printShortestPathBetweenNodes();
        }
        else if (choice == 7)
        {
            printAllPathsBetweenNodes();
        }
    } while (choice != 8);
    printf("\nProgram terminated. Final result displayed above.\n");
    return 0;
}
