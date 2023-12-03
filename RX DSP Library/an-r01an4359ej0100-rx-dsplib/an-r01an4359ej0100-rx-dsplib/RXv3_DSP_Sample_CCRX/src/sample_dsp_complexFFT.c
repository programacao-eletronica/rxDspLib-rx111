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
* File Name    : sample_dsp_complexFFT.c
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
#include "r_dsp_transform.h"
#include "cFFT_in64_i16.h"

/******************************************************************************
Macro definitions
******************************************************************************/
#define FFT_POINTS          (64) /* 2^FFT_LOGN */
#define FFT_LOGN            (6)

/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Exported global variables (to be accessed by other files)
******************************************************************************/
 
/******************************************************************************
Private global variables and functions
******************************************************************************/
static cplxi16_t buf_freq[FFT_POINTS];
static cplxi16_t buf_inverse[FFT_POINTS];

/* cFFT_buf_time is an cplxi16_t type array. */
static vector_t vtime = {FFT_POINTS, (void *)cFFT_buf_time};

/* buf_freq is an cplxi16_t type array. */
static vector_t vfreq = {FFT_POINTS, (void *)buf_freq};

/* buf_inverse is an cplxi16_t type array. */
static vector_t vout = {FFT_POINTS, (void *)buf_inverse};

/* initialize portion of handle structure */
static r_dsp_fft_t h = {FFT_POINTS, 0 /* default options set */};

/* initialize required buffer sizes for twiddles etc. */
/* NOTE real-valued input specified! */
static size_t ntwb; // # bytes for twiddle array
static size_t nbrb; // # bytes for bit-reverse table
static size_t nwkb; // # bytes for work area

static cplxi16_t fft_twiddles[FFT_POINTS];
static int32_t fft_bitrev[(((FFT_POINTS - (1<<((FFT_LOGN+1)>>1)) - 2) >> 1) + 1)];

/******************************************************************************
* Function Name: sample_dsp_complexFFT
* Description  : Sample code to demonstrate complex FFT
* Arguments    : none
* Return Value : status
******************************************************************************/
r_dsp_status_t sample_dsp_complexFFT(void)
{
    r_dsp_status_t status = R_DSP_STATUS_OK;
    
    status = R_DSP_FFT_BufSize_ci16ci16(&h, &ntwb, &nbrb, &nwkb);
    if (R_DSP_STATUS_OK != status)
    {
        return status;
    }
    else {
        if (ntwb < (sizeof(fft_twiddles)))
        {
            while(1)
            {
                /* array size is not enough. */
                ;
            }
        }

        if (nbrb < (sizeof(fft_bitrev)))
        {
            while(1)
            {
                /* array size is not enough. */
                ;
            }
        }
    }

    /* now that we have the buffer sizes, allocate working buffers for reference */
    /*
    h.twiddles = ntwb ? malloc(ntwb) : NULL;
    h.bitrev = nbrb ? malloc(nbrb) : NULL;
    h.work = nwkb ? malloc(nbrb) : NULL;
    */
    h.n = FFT_POINTS;
    h.work = NULL;
    h.options = R_DSP_FFT_SCALE_DEFAULT;

    /* fft_bitrev is an int32_t type array. */
    h.bitrev = (void *)fft_bitrev;

    /* set R_DSP_FFT_OPT_NO_BITREV like h.options |= R_DSP_FFT_OPT_NO_BITREV, if you don't need bit-reverse */
    h.twiddles = (void *)fft_twiddles;
    h.window = NULL; // always NULL in Complex FFT
    
    /* now we can complete initialization of the handle */
    status = R_DSP_FFT_Init_ci16ci16(&h);
    if (R_DSP_STATUS_OK != status)
    {
        return status;
    }    

    /* Execute Forward Complex FFT */
    status = R_DSP_FFT_ci16ci16(&h, &vtime, &vfreq);
    if (R_DSP_STATUS_OK != status)
    {
        return status;
    }    

    /* Execute Inverse Complex FFT */
    /*
       the buffer sizes and the result of initialization of the handle
       are same as these of complex FFT, you don't need to call functions
       R_DSP_FFT_BufSize_i16ci16 && R_DSP_FFT_f32cf32 anymore
     */
    status = R_DSP_IFFT_ci16ci16(&h, &vfreq, &vout);
    if (R_DSP_STATUS_OK != status)
    {
        return status;
    }    

    /* Use an option to perform scaling (division by 2) at the output of every other stage (R_DSP_FFT_OPT_SCALE_X2) */
    /* The order of 64-point FFT is 6, so every result value is divided by 2*2*2=8 in this case. */
    h.options = R_DSP_FFT_OPT_SCALE_X2;
    status = R_DSP_IFFT_ci16ci16(&h, &vfreq, &vout);

    /* clean up */

    /*---------------  Output data are now ready  ---------------*/
    return status;
    
} /* End of function sample_dsp_complexFFT()*/

/* End of File */
