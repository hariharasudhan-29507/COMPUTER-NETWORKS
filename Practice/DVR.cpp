#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

#define MAX 10
#define INF 999

int n;
string name[MAX];
int cost[MAX][MAX];
int nextHop[MAX][MAX];

void displayTable(int i)
{
    cout << "\nRouting Table of Router " << name[i] << "\n";
    cout << left << setw(12) << "Destination" << setw(12) << "Cost" << setw(12) << "NextHop" << "\n";
    for (int j = 0; j < n; j++)
    {
        if (i == j) continue;
        cout << left << setw(12) << name[j];

        if (cost[i][j] >= INF)
            cout << left << setw(12) << "INF" << setw(12) << "-" << "\n";
        else
            cout << left << setw(12) << cost[i][j] << setw(12) << name[nextHop[i][j]] << "\n";
    }
}

void displayAllTables()
{
    for (int i = 0; i < n; i++)
        displayTable(i);
}

void displayMatrix(const string &title)
{
    cout << "\n================ " << title << " ================\n\n";

    cout << left << setw(14) << "Info Stored";
    for (int j = 0; j < n; j++)
        cout << left << setw(6) << name[j];
    cout << "\n";

    for (int i = 0; i < n; i++)
    {
        cout << left << setw(14) << name[i];
        for (int j = 0; j < n; j++)
        {
            if (cost[i][j] >= INF)
                cout << left << setw(6) << "INF";
            else
                cout << left << setw(6) << cost[i][j];
        }
        cout << "\n";
    }
}

void readInput()
{
    cout << "Enter number of nodes: ";
    cin >> n;

    cout << "Enter node names:\n";
    for (int i = 0; i < n; i++)
        cin >> name[i];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cost[i][j] = (i == j) ? 0 : INF;

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            int link, c;
            cout << "Is there a link between " << name[i] << " and " << name[j] << "? (1-Yes, 0-No): ";
            cin >> link;

            if (link == 1)
            {
                cout << "Enter cost: ";
                cin >> c;
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

    displayMatrix("FINAL ROUTING TABLE");

    int choice;
    do
    {
        cout << "\n----- MENU -----\n";
        cout << "1. Display final table of one router\n";
        cout << "2. Display final tables of all routers\n";
        cout << "3. Display final routing table (matrix form)\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            string rname;
            cout << "Enter router name: ";
            cin >> rname;

            int idx = -1;
            for (int i = 0; i < n; i++)
                if (name[i] == rname) { idx = i; break; }

            if (idx == -1)
                cout << "Invalid router name!\n";
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

    cout << "\nProgram terminated. Final result displayed above.\n";
    return 0;
}
