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
* Copyright (C) 2011 Renesas Electronics Corporation. All rights reserved.    
*******************************************************************************/
/*******************************************************************************
* File Name    : windowCoefficient_f32.h
* Description  : Coefficient data for FFT
******************************************************************************/
/*****************************************************************************
* History      : YYYY.MM.DD  Version  Description
*              : 21.06.2012  1.00     First Release
*              : 2014.01.02  4.00     Fourth version
******************************************************************************/

/******************************************************************************
Exported global variables
******************************************************************************/
const float rfft_tbl_window[] =
{
    0.000000,
    0.000054,
    0.000217,
    0.000489,
    0.000870,
    0.001360,
    0.001970,
    0.002680,
    0.003520,
    0.004470,
    0.005540,
    0.006730,
    0.008050,
    0.009490,
    0.011100,
    0.012800,
    0.014600,
    0.016600,
    0.018800,
    0.021000,
    0.023500,
    0.026100,
    0.028800,
    0.031800,
    0.034900,
    0.038200,
    0.041600,
    0.045300,
    0.049100,
    0.053100,
    0.057400,
    0.061800,
    0.066400,
    0.071300,
    0.076400,
    0.081700,
    0.087200,
    0.092900,
    0.098900,
    0.105000,
    0.112000,
    0.118000,
    0.125000,
    0.132000,
    0.140000,
    0.148000,
    0.155000,
    0.164000,
    0.172000,
    0.181000,
    0.190000,
    0.199000,
    0.208000,
    0.218000,
    0.228000,
    0.238000,
    0.249000,
    0.259000,
    0.270000,
    0.281000,
    0.293000,
    0.304000,
    0.316000,
    0.328000,
    0.340000,
    0.352000,
    0.365000,
    0.378000,
    0.391000,
    0.404000,
    0.417000,
    0.430000,
    0.444000,
    0.457000,
    0.471000,
    0.485000,
    0.499000,
    0.513000,
    0.527000,
    0.541000,
    0.555000,
    0.569000,
    0.583000,
    0.597000,
    0.611000,
    0.625000,
    0.639000,
    0.653000,
    0.667000,
    0.681000,
    0.695000,
    0.708000,
    0.722000,
    0.735000,
    0.748000,
    0.761000,
    0.774000,
    0.786000,
    0.798000,
    0.810000,
    0.822000,
    0.834000,
    0.845000,
    0.856000,
    0.866000,
    0.877000,
    0.887000,
    0.896000,
    0.905000,
    0.914000,
    0.923000,
    0.931000,
    0.939000,
    0.946000,
    0.953000,
    0.959000,
    0.965000,
    0.971000,
    0.976000,
    0.980000,
    0.984000,
    0.988000,
    0.991000,
    0.994000,
    0.996000,
    0.998000,
    0.999000,
    1.000000,
    1.000000,
    1.000000,
    0.999000,
    0.998000,
    0.996000,
    0.994000,
    0.991000,
    0.988000,
    0.984000,
    0.980000,
    0.976000,
    0.971000,
    0.965000,
    0.959000,
    0.953000,
    0.946000,
    0.939000,
    0.931000,
    0.923000,
    0.914000,
    0.905000,
    0.896000,
    0.887000,
    0.877000,
    0.866000,
    0.856000,
    0.845000,
    0.834000,
    0.822000,
    0.810000,
    0.798000,
    0.786000,
    0.774000,
    0.761000,
    0.748000,
    0.735000,
    0.722000,
    0.708000,
    0.695000,
    0.681000,
    0.667000,
    0.653000,
    0.639000,
    0.625000,
    0.611000,
    0.597000,
    0.583000,
    0.569000,
    0.555000,
    0.541000,
    0.527000,
    0.513000,
    0.499000,
    0.485000,
    0.471000,
    0.457000,
    0.444000,
    0.430000,
    0.417000,
    0.404000,
    0.391000,
    0.378000,
    0.365000,
    0.352000,
    0.340000,
    0.328000,
    0.316000,
    0.304000,
    0.293000,
    0.281000,
    0.270000,
    0.259000,
    0.249000,
    0.238000,
    0.228000,
    0.218000,
    0.208000,
    0.199000,
    0.190000,
    0.181000,
    0.172000,
    0.164000,
    0.155000,
    0.148000,
    0.140000,
    0.132000,
    0.125000,
    0.118000,
    0.112000,
    0.105000,
    0.098900,
    0.092900,
    0.087200,
    0.081700,
    0.076400,
    0.071300,
    0.066400,
    0.061800,
    0.057400,
    0.053100,
    0.049100,
    0.045300,
    0.041600,
    0.038200,
    0.034900,
    0.031800,
    0.028800,
    0.026100,
    0.023500,
    0.021000,
    0.018800,
    0.016600,
    0.014600,
    0.012800,
    0.011100,
    0.009490,
    0.008050,
    0.006730,
    0.005540,
    0.004470,
    0.003520,
    0.002680,
    0.001970,
    0.001360,
    0.000870,
    0.000489,
    0.000217,
    0.000054
};

/* End of File */
