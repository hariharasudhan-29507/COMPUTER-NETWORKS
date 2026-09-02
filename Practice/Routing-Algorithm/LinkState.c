#include <stdio.h>
#include <string.h>

#define MAX 10
#define INF 999

int n;
char name[MAX][20];
int linkCost[MAX][MAX];
int dist[MAX][MAX];
int nextHop[MAX][MAX];
int pathCount;

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
            if (linkCost[i][j] < INF)
                printf("%-12s%-12d\n", name[j], linkCost[i][j]);
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
            linkCost[i][j] = (i == j) ? 0 : INF;
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
                linkCost[i][j] = c;
                linkCost[j][i] = c;
            }
            else
            {
                linkCost[i][j] = INF;
                linkCost[j][i] = INF;
            }
        }
    }
}

void dijkstra(int s)
{
    int visited[MAX] = {0};
    for (int i = 0; i < n; i++)
    {
        dist[s][i] = linkCost[s][i];
        if (i != s && linkCost[s][i] < INF)
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
            if (!visited[v] && linkCost[u][v] < INF &&
                dist[s][u] + linkCost[u][v] < dist[s][v])
            {
                dist[s][v] = dist[s][u] + linkCost[u][v];
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
        printf("Existing cost between %s and %s: INF (no direct link)\n", name[idx1], name[idx2]);
    else
        printf("Existing cost between %s and %s: %d\n", name[idx1], name[idx2], linkCost[idx1][idx2]);
    printf("Enter new cost: ");
    scanf("%d", &newCost);
    linkCost[idx1][idx2] = newCost;
    linkCost[idx2][idx1] = newCost;
    runLinkState();
    printf("Edge cost updated and routing table recalculated.\n");
    displayMatrix("FINAL ROUTING TABLE", dist);
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
    runLinkState();
    printf("Edge dropped and routing table recalculated.\n");
    displayMatrix("FINAL ROUTING TABLE", dist);
}

void printShortestPath()
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
    if (dist[src][dest] >= INF)
    {
        printf("No path exists from %s to %s\n", name[src], name[dest]);
        return;
    }
    printf("Shortest path from %s to %s (cost %d): ", name[src], name[dest], dist[src][dest]);
    int cur = src;
    printf("%s", name[cur]);
    int hops = 0;
    while (cur != dest)
    {
        if (nextHop[cur][dest] == -1 || hops > n)
        {
            printf(" -> [no path]");
            break;
        }
        cur = nextHop[cur][dest];
        printf(" -> %s", name[cur]);
        hops++;
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
        int totalCost = 0;
        for (int i = 0; i < pathLen - 1; i++)
        {
            printf("%s", name[path[i]]);
            if (i < pathLen - 1)
            {
                printf(" -> ");
                totalCost += linkCost[path[i]][path[i+1]];
            }
        }
        printf("%s (cost: %d)\n", name[dest], totalCost);
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

void printAllPaths()
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
    displayLSP();
    displayMatrix("INITIAL ROUTING TABLE", linkCost);
    runLinkState();
    displayMatrix("FINAL ROUTING TABLE", dist);
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
            displayMatrix("FINAL ROUTING TABLE", dist);
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
            printShortestPath();
        }
        else if (choice == 7)
        {
            printAllPaths();
        }
    } while (choice != 8);
    printf("\nProgram terminated. Final result displayed above.\n");
    return 0;
}
