#include <stdio.h>

int main() {
    // Get input for the number of processes and resources
    int n, m;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the number of resources: ");
    scanf("%d", &m);

    // Allocate memory for the matrices
    int alloc[n][m], max[n][m], avail[m], fin[n], ans[n];

    // Get input for the allocation matrix
    printf("\nEnter the allocation matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    // Get input for the maximum claim matrix
    printf("\nEnter the maximum claim matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Get input for the available resources vector
    printf("\nEnter the available resources vector:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
    }

    // Calculate the need matrix
    int need[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    // Initialize the finish array
    for (int i = 0; i < n; i++) {
        fin[i] = 0;
    }

    // Find a safe sequence using the Banker's algorithm
    int safe = 1, ind = 0;
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (fin[i] == 0) {
                int f = 0;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]) {
                        f = 1;
                        break;
                    }
                }

                if (f == 0) {
                    ans[ind++] = i;
                    for (int y = 0; y < m; y++) {
                        avail[y] += alloc[i][y];
                    }
                    fin[i] = 1;
                }
            }
        }
    }

    // Check if a safe sequence exists
    if (!safe) {
        printf("No safe sequence exists.\n");
        return 0;
    }

    // Print the safe sequence
    printf("Safe sequence: ");
    for (int i = 0; i < n - 1; i++) {
        printf("P%d -> ", ans[i]);
    }
    printf("P%d\n", ans[n - 1]);

    return 0;
}
