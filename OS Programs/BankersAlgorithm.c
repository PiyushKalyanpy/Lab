// Banker's Algorithm
#include <stdio.h>

int main()
{
    // Number of processes and resources
    int n = 5, m = 3;

    // Allocation matrix
    int alloc[5][3] = {
        {0, 1, 0},  // P0
        {2, 0, 0},  // P1
        {3, 0, 2},  // P2
        {2, 1, 1},  // P3
        {0, 0, 2}}; // P4

    // Maximum claim matrix
    int max[5][3] = {
        {7, 5, 3},  // P0
        {3, 2, 2},  // P1
        {9, 0, 2},  // P2
        {2, 2, 2},  // P3
        {4, 3, 3}}; // P4

    // Available resources vector
    int avail[3] = {3, 3, 2};

    // Finish array
    int fin[5];
    for (int i = 0; i < n; i++)
        fin[i] = 0;

    // Need matrix calculation
    int need[n][m];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    // Safe sequence array
    int ans[n], ind = 0;
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            if (fin[i] == 0)
            {
                int f = 0;
                for (int j = 0; j < m; j++)
                {
                    if (need[i][j] > avail[j])
                    {
                        f = 1;
                        break;
                    }
                }

                if (f == 0)
                {
                    ans[ind++] = i;
                    for (int y = 0; y < m; y++)
                        avail[y] += alloc[i][y];
                    fin[i] = 1;
                }
            }
        }
    }

    // Checking if a safe sequence exists
    int safe = 1;
    for (int i = 0; i < n; i++)
    {
        if (ans[i] != 1)
        {
            safe = 0;
            printf("No safe sequence exists\n");
            break;
        }
    }

    // Printing the safe sequence
    printf("Safe sequence: ");
    for (int i = 0; i < n - 1; i++)
        printf("P%d -> ", ans[i]);
    printf("P%d\n", ans[n - 1]);

    return 0;
}
