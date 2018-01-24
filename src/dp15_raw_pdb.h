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

#define  RPDB_PANEL                       1
#define  RPDB_PANEL_REF_RAW_PDB_RANGE     2       /* control type: numeric, callback function: (none) */
#define  RPDB_PANEL_C1_RAW_PDB_RANGE      3       /* control type: numeric, callback function: (none) */
#define  RPDB_PANEL_C2_RAW_PDB_RANGE      4       /* control type: numeric, callback function: (none) */
#define  RPDB_PANEL_TEXTMSG               5       /* control type: textMsg, callback function: (none) */
#define  RPDB_PANEL_REF_RAW_PDB           6       /* control type: numeric, callback function: (none) */
#define  RPDB_PANEL_C1_RAW_PDB            7       /* control type: numeric, callback function: (none) */
#define  RPDB_PANEL_C2_RAW_PDB            8       /* control type: numeric, callback function: (none) */
#define  RPDB_PANEL_TEXTMSG_30            9       /* control type: textMsg, callback function: (none) */
#define  RPDB_PANEL_TEXTMSG_29            10      /* control type: textMsg, callback function: (none) */
#define  RPDB_PANEL_TEXTMSG_28            11      /* control type: textMsg, callback function: (none) */
#define  RPDB_PANEL_TEXTMSG_27            12      /* control type: textMsg, callback function: (none) */
#define  RPDB_PANEL_TEXTMSG_3             13      /* control type: textMsg, callback function: (none) */
#define  RPDB_PANEL_TEXTMSG_7             14      /* control type: textMsg, callback function: (none) */
#define  RPDB_PANEL_TEXTMSG_8             15      /* control type: textMsg, callback function: (none) */
#define  RPDB_PANEL_REF_RAW_PDB_AVG       16      /* control type: numeric, callback function: (none) */
#define  RPDB_PANEL_C1_RAW_PDB_AVG        17      /* control type: numeric, callback function: (none) */
#define  RPDB_PANEL_C2_RAW_PDB_AVG        18      /* control type: numeric, callback function: (none) */
#define  RPDB_PANEL_TEXTMSG_26            19      /* control type: textMsg, callback function: (none) */
#define  RPDB_PANEL_TEXTMSG_25            20      /* control type: textMsg, callback function: (none) */
#define  RPDB_PANEL_TEXTMSG_24            21      /* control type: textMsg, callback function: (none) */
#define  RPDB_PANEL_TEXTMSG_23            22      /* control type: textMsg, callback function: (none) */
#define  RPDB_PANEL_TEXTMSG_9             23      /* control type: textMsg, callback function: (none) */
#define  RPDB_PANEL_TEXTMSG_10            24      /* control type: textMsg, callback function: (none) */
#define  RPDB_PANEL_TEXTMSG_11            25      /* control type: textMsg, callback function: (none) */
#define  RPDB_PANEL_TEXTMSG_12            26      /* control type: textMsg, callback function: (none) */
#define  RPDB_PANEL_REF_RAW_PDB_STD       27      /* control type: numeric, callback function: (none) */
#define  RPDB_PANEL_C1_RAW_PDB_STD        28      /* control type: numeric, callback function: (none) */
#define  RPDB_PANEL_C2_RAW_PDB_STD        29      /* control type: numeric, callback function: (none) */
#define  RPDB_PANEL_TEXTMSG_2             30      /* control type: textMsg, callback function: (none) */
#define  RPDB_PANEL_TEXTMSG_15            31      /* control type: textMsg, callback function: (none) */
#define  RPDB_PANEL_C3_RAW_PDB_AVG        32      /* control type: numeric, callback function: (none) */
#define  RPDB_PANEL_C3_RAW_PDB_RANGE      33      /* control type: numeric, callback function: (none) */
#define  RPDB_PANEL_STRIPCHART            34      /* control type: strip, callback function: (none) */
#define  RPDB_PANEL_TEXTMSG_19            35      /* control type: textMsg, callback function: (none) */
#define  RPDB_PANEL_C3_RAW_PDB            36      /* control type: numeric, callback function: (none) */
#define  RPDB_PANEL_C3_RAW_PDB_STD        37      /* control type: numeric, callback function: (none) */
#define  RPDB_PANEL_TEXTMSG_20            38      /* control type: textMsg, callback function: (none) */
#define  RPDB_PANEL_RETURN                39      /* control type: command, callback function: ReturnToMain */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK ReturnToMain(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
