/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    10-February-2018
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include <stdio.h>
#include <stdlib.h>

//#define ARM_MATH_CM4
#include "arm_math.h"
//#include "arm_const_structs.h"

#define FILTER_SIZE 121
#define SAMPLES_SIZE 2016
#define BLOCK_SIZE 32

extern void initialise_monitor_handles(void);

static float32_t firStateF32[BLOCK_SIZE + FILTER_SIZE +1];

int main(void)
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

	initialise_monitor_handles();

	printf("Hello world!\n");

	/**
	 * Reading from files to buffers
	 */
	fp = fopen("/home/lazarc/Documents/Faks/32bit/filter_float.bin", "rb");
	if(fp == NULL)
	{
		printf("Could not open file.\n");
		return 1;
	}

	fread(filter, sizeof(filter), sizeof(filter)/sizeof(float32_t), fp);

	fclose(fp);

	fp = fopen("/home/lazarc/Documents/Faks/32bit/samples_float.bin", "rb");
	if(fp == NULL)
	{
		printf("Could not open file.\n");
		return 1;
	}

	fread(samples, sizeof(samples), sizeof(samples)/sizeof(float32_t), fp);

	fclose(fp);

	printf("Ucitavanje i inicijalizacija(ende)\n");

	/**
	 * Perform filtering function from arms library
	 */
	arm_fir_init_f32(&S, FILTER_SIZE, (float32_t *)&filter[0], &firStateF32[0], blockSize);

	for( i = 0; i < numBlocks; i++)
	{
		arm_fir_f32(&S, samples + (i*blockSize), output + (i*blockSize), blockSize);
	}

	printf("Filtriranje (ende)\n");

	/**
	 * Put results in file
	 */

	fp = fopen("/home/lazarc/Documents/Faks/32bit/output_float.bin", "wb");
	if(fp == NULL)
	{
		printf("Could not open file.\n");
		return 1;
	}

	for( i = 0; i < 2016; i++)
		fwrite(&output[i], sizeof(float32_t), 1, fp);

//	fwrite(output, sizeof(output), sizeof(output)/sizeof(float32_t), fp);
	fclose(fp);

	printf("Ispis(ende)\n");

	/**
	 * Perform FFT on the samples, and on the filter coefficients
	 * Do the multiplying and do inverse FFT
	 */

	/**
	 * Put results in file
	 */

	for(;;);
}
