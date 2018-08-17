#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include <stdio.h>
#include <stdlib.h>
#include "arm_math.h"
#include "arm_const_structs.h"
#include "math.h"

#define FILTER_SIZE 512
#define SAMPLES_SIZE 512
#define BLOCK_SIZE 16
#define NFFT	512
#define NSig 	512  	// Signal length

#define FIR		0


static float32_t firStateF32[BLOCK_SIZE + FILTER_SIZE +1];

int main()
{
    /**
    * Defines
    */
    FILE *fp;
    float32_t filter[FILTER_SIZE];
    float32_t samples[SAMPLES_SIZE];
    float32_t output[SAMPLES_SIZE];

    #if FIR
    arm_fir_instance_f32 S;
    uint32_t i;
    uint32_t blockSize = BLOCK_SIZE;
    uint32_t numBlocks = SAMPLES_SIZE/BLOCK_SIZE;
    #else
    /**
    *	fast fft
    */
    arm_rfft_fast_instance_f32 FFT;
    float32_t meanSignal = 0;

    uint32_t fftSize = 512;
    uint32_t ifftFlag = 0;
    uint32_t doBitReverse = 1;
    #endif



    #if FIR
    /**
    * Reading filter samples to buffer
    */
    fp = fopen("C:\\Users\\lazar\\Documents\\32bit\\samples_float.bin", "rb");
    if(fp == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    fread(samples, sizeof(samples), sizeof(samples)/sizeof(float32_t), fp);
    fclose(fp);

    /**
    * Reading filter samples to buffer
    */
    fp = fopen("C:\\Users\\lazar\\Documents\\32bit\\filterNorm_float.bin", "rb");
    if(fp == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    fread(filter, sizeof(filter), sizeof(filter)/sizeof(float32_t), fp);
    fclose(fp);

    printf("Reading data from files finished...\r\n");

    /**
    * Perform filtering function from arms library
    */
    arm_fir_init_f32(&S, FILTER_SIZE, (float32_t *)&filter[0], &firStateF32[0], blockSize);

    for( i = 0; i < numBlocks; i++)
    {
        arm_fir_f32(&S, samples + (i*blockSize), output + (i*blockSize), blockSize);
    }

    printf("Filtering with CMSIS filter function finished...\r\n");

    #else
    /**
    * Reading filter samples to buffer
    */
    fp = fopen("C:\\Users\\lazar\\Documents\\32bit\\samples_float.bin", "rb");
    if(fp == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    for(int i = 0; i < SAMPLES_SIZE; i+=2)
    {
        fread(&samples[i], sizeof(float32_t), 1, fp);
        samples[i+1] = 0;
    }
    fclose(fp);

    /**
    * Reading filter samples to buffer
    */
    fp = fopen("C:\\Users\\lazar\\Documents\\32bit\\filterPAD_float.bin", "rb");
    if(fp == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    for(int i = 0; i < SAMPLES_SIZE; i+=2)
    {
        fread(&filter[i], sizeof(float32_t), 1, fp);
        filter[i+1] = 0;
    }
    fclose(fp);

    printf("Reading data from files finished...\r\n");

    /* Process the data through the CFFT/CIFFT module */
    arm_cfft_f32(&arm_cfft_sR_f32_len256, samples, ifftFlag, doBitReverse);

    arm_cfft_f32(&arm_cfft_sR_f32_len256, filter, ifftFlag, doBitReverse);

    printf("Calculating FFT finished...\r\n");


    for(int i = 0; i < NFFT; i+=2)
    {
        //output[i/2] = sqrt(pow(samples[i] * filter[i] - samples[i+1] * filter[i+1], 2) + pow(samples[i] * filter[i+1] + samples[i+1] * filter[i], 2));
        output[i] = samples[i] * filter[i] - samples[i+1] * filter[i+1];
        output[i+1] = samples[i] * filter[i+1] + samples[i+1] * filter[i];
    }

    printf("Multiplication finished...\r\n");

    // Calculate IFFT
    arm_cfft_f32(&arm_cfft_sR_f32_len256, output, 1, doBitReverse);

    printf("Calculating IFFT finished...\r\n");

    #endif

    /**
    * Put results in file
    */
    fp = fopen("C:\\Users\\lazar\\Documents\\32bit\\output_float.bin", "wb");
    if(fp == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    //fwrite(output, sizeof(output), sizeof(output)/sizeof(float32_t), fp);
    for(int i = 0; i < NFFT; i+=2)
        fwrite(&output[i], sizeof(float32_t), 1, fp);
    fclose(fp);
    printf("Writing output to the file finished...\r\n");

    return 0;
}
