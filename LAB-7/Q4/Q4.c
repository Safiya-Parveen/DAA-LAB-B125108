#include <stdio.h>

int main()
{
    int n;
    printf("Enter number of switches: ");
    scanf("%d", &n);

    int a[20];

    // Initially all switches are ON
    for (int i = 0; i < n; i++)
        a[i] = 1;

    int moves = 0;

    while (1)
    {
        int done = 1;

        // Check whether all are OFF
        for (int i = 0; i < n; i++)
        {
            if (a[i] == 1)
            {
                done = 0;
                break;
            }
        }

        if (done)
            break;

        /*
           Start from the rightmost switch.
           A switch can be toggled if:
           - it is the rightmost switch, OR
           - immediate right switch is ON
           - all switches after that are OFF
        */

        for (int i = n - 1; i >= 0; i--)
        {
            int allowed = 1;

            if (i != n - 1)
            {
                if (a[i + 1] == 0)
                    allowed = 0;

                for (int j = i + 2; j < n; j++)
                {
                    if (a[j] == 1)
                    {
                        allowed = 0;
                        break;
                    }
                }
            }

            if (allowed)
            {
                // Toggle the switch
                if (a[i] == 1)
                    a[i] = 0;
                else
                    a[i] = 1;

                moves++;
                break;
            }
        }
    }

    printf("Minimum number of moves = %d\n", moves);

    return 0;
}