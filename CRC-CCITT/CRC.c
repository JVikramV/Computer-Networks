#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char rem[50], a[100], s[100], c, msj[50], gen[30];
    int i, genlen, t, j, flag = 0, k, n;

    printf("Enter the generator polynomial: ");
    fgets(gen, sizeof(gen), stdin);
    gen[strcspn(gen, "\n")] = '\0';  // remove newline

    printf("Generator polynomial (CRC-CCITT): %s\n", gen);

    genlen = strlen(gen);
    k = genlen - 1;

    printf("Enter the message: ");
    fgets(msj, sizeof(msj), stdin);
    msj[strcspn(msj, "\n")] = '\0';  // remove newline

    n = strlen(msj);

    // Copy message and append k zeros
    for (i = 0; i < n; i++)
        a[i] = msj[i];
    for (i = 0; i < k; i++)
        a[n + i] = '0';
    a[n + k] = '\0';

    printf("\nMessage polynomial appended with zeros:\n");
    puts(a);

    // Division step (mod-2 division)
    for (i = 0; i < n; i++)
    {
        if (a[i] == '1')
        {
            t = i;
            for (j = 0; j <= k; j++)
            {
                a[t] = (a[t] == gen[j]) ? '0' : '1';
                t++;
            }
        }
    }

    // Extract remainder
    for (i = 0; i < k; i++)
        rem[i] = a[n + i];
    rem[k] = '\0';

    printf("The checksum is:\n");
    puts(rem);

    // Message with checksum appended
    for (i = 0; i < n; i++)
        a[i] = msj[i];
    for (i = 0; i < k; i++)
        a[n + i] = rem[i];
    a[n + k] = '\0';

    printf("\nTransmitted message with checksum:\n");
    puts(a);

    // Receiver side
    printf("Enter the received message: ");
    fgets(s, sizeof(s), stdin);
    s[strcspn(s, "\n")] = '\0';  // remove newline
    n = strlen(s);

    // Perform division again
    for (i = 0; i < n - k; i++)
    {
        if (s[i] == '1')
        {
            t = i;
            for (j = 0; j <= k; j++, t++)
            {
                s[t] = (s[t] == gen[j]) ? '0' : '1';
            }
        }
    }

    // Check remainder
    flag = 0;
    for (i = n - k; i < n; i++)
    {
        if (s[i] == '1')
        {
            flag = 1;
            break;
        }
    }

    if (flag == 0)
        printf("Received polynomial is error-free.\n");
    else
        printf("Received polynomial contains an error.\n");

    return 0;
}
