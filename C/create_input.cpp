#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int i;
    int n = 1000;
    double *data;
    FILE *f;

    data = (double*)malloc((size_t)n * sizeof(double));
    if (data == NULL) {
        fprintf(stderr, "Error: could not allocate memory.\n");
        return 1;
    }

    for (i = 0; i < n; ++i) {
        data[i] = (double)i;
    }

    f = fopen("input.bin", "wb");
    if (f == NULL) {
        fprintf(stderr, "Error: could not create input.bin\n");
        free(data);
        return 1;
    }

    if ((int)fwrite(data, sizeof(double), (size_t)n, f) != n) {
        fprintf(stderr, "Error: failed to write input.bin\n");
        fclose(f);
        free(data);
        return 1;
    }

    fclose(f);
    free(data);

    printf("Created input.bin with %d doubles (%zu bytes).\n",
           n, (size_t)n * sizeof(double));

    return 0;
}
