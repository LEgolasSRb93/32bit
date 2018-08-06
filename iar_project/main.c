#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include <stdio.h>
#include <stdlib.h>
#include "arm_math.h"

#define FILTER_SIZE 121
#define SAMPLES_SIZE 2016
#define BLOCK_SIZE 32

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
    arm_fir_instance_f32 S;
    uint32_t i;
    uint32_t blockSize = BLOCK_SIZE;
    uint32_t numBlocks = SAMPLES_SIZE/BLOCK_SIZE;
    
    
    /**
    * Reading filter samples to buffer
    */
    fp = fopen("C:\\Users\\lazarc\\Documents\\32bit\\filter_float.bin", "rb");
    if(fp == NULL)
    {
      printf("Could not open file.\n");
      return 1;
    }
    fread(filter, sizeof(filter), sizeof(filter)/sizeof(float32_t), fp);
    fclose(fp);
    
    /**
    * Reading data samples to buffer
    */
    fp = fopen("C:\\Users\\lazarc\\Documents\\32bit\\samples_float.bin", "rb");
    if(fp == NULL)
    {
      printf("Could not open file.\n");
      return 1;
    }
    fread(samples, sizeof(samples), sizeof(samples)/sizeof(float32_t), fp);
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
    
    
    
    /**
    * Put results in file
    */
    
    fp = fopen("C:\\Users\\lazarc\\Documents\\32bit\\output_float.bin", "wb");
    if(fp == NULL)
    {
      printf("Could not open file.\n");
      return 1;
    }
    
    for( i = 0; i < 2016; i++)
      fwrite(&output[i], sizeof(float32_t), 1, fp);
    
    //	fwrite(output, sizeof(output), sizeof(output)/sizeof(float32_t), fp);
    fclose(fp);
    
    printf("Writing output samples to the file finished...\r\n");
    
    
    return 0;
}