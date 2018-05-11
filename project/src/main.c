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

#define ARM_MATH_CM4
#include "arm_math.h"

#define FILTER_SIZE 122
#define SAMPLES_SIZE 2000
#define MAX_BUFF 15

extern void initailse_monitor_handles(void);

int main(void)
{
	/**
	 * Defines
	 */
	FILE *fp;
//	float filter[FILTER_SIZE];
//	float samples[SAMPLES_SIZE];
	int i = 0; //, k = 0;
	float oneNum;
	char buff[MAX_BUFF];
	char tempCh;
	
	initialise_monitor_handles();

	printf("Hello world!\n");

	/**
	 * Reading from files to buffers
	 */
	fp = fopen("C:\\Users\\lazarc\\Documents\\32bit\\filter.txt", "r");
	if(fp == NULL)
	{
		printf("Could not open file.\n");
		return 1;
	}
	//fp = fopen("C:\\Users\\lazarc\\Documents\\32bit\\samples.txt", "r");
	//if(fp == NULL)
	//{
	//	printf("Could not open file.\n");
	//	return 1;
	//}
	
	// probaj ovo, ako ne bude moglo da se cita float po float
	tempCh = fgetc(fp);
	while(tempCh != EOF)
	{
		if(tempCh == '\n')
		{
			buff[i] = '\0';
			oneNum = atof(buff);
			//filter[k] = atof(buff);
			//k++;
			break;
		}
		else
		{
			buff[i] = tempCh;
			i++;
		}
	}

//	fgets(buff, 15, (FILE*)fp);
//	fscanf(fp, "%f", &oneNum);
	printf("%f\n", oneNum);

//	for( i = 0; i < FILTER_SIZE; i++)
//	{
//		fscanf(fp, "%f", filter[i]);
//		printf("%f\n", filter[i]);
//	}
//	for( i = 0; i < SAMPLES_SIZE; i++)
//	{
//		fscanf(fp, "%f", samples[i]);
//		printf("%f\n", samples[i]);
//	}

	/**
	 * Perform filtering function from arms library
	 */
	// here it goes
	// arm_fir_

	/**
	 * Put results in file
	 */

	/**
	 * Perform FFT on the samples, and on the filter coefficients
	 * Do the multiplying and do inverse FFT
	 */

	/**
	 * Put results in file
	 */

	for(;;);
}
