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

#define  MAIN_PANEL                       1
#define  MAIN_PANEL_START_FILE_44         2       /* control type: numeric, callback function: StartFile44 */
#define  MAIN_PANEL_QUITBUTTON            3       /* control type: command, callback function: QuitCallback */
#define  MAIN_PANEL_START_FILE_45         4       /* control type: numeric, callback function: StartFile45 */
#define  MAIN_PANEL_START_FILE_TEMP       5       /* control type: numeric, callback function: StartFileTemp */
#define  MAIN_PANEL_TOTAL_RUNS            6       /* control type: numeric, callback function: TotalRuns */
#define  MAIN_PANEL_CERT_REF_PDB          7       /* control type: numeric, callback function: CertREFPdb */
#define  MAIN_PANEL_REF_SAMPLING_TIME     8       /* control type: numeric, callback function: REFSamplingTime */
#define  MAIN_PANEL_GC_SAMPLING_TIME      9       /* control type: numeric, callback function: GCSamplingTime */
#define  MAIN_PANEL_REF_LIN_REG_POINTS    10      /* control type: numeric, callback function: REFLinRegPoints */
#define  MAIN_PANEL_GC_LIN_REG_POINTS     11      /* control type: numeric, callback function: GCLinRegPoints */
#define  MAIN_PANEL_REF_MVG_AVG_POINTS    12      /* control type: numeric, callback function: REFMvgAvgPoints */
#define  MAIN_PANEL_GC_MVG_AVG_POINTS     13      /* control type: numeric, callback function: GCMvgAvgPoints */
#define  MAIN_PANEL_TOTAL_GC_PULSES       14      /* control type: numeric, callback function: TotalGCPulses */
#define  MAIN_PANEL_RANGE_START_TIME      15      /* control type: numeric, callback function: RangeStartTime */
#define  MAIN_PANEL_AREA_THRESHOLD        16      /* control type: numeric, callback function: AreaThreshold */
#define  MAIN_PANEL_C2_STOP_45            17      /* control type: numeric, callback function: C2Stop45 */
#define  MAIN_PANEL_C2_STOP_44            18      /* control type: numeric, callback function: C2Stop44 */
#define  MAIN_PANEL_C2_START_45           19      /* control type: numeric, callback function: C2Start45 */
#define  MAIN_PANEL_C3_STOP_45            20      /* control type: numeric, callback function: C3Stop45 */
#define  MAIN_PANEL_C3_STOP_44            21      /* control type: numeric, callback function: C3Stop44 */
#define  MAIN_PANEL_C3_START_45           22      /* control type: numeric, callback function: C3Start45 */
#define  MAIN_PANEL_C3_START_44           23      /* control type: numeric, callback function: C3Start44 */
#define  MAIN_PANEL_C2_START_44           24      /* control type: numeric, callback function: C2Start44 */
#define  MAIN_PANEL_C1_STOP_45            25      /* control type: numeric, callback function: C1Stop45 */
#define  MAIN_PANEL_C1_STOP_44            26      /* control type: numeric, callback function: C1Stop44 */
#define  MAIN_PANEL_C1_START_45           27      /* control type: numeric, callback function: C1Start45 */
#define  MAIN_PANEL_C1_START_44           28      /* control type: numeric, callback function: C1Start44 */
#define  MAIN_PANEL_REF_STOP_45           29      /* control type: numeric, callback function: REFStop45 */
#define  MAIN_PANEL_REF_STOP_44           30      /* control type: numeric, callback function: REFStop44 */
#define  MAIN_PANEL_REF_START_45          31      /* control type: numeric, callback function: REFStart45 */
#define  MAIN_PANEL_REF_START_44          32      /* control type: numeric, callback function: REFStart44 */
#define  MAIN_PANEL_TEXTMSG               33      /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_TEXTMSG_3             34      /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_TEXTMSG_2             35      /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_AUTO_45_INT_FLAG      36      /* control type: radioButton, callback function: Auto45IntFlag */
#define  MAIN_PANEL_AUTO_45_INT_OFFSET    37      /* control type: numeric, callback function: Auto45IntOffset */
#define  MAIN_PANEL_RUN_DATA_PROC         38      /* control type: command, callback function: DataProc */
#define  MAIN_PANEL_REF_CHOICE            39      /* control type: ring, callback function: RefChoice */
#define  MAIN_PANEL_REF_NOISE_START_TIME  40      /* control type: numeric, callback function: RefNoiseStartTime */
#define  MAIN_PANEL_REF_NOISE_STOP_TIME   41      /* control type: numeric, callback function: RefNoiseStopTime */
#define  MAIN_PANEL_BASELINE_NOISE_START  42      /* control type: numeric, callback function: BaselineNoiseStart */
#define  MAIN_PANEL_BASELINE_NOISE_STOP   43      /* control type: numeric, callback function: BaselineNoiseStop */
#define  MAIN_PANEL_TEXTMSG_4             44      /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_TEXTMSG_5             45      /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_TEXTMSG_6             46      /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_TEXTMSG_7             47      /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_TEXTMSG_8             48      /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_TEXTMSG_10            49      /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_TEXTMSG_11            50      /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_TEXTMSG_9             51      /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_TEXTMSG_12            52      /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_OUTPUT_SELECTION      53      /* control type: ring, callback function: OutputSelection */
#define  MAIN_PANEL_TEXTMSG_13            54      /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_TEXTMSG_14            55      /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_TEXTMSG_15            56      /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_TEXTMSG_16            57      /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_TEXTMSG_17            58      /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_TEXTMSG_18            59      /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_TEXTMSG_19            60      /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_TEXTMSG_20            61      /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_TEXTMSG_21            62      /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_TEXTMSG_22            63      /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_TEXTMSG_23            64      /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_TEXTMSG_24            65      /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_TEXTMSG_25            66      /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_TEXTMSG_26            67      /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_TEXTMSG_27            68      /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_TEXTMSG_28            69      /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_TEXTMSG_29            70      /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK AreaThreshold(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Auto45IntFlag(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Auto45IntOffset(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK BaselineNoiseStart(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK BaselineNoiseStop(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK C1Start44(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK C1Start45(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK C1Stop44(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK C1Stop45(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK C2Start44(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK C2Start45(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK C2Stop44(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK C2Stop45(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK C3Start44(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK C3Start45(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK C3Stop44(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK C3Stop45(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CertREFPdb(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK DataProc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK GCLinRegPoints(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK GCMvgAvgPoints(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK GCSamplingTime(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OutputSelection(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK QuitCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK RangeStartTime(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK RefChoice(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK REFLinRegPoints(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK REFMvgAvgPoints(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK RefNoiseStartTime(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK RefNoiseStopTime(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK REFSamplingTime(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK REFStart44(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK REFStart45(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK REFStop44(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK REFStop45(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK StartFile44(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK StartFile45(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK StartFileTemp(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK TotalGCPulses(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK TotalRuns(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
