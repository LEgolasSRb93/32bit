#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    FILE *fp;
    float tempNum;
    int i = 0;

    fp = fopen("samples_float.bin", "rb");

    while(i<2000)
    {
        fread(&tempNum, sizeof(float), 1, fp);
        printf("%f\n", tempNum);
        i++;
    }

    // fscanf(fp, "%f", &tempNum);

    // while(fgetc(fp) != EOF)
    // {
        // printf("%f\n", tempNum);
        // fscanf(fp, "%f", &tempNum);
    // }

    printf("ende\n");

    return 0;
}
