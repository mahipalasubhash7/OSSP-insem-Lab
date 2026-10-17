
#include <stdio.h>

int n, m;
int alloc[10][10], max[10][10], need[10][10];
int avail[10], work[10];
int finish[10] = {0}, safeSeq[10];
int count = 0, total = 0;

void findSafeSequences(int depth)
{
    int i, j, k;

    if (depth == n)
    {
        total++;
        printf("Safe Sequence %d: ", total);

        for (i = 0; i < n; i++)
            printf("P%d ", safeSeq[i]);

        printf("\n");
        return;
    }

    for (i = 0; i < n; i++)
    {
        if (!finish[i])
        {
            for (j = 0; j < m; j++)
                if (need[i][j] > work[j])
                    break;

            if (j == m)
            {
                for (k = 0; k < m; k++)
                    work[k] += alloc[i][k];

                finish[i] = 1;
                safeSeq[depth] = i;

                findSafeSequences(depth + 1);

                finish[i] = 0;

                for (k = 0; k < m; k++)
                    work[k] -= alloc[i][k];
            }
        }
    }
}

int main()
{
    int i, j;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    printf("Enter Allocation Matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Maximum Claim Matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
        {
            scanf("%d", &max[i][j]);
            need[i][j] = max[i][j] - alloc[i][j];
        }

    printf("Enter Available Resource Vector:\n");
    for (i = 0; i < m; i++)
    {
        scanf("%d", &avail[i]);
        work[i] = avail[i];
    }

    printf("\nNeed Matrix:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
            printf("%d ", need[i][j]);

        printf("\n");
    }

    printf("\nAll Safe Sequences:\n");
    findSafeSequences(0);

    if (total == 0)
        printf("System is in an UNSAFE state.\n");
    else
        printf("\nTotal Safe Sequences: %d\n", total);

    return 0;
}


