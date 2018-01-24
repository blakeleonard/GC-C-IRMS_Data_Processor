/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/* Copyright (c) National Instruments 2013. All Rights Reserved.          */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  S45_PANEL                        1
#define  S45_PANEL_REF_SIG_RANGE_45       2       /* control type: numeric, callback function: (none) */
#define  S45_PANEL_C1_SIG_RANGE_45        3       /* control type: numeric, callback function: (none) */
#define  S45_PANEL_C2_SIG_RANGE_45        4       /* control type: numeric, callback function: (none) */
#define  S45_PANEL_TEXTMSG                5       /* control type: textMsg, callback function: (none) */
#define  S45_PANEL_REF_SIG_45             6       /* control type: numeric, callback function: (none) */
#define  S45_PANEL_C1_SIG_45              7       /* control type: numeric, callback function: (none) */
#define  S45_PANEL_C2_SIG_45              8       /* control type: numeric, callback function: (none) */
#define  S45_PANEL_TEXTMSG_30             9       /* control type: textMsg, callback function: (none) */
#define  S45_PANEL_TEXTMSG_29             10      /* control type: textMsg, callback function: (none) */
#define  S45_PANEL_TEXTMSG_28             11      /* control type: textMsg, callback function: (none) */
#define  S45_PANEL_TEXTMSG_27             12      /* control type: textMsg, callback function: (none) */
#define  S45_PANEL_TEXTMSG_3              13      /* control type: textMsg, callback function: (none) */
#define  S45_PANEL_TEXTMSG_7              14      /* control type: textMsg, callback function: (none) */
#define  S45_PANEL_TEXTMSG_8              15      /* control type: textMsg, callback function: (none) */
#define  S45_PANEL_REF_SIG_AVG_45         16      /* control type: numeric, callback function: (none) */
#define  S45_PANEL_C1_SIG_AVG_45          17      /* control type: numeric, callback function: (none) */
#define  S45_PANEL_C2_SIG_AVG_45          18      /* control type: numeric, callback function: (none) */
#define  S45_PANEL_TEXTMSG_26             19      /* control type: textMsg, callback function: (none) */
#define  S45_PANEL_TEXTMSG_25             20      /* control type: textMsg, callback function: (none) */
#define  S45_PANEL_TEXTMSG_24             21      /* control type: textMsg, callback function: (none) */
#define  S45_PANEL_TEXTMSG_23             22      /* control type: textMsg, callback function: (none) */
#define  S45_PANEL_TEXTMSG_9              23      /* control type: textMsg, callback function: (none) */
#define  S45_PANEL_TEXTMSG_10             24      /* control type: textMsg, callback function: (none) */
#define  S45_PANEL_TEXTMSG_11             25      /* control type: textMsg, callback function: (none) */
#define  S45_PANEL_TEXTMSG_12             26      /* control type: textMsg, callback function: (none) */
#define  S45_PANEL_REF_SIG_STD_45         27      /* control type: numeric, callback function: (none) */
#define  S45_PANEL_C1_SIG_STD_45          28      /* control type: numeric, callback function: (none) */
#define  S45_PANEL_C2_SIG_STD_45          29      /* control type: numeric, callback function: (none) */
#define  S45_PANEL_TEXTMSG_2              30      /* control type: textMsg, callback function: (none) */
#define  S45_PANEL_TEXTMSG_15             31      /* control type: textMsg, callback function: (none) */
#define  S45_PANEL_C3_SIG_AVG_45          32      /* control type: numeric, callback function: (none) */
#define  S45_PANEL_C3_SIG_RANGE_45        33      /* control type: numeric, callback function: (none) */
#define  S45_PANEL_STRIPCHART             34      /* control type: strip, callback function: (none) */
#define  S45_PANEL_TEXTMSG_19             35      /* control type: textMsg, callback function: (none) */
#define  S45_PANEL_C3_SIG_45              36      /* control type: numeric, callback function: (none) */
#define  S45_PANEL_C3_SIG_STD_45          37      /* control type: numeric, callback function: (none) */
#define  S45_PANEL_TEXTMSG_20             38      /* control type: textMsg, callback function: (none) */
#define  S45_PANEL_RETURN                 39      /* control type: command, callback function: ReturnToMain */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK ReturnToMain(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
