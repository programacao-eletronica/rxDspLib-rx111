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
* File Name    : rFFT_in256_f32.h
* Description  : input data for real FFT
******************************************************************************/
/*****************************************************************************
* History      : YYYY.MM.DD  Version  Description
*              : 21.06.2012  1.00     First Release
*              : 2014.01.02  4.00     Fourth version
******************************************************************************/

/******************************************************************************
Macro definitions
******************************************************************************/

/******************************************************************************
Exported global variables
******************************************************************************/
const float rFFT_buf_time[] =
{
    2.911345,
    6.463021,
    9.591833,
    12.115864,
    13.899816,
    14.864467,
    14.991436,
    14.322877,
    12.956190,
    11.034286,
    8.732257,
    6.241704,
    3.754082,
    1.444545,
    -0.542295,
    -2.103477,
    -3.184718,
    -3.782812,
    -3.943240,
    -3.753294,
    -3.331398,
    -2.813663,
    -2.338959,
    -2.033903,
    -1.999175,
    -2.298464,
    -2.951057,
    -3.928812,
    -5.157795,
    -6.524481,
    -7.885962,
    -9.083267,
    -9.956574,
    -10.360957,
    -10.181190,
    -9.344276,
    -7.828486,
    -5.668057,
    -2.953040,
    0.175772,
    3.536462,
    6.919389,
    10.103257,
    12.872499,
    15.034488,
    16.435122,
    16.971416,
    16.600048,
    15.341068,
    13.276501,
    10.543909,
    7.325496,
    3.833654,
    0.294212,
    -3.071201,
    -6.062178,
    -8.514503,
    -10.311825,
    -11.393065,
    -11.755020,
    -11.449964,
    -10.578578,
    -9.278891,
    -7.712266,
    -6.047749,
    -4.446184,
    -3.045551,
    -1.948832,
    -1.215476,
    -0.857211,
    -0.838539,
    -1.081826,
    -1.476485,
    -1.891355,
    -2.189127,
    -2.241429,
    -1.943165,
    -1.224748,
    -0.061038,
    1.523855,
    3.456438,
    5.618427,
    7.855718,
    9.990990,
    11.838839,
    13.222131,
    13.988111,
    14.022840,
    13.262627,
    11.701445,
    9.393576,
    6.451217,
    3.037186,
    -0.646712,
    -4.374694,
    -7.914135,
    -11.043409,
    -13.568901,
    -15.339787,
    -16.259317,
    -16.291668,
    -15.463810,
    -13.862245,
    -11.624953,
    -8.929258,
    -5.976685,
    -2.976148,
    -0.126927,
    2.397104,
    4.460646,
    5.976436,
    6.910237,
    7.280990,
    7.156199,
    6.643044,
    5.876093,
    5.002785,
    4.168049,
    3.499490,
    3.094509,
    3.010563,
    3.259436,
    3.806070,
    4.572051,
    5.443437,
    6.282200,
    6.940236,
    7.274638,
    7.162828,
    6.516116,
    5.290418,
    3.493098,
    1.185228,
    -1.520991,
    -4.469537,
    -7.471995,
    -10.322186,
    -12.812738,
    -14.752199,
    -15.981182,
    -16.386162,
    -15.909685,
    -14.556087,
    -12.392209,
    -9.542988,
    -6.182299,
    -2.519781,
    1.215227,
    4.791300,
    7.992601,
    10.635129,
    12.580174,
    13.743884,
    14.102149,
    13.690468,
    12.598853,
    10.962300,
    8.947694,
    6.738366,
    4.517681,
    2.453114,
    0.682228,
    -0.698227,
    -1.639167,
    -2.141423,
    -2.253232,
    -2.063286,
    -1.690008,
    -1.268112,
    -0.933709,
    -0.809380,
    -0.990607,
    -1.534865,
    -2.454395,
    -3.713375,
    -5.229781,
    -6.881818,
    -8.518372,
    -9.972554,
    -11.077157,
    -11.680598,
    -11.661925,
    -10.943508,
    -9.500207,
    -7.364175,
    -4.624761,
    -1.423460,
    2.055726,
    5.599748,
    8.982675,
    11.983212,
    14.402079,
    16.077784,
    16.899431,
    16.815485,
    15.837730,
    14.040099,
    11.552478,
    8.550019,
    5.238904,
    1.839763,
    -1.429811,
    -4.372169,
    -6.824495,
    -8.670435,
    -9.847514,
    -10.349770,
    -10.225440,
    -9.570009,
    -8.515291,
    -7.215604,
    -5.832312,
    -4.518169,
    -3.402888,
    -2.581241,
    -2.104763,
    -1.977793,
    -2.158180,
    -2.562562,
    -3.075717,
    -3.563076,
    -3.885245,
    -3.913150,
    -3.542397,
    -2.705483,
    -1.380679,
    0.403272,
    2.567151,
    4.986018,
    7.498381,
    9.919004,
    12.054276,
    13.718793,
    14.751711,
    15.031407,
    14.487149,
    13.106695,
    10.939127,
    8.092607,
    4.727194,
    1.043296,
    -2.733304,
    -6.368584,
    -9.638159,
    -12.344378,
    -14.331219,
    -15.495718,
    -15.795007,
    -15.248373,
    -13.934230,
    -11.982290,
    -9.561667,
    -6.865973,
    -4.096731,
    -1.446568,
    0.916368
};

/* End of File */
