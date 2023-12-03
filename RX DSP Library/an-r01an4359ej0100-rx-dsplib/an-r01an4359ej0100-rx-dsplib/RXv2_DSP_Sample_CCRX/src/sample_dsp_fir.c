/*******************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only 
* intended for use with Renesas products. No other uses are authorized. This 
* software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE 
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS 
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE 
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software
* and to discontinue the availability of this software. By using this software,
* you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer *
* Copyright (C) 2012 Renesas Electronics Corporation. All rights reserved.    
*******************************************************************************/
/*******************************************************************************
* File Name    : sample_dsp_fir.c
* Device(s)    : RX
* Tool-Chain   : e2studio 3.0.0.10, RX standard toolchain ver. 2.01.0
******************************************************************************/
/*****************************************************************************
* History      : YYYY.MM.DD  Version  Description
*              : 21.06.2012  1.00     First Release
*              : 2014.01.02  4.00     Fourth version
*              : 2017.11.06  4.20     Remove useless input setting on calculation
*              : 2018.07.11  5.00
******************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_dsp_filters.h"

/******************************************************************************
Macro definitions
******************************************************************************/
#define NUM_SAMPLES         (10)
#define NUM_TAPS            (10)
#define FRACTION_BITS       (15)
#define CONVERSION_CONST    ((uint16_t)(1<<FRACTION_BITS)-1)

/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Exported global variables (to be accessed by other files)
******************************************************************************/
 
/******************************************************************************
Private global variables and functions
******************************************************************************/
/* coeffients stored in time-reversed order */
static cplxi16_t myCoeffs[NUM_TAPS] =
{
    /* following coefficient format in Q1.15 */
    {(int16_t)(  0.0029024  * CONVERSION_CONST), (int16_t)((-0.0210426) * CONVERSION_CONST)}, /* h(9) */
    {(int16_t)(  0.0100975  * CONVERSION_CONST), (int16_t)((-0.0460262) * CONVERSION_CONST)}, /* h(8) */
    {(int16_t)(  0.0098667  * CONVERSION_CONST), (int16_t)((-0.0547532) * CONVERSION_CONST)}, /* h(7) */
    {(int16_t)(  0.0010075  * CONVERSION_CONST), (int16_t)((-0.0490032) * CONVERSION_CONST)}, /* h(6) */
    {(int16_t)((-0.0149086) * CONVERSION_CONST), (int16_t)((-0.0336059) * CONVERSION_CONST)}, /* h(5) */
    {(int16_t)((-0.0336059) * CONVERSION_CONST), (int16_t)((-0.0149086) * CONVERSION_CONST)}, /* h(4) */
    {(int16_t)((-0.0490032) * CONVERSION_CONST), (int16_t)(  0.0010075  * CONVERSION_CONST)}, /* h(3) */
    {(int16_t)((-0.0547532) * CONVERSION_CONST), (int16_t)(  0.0098667  * CONVERSION_CONST)}, /* h(2) */
    {(int16_t)((-0.0460262) * CONVERSION_CONST), (int16_t)(  0.0100975  * CONVERSION_CONST)}, /* h(1) */
    {(int16_t)((-0.0210426) * CONVERSION_CONST), (int16_t)(  0.0029024  * CONVERSION_CONST)}  /* h(0) */
};

/* state & two blocks of input,
   stored in time-sequential order */
static cplxi16_t inputData[(NUM_TAPS - 1) + (NUM_SAMPLES * 2)] =
{
    /* following input data format in Q1.15 */
    {0, 0}, /* x(-9), start of delayline */
    {0, 0}, /* x(-8) */
    {0, 0}, /* x(-7) */
    {0, 0}, /* x(-6) */
    {0, 0}, /* x(-5) */
    {0, 0}, /* x(-4) */
    {0, 0}, /* x(-3) */
    {0, 0}, /* x(-2) */
    {0, 0}, /* x(-1) */
    {(int16_t)(  1.0000 * CONVERSION_CONST), (int16_t)(  0.0000  * CONVERSION_CONST)}, /* x(0),start of 1st block input */
    {(int16_t)(  0.0530 * CONVERSION_CONST), (int16_t)(  0.2662  * CONVERSION_CONST)}, /* x(1) */
    {(int16_t)(  0.7877 * CONVERSION_CONST), (int16_t)((-0.3263) * CONVERSION_CONST)}, /* x(2) */
    {(int16_t)(  0.4080 * CONVERSION_CONST), (int16_t)(  0.6106  * CONVERSION_CONST)}, /* x(3) */
    {(int16_t)(  0.3210 * CONVERSION_CONST), (int16_t)((-0.3210) * CONVERSION_CONST)}, /* x(4) */
    {(int16_t)(  0.8155 * CONVERSION_CONST), (int16_t)(  0.5449  * CONVERSION_CONST)}, /* x(5) */
    {(int16_t)((-0.0300)* CONVERSION_CONST), (int16_t)(  0.0725  * CONVERSION_CONST)}, /* x(6) */
    {(int16_t)(  0.9202 * CONVERSION_CONST), (int16_t)(  0.1830  * CONVERSION_CONST)}, /* x(7) */
    {(int16_t)(  0.0000 * CONVERSION_CONST), (int16_t)(  0.5878  * CONVERSION_CONST)}, /* x(8) */
    {(int16_t)(  0.6072 * CONVERSION_CONST), (int16_t)((-0.1208) * CONVERSION_CONST)}, /* x(9) */
    {(int16_t)(  0.3536 * CONVERSION_CONST), (int16_t)(  0.8536  * CONVERSION_CONST)}, /* x(10),start of 2nd block input */
    {(int16_t)(  0.0977 * CONVERSION_CONST), (int16_t)((-0.0653) * CONVERSION_CONST)}, /* x(11) */
    {(int16_t)(  0.6984 * CONVERSION_CONST), (int16_t)(  0.6984  * CONVERSION_CONST)}, /* x(12) */
    {(int16_t)((-0.2326)* CONVERSION_CONST), (int16_t)(  0.3481  * CONVERSION_CONST)}, /* x(13) */
    {(int16_t)(  0.7025 * CONVERSION_CONST), (int16_t)(  0.2910  * CONVERSION_CONST)}, /* x(14) */
    {(int16_t)((-0.1622)* CONVERSION_CONST), (int16_t)(  0.8155  * CONVERSION_CONST)}, /* x(15) */
    {(int16_t)(  0.3090 * CONVERSION_CONST), (int16_t)(  0.0000  * CONVERSION_CONST)}, /* x(16) */
    {(int16_t)(  0.1949 * CONVERSION_CONST), (int16_t)(  0.9800  * CONVERSION_CONST)}, /* x(17) */
    {(int16_t)((-0.2157)* CONVERSION_CONST), (int16_t)(  0.0893  * CONVERSION_CONST)}, /* x(18) */
    {(int16_t)(  0.4847 * CONVERSION_CONST), (int16_t)(  0.7255  * CONVERSION_CONST)}, /* x(19) */
};

/* To store two blocks of output */
static cplxi16_t outputData[NUM_SAMPLES*2];

/******************************************************************************
* Function Name: sample_dsp_fir
* Description  : Sample code to demonstrate generic FIR filter
* Arguments    : none
* Return Value : status
******************************************************************************/
r_dsp_status_t sample_dsp_fir(void)
{
    r_dsp_status_t     myFIRFlags = R_DSP_STATUS_OK;
    r_dsp_firfilter_t  myFilterHandle;
    vector_t           myInput;
    vector_t           myOutput;

    /*--------------  Set up the FIR filter ------------*/
    myFilterHandle.taps  = NUM_TAPS;
    /* Scale should be set to the number of fraction bits of coefficients */
    myFilterHandle.scale.i32 = FRACTION_BITS;
    myFilterHandle.options = (R_DSP_SATURATE | R_DSP_ROUNDING_NEAREST);

    /* No need to call StateSize API for FIR, as it always return 0.
      The delayline & input share the same buffer. */
    myFilterHandle.state = (void *)&inputData[0]; // start of delay line

    /*----- Initialize the coefficients and internal state ------*/
    myFilterHandle.coefs = (void *)myCoeffs;
    myFIRFlags = R_DSP_FIR_Init_ci16ci16(&myFilterHandle); // initialize delay line
    if(R_DSP_STATUS_OK != myFIRFlags)
    {
        return myFIRFlags;
    }

    /*----------------  Set up the input/output  ----------------*/
    myInput.n = NUM_SAMPLES;
    myOutput.n = NUM_SAMPLES;

    /* outputData is an cplxi16_t type array. */
    myOutput.data = (void *)outputData;

    /*------------------  Wait for input data  ------------------*/
    
    /*---------------  Main library function call  --------------*/
    /* process 1st input block */
    myFIRFlags = R_DSP_FIR_ci16ci16(&myFilterHandle, &myInput, &myOutput);
    if(R_DSP_STATUS_OK != myFIRFlags)
    {
        return myFIRFlags;
    }

    /* process 2nd input block */
    myFilterHandle.state = (void *)&inputData[NUM_SAMPLES]; /* start of delay line for 2nd block */

    /* start of 2nd block output */
    myOutput.data = (void *)&outputData[NUM_SAMPLES];

    myFIRFlags = R_DSP_FIR_ci16ci16(&myFilterHandle, &myInput, &myOutput);
    
    /*---------------  Output data are now ready  ---------------
    * Note: At this point myOutput.n holds the number of output samples generated by
    * the library, where the data are written to the array pointed to by myOutput.data.
    *------------------------------------------------------------*/
    return myFIRFlags;
    
} /* End of function sample_dsp_fir() */

/* End of File */
