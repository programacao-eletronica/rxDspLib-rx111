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
* File Name    : sample_dsp_realFFT.c
* Device(s)    : RX
* Tool-Chain   : e2studio 3.0.0.10, RX standard toolchain ver. 2.01.0
******************************************************************************/
/*****************************************************************************
* History      : YYYY.MM.DD  Version  Description
*              : 21.06.2012  1.00     First Release
*              : 2014.01.02  4.00     Fourth version
*              : 2017.10.24  4.20     Change reference macro FPU_SUP to __FPU
*              : 2018.07.11  5.00
******************************************************************************/
#if __FPU == 1
/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_dsp_transform.h"
#include "rFFT_in256_f32.h"
#include "windowCoefficient_f32.h"

/******************************************************************************
Macro definitions
******************************************************************************/
#define FFT_POINTS          (256) /* 2^FFT_LOGN */
#define FFT_LOGN            (8)

/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Exported global variables (to be accessed by other files)
******************************************************************************/
 
/******************************************************************************
Private global variables and functions
******************************************************************************/
static cplxf32_t buf_freq[FFT_POINTS/2];
static float buf_inverse[FFT_POINTS];

/* rFFT_buf_time is an float type array. */
static vector_t vtime = {FFT_POINTS, (void *)rFFT_buf_time};

/* buf_freq is an float type array. */
static vector_t vfreq = {FFT_POINTS/2, (void *)buf_freq}; // half the samples if treated as complex.

/* buf_inverse is an float type array. */
static vector_t vout = {FFT_POINTS, (void *)buf_inverse};

/* initialize portion of handle structure */
static r_dsp_fft_t h = {FFT_POINTS, 0 /* default options set */};

/* initialize required buffer sizes for twiddles etc. */
/* NOTE real-valued input specified! */
static size_t ntwb; // # bytes for twiddle array
static size_t nbrb; // # bytes for bit-reverse table
static size_t nwkb; // # bytes for work area

static cplxf32_t fft_twiddles[(FFT_POINTS/2) + (FFT_POINTS/4)];
static int32_t fft_bitrev[((((FFT_POINTS>>1) - (1<<(FFT_LOGN>>1)) - 2) >> 1) + 1)];

/******************************************************************************
* Function Name: sample_dsp_realFFT
* Description  : Sample code to demonstrate real FFT
* Arguments    : none
* Return Value : status
******************************************************************************/
r_dsp_status_t sample_dsp_realFFT(void)
{
    r_dsp_status_t status = R_DSP_STATUS_OK;
    
    status = R_DSP_FFT_BufSize_f32cf32(&h, &ntwb, &nbrb, &nwkb);
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
    h.options = 0;

    /* fft_bitrev is an int32_t type array. */
    h.bitrev = (void *)fft_bitrev;

    /* set R_DSP_FFT_OPT_NO_BITREV if you don't need bit-reverse like h.options |= R_DSP_FFT_OPT_NO_BITREV */
    h.twiddles = (void *)fft_twiddles;

    /* set NULL if you don't need windowing */
    h.window = (void *)rfft_tbl_window;

    /* now we can complete initialization of the handle */
    /* NOTE real-valued input specified in the function name */
    status = R_DSP_FFT_Init_f32cf32(&h);
    if (R_DSP_STATUS_OK != status)
    {
        return status;
    }    

    status = R_DSP_FFT_f32cf32(&h, &vtime, &vfreq);
    if (R_DSP_STATUS_OK != status)
    {
        return status;
    }    
    
    h.n = FFT_POINTS;
    h.window = NULL; // Do not refer in Inverse Complex-Conjugate-Symmetric Inverse FFT

    /* now re-initialization of the handle */
    status = R_DSP_FFT_Init_cf32f32(&h);
    if (R_DSP_STATUS_OK != status)
    {
        return status;
    }    
    
    status = R_DSP_IFFT_CCS_cf32f32(&h, &vfreq, &vout);

    /* clean up */
    /*
    if (h.work != NULL) {
        free(h.work);
    }
    */
    
    /*---------------  Output data are now ready  ---------------*/
    return status;
    
} /* End of function sample_dsp_realFFT() */
#endif /* __FPU */

/* End of File */
