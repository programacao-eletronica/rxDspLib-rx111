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
* File Name    : sample_dsp_main.c
* Device(s)    : RX
* Tool-Chain   : e2studio 3.0.0.10, RX standard toolchain ver. 2.01.0
* Description  : Main program to demonstrate RX DSP library
* Operation       : 1. Compile and download the sample code. Click 'Reset Go'
*                   to start the software.   
* Limitations  : 
******************************************************************************/
/*****************************************************************************
* History      : YYYY.MM.DD  Version  Description
*              : 21.06.2012  1.00     First Release
*              : 2014.01.02  4.00     Fourth version
*              : 2017.10.24  4.20     Change reference macro FPU_SUP to __FPU
*              : 2018.07.12  5.00
******************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_dsp_types.h"
#include "sample_dsp_main.h"

/******************************************************************************
Macro definitions
******************************************************************************/
#define MY_MIN_DSP_LIB_VERSION    (0x05000000u)      /* requires at least v5.0.0 (BCD format) */

/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Exported global variables (to be accessed by other files)
******************************************************************************/

/******************************************************************************
Private global variables and functions
******************************************************************************/
static uint32_t            myCurrentVersion;

/******************************************************************************
* Function Name: main
* Description  : The main function of RX DSP sample program
* Arguments    : none
* Return Value : none
******************************************************************************/
void main(void)
{
    r_dsp_status_t status = R_DSP_STATUS_OK;

    /*--------------  Get Library Version ------------------*/
    myCurrentVersion = R_DSP_GetVersion();
    if (MY_MIN_DSP_LIB_VERSION > myCurrentVersion) // correct version?
    {
        return;
    }

    /*--------------  Real FFT ----------------------------*/
#if __FPU == 1
    status = sample_dsp_realFFT();
    if(status < R_DSP_STATUS_OK)
    {
        return;
    }
#endif

    /*--------------  Complex FFT ------------------------*/
    status = sample_dsp_complexFFT();
    if (status < R_DSP_STATUS_OK)
    {
        return;
    }
    
    /*--------------  FIR filter -------------------------*/
    status = sample_dsp_fir();
    if (status < R_DSP_STATUS_OK)
    {
        return;
    }

    /*--------------  IIR Biquad filter ------------------*/
    status = sample_dsp_iirbiquad();
    if (status < R_DSP_STATUS_OK)
    {
        return;
    }

    /*--------------  IIR Single-pole filter ----------*/
    status = sample_dsp_iirsinglepole();
    if (status < R_DSP_STATUS_OK)
    {
        return;
    }

    while(1)
    {
        /* nop */
        ;
    };

} /* End of function main() */

/* End of File */
