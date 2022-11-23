#include <stdio.h>

int sum()
{
    float odin_add(float, float);
    float add(float, float);

    const int MAX_I = 5;
    const int MAX_J = 5;

    float x = 0.0;
    float y = 0.0;

    float odin_sum = odin_add(x, y);
    float sum = add(x, y);
    int i;
    int j;
    for (i = 0; i < MAX_I; i = i + 1)
    {
        for (j = 0; j < MAX_J; j = j + 1)
        {
            odin_sum = odin_sum + odin_add(x, y);
            sum = sum + add(x, y);
            y = y + 1;
        }
        x = x + 1;
    }

    return 0;
}

float add(float a, float b)
{
    float sum = a + b;
    printf("Adding: %f plus %f = %f", a, b, sum);
    return sum;
}