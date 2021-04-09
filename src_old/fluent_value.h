/*
 *   Copyright (c) 2020 Chen Xiaoxiao
 *   All rights reserved.

 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at

 *   http://www.apache.org/licenses/LICENSE-2.0

 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */

#ifndef fluent_value_h
#define fluent_value_h
namespace FLUENT
{
    // Fluent mesh file index
    //
    enum
    {
        COMMENT = 0,
        HEADER = 1,
        DIMESNSIONS = 2,
        NODES = 10,
        CELLS = 12,
        FACES = 13,
        PSF = 18 // Periodic Shadow Faces
    };

    enum CELL_TYPE
    {
        Mixed,
        Tri,
        Tet,
        Quad,
        Hex,
        Pyramid,
        Wedge,
        Polyhedral
    };

    enum FACE_TYPE
    {
        Mixed_f = 0,
        Linear = 2,
        Tri_f = 3,
        Quad_f = 4,
        Polygon = 5
    };

    enum BC_TYPE
    {
    };

    enum VARIABLE
    {
        NULL = 0,
        NULL_M1 = 0,
        NULL_M2 = 0,
        NULL_MEAN = 0,
        NULL_RMS = 0,
        NULL_FC_0 = 0,
        NULL_FC_1 = 0,
        PRESSURE = 1,
        MOMENTUM = 2,
        TEMPERATURE = 3,
        ENTHALPY = 4,
        TKE = 5,
        TED = 6,
        SPECIES = 7,
        G = 8,
        G_M1 = 0, /* never stored but symbol is required */
        G_M2 = 0,
        WSWIRL = 9,
        DPMS_MASS = 10,
        DPMS_MOM = 11,
        DPMS_ENERGY = 12,
        DPMS_SPECIES = 13,
        DVOLUME_DT = 14,
        BODY_FORCES = 15,
        FMEAN = 16,
        FVAR = 17,
        MASS_FLUX = 18,
        WALL_SHEAR = 19,
        BOUNDARY_HEAT_FLUX = 20,
        BOUNDARY_RAD_HEAT_FLUX = 21,
        OLD_PRESSURE = 22,
        POLLUT = 23,
        DPMS_P1_S = 24,
        DPMS_P1_AP = 25,
        WALL_GAS_TEMPERATURE = 26,
        DPMS_P1_DIFF = 27,
        DR_SURF = 28,

        /* conserved variables at n-1 and n-2 time levels (rampant) */
        W_M1 = 29,
        W_M2 = 30,

        DPMS_BURNOUT = 31,
        DPMS_CONCENTRATION = 32,
        PDF_MW = 33,
        DPMS_WSWIRL = 34,
        YPLUS = 35,
        YPLUS_UTAU = 36,
        WALL_SHEAR_SWIRL = 37,

        WALL_T_INNER = 38,
        POLLUT0 = 39,
        POLLUT1 = 40,
        WALL_G_INNER = 41,
        PREMIXC = 42,
        PREMIXC_T = 43,
        PREMIXC_RATE = 44,
        POLLUT2 = 45,
        POLLUT3 = 46,

        MASS_FLUX_M1 = 47,
        MASS_FLUX_M2 = 48,
        GRID_FLUX = 49,

        DO_I = 50,
        DO_RECON_I = 51,
        DO_ENERGY_SOURCE = 52,
        DO_IRRAD = 53,
        DO_QMINUS = 54,
        DO_IRRAD_OLD = 55,
        DO_IWX = 56,
        DO_IWY = 57,
        DO_IWZ = 58,

        MACH = 59,

        SLIP_U = 60,
        SLIP_V = 61,
        SLIP_W = 62,

        SDR = 63, /* omega in the k-w model */
        SDR_M1 = 64,
        SDR_M2 = 65,

        POLLUT4 = 66,
        GRANULAR_TEMP = 67,
        GRANULAR_TEMP_M1 = 68,
        GRANULAR_TEMP_M2 = 69,

        VFLUX = 70,

        SOUND_MODEL_SRC_M1 = 71, /* SOUND_MODEL_SRC=427 */
        SOUND_MODEL_SRC_M2 = 72,
        SOUND_MODEL_SRC_M3 = 73,
        SOUND_MODEL_SRC_M4 = 74,
        SOUND_MODEL_SRC_M5 = 75,
        SOUND_MODEL_SRC_M6 = 76,

        VFLUX_M1 = 80,

        VFLUX_M2 = 90,

        DO_QNET = 91,
        DO_QTRANS = 92,
        DO_QREFL = 93,
        DO_QABS = 94,

        POLLUT5 = 95,
        WALL_DIST = 96,

        SOLAR_SOURCE = 97,
        SOLAR_QREFL = 98,
        SOLAR_QABS = 99,
        SOLAR_QTRANS = 100,

        DENSITY = 101,
        MU_LAM = 102,
        MU_TURB = 103,
        CP = 104,
        KTC = 105,
        VGS_DTRM = 106,
        VGF_DTRM = 107,
        RSTRESS = 108, /* V4 reynolds stress model */
        THREAD_RAD_FLUX = 109,

        /* mass absorption term for absorbing porous media model */
        SPE_Q = 110,

        X_VELOCITY = 111,
        Y_VELOCITY = 112,
        Z_VELOCITY = 113,
        WALL_VELOCITY = 114,

        /* never stored but symbol is required */
        X_VELOCITY_M1 = 115,
        Y_VELOCITY_M1 = 116,
        Z_VELOCITY_M1 = 117,

        PHASE_MASS = 118, /* cavitation mass source */
        TKE_M1 = 119,
        TED_M1 = 120,

        POLLUT6 = 121,

        X_VELOCITY_M2 = 122,
        Y_VELOCITY_M2 = 123,
        Z_VELOCITY_M2 = 124,
        TKE_M2 = 126,
        TED_M2 = 127,

        RUU = 128, /* V5 reynolds stress model */
        RVV = 129, /* V5 reynolds stress model */
        RWW = 130, /* V5 reynolds stress model */
        RUV = 131, /* V5 reynolds stress model */
        RVW = 132, /* V5 reynolds stress model */
        RUW = 133, /* V5 reynolds stress model */

        DPMS_EROSION = 134,
        DPMS_ACCRETION = 135,

        FMEAN2 = 136,
        FVAR2 = 137,

        ENTHALPY_M1 = 138,
        ENTHALPY_M2 = 139,

        FMEAN_M1 = 140,
        FMEAN_M2 = 141,
        FVAR_M1 = 142,
        FVAR_M2 = 143,
        FMEAN2_M1 = 144,
        FMEAN2_M2 = 145,
        FVAR2_M1 = 146,
        FVAR2_M2 = 147,

        PREMIXC_M1 = 148,
        PREMIXC_M2 = 149,

        /*vof 1,2,3,4 kept for v5 compatibility */
        VOF = 150,
        VOF_1 = 151,
        VOF_2 = 152,
        VOF_3 = 153,
        VOF_4 = 154,

        VOF_M1 = 160,
        VOF_1_M1 = 161,
        VOF_2_M1 = 162,
        VOF_3_M1 = 163,
        VOF_4_M1 = 164,

        VOF_M2 = 170,
        VOF_1_M2 = 171,
        VOF_2_M2 = 172,
        VOF_3_M2 = 173,
        VOF_4_M2 = 174,

        VOF_NORM = 155,
        VOF_1_NORM = 156,
        VOF_2_NORM = 157,
        VOF_3_NORM = 158,
        VOF_4_NORM = 159,

        /* dynamic mesh */
        CENTROID_SLIDE = 177,
        CENTROID_M1 = 178,
        CELL_GRID_VELOCITY = 179,
        VOLUME_M2 = 180,
        WALL_GRID_VELOCITY = 181,

        POLLUT7 = 182,
        POLLUT8 = 183,
        POLLUT9 = 184,
        POLLUT10 = 185,
        POLLUT11 = 186,
        POLLUT12 = 187,
        POLLUT13 = 188,
        POLLUT14 = 189,
        SV_T_AUX = 190,    /* auxilliary temperature for particles */
        SV_T_AP_AUX = 191, /* auxilliary ap coefficient for particles */
        TOTAL_PRESSURE = 192,
        TOTAL_TEMPERATURE = 193,
        NRBC_DC = 194, /* change in char. var for nrbc*/
        DP_TMFR = 195, /* pressure inc. due to target mfr*/

        TVAR = 196,
        TVAR_M1 = 197,
        TVAR_M2 = 198,

        // Y_ = 200,                       /* species */
        // EXPAND_50(Y_, _M1 =, 250),      /* species at fist time level */
        // EXPAND_50(Y_, _M2 =, 300),      /* species at second time level */
        // EXPAND_50_EQUAL(DR_SURF_, 350), /* surface deposition rate */

        /* Please start next  subsection ids at 400 or above
     * to allow room for the addition of more species ids if needed */

        PRESSURE_MEAN = 400,
        PRESSURE_RMS = 401,
        X_VELOCITY_MEAN = 402,
        X_VELOCITY_RMS = 403,
        Y_VELOCITY_MEAN = 404,
        Y_VELOCITY_RMS = 405,
        Z_VELOCITY_MEAN = 406,
        Z_VELOCITY_RMS = 407,
        TEMPERATURE_MEAN = 408,
        TEMPERATURE_RMS = 409,
        VOF_MEAN = 410,
        VOF_RMS = 411,
        PRESSURE_M1 = 412,
        PRESSURE_M2 = 413,
        GRANULAR_TEMP_MEAN = 414,
        GRANULAR_TEMP_RMS = 415,
        DPM_CELLSTEPS = 416,
        DPM_FACESTEPS = 417,
        PHASE_DIAMETER_MEAN = 418,
        PHASE_DIAMETER_RMS = 419,
        DPM_PARTITION = 420,

        SOUND_VAR = 421,
        SOUND_VAR_M1 = 0,
        SOUND_VAR_M2 = 0,
        SOUND_P_MEAN = 422,
        SOUND_P_RMS = 423,
        SOUND_DDT = 424,
        SOUND_D2DT2 = 425,
        SOUND_SPACE_TERM = 426,
        SOUND_MODEL_SRC = 427, /* old timesteps M1 to M6 are 71-76 */
        SOUND_MODEL_SRC_MEAN = 428,
        SOUND_MODEL_SRC_RMS = 429,
        SOUND_MODEL_SRC_SMOOTH = 430,
        SOUND_MODEL_SRC_MASK = 431,
        SOUND_SPONGE = 432,

        FWH_P = 433,
        FWH_P_M1 = 434,
        FWH_P_M2 = 435,
        FWH_U = 436,
        FWH_U_M1 = 437,
        FWH_U_M2 = 438,
        FWH_V = 439,
        FWH_V_M1 = 440,
        FWH_V_M2 = 441,
        FWH_W = 442,
        FWH_W_M1 = 443,
        FWH_W_M2 = 444,
        FWH_R = 445,
        FWH_R_M1 = 446,
        FWH_R_M2 = 447,

        // EXPAND_50_EQUAL(DPMS_Y_, 450),

        /* Don't add section ids here unless you need a large contiguous chunk.
     * Use id's 40-100 first! */
        NUT = 500,
        NUT_M1 = 501,
        NUT_M2 = 502,

        RUU_M1 = 503,
        RVV_M1 = 504,
        RWW_M1 = 505,
        RUV_M1 = 506,
        RVW_M1 = 507,
        RUW_M1 = 508,

        RUU_M2 = 509,
        RVV_M2 = 510,
        RWW_M2 = 511,
        RUV_M2 = 512,
        RVW_M2 = 513,
        RUW_M2 = 514,

        ENERGY_M1 = 515,
        ENERGY_M2 = 516,

        DENSITY_M1 = 517,
        DENSITY_M2 = 518,

        DPMS_PDF_1 = 519,
        DPMS_PDF_2 = 520,

        V2 = 521,
        V2_M1 = 522,
        V2_M2 = 523,
        FEL = 524,
        FEL_M1 = 525,
        FEL_M2 = 526,
        LKE = 527,
        LKE_M1 = 528,
        LKE_M2 = 529,

        /* shell: using 530->539 */
        SHELL_CELL_T = 530,
        SHELL_FACE_T = 531,
        SHELL_CELL_ENERGY_M1 = 532,
        SHELL_CELL_ENERGY_M2 = 533,
        DO_RECON_I_SHELL = 534,
        DO_IRRAD_SHELL = 535,
        DO_I_SHELL = 536,

        /* dpm turblence sources */
        DPMS_TKE = 540,
        DPMS_D = 541,
        DPMS_O = 542,
        DPMS_TKE_RUU = 543,
        DPMS_TKE_RVV = 544,
        DPMS_TKE_RWW = 545,
        DPMS_TKE_RUV = 546,
        DPMS_TKE_RVW = 547,
        DPMS_TKE_RUW = 548,
        /* dpm source term deltas */
        DPMS_DS_MASS = 549,
        DPMS_DS_ENERGY = 550,
        DPMS_DS_TKE = 551,
        DPMS_DS_D = 552,
        DPMS_DS_O = 553,
        DPMS_DS_TKE_RUU = 554,
        DPMS_DS_TKE_RVV = 555,
        DPMS_DS_TKE_RWW = 556,
        DPMS_DS_TKE_RUV = 557,
        DPMS_DS_TKE_RVW = 558,
        DPMS_DS_TKE_RUW = 559,
        DPMS_DS_PDF_1 = 560,
        DPMS_DS_PDF_2 = 561,
        DPMS_DS_EMISS = 562,
        DPMS_DS_ABS = 563,
        DPMS_DS_SCAT = 564,
        DPMS_DS_BURNOUT = 565,
        DPMS_DS_MOM = 566,
        DPMS_DS_WSWIRL = 567,
        DPM_DIST_F = 578,
        DPM_DIST_C = 579, /* maintain number for backward compatibiltiy
                                    with DPM_DIST */

        MU_TURB_L = 580,
        MU_TURB_S = 581,
        TKE_TRANS = 582,
        TKE_TRANS_M1 = 583,
        TKE_TRANS_M2 = 584,
        MU_TURB_W = 585,

        INTERMIT = 586,
        INTERMIT_M1 = 587,
        INTERMIT_M2 = 588,
        RETHETA = 589,
        RETHETA_M1 = 590,
        RETHETA_M2 = 591,

        POLLUT15 = 592,
        POLLUT16 = 593,
        POLLUT17 = 594,
        POLLUT18 = 595,
        POLLUT19 = 596,
        POLLUT20 = 597,
        POLLUT21 = 598,
        POLLUT22 = 599,

        DELH = 600, /* obsolete  for >= v6.0*/
        DPMS_MOM_AP = 601,
        DPMS_WSWIRL_AP = 602,
        X_PULL = 603,
        Y_PULL = 604,
        Z_PULL = 605,
        LIQF = 606,

        DPMS_INERT = 608,
        DPMS_DS_INERT = 609,

        /* pdf transport */
        PDFT_QBAR = 610,
        PDFT_PHI = 611,
        PDFT_Q_TA = 612,
        PDFT_SVOL_TA = 613,
        PDFT_MASS_TA = 614,
        PDFT_T4_TA = 615,

        MICRO_MIX_FVAR1 = 620,
        MICRO_MIX_FVAR2 = 621,
        MICRO_MIX_FVAR3 = 622,
        MICRO_MIX_FVAR1_M1 = 623,
        MICRO_MIX_FVAR2_M1 = 624,
        MICRO_MIX_FVAR3_M1 = 625,
        MICRO_MIX_FVAR1_M2 = 626,
        MICRO_MIX_FVAR2_M2 = 627,
        MICRO_MIX_FVAR3_M2 = 628,

        SCAD_LES = 630,

        UFLA_Y = 635,
        UFLA_Y_M1 = 636,
        UFLA_Y_M2 = 637,

        REACTOR_NET_INDEX = 640,

        /* Crevice model */
        CREV_MASS = 645,
        CREV_ENRG = 646,
        CREV_MOM = 647,

        /*Acoustics*/
        XF_ACOUSTICS_MODEL = 650,
        XF_RF_AC_FWH_RECEIVERS_DATA = 651,
        SV_DPDT_RMS = 652,
        XF_RF_AC_WAVEEQ_RECEIVERS_DATA = 653,
        /*SV_PRESSURE_M1 = 653,  not used */
        XF_RF_AC_PERIODIC_INDEX = 654, /* not used */
        XF_RF_AC_PERIODIC_PS = 655,    /* not used */
        XF_RF_AC_F_NORMAL = 656,
        XF_RF_AC_F_CENTROID = 657,
        XF_RF_AC_MODAL_ANALYSIS = 658,

        /* Autoignition */
        IGNITE = 660,
        IGNITE_M1 = 661,
        IGNITE_M2 = 662,
        IGNITE_RATE = 663,

        /* ECFM */
        ECFM_SIGMA = 665,
        ECFM_SIGMA_M1 = 666,
        ECFM_SIGMA_M2 = 667,

        WALL_SHEAR_MEAN = 680,
        UV_MEAN = 681,
        UW_MEAN = 682,
        VW_MEAN = 683,
        UT_MEAN = 684,
        VT_MEAN = 685,
        WT_MEAN = 686,
        BOUNDARY_HEAT_FLUX_MEAN = 687,

        /* Inert species transport */
        INERT = 697,
        INERT_M1 = 698,
        INERT_M2 = 699,

        // EXPAND_50_EQUAL(UDS_, 700),  /* user defined scalar */
        // EXPAND_50(UDS_, _M1 =, 750), /* user defined scalar
        //                              * at fist time level */
        // EXPAND_50(UDS_, _M2 =, 800), /* user defined scalar
        //                              * at second time level */
        // EXPAND_50_EQUAL(DPMS_DS_Y_, 850),
        GRANULAR_PRESSURE = 910,
        GRANULAR_PRESSURE_M1 = 0, /* never stored but symbol is required */
        GRANULAR_PRESSURE_M2 = 0, /* never stored but symbol is required */
        DPMS_DS_P1_S = 911,
        DPMS_DS_P1_AP = 912,
        DPMS_DS_P1_DIFF = 913,
        DPMS_WALL_FORCE = 914,
        // E//XPAND_50_EQUAL(DPMS_DS_SURFACE_SPECIES_, 920),

        UDM_I = 970,
        NODE_UDM_I = 971,

        /* G Equation */
        GEQN = 980,
        GEQN_M1 = 981,
        GEQN_M2 = 982,
        GVAR = 983,
        GVAR_M1 = 984,
        GVAR_M2 = 985,

        /* Don't add section ids here unless you need a large contiguous chunk.
     * Use id's 40-100 and 128-200 first! */

        // EXPAND_50(Y_, _MEAN =, 1000), /*  time average species */
        // EXPAND_50(Y_, _RMS =, 1050),  /*  RMS species  */

        // EXPAND_50_EQUAL(Y_EDC_, 1100),                /* EDC species */
        // EXPAND_50_EQUAL(DPMS_SURFACE_SPECIES_, 1150), /* particle surface
        // species
        // */ EXPAND_50_EQUAL(SITE_F_, 1200),               /* surface site
        // coverage
        // */ EXPAND_50_EQUAL(CREV_Y_, 1250), /* crevice model species sources
        // */

        WSB = 1301, /*for wetsteam model*/
        WSN = 1302,
        WSR = 1303,

        WSB_M1 = 1304,
        WSB_M2 = 1305,

        WSN_M1 = 1306,
        WSN_M2 = 1307,

        WSR_M1 = 1308,
        WSR_M2 = 1309,

        MASGEN = 1310,
        NUCRAT = 1311,

        FILM_HEAT_FLUX = 1323,
        LIQUID_HEAT_FLUX = 1324,
        VAPOR_HEAT_FLUX = 1325,
        QUENCH_HEAT_FLUX = 1326,
        EVAP_HEAT_FLUX = 1327,

        DT_BC_SOURCE = 1328,
        /*  DT_SOURCE = 1329,  */
        TEMPERATURE_M1 = 1330, /*T_M1 & T_M2 neede for general NRBC */
        TEMPERATURE_M2 = 1331,

        POROSITY_M1 = 1332,
        POROSITY_M2 = 1333,

        MT = 1334,
        BL_DS_DP = 1335,           /*  boiling model */
        SAT_TEMP = 1336,           /* boiling model  */
        THIN_FILM = 1337,          /* thin film in boiling model */
        SPE_FROM = 1338,           /* species transfer model */
        SPE_TO = 1339,             /* species transfer model */
        SAT_TEMP_DEW = 1340,       /* 2nd mixture based sat temperature, dew point */
        MT_VAPOR_PRESS = 1341,     /* vapor pressure for mass tr mechanisms */
        MT_SAT_TEMP = 1342,        /* evap-cond model  */
        MT_QSP_TOTAL_FLUX = 1343,  /* sbm model total single phase heat flux */
        MT_QNUC_TOTAL_FLUX = 1344, /* sbm model total nucleate heat flux */
        MT_QSP_FLUX = 1345,        /* sbm model mech specific single phase heat flux */

        PRESSURE_FC_0 = 10150,
        PRESSURE_FC_1 = 10151,
        X_VELOCITY_FC_0 = 10152,
        X_VELOCITY_FC_1 = 10153,
        Y_VELOCITY_FC_0 = 10154,
        Y_VELOCITY_FC_1 = 10155,
        Z_VELOCITY_FC_0 = 10156,
        Z_VELOCITY_FC_1 = 10157,
        TEMPERATURE_FC_0 = 10158,
        TEMPERATURE_FC_1 = 10159,

        TVAR_FC_0 = 10160,
        TVAR_FC_1 = 10161,
        TKE_FC_0 = 10162,
        TKE_FC_1 = 10163,
        LKE_FC_0 = 10164,
        LKE_FC_1 = 10165,
        TKE_TRANS_FC_0 = 10166,
        TKE_TRANS_FC_1 = 10167,
        TED_FC_0 = 10168,
        TED_FC_1 = 10169,

        SDR_FC_0 = 10170,
        SDR_FC_1 = 10171,
        V2_FC_0 = 10172,
        V2_FC_1 = 10173,
        FEL_FC_0 = 10174,
        FEL_FC_1 = 10175,
        INTERMIT_FC_0 = 10176,
        INTERMIT_FC_1 = 10177,
        RETHETA_FC_0 = 10178,
        RETHETA_FC_1 = 10179,

        PREMIXC_FC_0 = 10180,
        PREMIXC_FC_1 = 10181,
        FMEAN_FC_0 = 10182,
        FMEAN_FC_1 = 10183,
        FMEAN2_FC_0 = 10184,
        FMEAN2_FC_1 = 10185,
        FVAR_FC_0 = 10186,
        FVAR_FC_1 = 10187,
        FVAR2_FC_0 = 10188,
        FVAR2_FC_1 = 10189,

        ENTHALPY_FC_0 = 10190,
        ENTHALPY_FC_1 = 10191,
        G_FC_0 = 10192,
        G_FC_1 = 10193,
        RUU_FC_0 = 10194,
        RUU_FC_1 = 10195,
        RVV_FC_0 = 10196,
        RVV_FC_1 = 10197,
        RWW_FC_0 = 10198,
        RWW_FC_1 = 10199,

        RUV_FC_0 = 10200,
        RUV_FC_1 = 10201,
        RVW_FC_0 = 10202,
        RVW_FC_1 = 10203,
        RUW_FC_0 = 10204,
        RUW_FC_1 = 10205,
        NUT_FC_0 = 10206,
        NUT_FC_1 = 10207,
        IGNITE_FC_0 = 10208,
        IGNITE_FC_1 = 10209,

        UFLA_Y_FC_0 = 10210,
        UFLA_Y_FC_1 = 10211,
        DW_FC_0 = 10212,
        DW_FC_1 = 10213,
        EPDF_H_FC_0 = 10214,
        EPDF_H_FC_1 = 10215,
        IAC_FC_0 = 10216,
        IAC_FC_1 = 10217,
        WSB_FC_0 = 10218,
        WSB_FC_1 = 10219,

        WSN_FC_0 = 10220,
        WSN_FC_1 = 10221,
        WSR_FC_0 = 10222,
        WSR_FC_1 = 10223,
        ECFM_SIGMA_FC_0 = 10224,
        ECFM_SIGMA_FC_1 = 10225,
        INERT_FC_0 = 10226,
        INERT_FC_1 = 10227,
        MICRO_MIX_FVAR1_FC_0 = 10228,
        MICRO_MIX_FVAR1_FC_1 = 10229,

        MICRO_MIX_FVAR2_FC_0 = 10230,
        MICRO_MIX_FVAR2_FC_1 = 10231,
        MICRO_MIX_FVAR3_FC_0 = 10232,
        MICRO_MIX_FVAR3_FC_1 = 10233,
        GRANULAR_PRESSURE_FC_0 = 10234,
        GRANULAR_PRESSURE_FC_1 = 10235,
        GRANULAR_TEMP_FC_0 = 10236,
        GRANULAR_TEMP_FC_1 = 10237,

        E_POR_SOLID_M1 = 10238,
        E_POR_SOLID_M2 = 10239,

        /* Departure Enthalpy non-premixed with real-gas */
        PDF_DEP_ENTH = 10240,

        LSF_FC_0 = 10241,
        LSF_FC_1 = 10242,

        /* Departure Enthalpy partially-premixed with real-gas */
        PDF_DEP_ENTH_U = 10243,

        /* Eulerian Wall Film Model */
        EFILM_HEIGHT = 10300,
        EFILM_U = 10301,
        EFILM_V = 10302,
        EFILM_W = 10303,
        EFILM_T = 10304,

        EFILM_CFL = 10305,
        EFILM_WEBER = 10306,
        EFILM_US = 10307,
        EFILM_VS = 10308,
        EFILM_WS = 10309,
        EFILM_TS = 10310,
        EFILM_T_ALPHA = 10311,
        EFILM_T_BETA = 10312,
        EFILM_TS_FLUX = 10313,

        EFILM_VAP_SRC = 10320,
        EFILM_VAP_APP = 10321,

        EFILM_S = 10330,

        EFILM_SEPARATED_DIAM = 10340,
        EFILM_STRIPPED_DIAM = 10341,
        EFILM_OUTFLOW_MASS_SUM = 10342,

        EFILM_DPM_MASS_S = 10350,
        EFILM_DPM_MOM_X_S = 10351,
        EFILM_DPM_MOM_Y_S = 10352,
        EFILM_DPM_MOM_Z_S = 10353,
        EFILM_DPM_ENERGY_S = 10354,
        EFILM_SEPARATED_MASS = 10355,
        EFILM_STRIPPED_MASS = 10356,
        EFILM_STRIPPED_MASS_SUM = 10357,
        EFILM_DPM_PRESSURE = 10358,
        EFILM_SEPARATED_MASS_SUM = 10359,
        /* End Eulerian Wall Film Model */

        EM_MAP = 10465,

        PB_DQMOM_FC_0 = 10468,
        PB_DQMOM_FC_1 = 10469,

        /* Adjoint solver */
        ADJOINT_U = 10500,
        ADJOINT_V = 10501,
        ADJOINT_W = 10502,
        ADJOINT_P = 10503,
        ADJOINT_AP = 10504,
        ADJOINT_HISTORY_0 = 10505,
        ADJOINT_HISTORY_1 = 10506,
        ADJOINT_HISTORY_2 = 10507,
        ADJOINT_HISTORY_3 = 10508,
        ADJOINT_HISTORY_4 = 10509,
        ADJOINT_CELL_MARKER = 10510,
        DVOLUME_M2_DT = 10511,
        GRID_FLUX_M2 = 10512,
        ADJOINT_T = 10513,
        ADJOINT_ARTIFICIAL_DISS = 10514,
        ADJOINT_TOPOLOGY_DENSITY = 10515,
        ADJOINT_DTOPOLOGY_DENSITY1 = 10516,
        ADJOINT_DTOPOLOGY_DENSITY2 = 10517,
        ADJOINT_DTOPOLOGY_DENSITY3 = 10518,
        ADJOINT_DTOPOLOGY_DENSITY4 = 10519,
        ADJOINT_DTOPOLOGY_DENSITY5 = 10520,
        ADJOINT_DTOPOLOGY_DENSITY6 = 10521,
        ADJOINT_DTOPOLOGY_DENSITY7 = 10522,
        ADJOINT_DTOPOLOGY_DENSITY8 = 10523,
        ADJOINT_DTOPOLOGY_DENSITY9 = 10524,
        ADJOINT_DTOPOLOGY_DENSITY10 = 10525,
        ADJOINT_K = 10526,
        ADJOINT_O = 10527,

        /* pollutant time levels */
        POLLUT0_M1 = 10600,
        POLLUT0_M2 = 10601,
        POLLUT1_M1 = 10602,
        POLLUT1_M2 = 10603,
        POLLUT2_M1 = 10604,
        POLLUT2_M2 = 10605,
        POLLUT3_M1 = 10606,
        POLLUT3_M2 = 10607,
        POLLUT4_M1 = 10608,
        POLLUT4_M2 = 10609,
        POLLUT5_M1 = 10610,
        POLLUT5_M2 = 10611,
        POLLUT6_M1 = 10612,
        POLLUT6_M2 = 10613,
        POLLUT7_M1 = 10614,
        POLLUT7_M2 = 10615,
        POLLUT8_M1 = 10616,
        POLLUT8_M2 = 10617,
        POLLUT9_M1 = 10618,
        POLLUT9_M2 = 10619,
        POLLUT10_M1 = 10620,
        POLLUT10_M2 = 10621,
        POLLUT11_M1 = 10622,
        POLLUT11_M2 = 10623,
        POLLUT12_M1 = 10624,
        POLLUT12_M2 = 10625,
        POLLUT13_M1 = 10626,
        POLLUT13_M2 = 10627,
        POLLUT14_M1 = 10628,
        POLLUT14_M2 = 10629,
        POLLUT15_M1 = 10630,
        POLLUT15_M2 = 10631,
        POLLUT16_M1 = 10632,
        POLLUT16_M2 = 10633,
        POLLUT17_M1 = 10634,
        POLLUT17_M2 = 10635,
        POLLUT18_M1 = 10636,
        POLLUT18_M2 = 10637,
        POLLUT19_M1 = 10638,
        POLLUT19_M2 = 10639,
        POLLUT20_M1 = 10640,
        POLLUT20_M2 = 10641,
        POLLUT21_M1 = 10642,
        POLLUT21_M2 = 10643,
        POLLUT22_M1 = 10644,
        POLLUT22_M2 = 10645,

        /* DPM Sources per injection material */

        /* More DPM linearisations */
        DPMS_DS_MOM_AP = 10710,
        DPMS_DS_WSWIRL_AP = 10711,
        DPMS_ENERGY_AP = 10712,
        DPMS_DS_ENERGY_AP = 10713,

        VIRTUAL_MASS = 10830,

        /* DPM DS Sources per injection material */
        IMP_W5 = 11020,
        IMP_W5_M1 = 11021,

        IMP_W1 = 11022,
        IMP_W1_M1 = 11023,

        /* DPM time statistics */
        DPM_DIST_MEAN_C = 11024,
        DPM_DIST_RMS_C = 11025, /* Place holder, data field removed in v180. */

        /* Dynamic DPM sources sections */
        DPMS_Y = 11026,
        DPMS_Y_AP = 11027,
        DPMS_DS_Y = 11028,
        DPMS_DS_Y_AP = 11029,

        UBAR_M1 = 11030, /* transient rhie-chow */
        PW_PREV = 11031,

        /* Data for Multiband P1 */
        P1_IRRAD = 11032,

        PHI_1 = 11050, /* electric potential */
        PHI_1_M1 = 11051,
        PHI_1_M2 = 11052,
        FARADAIC_FLUX_1 = 11053,
        VOLTAGE_JUMP_1 = 11054,
        CONTACT_RESISTANCE_1 = 11055,
        PHI_HSRC_1 = 11056,
        PHI_CORROSION_RATE_1 = 11057,
        PHI_SAVED_G_1 = 11058,
        PHI_ACCU_CORROSION_RATE_1 = 11059,

        /* please start next id at 11100 or higher */

        MESH_UD_CELLS = 11100,
        PB_MT = 11110,

        SOOT_MOM_AREA = 11171,
        SOOT_MOM_AREA_M1 = 11172,
        SOOT_MOM_AREA_M2 = 11173,

        /*Data for MonteCarlo*/
        MC_SOURCE = 11189,

        /* please start next id at 11250 or higher */

        MC_I = 11250,
        MC_SDV = 11251,

        DPMS_EROSION_MDM = 11252,
        SURFACE_DEFORMATION = 11253,
        SURFACE_INIT_AREA = 11254,

        /* Outflow data */
        OUTFLOW_DEFICIT = 11255,
        OUTFLOW_DEFICIT_M1 = 11256,
        OUTFLOW_DEFICIT_M2 = 11257,

        /*Data for Bounded Second order Time Formulation: reserve till 11270 */
        BETA_PH = 11260,
        BETA_NH = 11261,

        /* Volumetric synthetic turbulence scaling factor */
        VSTG_SBES_FW = 11270,

        ROUGH_SIZE = 11271, /* store roughness height at each cell */

        FVAR_RANS = 11340,    /*Variances in RANS zone with hybrid turb models*/
        FVAR_RANS_M1 = 11341, /*Variances in RANS zone with hybrid turb models*/
        FVAR_RANS_M2 = 11342,
        FVAR2_RANS = 11343,
        FVAR2_RANS_M1 = 11344,
        FVAR2_RANS_M2 = 11345,
        MPM_X_VELO_SCALE = 11346,
        MPM_Y_VELO_SCALE = 11347,
        MPM_Z_VELO_SCALE = 11348,

        /* Data for structural mechanics */
        N_DISP_X = 11431,
        N_DISP_X_M1 = 11432,
        N_DISP_X_DOT1 = 11433,
        N_DISP_X_DOT1_M1 = 11434,
        N_DISP_X_DOT2 = 11435,
        N_DISP_X_DOT2_M1 = 11436,
        N_DISP_Y = 11437,
        N_DISP_Y_M1 = 11438,
        N_DISP_Y_DOT1 = 11439,
        N_DISP_Y_DOT1_M1 = 11440,
        N_DISP_Y_DOT2 = 11441,
        N_DISP_Y_DOT2_M1 = 11442,
        N_DISP_Z = 11443,
        N_DISP_Z_M1 = 11444,
        N_DISP_Z_DOT1 = 11445,
        N_DISP_Z_DOT1_M1 = 11446,
        N_DISP_Z_DOT2 = 11447,
        N_DISP_Z_DOT2_M1 = 11448,

        SIGMA_XX = 11449,
        SIGMA_YY = 11450,
        SIGMA_XY = 11451,
        SIGMA_ZZ = 11452,
        SIGMA_YZ = 11453,
        SIGMA_XZ = 11454,

        N_STRUCTURE_X = 11455,
        N_STRUCTURE_Y = 11456,
        N_STRUCTURE_Z = 11457,

        /* Artificial wall flag*/
        ARTIFICIAL_WALL_FLAG = 11458,

        /* Data for li-ion battery model*/
        LITHIUM = 11640,
        LITHIUM_M1 = 11641,
        LITHIUM_M2 = 11642,
        LITHIUM_MIGRATION_SOURCE = 11643,
        LITHIUM_SAVED_G = 11644,
        LITHIUM_IE = 11645,
        LITHIUM_JUMP = 11646,
        LITHIUM_CONTACT_RESISTANCE = 11647,
        LITHIUM_WALL = 11648,
        LITHIUM_WALL2 = 11649,

        /* Data for non/partially premixed model linearized sources */
        DPMS_PDF_1_AP = 11650,
        DPMS_PDF_2_AP = 11651,
        DPMS_INERT_AP = 11652,
        DPMS_DS_PDF_1_AP = 11653,
        DPMS_DS_PDF_2_AP = 11654,
        DPMS_DS_INERT_AP = 11655,
        DPMS_MASS_AP = 11656,
        DPMS_DS_MASS_AP = 11657
    };
} // namespace FLUENT
#endif