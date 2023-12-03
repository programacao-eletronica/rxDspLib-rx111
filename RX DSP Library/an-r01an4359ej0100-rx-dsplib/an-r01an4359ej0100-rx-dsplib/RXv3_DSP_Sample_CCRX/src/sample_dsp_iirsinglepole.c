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
* File Name    : sample_dsp_iirsinglepole.c
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
#include <stdlib.h>
#include "r_dsp_filters.h"

/******************************************************************************
Macro definitions
******************************************************************************/
#define INPUT_N             (10)
#define FRACTION_BITS       (31)
#define CONVERSION_CONST    ((uint32_t)(1<<FRACTION_BITS)-1) /* 0x7FFFFFFF */

/******************************************************************************
Typedef definitions
******************************************************************************/
static int32_t    gs_buff_out[INPUT_N];

/******************************************************************************
Exported global variables (to be accessed by other files)
******************************************************************************/
 
/******************************************************************************
Private global variables and functions
******************************************************************************/
static const int32_t gs_buff_in[INPUT_N] =
{
    /* following input data format in Q1.31 */
    (int32_t)(  1.0000000000000000 * CONVERSION_CONST), /* x(0) */
    (int32_t)(  0.0710197609601031 * CONVERSION_CONST), /* x(1) */
    (int32_t)(  0.5590169943749470 * CONVERSION_CONST), /* x(2) */
    (int32_t)(  0.4484011233337100 * CONVERSION_CONST), /* x(3) */
    (int32_t)((-0.2500000000000000)* CONVERSION_CONST), /* x(4) */
    (int32_t)(  0.5000000000000000 * CONVERSION_CONST), /* x(5) */
    (int32_t)((-0.5590169943749470)* CONVERSION_CONST), /* x(6) */
    (int32_t)((-0.1393841289587630)* CONVERSION_CONST), /* x(7) */
    (int32_t)((-0.2500000000000000)* CONVERSION_CONST), /* x(8) */
    (int32_t)((-0.8800367553350520)* CONVERSION_CONST), /* x(9) */
};

/******************************************************************************
* Function Name: sample_dsp_iirsinglepole
* Description  : Sample code to demonstrate single-pole IIR filter
* Arguments    : none
* Return Value : status
******************************************************************************/
r_dsp_status_t sample_dsp_iirsinglepole(void)
{
    r_dsp_status_t          result = R_DSP_STATUS_OK;
    vector_t                input;
    vector_t                output;
    int32_t                 state;
    int32_t                 coeff;
    r_dsp_iirsinglepole_t   handle;

    state = 0;

    /* coefficient format in Q1.31. */
    coeff = (int32_t)((-0.15) * CONVERSION_CONST);

    /*---------------------------*/
    /* Single-pole IIR filter    */
    /*---------------------------*/
    handle.scale.i32    = FRACTION_BITS;
    handle.options      = (R_DSP_NOSATURATE | R_DSP_ROUNDING_TRUNC);
    handle.coefs        = &coeff;
    handle.state        = &state;

    /*---------------------------*/
    /* Input data                */
    /*---------------------------*/
    input.n     = INPUT_N;

    /* gs_buff_in is an int32_t type array. */
    input.data  = (void*)gs_buff_in;

    /*---------------------------*/
    /* Output data               */
    /*---------------------------*/
    output.n    = INPUT_N;

    /* gs_buff_out is an int32_t type array. */
    output.data = (void *)gs_buff_out;

    result = R_DSP_IIRSinglePole_i32i32(&handle, &input, &output);

    return (result);

} /* End of function sample_dsp_iirsinglepole() */

/* End of File */
