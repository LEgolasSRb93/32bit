#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include <stdio.h>
#include <stdlib.h>
#include "arm_math.h"

#define FILTER_SIZE 121
#define SAMPLES_SIZE 504
#define BLOCK_SIZE 16

static float32_t firStateF32[BLOCK_SIZE + FILTER_SIZE +1];

/* Reference index at which max energy of bin ocuurs */ 
uint32_t refIndex = 53, testIndex = 0; 

int main()
{
    /**
    * Defines
    */
    FILE *fp;
    float32_t filter[FILTER_SIZE];
    float32_t testOutput[SAMPLES_SIZE];
    float32_t samples[SAMPLES_SIZE];
    float32_t output[SAMPLES_SIZE];
//    arm_fir_instance_f32 S;
//    uint32_t i;
//    uint32_t blockSize = BLOCK_SIZE;
//    uint32_t numBlocks = SAMPLES_SIZE/BLOCK_SIZE;
    /* ------------------------------------------------------------------ 
    * Global variables for FFT Bin Example 
    * ------------------------------------------------------------------- */ 
    uint32_t fftSize = 256; 
    uint32_t ifftFlag = 0; 
    uint32_t doBitReverse = 0; 
    
    arm_status status; 
    arm_cfft_radix4_instance_f32 	CS;
    arm_rfft_instance_f32 		RS;
    float32_t maxValue; 
    
    status = ARM_MATH_SUCCESS; 
        
    
    /**
    * Reading filter samples to buffer
    */
    fp = fopen("C:\\Users\\lazar\\Documents\\32bit\\filter_float.bin", "rb");
    if(fp == NULL)
    {
      printf("Could not open file.\n");
      return 1;
    }
    fread(filter, sizeof(filter), sizeof(filter)/sizeof(float32_t), fp);
    fclose(fp);
   
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

    printf("Reading data from files finished...\r\n");
    
    
//    /* Initialize the CFFT/CIFFT module */  
//    status = arm_cfft_radix4_init_f32(&SF, fftSize, ifftFlag, doBitReverse); 
//    
//    /* Process the data through the CFFT/CIFFT module */ 
//    arm_cfft_radix4_f32(&SF, samples); 
//    
    /* Initialize the RFFT/RIFFT module */  
    status = arm_rfft_init_f32(&RS, &CS, fftSize, ifftFlag, doBitReverse); 
    
    /* Process the data through the RFFT/RIFFT module */ 
    arm_rfft_f32(&RS, samples, testOutput); 
    
    
//    /* Process the data through the Complex Magnitude Module for  
//    calculating the magnitude at each bin */ 
//    arm_cmplx_mag_f32(samples, testOutput, fftSize);  
//    
//    /* Calculates maxValue and returns corresponding BIN value */ 
//    arm_max_f32(testOutput, fftSize, &maxValue, &testIndex); 
//    
//    if(testIndex !=  refIndex) 
//    { 
//	status = ARM_MATH_TEST_FAILURE; 
//    } 
//    
//    /**
//    * Perform filtering function from arms library
//    */
//    arm_fir_init_f32(&S, FILTER_SIZE, (float32_t *)&filter[0], &firStateF32[0], blockSize);
//    
//    for( i = 0; i < numBlocks; i++)
//    {
//      arm_fir_f32(&S, samples + (i*blockSize), output + (i*blockSize), blockSize);
//    }
//    
//    printf("Filtering with CMSIS filter function finished...\r\n");
//    
    free(samples);
    free(filter);
    
    /**
    * Put results in file
    */
    fp = fopen("C:\\Users\\lazar\\Documents\\32bit\\samplesoutput_float.bin", "wb");
    if(fp == NULL)
    {
      printf("Could not open file.\n");
      return 1;
    }
    //fwrite(output, sizeof(output), sizeof(output)/sizeof(float32_t), fp);
    for(int i = 0; i < SAMPLES_SIZE; i++)
    	fwrite(&testOutput[i], sizeof(float32_t), 1, fp);
    fclose(fp);
    
    printf("Writing output samples to the file finished...\r\n");
    
    
    return 0;
}