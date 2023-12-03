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
* File Name    : sample_dsp_iirbiquad.c
* Device(s)    : RX
* Tool-Chain   : e2studio 3.0.0.10, RX standard toolchain ver. 2.01.0
******************************************************************************/
/*****************************************************************************
* History      : YYYY.MM.DD  Version  Description
*              : 21.06.2012  1.00     First Release
*              : 2014.01.02  4.00     Fourth version
*              : 2018.07.11  5.00
******************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_dsp_filters.h"

/******************************************************************************
Macro definitions
******************************************************************************/
#define NUM_SAMPLES                (10)
#define NUM_TAPS_PER_BIQUAD        (5) 
#define NUM_BIQUAD_STAGES          (2)
#define QINT                       (1)
#define FRACTION_BITS              (31)
#define COEFFS_CONVERSION_CONST    ((uint32_t)(1<<(FRACTION_BITS - QINT))-1)
#define INPUT_CONVERSION_CONST     ((uint32_t)(1<<FRACTION_BITS)-1)

/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Exported global variables (to be accessed by other files)
******************************************************************************/
 
/******************************************************************************
Private global variables and functions
******************************************************************************/
static const cplxi32_t myCoeffs[NUM_TAPS_PER_BIQUAD * NUM_BIQUAD_STAGES] =
{
    /* following coefficients format in Q(1+qint).(31-qint) */
    {(int32_t)(  0.0412535372417203  * COEFFS_CONVERSION_CONST), (int32_t)(  0                   * COEFFS_CONVERSION_CONST)}, /* b0 */
    {(int32_t)(  0.0484964426642926  * COEFFS_CONVERSION_CONST), (int32_t)((-0.0667496246335888) * COEFFS_CONVERSION_CONST)}, /* b1 */
    {(int32_t)((-0.0127480428242319) * COEFFS_CONVERSION_CONST), (int32_t)((-0.0392344458238619) * COEFFS_CONVERSION_CONST)}, /* b2 */
    {(int32_t)((-0.792903364023193 ) * COEFFS_CONVERSION_CONST), (int32_t)(  1.09133781802571    * COEFFS_CONVERSION_CONST)}, /* b3 */
    {(int32_t)((-0.158829124397261 ) * COEFFS_CONVERSION_CONST), (int32_t)((-0.488825834862321 ) * COEFFS_CONVERSION_CONST)}, /* b4 */
    {(int32_t)(  0.855930601814815   * COEFFS_CONVERSION_CONST), (int32_t)(  0                   * COEFFS_CONVERSION_CONST)}, /* a1 */
    {(int32_t)((-1.00620679173049  ) * COEFFS_CONVERSION_CONST), (int32_t)(  1.38492478957080    * COEFFS_CONVERSION_CONST)}, /* a2 */
    {(int32_t)((-0.264497075791865 ) * COEFFS_CONVERSION_CONST), (int32_t)((-0.814038384857019 ) * COEFFS_CONVERSION_CONST)}, /* a3 */
    {(int32_t)((-0.993942754008415 ) * COEFFS_CONVERSION_CONST), (int32_t)(  1.36804479034885    * COEFFS_CONVERSION_CONST)}, /* a4 */
    {(int32_t)((-0.226424773198911 ) * COEFFS_CONVERSION_CONST), (int32_t)((-0.696863873124631 ) * COEFFS_CONVERSION_CONST)}, /* a5 */
};

/* state to be stored in section-reversed order */
static cplxi32_t   myDLine[NUM_TAPS_PER_BIQUAD * NUM_BIQUAD_STAGES]; 

/* input stored in time-sequential order */
static cplxi32_t   inputData[NUM_SAMPLES] = 
{
    /* following input data format in Q1.31 */
    {(int32_t)(  0.0625               * INPUT_CONVERSION_CONST), (int32_t)(  0.0                  * INPUT_CONVERSION_CONST)}, /* x(0) */
    {(int32_t)(  0.0440845988319186   * INPUT_CONVERSION_CONST), (int32_t)(  0.0333673389948372   * INPUT_CONVERSION_CONST)}, /* x(1) */
    {(int32_t)(  0.010252390566028    * INPUT_CONVERSION_CONST), (int32_t)(  0.0346703130851088   * INPUT_CONVERSION_CONST)}, /* x(2) */
    {(int32_t)((-0.002828057179952  ) * INPUT_CONVERSION_CONST), (int32_t)(  0.0114719299456694   * INPUT_CONVERSION_CONST)}, /* x(3) */
    {(int32_t)(  0.00976214803848264  * INPUT_CONVERSION_CONST), (int32_t)((-0.00238711193338593) * INPUT_CONVERSION_CONST)}, /* x(4) */
    {(int32_t)(  0.0198136774573159   * INPUT_CONVERSION_CONST), (int32_t)(  0.00643785282684296  * INPUT_CONVERSION_CONST)}, /* x(5) */
    {(int32_t)(  0.00895367859952169  * INPUT_CONVERSION_CONST), (int32_t)(  0.0152374129789553   * INPUT_CONVERSION_CONST)}, /* x(6) */
    {(int32_t)((-0.00444181075510635) * INPUT_CONVERSION_CONST), (int32_t)(  0.00130225344483808  * INPUT_CONVERSION_CONST)}, /* x(7) */
    {(int32_t)(  0.0078397187881209   * INPUT_CONVERSION_CONST), (int32_t)((-0.0220226664533282 ) * INPUT_CONVERSION_CONST)}, /* x(8) */
    {(int32_t)(  0.0408825349841861   * INPUT_CONVERSION_CONST), (int32_t)((-0.0208961483210166 ) * INPUT_CONVERSION_CONST)}  /* x(9) */
};

/* To store 1 block of output */
static cplxi32_t outputData[NUM_SAMPLES];

/******************************************************************************
* Function Name: sample_dsp_iirbiquad
* Description  : Sample code to demonstrate generic biquad IIR filter
* Arguments    : none
* Return Value : status
******************************************************************************/
r_dsp_status_t sample_dsp_iirbiquad(void)
{
    r_dsp_status_t      myIIRFlags = R_DSP_STATUS_OK;
    r_dsp_iirbiquad_t   myFilterHandle;
    vector_t            myInput; // See introduction section describing the API document
    vector_t            myOutput; // for a definition of the vector data type
    int32_t             dynMemSize;
    int32_t             staMemSize;
    
    /*--------------  Set up the IIR filter biquads  ------------*/ 
    myFilterHandle.stages       = NUM_BIQUAD_STAGES;
    myFilterHandle.form         = R_DSP_BIQUAD_FORM_I;
 
    /* Setup data format and options */ 
    /* Scale should be set to the number of fraction bits of coefficients */
    myFilterHandle.scale.i32    = FRACTION_BITS; // convert Q2.62 product to Q1.31
    myFilterHandle.qint         = QINT; // coefficients and input all in Q2.30 when qint is 1
    myFilterHandle.options      = (R_DSP_SATURATE | R_DSP_ROUNDING_NEAREST);
 
    /* !!! It is important to setup the stages and the form before */ 
    /* !!! calling function R_DSP_IIRBiquad_StSize_xyyxyy() */ 
    staMemSize = NUM_TAPS_PER_BIQUAD * NUM_BIQUAD_STAGES * sizeof(cplxi32_t);
    dynMemSize = R_DSP_IIRBiquad_StateSize_ci32ci32(&myFilterHandle);
    if (staMemSize >= dynMemSize)
    { 
        /* myDLine is an cplxi32_t type array. */
        myFilterHandle.state = (void *)myDLine; // probably more common
    } 
    else {
        while(1)
        {
            /* state array size is not enough. */
            ;
        }
    } 
 
    /* Initialize the coefficients and internal state */ 
    myFilterHandle.coefs = (void *)myCoeffs;
    myIIRFlags = R_DSP_IIRBiquad_Init_ci32ci32(&myFilterHandle); 
    if(R_DSP_STATUS_OK != myIIRFlags)
    {
        return myIIRFlags;
    }
 
    /*----------------  Set up the input/output  ----------------*/
    myInput.n = NUM_SAMPLES;
    myOutput.n = NUM_SAMPLES;

    /* inputData is an cplxi32_t type array. */
    myInput.data  = (void *)inputData;

    /* outputData is an cplxi32_t type array. */
    myOutput.data = (void *)outputData;
 
    /*------------------  Wait for input data  ------------------*/
 
    /*---------------  Main library function call  --------------*/
    myIIRFlags = R_DSP_IIRBiquad_ci32ci32(&myFilterHandle, &myInput, &myOutput);
    
    /*---------------  Output data are now ready  ---------------
    * Note: At this point myOutput.n holds the number of output samples generated by
    * the library, where the data are written to the array pointed to by
    myOutput.data.
    *------------------------------------------------------------*/

    return myIIRFlags;
    
} /* End of function sample_dsp_iirbiquad() */

/* End of File */
