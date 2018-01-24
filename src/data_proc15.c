// GC-C-IRMS Data Processing Software, v. 1.5

// Processes sets of .asc files, produced by PeakSimple during a GC-C-IRMS analysis of a gas sample, in order to determine the carbon isotope ratios of the methane, ethane, and propane present.


// Blake Leonard	2014

// Monitor Instruments


#include <utility.h>

#include <userint.h>

#include <cvirte.h>

#include <stdio.h>

#include <string.h>

#include <stdlib.h>

#include <math.h>

#include "dp15_main.h"

#include "dp15_pdb.h"

#include "dp15_raw_pdb.h"

#include "dp15_sig_44.h"

#include "dp15_sig_45.h"

#include "linear.h"


// Global Variable Declaration ( Peak Finding Settings)

int starting_file_num_44 = 0;

int starting_file_num_45 = 0;

int starting_file_num_temp = 0;

double software_sampling_time_ref = 0.4;                   	// seconds per point

double ref_sampling_freq = 50;

double software_sampling_time = 0.4;                    	// seconds per point
	
double gc_sampling_freq = 50;

int linear_reg_points_ref = 25;
	
int linear_reg_points = 25;

int mvg_avg_points_ref = 25;
	
int mvg_avg_points = 25;

int num_of_pulses = 3;

double cert_ref_pdb = -39.88;
	
double orig_area_threshold = 1E-8;

int ref_choice = 3;

int int_44_45_flag = 0;
	
double int_44_45_offset = 0;                        		// seconds

int total_runs = 100000; 

double range_start_time = 0;

int oxy_corr_flag = 0;

char *mode = "r"; 

char line[256]; 

int word_count, i, j;
	
double d;
	
char * next_word_ptr;

int slope_threshold_start_44[4], slope_threshold_end_44[4], slope_threshold_start_45[4], slope_threshold_end_45[4], int_start_stop_offset[4];
	
double ref_noise_start_time = 0.5, ref_noise_end_time = 0.8, baseline_noise_start_time = 0, baseline_noise_end_time = 0.3;
		
int output_selection = 0;


void main(int argc, char *argv[])
{
	
	InitCVIRTE (0, argv, 0);
	
	int main_panel = 0;
	
	DiscardPanel ( main_panel );
		
	main_panel = LoadPanel (0, "dp15_main.uir", MAIN_PANEL); 
	
	
	// Variable Declaration
	
	slope_threshold_start_44[0] = 75;                   	// Reference (micro-volts per sec)

	slope_threshold_end_44[0] =   75;                  

	slope_threshold_start_45[0] = 75;                  

	slope_threshold_end_45[0] =   75;                   
	
	slope_threshold_start_44[1] = 75;                   	// C1

	slope_threshold_end_44[1] =   75;                   

	slope_threshold_start_45[1] = 75;                  

	slope_threshold_end_45[1] =   75 ;                   
	
	slope_threshold_start_44[2] = 75;                   	// C2

	slope_threshold_end_44[2] =   75;                   

	slope_threshold_start_45[2] = 75;                   

	slope_threshold_end_45[2] =   75;                   
	
	slope_threshold_start_44[3] = 75;                   	// C3

	slope_threshold_end_44[3] =   75;                   

	slope_threshold_start_45[3] = 75;                  

	slope_threshold_end_45[3] =   75;                                 

	
	int_start_stop_offset[0] = 1;
	
	int_start_stop_offset[1] = 1;
	
	int_start_stop_offset[2] = 1;
	
	int_start_stop_offset[3] = 1;
	
	
	// Open and Read Settings File
	
	FILE *ifp;
	
	char settings_file[] = "ps_settings_15.ini";
	
	
	ifp = fopen(settings_file, mode);
	
	if (ifp == NULL) 
	{
		fprintf(stderr, "Can't open settings file.  Using internal settings.\n\n");
	}
	else
	{
			
		// Read in 44 Starting File
		
		word_count = 0;
		
		fgets(line, 256, ifp);
		
		next_word_ptr = strtok(line,":");   // split using colon as divider

		while (next_word_ptr != NULL) 
		{

			if ( word_count == 1 )
			{
				i = atoi(next_word_ptr);
					
				starting_file_num_44 = i;
				
			}
				
			word_count++;

			next_word_ptr = strtok(NULL,":");

		}
			
			
		// Read in 45 Starting File
		
		word_count = 0;
		
		fgets(line, 256, ifp);
	
		fgets(line, 256, ifp);
		
		next_word_ptr = strtok(line,":");   // split using colon as divider

		while (next_word_ptr != NULL) 
		{

			if ( word_count == 1 )
			{
				i = atoi(next_word_ptr);
					
				starting_file_num_45 = i;
				
			}
				
			word_count++;

			next_word_ptr = strtok(NULL,":");

		}

			
		// Read in TEMP Starting File
		
		word_count = 0;
		
		fgets(line, 256, ifp);
	
		fgets(line, 256, ifp);
		
		next_word_ptr = strtok(line,":");   // split using colon as divider

		while (next_word_ptr != NULL) 
		{

			if ( word_count == 1 )
			{
				i = atoi(next_word_ptr);
					
				starting_file_num_temp = i;
				
			}
				
			word_count++;

			next_word_ptr = strtok(NULL,":");

		}
			
			
		// Read in # of Runs
		
		word_count = 0;
		
		fgets(line, 256, ifp);
	
		fgets(line, 256, ifp);
		
		next_word_ptr = strtok(line,":");   // split using colon as divider

		while (next_word_ptr != NULL) 
		{

			if ( word_count == 1 )
			{
				i = atoi(next_word_ptr);
					
				total_runs = i;
				
			}
				
			word_count++;

			next_word_ptr = strtok(NULL,":");

		}
			
			
		// Read in Total GC pulses
		
		word_count = 0;
		
		fgets(line, 256, ifp);
	
		fgets(line, 256, ifp);
		
		next_word_ptr = strtok(line,":");   // split using colon as divider

		while (next_word_ptr != NULL) 
		{

			if ( word_count == 1 )
			{
				i = atoi(next_word_ptr);
					
				num_of_pulses = i;
			
			}
				
			word_count++;

			next_word_ptr = strtok(NULL,":");

		}

			
		// Read in Certified Ref PDB
		
		word_count = 0;
		
		fgets(line, 256, ifp);
	
		fgets(line, 256, ifp);
		
		next_word_ptr = strtok(line,":");   // split using colon as divider

		while (next_word_ptr != NULL) 
		{

			if ( word_count == 1 )
			{
				d = atof(next_word_ptr);
					
				cert_ref_pdb = d;
				
			}
				
			word_count++;

			next_word_ptr = strtok(NULL,":");

		}
			
			
		// Read in Range Start Time
		
		word_count = 0;
		
		fgets(line, 256, ifp);
	
		fgets(line, 256, ifp);
		
		next_word_ptr = strtok(line,":");   // split using colon as divider

		while (next_word_ptr != NULL) 
		{

			if ( word_count == 1 )
			{
				d = atof(next_word_ptr);
				
				range_start_time = d;
					
			
			}
				
			word_count++;

			next_word_ptr = strtok(NULL,":");

		}
		
			
		// Read in Area Threshold
		
		word_count = 0;
		
		fgets(line, 256, ifp);
	
		fgets(line, 256, ifp);
		
		next_word_ptr = strtok(line,":");   // split using colon as divider

		while (next_word_ptr != NULL) 
		{

			if ( word_count == 1 )
			{
				d = atof(next_word_ptr);
					
				orig_area_threshold = d;
			
			}
				
			word_count++;

			next_word_ptr = strtok(NULL,":");

		}
		

		// Read in Reference Software Sampling Time
		
		word_count = 0;
		
		fgets(line, 256, ifp);
	
		fgets(line, 256, ifp);
		
		next_word_ptr = strtok(line,":");   // split using colon as divider

		while (next_word_ptr != NULL) 
		{

			if ( word_count == 1 )
			{
				d = atof(next_word_ptr);
					
				software_sampling_time_ref = d;

			}
				
			word_count++;

			next_word_ptr = strtok(NULL,":");

		}
		

		// Read in GC Software Sampling Time
		
		word_count = 0;
		
		fgets(line, 256, ifp);
	
		fgets(line, 256, ifp);
		
		next_word_ptr = strtok(line,":");   // split using colon as divider

		while (next_word_ptr != NULL) 
		{

			if ( word_count == 1 )
			{
				d = atof(next_word_ptr);
					
				software_sampling_time = d;

			}
				
			word_count++;

			next_word_ptr = strtok(NULL,":");

		}
		

		// Read in Reference Linear Regression Points
		
		word_count = 0;
		
		fgets(line, 256, ifp);
	
		fgets(line, 256, ifp);
		
		next_word_ptr = strtok(line,":");   // split using colon as divider

		while (next_word_ptr != NULL) 
		{

			if ( word_count == 1 )
			{
				i = atoi(next_word_ptr);
					
				linear_reg_points_ref = i;
				
			}
				
			word_count++;

			next_word_ptr = strtok(NULL,":");

		}
		

		// Read in GC Linear Regression Points
		
		word_count = 0;
		
		fgets(line, 256, ifp);
	
		fgets(line, 256, ifp);
		
		next_word_ptr = strtok(line,":");   // split using colon as divider

		while (next_word_ptr != NULL) 
		{

			if ( word_count == 1 )
			{
				i = atoi(next_word_ptr);
					
				linear_reg_points = i;
				
			}
				
			word_count++;

			next_word_ptr = strtok(NULL,":");

		}
		

		// Read in Reference Moving Average Points
		
		word_count = 0;
		
		fgets(line, 256, ifp);
	
		fgets(line, 256, ifp);
		
		next_word_ptr = strtok(line,":");   // split using colon as divider

		while (next_word_ptr != NULL) 
		{

			if ( word_count == 1 )
			{
				i = atoi(next_word_ptr);
					
				mvg_avg_points_ref = i;
			
			}
				
			word_count++;

			next_word_ptr = strtok(NULL,":");

		}


		// Read in GC Moving Average Points 
		
		word_count = 0;
		
		fgets(line, 256, ifp);
	
		fgets(line, 256, ifp);
		
		next_word_ptr = strtok(line,":");   // split using colon as divider

		while (next_word_ptr != NULL) 
		{

			if ( word_count == 1 )
			{
				i = atoi(next_word_ptr);
					
				mvg_avg_points = i;
			
			}
				
			word_count++;

			next_word_ptr = strtok(NULL,":");

		}
		

		// Read in REF Slope Threshold
		
		word_count = 0;
		
		fgets(line, 256, ifp);
	
		fgets(line, 256, ifp);
		
		next_word_ptr = strtok(line,":");   // split using colon as divider

		while (next_word_ptr != NULL) 
		{

			if ( word_count == 1 )
			{
				i = atoi(next_word_ptr);
					
				slope_threshold_start_44[0] = i;                        
			
			}
			else if ( word_count == 2 )
			{
				i = atoi(next_word_ptr);
					
				slope_threshold_end_44[0] = i;                        
			
			}
			else if ( word_count == 3 )
			{
				i = atoi(next_word_ptr);
					
				slope_threshold_start_45[0] = i;                        
			
			}
			else if ( word_count == 4 )
			{
				i = atoi(next_word_ptr);
					
				slope_threshold_end_45[0] = i;                        
			
			}	

			word_count++;

			next_word_ptr = strtok(NULL,":");

		}
		

		// Read in C1 Slope Threshold
		
		word_count = 0;
		
		fgets(line, 256, ifp);
	
		fgets(line, 256, ifp);
		
		next_word_ptr = strtok(line,":");   // split using colon as divider

		while (next_word_ptr != NULL) 
		{

			if ( word_count == 1 )
			{
				i = atoi(next_word_ptr);
					
				slope_threshold_start_44[1] = i;                        
			
			}
			else if ( word_count == 2 )
			{
				i = atoi(next_word_ptr);
					
				slope_threshold_end_44[1] = i;                        
			
			}
			else if ( word_count == 3 )
			{
				i = atoi(next_word_ptr);
					
				slope_threshold_start_45[1] = i;                        
			
			}
			else if ( word_count == 4 )
			{
				i = atoi(next_word_ptr);
					
				slope_threshold_end_45[1] = i;                        
			
			}	
				
			word_count++;

			next_word_ptr = strtok(NULL,":");

		}
		

		// Read in C2 Slope Threshold
		
		word_count = 0;
		
		fgets(line, 256, ifp);
	
		fgets(line, 256, ifp);
		
		next_word_ptr = strtok(line,":");   // split using colon as divider

		while (next_word_ptr != NULL) 
		{

			if ( word_count == 1 )
			{
				i = atoi(next_word_ptr);
					
				slope_threshold_start_44[2] = i;                        
			
			}
			else if ( word_count == 2 )
			{
				i = atoi(next_word_ptr);
					
				slope_threshold_end_44[2] = i;                        
			
			}
			else if ( word_count == 3 )
			{
				i = atoi(next_word_ptr);
					
				slope_threshold_start_45[2] = i;                        
			
			}
			else if ( word_count == 4 )
			{
				i = atoi(next_word_ptr);
					
				slope_threshold_end_45[2] = i;                        
			
			}	
				
			word_count++;

			next_word_ptr = strtok(NULL,":");

		}
		

		// Read in C3 Slope Threshold
		
		word_count = 0;
		
		fgets(line, 256, ifp);
	
		fgets(line, 256, ifp);
		
		next_word_ptr = strtok(line,":");   // split using colon as divider

		while (next_word_ptr != NULL) 
		{

			if ( word_count == 1 )
			{
				i = atoi(next_word_ptr);
					
				slope_threshold_start_44[3] = i;                        
			
			}
			else if ( word_count == 2 )
			{
				i = atoi(next_word_ptr);
					
				slope_threshold_end_44[3] = i;                        
			
			}
			else if ( word_count == 3 )
			{
				i = atoi(next_word_ptr);
					
				slope_threshold_start_45[3] = i;                        
			
			}
			else if ( word_count == 4 )
			{
				i = atoi(next_word_ptr);
					
				slope_threshold_end_45[3] = i;                        
			
			}	
				
			word_count++;

			next_word_ptr = strtok(NULL,":");

		}
		
			
		// Read in Ref Choice
		
		word_count = 0;
		
		fgets(line, 256, ifp);
	
		fgets(line, 256, ifp);
		
		next_word_ptr = strtok(line,":");   // split using colon as divider

		while (next_word_ptr != NULL) 
		{

			if ( word_count == 1 )
			{
				i = atoi(next_word_ptr);
					
				ref_choice = i;
			
			}
			
			word_count++;

			next_word_ptr = strtok(NULL,":");

		}			
		

		// Read in Ref Noise Time Interval
		
		word_count = 0;
		
		fgets(line, 256, ifp);
	
		fgets(line, 256, ifp);
		
		next_word_ptr = strtok(line,":");   // split using colon as divider

		while (next_word_ptr != NULL) 
		{

			if ( word_count == 1 )
			{
				d = atof(next_word_ptr);
					
				ref_noise_start_time = d;                        
			
			}
			else if ( word_count == 2 )
			{
				d = atof(next_word_ptr);
					
				ref_noise_end_time = d;                        
			
			}
				
			word_count++;

			next_word_ptr = strtok(NULL,":");

		}		
		

		// Read in Baseline Noise Time Interval
		
		word_count = 0;
		
		fgets(line, 256, ifp);
	
		fgets(line, 256, ifp);
		
		next_word_ptr = strtok(line,":");   // split using colon as divider

		while (next_word_ptr != NULL) 
		{

			if ( word_count == 1 )
			{
				d = atof(next_word_ptr);
					
				baseline_noise_start_time = d;                        
			
			}
			else if ( word_count == 2 )
			{
				d = atof(next_word_ptr);
					
				baseline_noise_end_time = d;                        
			
			}
				
			word_count++;

			next_word_ptr = strtok(NULL,":");

		}			
		

		// Read in 44-45 Integration Flag ( decide to use 44 integration times for 45 )
		
		word_count = 0;
		
		fgets(line, 256, ifp);
	
		fgets(line, 256, ifp);
		
		next_word_ptr = strtok(line,":");   // split using colon as divider

		while (next_word_ptr != NULL) 
		{

			if ( word_count == 1 )
			{
				i = atoi(next_word_ptr);
					
				int_44_45_flag = i;
			
			}
				
			word_count++;

			next_word_ptr = strtok(NULL,":");

		}
		
			
		// Read in 44-45 Integration Time Offset
		
		word_count = 0;
		
		fgets(line, 256, ifp);
	
		fgets(line, 256, ifp);
		
		next_word_ptr = strtok(line,":");   // split using colon as divider

		while (next_word_ptr != NULL) 
		{

			if ( word_count == 1 )
			{
				d = atof(next_word_ptr);
					
				int_44_45_offset = d;
			
			}
				
			word_count++;

			next_word_ptr = strtok(NULL,":");

		}
		

		// Read in Output Selection
		
		word_count = 0;
		
		fgets(line, 256, ifp);
	
		fgets(line, 256, ifp);
		
		next_word_ptr = strtok(line,":");   // split using colon as divider

		while (next_word_ptr != NULL) 
		{

			if ( word_count == 1 )
			{
				i = atoi(next_word_ptr);
					
				output_selection = i;
			
			}
				
			word_count++;

			next_word_ptr = strtok(NULL,":");

		}			
		
	
		// Read in Oxygen Correction Flag
		
		word_count = 0;
		
		fgets(line, 256, ifp);
	
		fgets(line, 256, ifp);
		
		next_word_ptr = strtok(line,":");   // split using colon as divider

		while (next_word_ptr != NULL) 
		{

			if ( word_count == 1 )
			{
				i = atoi(next_word_ptr);
					
				oxy_corr_flag = i;
			
			}
				
			word_count++;

			next_word_ptr = strtok(NULL,":");

		}
		
				
		// Read in Integration C1 Start-Stop Offset
		
		word_count = 0;
		
		fgets(line, 256, ifp);
	
		fgets(line, 256, ifp);
		
		next_word_ptr = strtok(line,":");   // split using colon as divider

		while (next_word_ptr != NULL) 
		{

			if ( word_count == 1 )
			{
				d = atof(next_word_ptr);
				
				d = d * 60;
				
				d = d / software_sampling_time;
					
				int_start_stop_offset[0] = floor( d + 0.5);
			
			}
				
			word_count++;

			next_word_ptr = strtok(NULL,":");

		}
		

		// Read in Integration C2 Start-Stop Offset
		
		word_count = 0;
		
		fgets(line, 256, ifp);
	
		fgets(line, 256, ifp);
		
		next_word_ptr = strtok(line,":");   // split using colon as divider

		while (next_word_ptr != NULL) 
		{

			if ( word_count == 1 )
			{
				d = atof(next_word_ptr);
				
				d = d * 60;
				
				d = d / software_sampling_time;
					
				int_start_stop_offset[1] = floor( d + 0.5);
			
			}
				
			word_count++;

			next_word_ptr = strtok(NULL,":");

		}
		

		// Read in Integration C3 Start-Stop Offset
		
		word_count = 0;
		
		fgets(line, 256, ifp);
	
		fgets(line, 256, ifp);
		
		next_word_ptr = strtok(line,":");   // split using colon as divider

		while (next_word_ptr != NULL) 
		{

			if ( word_count == 1 )
			{
				d = atof(next_word_ptr);
				
				d = d * 60;
				
				d = d / software_sampling_time;
					
				int_start_stop_offset[2] = floor( d + 0.5);
			
			}
				
			word_count++;

			next_word_ptr = strtok(NULL,":");

		}
			
	}

	fclose(ifp);
	
	
	// Set Panel values to defaults from settings file
	
	SetCtrlVal (main_panel, MAIN_PANEL_START_FILE_44, starting_file_num_44);
	
	SetCtrlVal (main_panel, MAIN_PANEL_START_FILE_45, starting_file_num_45);
	
	SetCtrlVal (main_panel, MAIN_PANEL_START_FILE_TEMP, starting_file_num_temp);
	
	SetCtrlVal (main_panel, MAIN_PANEL_TOTAL_RUNS, total_runs);
	
	SetCtrlVal (main_panel, MAIN_PANEL_TOTAL_GC_PULSES, num_of_pulses);
	
	SetCtrlVal (main_panel, MAIN_PANEL_CERT_REF_PDB, cert_ref_pdb); 
	
	SetCtrlVal (main_panel, MAIN_PANEL_RANGE_START_TIME, range_start_time);
	
	SetCtrlVal (main_panel, MAIN_PANEL_AREA_THRESHOLD, orig_area_threshold);
	
	SetCtrlVal (main_panel, MAIN_PANEL_REF_SAMPLING_TIME, software_sampling_time_ref);
	
	SetCtrlVal (main_panel, MAIN_PANEL_GC_SAMPLING_TIME, software_sampling_time);
	
	SetCtrlVal (main_panel, MAIN_PANEL_REF_LIN_REG_POINTS, linear_reg_points_ref);
	
	SetCtrlVal (main_panel, MAIN_PANEL_GC_LIN_REG_POINTS, linear_reg_points);
	
	SetCtrlVal (main_panel, MAIN_PANEL_REF_MVG_AVG_POINTS, mvg_avg_points_ref); 
	
	SetCtrlVal (main_panel, MAIN_PANEL_GC_MVG_AVG_POINTS, mvg_avg_points);
	
	SetCtrlVal (main_panel, MAIN_PANEL_REF_START_44, slope_threshold_start_44[0]);
	
	SetCtrlVal (main_panel, MAIN_PANEL_REF_STOP_44, slope_threshold_end_44[0]); 
	
	SetCtrlVal (main_panel, MAIN_PANEL_REF_START_45, slope_threshold_start_45[0]); 
	
	SetCtrlVal (main_panel, MAIN_PANEL_REF_STOP_45, slope_threshold_end_45[0]);
	
	SetCtrlVal (main_panel, MAIN_PANEL_C1_START_44, slope_threshold_start_44[1]);
	
	SetCtrlVal (main_panel, MAIN_PANEL_C1_STOP_44, slope_threshold_end_44[1]); 
	
	SetCtrlVal (main_panel, MAIN_PANEL_C1_START_45, slope_threshold_start_45[1]); 
	
	SetCtrlVal (main_panel, MAIN_PANEL_C1_STOP_45, slope_threshold_end_45[1]); 
	
	SetCtrlVal (main_panel, MAIN_PANEL_C2_START_44, slope_threshold_start_44[2]);
	
	SetCtrlVal (main_panel, MAIN_PANEL_C2_STOP_44, slope_threshold_end_44[2]); 
	
	SetCtrlVal (main_panel, MAIN_PANEL_C2_START_45, slope_threshold_start_45[2]); 
	
	SetCtrlVal (main_panel, MAIN_PANEL_C2_STOP_45, slope_threshold_end_45[2]); 
	
	SetCtrlVal (main_panel, MAIN_PANEL_C3_START_44, slope_threshold_start_44[3]);
	
	SetCtrlVal (main_panel, MAIN_PANEL_C3_STOP_44, slope_threshold_end_44[3]); 
	
	SetCtrlVal (main_panel, MAIN_PANEL_C3_START_45, slope_threshold_start_45[3]); 
	
	SetCtrlVal (main_panel, MAIN_PANEL_C3_STOP_45, slope_threshold_end_45[3]);
	
	SetCtrlVal (main_panel, MAIN_PANEL_REF_CHOICE, ref_choice); 
	
	SetCtrlVal (main_panel, MAIN_PANEL_AUTO_45_INT_FLAG, int_44_45_flag); 
	
	SetCtrlVal (main_panel, MAIN_PANEL_AUTO_45_INT_OFFSET, int_44_45_offset); 
	
	SetCtrlVal (main_panel, MAIN_PANEL_REF_NOISE_START_TIME, ref_noise_start_time);  
	
	SetCtrlVal (main_panel, MAIN_PANEL_REF_NOISE_STOP_TIME, ref_noise_end_time);
	
	SetCtrlVal (main_panel, MAIN_PANEL_BASELINE_NOISE_START, baseline_noise_start_time);
	
	SetCtrlVal (main_panel, MAIN_PANEL_BASELINE_NOISE_STOP, baseline_noise_end_time);
	
	SetCtrlVal (main_panel, MAIN_PANEL_OUTPUT_SELECTION, output_selection);
	
	
	range_start_time = range_start_time * 60;
				
	range_start_time = floor ( range_start_time + 0.5 );
	
	
	DisplayPanel (main_panel); 
	
	RunUserInterface();
	
	return;
	
}


int CVICALLBACK DataProc (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	
	switch (event)
	{
		case EVENT_COMMIT:
			
		
		// Local Variable Declaration and Processing
			
		double run_time = 300;                                     		// seconds

		double hardware_sampling_time = 0.1;                    		// seconds per point

		double spillover_pct = 0.1;
	
		double max_point_slope_threshold = 300;                 		// micro-volts
	
		int ref_corr_flag = 1;
	
		double offset_voltage = 0;                         			// micro-volts
	
		double cert_ref_ratio;		 
	
		double range_end_time = run_time;
	
		FILE *ifp, *ofp;
	
		char outputFilename[] = "ps_run_output_15.txt";
	
		const int baseline_flag = 1;

		char a;

		double temp_hardware_sampling_points; 

		int hardware_sampling_points;

		double temp_software_sampling_points;

		double software_sampling_points_ref;

		double software_sampling_points;	

		double temp_soft_hard_sampling_time_ratio_ref;

		int soft_hard_sampling_time_ratio_ref;
	
		double temp_soft_hard_sampling_time_ratio;

		int soft_hard_sampling_time_ratio;

		double ratio[4], ratio_corr[4], pdb[4], raw_pdb[4];

		double pdb_max[4], pdb_min[4], pdb_range[4], raw_pdb_max[4], raw_pdb_min[4], raw_pdb_range[4];

		double temp_range_orig_start_point, temp_range_end_point;

		int range_orig_start_point_ref, range_start_point_44, range_start_point_45, range_end_point_ref, max_point_44, max_point_45;

		int range_orig_start_point, range_end_point;
	
		int istep, jstep, kstep, lstep, pstep, qstep, k, l, m, display_panel = 0;
	
		static int hardware_pulse_function_1_44[20000];

		static int hardware_pulse_function_1_45[20000];

		static int hardware_pulse_function_1_temp[20000];

		static int hardware_pulse_function_2_44[20000];
		
		static int hardware_pulse_function_2_45[20000];

		static int hardware_pulse_function_2_temp[20000];

		static double pulse_function_44_ref[20000], pulse_function_44[20000];

		static double pulse_function_45_ref[20000], pulse_function_45[20000];

		static double smoothed_pulse_function_44_ref[20000], smoothed_pulse_function_44[20000];

		static double smoothed_pulse_function_45_ref[20000], smoothed_pulse_function_45[20000];
		
		double temp_average = 0;

		double linear_reg_data[100];

		char filename[32];
		
		double area_44[4];

		double area_45[4];

		double original_ref_ratio = 0;

		int integration_start_44, integration_start_45, integration_stop_44, integration_stop_45;

		double slope, correction_factor;

		double baseline_slope_44[4], baseline_slope_45[4];

		double baseline_y_int_44[4], baseline_y_int_45[4];

		double pulse_height_44[4], pulse_height_45[4];
		
		double height_avg_44[4], height_avg_45[4], height_min_44[4], height_max_44[4], height_min_45[4], height_max_45[4];
		
		double height_range_44[4], height_range_45[4], height_std_44[4], height_std_45[4];
	
		double R;
	
		double pdb_avg[4], sig_avg_44[4], sig_avg_45[4], pdb_std[4], sig_std_44[4], sig_std_45[4];
		
		double raw_pdb_avg[4], raw_pdb_std[4];
		
		double sig_min_44[4], sig_max_44[4], sig_min_45[4], sig_max_45[4], sig_range_44[4], sig_range_45[4];
	
		int first_file_num_44 = 0, first_file_num_45 = 0, first_file_num_temp = 0;
	
		char exit_char;
		
		double int_start_time_44[4], int_stop_time_44[4], int_max_time_44[4];
	
		double int_start_time_45[4], int_stop_time_45[4], int_max_time_45[4];
		
		double start_time_avg_44[4], start_time_avg_45[4], stop_time_avg_44[4], stop_time_avg_45[4];
		
		double start_time_min_44[4], start_time_max_44[4], start_time_min_45[4], start_time_max_45[4];
		
		double stop_time_min_44[4], stop_time_max_44[4], stop_time_min_45[4], stop_time_max_45[4];
		
		double start_time_range_44[4], start_time_range_45[4], stop_time_range_44[4], stop_time_range_45[4];
		
		double start_time_std_44[4], start_time_std_45[4], stop_time_std_44[4], stop_time_std_45[4];
	
		int orig_range_start_point_44, orig_range_start_point_45;
	
		double sigma[4];
		
		int zero_signals[4];
		
		int int_time_flag = 0;
		
		double area_threshold = 1E-9;
		
		double ref_noise_44 = 0, ref_noise_45 = 0, baseline_noise_44 = 0, baseline_noise_45 = 0;
		
		double ref_noise_avg_44 = 0, ref_noise_avg_45 = 0, baseline_noise_avg_44 = 0, baseline_noise_avg_45 = 0;
		
		double temp_ref_noise_start_point, temp_ref_noise_end_point, temp_baseline_noise_start_point, temp_baseline_noise_end_point;
		
		int ref_noise_start_point, ref_noise_end_point, baseline_noise_start_point, baseline_noise_end_point;
		
		double ref_avg_44, ref_avg_45, baseline_avg_44, baseline_avg_45, temp_avg;
		
		double baseline_noise_min_44, baseline_noise_max_44, baseline_noise_min_45, baseline_noise_max_45, ref_noise_min_44, ref_noise_max_44, ref_noise_min_45, ref_noise_max_45;
		
		double temp_min, temp_max, temp_range;
		
		double baseline_noise_range_44, baseline_noise_range_45, ref_noise_range_44, ref_noise_range_45;
		
		
		double raw_pdb_save[4][total_runs], pdb_save[4][total_runs], area_44_save[4][total_runs], area_45_save[4][total_runs], pulse_height_44_save[4][total_runs], pulse_height_45_save[4][total_runs];
		
		double int_start_time_44_save[4][total_runs], int_start_time_45_save[4][total_runs], int_stop_time_44_save[4][total_runs], int_stop_time_45_save[4][total_runs];
		
		double area_44_convert[4], area_45_convert[4], sig_range_44_convert[4], sig_range_45_convert[4];
		
		char *date, *time;
								 
		date = "unknown", time = "unknown";
							   
		
		zero_signals[0] = 0, zero_signals[1] = 0, zero_signals[2] = 0, zero_signals[3] = 0;
		
		baseline_slope_44[0] = 0, baseline_slope_44[1] = 0, baseline_slope_44[2] = 0, baseline_slope_44[3] = 0;
		
		baseline_slope_45[0] = 0, baseline_slope_45[1] = 0, baseline_slope_45[2] = 0, baseline_slope_45[3] = 0; 
		
		baseline_y_int_44[0] = 0, baseline_y_int_44[1] = 0, baseline_y_int_44[2] = 0, baseline_y_int_44[3] = 0;
		
		baseline_y_int_45[0] = 0, baseline_y_int_45[1] = 0, baseline_y_int_45[2] = 0, baseline_y_int_45[3] = 0;
		

		// convert amps-sec (coulombs) to uV-sec
	
		area_threshold = ( orig_area_threshold * 1E8 ) * 1E6;
	
		
		// Convert Times to Points 
	
		temp_range_orig_start_point = range_start_time / software_sampling_time_ref;

		range_orig_start_point_ref = floor(temp_range_orig_start_point + 0.5);
	
	
		temp_range_orig_start_point = range_start_time / software_sampling_time;

		range_orig_start_point = floor(temp_range_orig_start_point + 0.5);
		
		
		// Open Output File

		ofp = fopen(outputFilename, "w");

		if (ofp == NULL) {
		  fprintf(stderr, "Can't open output file %s!\n",
				  outputFilename);
		  return 0;
		}
	
		fprintf(ofp, "Run, 44 File #, Date, Time, Raw REF, Raw C1, Raw C2, Raw C3, Corrected REF, Corrected C1, Corrected C2, Corrected C3, 44 Ref Sig (Coulombs), 45 Ref Sig (Coulombs), 44 C1 Sig (Coulombs), 45 C1 Sig (Coulombs), 44 C2 Sig (Coulombs), 45 C2 Sig (Coulombs), 44 C3 Sig (Coulombs), 45 C3 Sig (Coulombs), 44 REF Height (mV), 45 REF Height (mV), 44 C1 Height (mV), 45 C1 Height (mV), 44 C2 Height (mV), 45 C2 Height (mV), 44 C3 Height (mV), 45 C3 Height (mV), REF 44 Start Time (Min), REF 44 End Time (Min), REF 45 Start Time (Min), REF 45 End Time (Min), C1 44 Start Time (Min), C1 44 End Time (Min), C1 45 Start Time (Min), C1 45 End Time (Min), C2 44 Start Time (Min), C2 44 End Time (Min), C2 45 Start Time (Min), C2 45 End Time (Min), C3 44 Start Time (Min), C3 44 End Time (Min), C3 45 Start Time (Min), C3 45 End Time (Min), REF 44 Time STD (Sec), C1 44 Time STD (Sec), C2 44 Time STD (Sec), C3 44 Time STD (Sec),");
		
		fprintf(ofp, "REF 44 Noise STD (mV), REF 45 Noise STD (mV), Baseline 44 Noise STD (mV), Baseline 45 Noise (mV), Temperature(mV)\n");
			
		
		// Initialize Min, Max, and Sums for Averaging
	
		for ( pstep = 0; pstep < 4; pstep ++ )
		{
	
			pdb_min[pstep] = 1E6; 
			
			pdb_max[pstep] = -1E6;
			
			raw_pdb_min[pstep] = 1E6;

			raw_pdb_max[pstep] = -1E6;
			
			sig_min_44[pstep] = 1E12;
				
			sig_max_44[pstep] = -1E12;
			
			sig_min_45[pstep] = 1E12;
			
			sig_max_45[pstep] = -1E12;
			
			height_min_44[pstep] = 1E12;
			
			height_max_44[pstep] = -1E12;
			
			height_min_45[pstep] = 1E12;
			
			height_max_45[pstep] = -1E12;
			
			start_time_min_44[pstep] = 1E6;
			
			start_time_max_44[pstep] = -1E6;
			
			start_time_min_45[pstep] = 1E6;
			
			start_time_max_45[pstep] = -1E6;
			
			stop_time_min_44[pstep] = 1E6;
			
			stop_time_max_44[pstep] = -1E6;
			
			stop_time_min_45[pstep] = 1E6;
			
			stop_time_max_45[pstep] = -1E6;
			
			baseline_noise_min_44 = 1E6;
			
			baseline_noise_max_44 = -1E6;
			
			baseline_noise_min_45 = 1E6;
			
			baseline_noise_max_45 = -1E6;
			
			ref_noise_min_44 = 1E6;
			
			ref_noise_max_44 = -1E6;
			
			ref_noise_min_45 = 1E6;
			
			ref_noise_max_45 = -1E6;
			
			temp_min = 1E12;
			
			temp_max = -1E12;
			
			
			pdb_avg[pstep] = 0;   
			
			raw_pdb_avg[pstep] = 0;
			
			sig_avg_44[pstep] = 0;   
		
			sig_avg_45[pstep] = 0;
			
			height_avg_44[pstep] = 0;
			
			height_avg_45[pstep] = 0;
			
			start_time_avg_44[pstep] = 0;
				
			start_time_avg_45[pstep] = 0;
			
			stop_time_avg_44[pstep] = 0;
			
			stop_time_avg_45[pstep] = 0;
			
			ref_noise_avg_44 = 0;
			
			ref_noise_avg_45 = 0;
			
			baseline_noise_avg_44 = 0;
			
			baseline_noise_avg_45 = 0;
			
			temp_avg = 0;
			
			
			raw_pdb_std[pstep] = 0;
			
			pdb_std[pstep] = 0;
			
			sig_std_44[pstep] = 0;
			
			sig_std_45[pstep] = 0;
			
			height_std_44[pstep] = 0;
			
			height_std_45[pstep] = 0;
			
			start_time_std_44[pstep] = 0;
			
			start_time_std_45[pstep] = 0;
			
			stop_time_std_44[pstep] = 0;
			
			stop_time_std_45[pstep] = 0;
		
		}

	
		// Find First Files in backup directory
	
		for ( jstep = 1; jstep < 10000; jstep ++ )
		{
	
			sprintf( filename, "CH1 %i.asc", jstep ); 

			ifp = fopen(filename, mode);

			if (ifp != NULL) 
			{
			
				fclose(ifp); 
			
				first_file_num_44 = jstep;
			
				break;

			}
			
		}
	
	
		for ( jstep = 1; jstep < 10000; jstep ++ )
		{
	
			sprintf( filename, "CH2 %i.asc", jstep ); 

			ifp = fopen(filename, mode);

			if (ifp != NULL) 
			{
			
				fclose(ifp); 
			
				first_file_num_45 = jstep;
			
				break;

			}
		
		}
		
		for ( jstep = 1; jstep < 10000; jstep ++ )
		{
	
			sprintf( filename, "TEMP %i.asc", jstep ); 

			ifp = fopen(filename, mode);

			if (ifp != NULL) 
			{
			
				fclose(ifp); 
			
				first_file_num_temp = jstep;
			
				break;

			}
		
		}
	
		
		if ( ( starting_file_num_44 == 0 ) && ( starting_file_num_45 == 0 ) )
		{
		
			starting_file_num_44 = first_file_num_44;
		
			starting_file_num_45 = first_file_num_45;
		
		}
		
		
		if ( starting_file_num_temp == 0 )
		{
			
			starting_file_num_temp = first_file_num_temp;
			
		}
	
	
		k = starting_file_num_44;

		l = starting_file_num_45;
		
		m = starting_file_num_temp;
	
		
		DiscardPanel ( display_panel );
		
		if ( output_selection == 0 )
		{
		
			display_panel = LoadPanel (0, "dp15_pdb.uir", PDB_PANEL); 
		
			ClearStripChart (display_panel, PDB_PANEL_STRIPCHART);
	
			DisplayPanel (display_panel); 
	  
		}
		else if ( output_selection == 1 )
		{
		
			display_panel = LoadPanel (0, "dp15_raw_pdb.uir", RPDB_PANEL); 
		
			ClearStripChart (display_panel, RPDB_PANEL_STRIPCHART);
	
			DisplayPanel (display_panel); 
	  
		}
		else if ( output_selection == 2 )
		{
		
			display_panel = LoadPanel (0, "dp15_sig_44.uir", S44_PANEL); 
		
			ClearStripChart (display_panel, S44_PANEL_STRIPCHART);
	
			DisplayPanel (display_panel); 
	  
		}
		else if ( output_selection == 3 )
		{
		
			display_panel = LoadPanel (0, "dp15_sig_45.uir", S45_PANEL); 
		
			ClearStripChart (display_panel, S45_PANEL_STRIPCHART);
	
			DisplayPanel (display_panel); 
	  
		}
			
		
		// Process Data Looping through Peak Simple Data Files

		for ( jstep = 0; jstep < total_runs; jstep ++ )
		{
	
			range_start_point_44 = range_orig_start_point_ref;
		
			range_start_point_45 = range_orig_start_point_ref;
			
			
			ref_noise_44 = 0, ref_noise_45 = 0;
			
			baseline_noise_44 = 0, baseline_noise_45 = 0;
			
			ref_avg_44 = 0, ref_avg_45 = 0;
			
			baseline_avg_44 = 0, baseline_avg_45 = 0;
			
			temp_average = 0;
			

			// Read 44 Data into array
		
			sprintf( filename, "CH1 %i.asc", k ); 

			ifp = fopen(filename, mode);

			if (ifp == NULL) 
			{
			
				break;

			}


			// Skip first 18 lines

			for ( istep = 0; istep < 18; istep ++ )
			{

				fgets(line, 256, ifp);

			}
			
			
			// Read in Date
		
			fgets(line, 8, ifp);
			
			fgets(date, 11, ifp);

			fgets(line, 256, ifp);
		
			
			// Read in Time
			
			fgets(line, 8, ifp);
			
			fgets(time, 9, ifp);
		
			fgets(line, 256, ifp);
		
			
			// Read in Peak Simple Sampling Time
		
			word_count = 0;
		
			fgets(line, 256, ifp);
		
			next_word_ptr = strtok(line,"=");   // split using colon as divider

			while (next_word_ptr != NULL) 
			{

				if ( word_count == 1 )
				{
					i = atoi(next_word_ptr);
				
				}
				
				word_count++;

				next_word_ptr = strtok(NULL,"=");

			}
		
			
			// Convert Hz to sampling time
		
			if ( i == 1 )
			{
				hardware_sampling_time = 1;
			}
			else if ( i == 2 )
			{
				hardware_sampling_time = 0.5;
			}
			else if ( i == 5 )
			{
				hardware_sampling_time = 0.2;
			}
			else if ( i == 10 )
			{
				hardware_sampling_time = 0.1;
			}
			else if ( i == 20 )
			{
				hardware_sampling_time = 0.05;
			}
		
		
			// Read in # of points to compute run time
		
			word_count = 0;
		
			fgets(line, 256, ifp);
		
			next_word_ptr = strtok(line,"=");   // split using colon as divider

			while (next_word_ptr != NULL) 
			{

				if ( word_count == 1 )
				{
					i = atoi(next_word_ptr);
				
				}
				
				word_count++;

				next_word_ptr = strtok(NULL,"=");

			}
		
			run_time = i * hardware_sampling_time;
		
			range_end_time = run_time;
		
			
			// Convert Times to Points
			
			temp_hardware_sampling_points = run_time / hardware_sampling_time; 

			hardware_sampling_points = floor( temp_hardware_sampling_points + 0.5 );

			if ( ( jstep == 0 ) && ( temp_hardware_sampling_points != hardware_sampling_points ) )
			{

				// printf ("Warning: Hardware sampling points is not an integer! \n");

			}


			temp_software_sampling_points = run_time / software_sampling_time_ref;

			software_sampling_points_ref = floor ( temp_software_sampling_points + 0.5 );

			if ( ( jstep == 0 ) && ( temp_software_sampling_points != software_sampling_points_ref ) )
			{

				// printf ("Warning: Software sampling points is not an integer! \n");

			}
		
		
			temp_software_sampling_points = run_time / software_sampling_time;

			software_sampling_points = floor ( temp_software_sampling_points + 0.5 );

			if ( ( jstep == 0 ) && ( temp_software_sampling_points != software_sampling_points ) )
			{

				// printf ("Warning: Software sampling points is not an integer! \n");

			}
		
		
			temp_soft_hard_sampling_time_ratio_ref = software_sampling_time_ref / hardware_sampling_time;        // needs to be an integer

			soft_hard_sampling_time_ratio_ref = floor(temp_soft_hard_sampling_time_ratio_ref + 0.5 );

			if ( ( jstep == 0 ) && ( temp_soft_hard_sampling_time_ratio_ref != soft_hard_sampling_time_ratio_ref ) )
			{

				// printf( "Warning: Soft-Hard Gaussian Sampling time ratio is not an integer! \n");

			}
		
		
			temp_soft_hard_sampling_time_ratio = software_sampling_time / hardware_sampling_time;        // needs to be an integer

			soft_hard_sampling_time_ratio = floor(temp_soft_hard_sampling_time_ratio + 0.5 );

			if ( ( jstep == 0 ) && ( temp_soft_hard_sampling_time_ratio != soft_hard_sampling_time_ratio ) )
			{

				// printf( "Warning: Soft-Hard Ref Sampling time ratio is not an integer! \n");

			}

		
			temp_range_end_point = range_end_time / software_sampling_time_ref;

			range_end_point_ref = floor(temp_range_end_point + 0.5);
		
			temp_range_end_point = range_end_time / software_sampling_time;

			range_end_point = floor(temp_range_end_point + 0.5);
			
			
			temp_ref_noise_start_point = ref_noise_start_time / hardware_sampling_time;

			ref_noise_start_point = floor(temp_ref_noise_start_point + 0.5);
		
		
			temp_ref_noise_end_point = ref_noise_end_time / hardware_sampling_time;

			ref_noise_end_point = floor(temp_ref_noise_end_point + 0.5);
		
		
			temp_baseline_noise_start_point = baseline_noise_start_time / hardware_sampling_time;

			baseline_noise_start_point = floor(temp_baseline_noise_start_point + 0.5);
			
		
			temp_baseline_noise_end_point = baseline_noise_end_time / hardware_sampling_time;

			baseline_noise_end_point = floor(temp_baseline_noise_end_point + 0.5);
		
		
			// Skip 3 lines
		
			for ( istep = 0; istep < 3; istep ++ )
			{

				fgets(line, 256, ifp);

			}
		
			for ( istep = 0; istep < hardware_sampling_points; istep ++ )
			{
		
				word_count = 0;
		
				fgets(line, 256, ifp);
			
				next_word_ptr = strtok(line,",");   // split using comma as divider

				while (next_word_ptr != NULL) 
				{

					if ( word_count == 0 )
					{
						i = atoi(next_word_ptr);
					
						hardware_pulse_function_1_44[istep] = i + offset_voltage;
					}
					else
					{
						j = atoi(next_word_ptr);
					
						hardware_pulse_function_2_44[istep] = j + offset_voltage;
					}
				
					word_count++;

					next_word_ptr = strtok(NULL,",");

				}

			}

			k++;

			fclose(ifp);


			// Read 45 Data into array

			sprintf( filename, "CH2 %i.asc", l ); 
		
			ifp = fopen(filename, mode);

			if (ifp == NULL) 
			{
		
				break;

			}

			for ( istep = 0; istep < 25; istep ++ )
			{

				fgets(line, 256, ifp);

			}

			for ( istep = 0; istep < hardware_sampling_points; istep ++ )
			{
				word_count = 0;
		
				fgets(line, 256, ifp);
			
				next_word_ptr = strtok(line,",");   // split using comma as divider

				while (next_word_ptr != NULL) 
				{

					if ( word_count == 0 )
					{
						i = atoi(next_word_ptr);
					
						hardware_pulse_function_1_45[istep] = i + offset_voltage;
					}
					else
					{
						j = atoi(next_word_ptr);
					
						hardware_pulse_function_2_45[istep] = j + offset_voltage;
					}
				
					word_count++;

					next_word_ptr = strtok(NULL,",");

				}

			}

			l++;

			fclose(ifp);
			
			
			// Read TEMP Data into array and Average
			
			if ( starting_file_num_temp != 9999 )
			{	

				sprintf( filename, "TEMP %i.asc", m ); 
		
				ifp = fopen(filename, mode);

				if (ifp == NULL) 
				{
		
					break;

				}

				for ( istep = 0; istep < 25; istep ++ )
				{

					fgets(line, 256, ifp);

				}

				for ( istep = 0; istep < hardware_sampling_points; istep ++ )
				{
					word_count = 0;
		
					fgets(line, 256, ifp);
			
					next_word_ptr = strtok(line,",");   // split using comma as divider

					while (next_word_ptr != NULL) 
					{

						if ( word_count == 0 )
						{
							i = atoi(next_word_ptr);
					
							hardware_pulse_function_1_temp[istep] = i + offset_voltage;
						}
						else
						{
							j = atoi(next_word_ptr);
					
							hardware_pulse_function_2_temp[istep] = j + offset_voltage;
						}
				
						word_count++;

						next_word_ptr = strtok(NULL,",");

					}
					
					temp_average += hardware_pulse_function_1_temp[istep];

				}
				
				
				temp_average = ( temp_average / hardware_sampling_points ) / 1000;        // Convert to mV

				m++;

				fclose(ifp);
				
			}
		
			
			// Average Raw Peak Simple Data Points over Software Sampling Time for Ref

			for ( istep = 0; istep < software_sampling_points_ref; istep ++ )
			{	


				pulse_function_44_ref[istep] = 0;

				pulse_function_45_ref[istep] = 0;

				for ( kstep = 0; kstep < soft_hard_sampling_time_ratio_ref; kstep ++ )
				{


					pulse_function_44_ref[istep] = pulse_function_44_ref[istep] + hardware_pulse_function_1_44[( istep * soft_hard_sampling_time_ratio_ref ) + kstep];    
		
					pulse_function_45_ref[istep] = pulse_function_45_ref[istep] + hardware_pulse_function_1_45[( istep * soft_hard_sampling_time_ratio_ref ) + kstep];    


				}


				pulse_function_44_ref[istep] = pulse_function_44_ref[istep] / soft_hard_sampling_time_ratio_ref;

				pulse_function_45_ref[istep] = pulse_function_45_ref[istep] / soft_hard_sampling_time_ratio_ref;

			}
			
			
			// Caculate REF Noise
			
			for ( istep = ref_noise_start_point; istep <= ref_noise_end_point; istep ++ )
			{
				
				ref_avg_44 += hardware_pulse_function_1_44[istep];
				
				ref_avg_45 += hardware_pulse_function_1_45[istep];
				
			}
			
			ref_avg_44 = ref_avg_44 / ( ref_noise_end_point - ref_noise_start_point + 1 );
			
			
			for ( istep = ref_noise_start_point; istep <= ref_noise_end_point; istep ++ )
			{
				
				ref_noise_44 += ( ( ref_avg_44 - hardware_pulse_function_1_44[istep] ) * ( ref_avg_44 - hardware_pulse_function_1_44[istep] ) );
				
				ref_noise_45 += ( ( ref_avg_45 - hardware_pulse_function_1_45[istep] ) * ( ref_avg_45 - hardware_pulse_function_1_45[istep] ) );
				
			}
			
			ref_noise_44 = sqrt( ref_noise_44 / ( ref_noise_end_point - ref_noise_start_point + 1 ) ) / 1000;
			
			ref_noise_45 = sqrt( ref_noise_45 / ( ref_noise_end_point - ref_noise_start_point + 1 ) ) / 1000;
			
			
			// Caculate Basline Noise
			
			for ( istep = baseline_noise_start_point; istep <= baseline_noise_end_point; istep ++ )
			{
				
				baseline_avg_44 += hardware_pulse_function_1_44[istep];
				
				baseline_avg_45 += hardware_pulse_function_1_45[istep];
				
			}
			
			baseline_avg_44 = baseline_avg_44 / ( baseline_noise_end_point - baseline_noise_start_point + 1 );
			
			
			for ( istep = baseline_noise_start_point; istep <= baseline_noise_end_point; istep ++ )
			{
				
				baseline_noise_44 += ( ( baseline_avg_44 - hardware_pulse_function_1_44[istep] ) * ( baseline_avg_44 - hardware_pulse_function_1_44[istep] ) );
				
				baseline_noise_45 += ( ( baseline_avg_45 - hardware_pulse_function_1_45[istep] ) * ( baseline_avg_45 - hardware_pulse_function_1_45[istep] ) );
				
			}
			
			baseline_noise_44 = sqrt( baseline_noise_44 / ( baseline_noise_end_point - baseline_noise_start_point + 1 ) ) / 1000;
			
			baseline_noise_45 = sqrt( baseline_noise_45 / ( baseline_noise_end_point - baseline_noise_start_point + 1 ) ) / 1000;
			
			
			// Average Raw Peak Simple Data Points over Software Sampling Time for C1,C2,C3

			for ( istep = 0; istep < software_sampling_points; istep ++ )
			{	

				pulse_function_44[istep] = 0;

				pulse_function_45[istep] = 0;

				for ( kstep = 0; kstep < soft_hard_sampling_time_ratio; kstep ++ )
				{


					pulse_function_44[istep] = pulse_function_44[istep] + hardware_pulse_function_1_44[( istep * soft_hard_sampling_time_ratio ) + kstep];    
		
					pulse_function_45[istep] = pulse_function_45[istep] + hardware_pulse_function_1_45[( istep * soft_hard_sampling_time_ratio ) + kstep];    

				}


				pulse_function_44[istep] = pulse_function_44[istep] / soft_hard_sampling_time_ratio;

				pulse_function_45[istep] = pulse_function_45[istep] / soft_hard_sampling_time_ratio;

			}
			
			
			// Smooth Data Using Moving Point Average In Order To Find Integration Points for ref

			for ( istep = 0; istep < ( ( mvg_avg_points_ref - 1 ) / 2 ); istep ++ )
			{

				smoothed_pulse_function_44_ref[istep] = pulse_function_44_ref[istep];
			
				smoothed_pulse_function_45_ref[istep] = pulse_function_45_ref[istep];

			}

			for ( istep = ( ( mvg_avg_points_ref - 1 ) / 2 ); istep < ( software_sampling_points_ref - ( ( mvg_avg_points_ref - 1 ) / 2 ) ); istep ++ )
			{

				smoothed_pulse_function_44_ref[istep] = 0;

				smoothed_pulse_function_45_ref[istep] = 0;


				for ( kstep = 0; kstep < mvg_avg_points_ref; kstep ++ )
				{

					smoothed_pulse_function_44_ref[istep] += pulse_function_44_ref[( istep - ( (mvg_avg_points_ref - 1) / 2 ) ) + kstep]; 

					smoothed_pulse_function_45_ref[istep] += pulse_function_45_ref[( istep - ( (mvg_avg_points_ref - 1) / 2 ) ) + kstep];


				}

				smoothed_pulse_function_44_ref[istep] = smoothed_pulse_function_44_ref[istep] / mvg_avg_points_ref;

				smoothed_pulse_function_45_ref[istep] = smoothed_pulse_function_45_ref[istep] / mvg_avg_points_ref;

			}


			for ( istep = ( software_sampling_points_ref - ( ( mvg_avg_points_ref - 1 ) / 2 ) ); istep < software_sampling_points_ref; istep ++ )
			{

				smoothed_pulse_function_44_ref[istep] = pulse_function_44_ref[istep];

				smoothed_pulse_function_45_ref[istep] = pulse_function_45_ref[istep];

			}
			
		
			// Smooth Data Using Moving Point Average In Order To Find Integration Points for C1,C2,C3

			for ( istep = 0; istep < ( ( mvg_avg_points - 1 ) / 2 ); istep ++ )
			{

				smoothed_pulse_function_44[istep] = pulse_function_44[istep];
			
				smoothed_pulse_function_45[istep] = pulse_function_45[istep];

			}

			for ( istep = ( ( mvg_avg_points - 1 ) / 2 ); istep < ( software_sampling_points - ( ( mvg_avg_points - 1 ) / 2 ) ); istep ++ )
			{

				smoothed_pulse_function_44[istep] = 0;

				smoothed_pulse_function_45[istep] = 0;


				for ( kstep = 0; kstep < mvg_avg_points; kstep ++ )
				{

					smoothed_pulse_function_44[istep] += pulse_function_44[( istep - ( (mvg_avg_points - 1) / 2 ) ) + kstep]; 

					smoothed_pulse_function_45[istep] += pulse_function_45[( istep - ( (mvg_avg_points - 1) / 2 ) ) + kstep];


				}

				smoothed_pulse_function_44[istep] = smoothed_pulse_function_44[istep] / mvg_avg_points;

				smoothed_pulse_function_45[istep] = smoothed_pulse_function_45[istep] / mvg_avg_points;

			}


			for ( istep = ( software_sampling_points - ( ( mvg_avg_points - 1 ) / 2 ) ); istep < software_sampling_points; istep ++ )
			{

				smoothed_pulse_function_44[istep] = pulse_function_44[istep];

				smoothed_pulse_function_45[istep] = pulse_function_45[istep];

			}

		
			// Process Ref Pulse
			
			pstep = 0;
		
			while ( pstep == 0 )
			{	
				
				// Find 44 Start Point
			
				integration_start_44 = range_start_point_44;
				
				orig_range_start_point_44 = range_start_point_44;
				

				for ( istep = ( range_start_point_44 + ( ( linear_reg_points_ref - 1 ) / 2 ) ); istep < range_end_point_ref; istep ++ )
				{

					// Linear Regression on surrounding n points

					for ( kstep = 0; kstep < linear_reg_points_ref; kstep ++ )
					{
					
						linear_reg_data[kstep] = smoothed_pulse_function_44_ref[( istep - ( (linear_reg_points_ref - 1) / 2 ) ) + kstep];

					}
				
					slope = linear_reg(linear_reg_data, linear_reg_points_ref, software_sampling_time_ref);
				
					if ( slope > slope_threshold_start_44[pstep] )
					{

						integration_start_44 = istep;

						break;

					}	

				}
				
				
				// If no 44 start point was found, set all output values to zero and break out of loop
				
				if ( integration_start_44 == range_start_point_44 )
				{
					
					for ( qstep = 0; qstep < 4; qstep ++ )
					{
						
						area_44[qstep] = 0;
						
						area_45[qstep] = 0;
						
						ratio[qstep] = 0;
						
						ratio_corr[qstep] = 0;
						
						pdb[qstep] = 0;
						
						sigma[qstep] = 0;		
						
					}
						
					break;
					
				}
				

				// Find 45 Start Point
				
				integration_start_45 = range_start_point_45;
				
				orig_range_start_point_45 = range_start_point_45;
				

				for ( istep = ( range_start_point_45 + ( ( linear_reg_points_ref - 1 ) / 2 ) ); istep < range_end_point; istep ++ )
				{

					// Linear Regression on surrounding n points

					for ( kstep = 0; kstep < linear_reg_points_ref; kstep ++ )
					{
					
						linear_reg_data[kstep] = smoothed_pulse_function_45_ref[( istep - ( (linear_reg_points_ref - 1) / 2 ) ) + kstep];

					}

					slope = linear_reg(linear_reg_data, linear_reg_points_ref, software_sampling_time_ref);

					if ( slope >  slope_threshold_start_45[pstep]  )
					{

						integration_start_45 = istep;

						break;
					}

				}
				
				
				// If no 45 start point was found, set all output values to zero and break out of loop
				
				if ( integration_start_45 == range_start_point_45 )
				{
					
					for ( qstep = 0; qstep < 4; qstep ++ )
					{
						
						area_44[qstep] = 0;
						
						area_45[qstep] = 0;
						
						ratio[qstep] = 0;
						
						ratio_corr[qstep] = 0;
						
						pdb[qstep] = 0;
						
						sigma[qstep] = 0;	
						
					}
						
					break;
					
				}
			
				
				// Find Max Points

				max_point_44 = range_end_point_ref - ( ( linear_reg_points_ref - 1 ) / 2 );

				for ( istep = integration_start_44; istep < ( range_end_point_ref - ( ( linear_reg_points_ref - 1 ) / 2 ) ); istep ++ )
				{

					// Linear Regression on surrounding n points

					for ( kstep = 0; kstep < linear_reg_points_ref; kstep ++ )
					{
			
						linear_reg_data[kstep] = smoothed_pulse_function_44_ref[( istep - ( (linear_reg_points_ref - 1) / 2 ) ) + kstep];

					}

					slope = linear_reg(linear_reg_data, linear_reg_points_ref, software_sampling_time_ref);

					if ( ( slope < 0 ) && ( smoothed_pulse_function_44_ref[istep] < smoothed_pulse_function_44_ref[istep - 1] ) )
					{
			
						max_point_44 = istep;
					
						pulse_height_44[pstep] = smoothed_pulse_function_44_ref[istep];

						break;

					}

				}


				max_point_45 = range_end_point_ref - ( ( linear_reg_points_ref - 1 ) / 2 );

				for ( istep = integration_start_45; istep < ( range_end_point_ref - ( ( linear_reg_points_ref - 1 ) / 2 ) ); istep ++ )
				{

					// Linear Regression on surrounding n points

					for ( kstep = 0; kstep < linear_reg_points_ref; kstep ++ )
					{
			
						linear_reg_data[kstep] = smoothed_pulse_function_45_ref[( istep - ( (linear_reg_points_ref - 1) / 2 ) ) + kstep];

					}

					slope = linear_reg(linear_reg_data, linear_reg_points_ref, software_sampling_time_ref);

					if ( ( slope < 0 ) && ( smoothed_pulse_function_45_ref[istep] < smoothed_pulse_function_45_ref[istep - 1] ) )
					{
			
						max_point_45 = istep;
					
						pulse_height_45[pstep] = smoothed_pulse_function_45_ref[istep];

						break;

					}

				}
			

				// Find End Points

				integration_stop_44 = range_end_point_ref - ( ( linear_reg_points_ref - 1 ) / 2 );

				for ( istep = max_point_44; istep < ( range_end_point_ref - ( ( linear_reg_points_ref - 1 ) / 2 ) ); istep ++ )
				{

					// Linear Regression on surrounding n points

					for ( kstep = 0; kstep < linear_reg_points_ref; kstep ++ )
					{
			
						linear_reg_data[kstep] = smoothed_pulse_function_44_ref[( istep - ( (linear_reg_points_ref - 1) / 2 ) ) + kstep];

					}

					slope = linear_reg(linear_reg_data, linear_reg_points_ref, software_sampling_time_ref);

					if ( ( slope > ( -1 * slope_threshold_end_44[pstep] ) ) && ( smoothed_pulse_function_44_ref[istep] < ( 0.5 * pulse_height_44[pstep] ) ) )
					{
			
						integration_stop_44 = istep;
					
						range_start_point_44 = integration_stop_44 + int_start_stop_offset[pstep];

						break;

					}

				}
				

				integration_stop_45 = range_end_point_ref - ( ( linear_reg_points_ref - 1 ) / 2 );

				for ( istep = max_point_45; istep < ( range_end_point_ref - ( ( linear_reg_points_ref - 1 ) / 2 ) ); istep ++ )
				{

					// Linear Regression on surrounding n points

					for ( kstep = 0; kstep < linear_reg_points_ref; kstep ++ )
					{
			
						linear_reg_data[kstep] = smoothed_pulse_function_45_ref[( istep - ( (linear_reg_points_ref - 1) / 2 ) ) + kstep];

					}

					slope = linear_reg(linear_reg_data, linear_reg_points_ref, software_sampling_time_ref);

					if ( ( slope > ( -1 * slope_threshold_end_45[pstep] ) ) && ( smoothed_pulse_function_45_ref[istep] < ( 0.5 * pulse_height_45[pstep] ) ) )
					{
			
						integration_stop_45 = istep;
					
						range_start_point_45 = integration_stop_45 + int_start_stop_offset[pstep];

						break;

					}

				}
			

				// Determine Baselines and Subtract Off

				if ( baseline_flag == 1 )
				{

					baseline_slope_44[pstep] = ( smoothed_pulse_function_44_ref[integration_stop_44] - smoothed_pulse_function_44_ref[integration_start_44] ) / ( ( integration_stop_44 - integration_start_44 ) * software_sampling_time_ref );

					baseline_slope_45[pstep] = ( smoothed_pulse_function_45_ref[integration_stop_45] - smoothed_pulse_function_45_ref[integration_start_45] ) / ( ( integration_stop_45 - integration_start_45 ) * software_sampling_time_ref );


					baseline_y_int_44[pstep] = ( smoothed_pulse_function_44_ref[integration_start_44] ) - ( baseline_slope_44[pstep] * (integration_start_44) * software_sampling_time_ref );

					baseline_y_int_45[pstep] = ( smoothed_pulse_function_45_ref[integration_start_45] ) - ( baseline_slope_45[pstep] * (integration_start_45) * software_sampling_time_ref );

					for ( istep = integration_start_44; istep < integration_stop_44; istep ++ )
					{

						pulse_function_44_ref[istep] -= ( baseline_slope_44[pstep] * ( istep * software_sampling_time_ref ) + baseline_y_int_44[pstep] );

					}

					for ( istep = integration_start_45; istep < integration_stop_45; istep ++ )
					{

						pulse_function_45_ref[istep] -= ( baseline_slope_45[pstep] * ( istep * software_sampling_time_ref ) + baseline_y_int_45[pstep] );

					}

				}
				
				
				// Allow 45 integration to use 44 times
			
				if ( int_44_45_flag == 1 )
				{
			
					integration_start_45 = integration_start_44 + floor ( 0.5 + ( int_44_45_offset / software_sampling_time_ref ) );
				
					max_point_45 = max_point_44 + floor ( 0.5 + ( int_44_45_offset / software_sampling_time_ref ) );
				
					integration_stop_45 = integration_stop_44 + floor ( 0.5 + ( int_44_45_offset / software_sampling_time_ref ) );
			
				}
			

				// Compute Areas

				area_44[pstep] = 0;

				for ( istep = integration_start_44; istep <= integration_stop_44; istep ++ )
				{
					
					area_44[pstep] = area_44[pstep] + pulse_function_44_ref[istep]; 

				}

				area_45[pstep] = 0;

				for ( istep = integration_start_45; istep <= integration_stop_45; istep ++ )
				{
			
					area_45[pstep] = area_45[pstep] + pulse_function_45_ref[istep]; 

				}
				

				area_44[pstep] = area_44[pstep] * software_sampling_time_ref;

				area_45[pstep] = area_45[pstep] * software_sampling_time_ref;
				
				
				// Estimate Pulse STD based on 44 
				
				sigma[pstep] = area_44[pstep] / ( 2.506628 * pulse_height_44[pstep] );
			
			
				pstep ++; 
				
			
				// If Area is too small, reject
			
				if ( ( area_44[pstep-1] < area_threshold ) && ( area_45[pstep-1] < area_threshold )  )
				{
			
					pstep --;
				
					range_start_point_44 = integration_stop_44;
				
					range_start_point_45 = integration_stop_45;
				
					// Break out if at end of data
				
					if ( integration_stop_44 == range_end_point_ref - ( ( linear_reg_points_ref - 1 ) / 2 ) )
					{
					
						break;
					
					} 
			
				}
				else if ( area_44[pstep-1] < area_threshold )
				{
			
					pstep --;
				
					range_start_point_44 = integration_stop_44;
				
					range_start_point_45 = orig_range_start_point_45;
			
				}
				else if ( area_45[pstep-1] < area_threshold )
				{
			
					pstep --;
				
					range_start_point_44 = orig_range_start_point_44;
				
					range_start_point_45 = integration_stop_45;
			
				}
				else
				{
			
					int_start_time_44[pstep-1] = ( integration_start_44 * software_sampling_time_ref ) / 60;

					int_stop_time_44[pstep-1] = ( integration_stop_44 * software_sampling_time_ref ) / 60;
				
					int_max_time_44[pstep-1] = ( max_point_44 * software_sampling_time_ref ) / 60;
				
				
					int_start_time_45[pstep-1] = ( integration_start_45 * software_sampling_time_ref ) / 60;

					int_stop_time_45[pstep-1] = ( integration_stop_45 * software_sampling_time_ref ) / 60;
				
					int_max_time_45[pstep-1] = ( max_point_45 * software_sampling_time_ref ) / 60;
			
				}
			
			}
			
		
			// Process C1, C2, and C3

			for ( pstep = 1; pstep < ( num_of_pulses + 1 ); pstep ++ )
			{
					
				// If no start point was found during ref pulse code, break out of loop
				
				if ( area_44[0] == 0 )
				{
					
					break;
					
				}
				
				
				// Find Start Points
				
				range_start_point_44 = floor ( 0.5 + range_start_point_44 * ( software_sampling_time_ref / software_sampling_time ) );
			
				range_start_point_45 = floor ( 0.5 + range_start_point_45 * ( software_sampling_time_ref / software_sampling_time ) );

				integration_start_44 = range_start_point_44;
				
				orig_range_start_point_44 = range_start_point_44;

				for ( istep = ( range_start_point_44 + ( ( linear_reg_points - 1 ) / 2 ) ); istep < range_end_point; istep ++ )
				{

					// Linear Regression on surrounding n points

					for ( kstep = 0; kstep < linear_reg_points; kstep ++ )
					{
					
						linear_reg_data[kstep] = smoothed_pulse_function_44[( istep - ( (linear_reg_points - 1) / 2 ) ) + kstep];

					}
				
					slope = linear_reg(linear_reg_data, linear_reg_points, software_sampling_time);
				
					if ( slope > slope_threshold_start_44[pstep] )
					{

						integration_start_44 = istep;

						break;

					}

				}
				
				
				// If no 44 start point was found, set all output values to zero and break out of loop
				
				if ( integration_start_44 == range_start_point_44 )
				{
					
					for ( qstep = pstep; qstep < ( num_of_pulses + 1 ); qstep ++ )
					{
						
						area_44[qstep] = 0;
						
						area_45[qstep] = 0;
						
						ratio[qstep] = 0;
						
						ratio_corr[qstep] = 0;
						
						pdb[qstep] = 0;
						
						sigma[qstep] = 0;
						
						
					}
						
					break;
					
				}
			
			
				integration_start_45 = range_start_point_45;
				
				orig_range_start_point_45 = range_start_point_45;

				for ( istep = ( range_start_point_45 + ( ( linear_reg_points - 1 ) / 2 ) ); istep < range_end_point; istep ++ )
				{

					// Linear Regression on surrounding n points

					for ( kstep = 0; kstep < linear_reg_points; kstep ++ )
					{
					
						linear_reg_data[kstep] = smoothed_pulse_function_45[( istep - ( (linear_reg_points - 1) / 2 ) ) + kstep];

					}

					slope = linear_reg(linear_reg_data, linear_reg_points, software_sampling_time);

					if ( slope >  slope_threshold_start_45[pstep]  )
					{

						integration_start_45 = istep;

						break;
					}

				}
				

				// If no 45 start point was found, set all output values to zero and break out of loop
				
				if ( integration_start_45 == range_start_point_45 )
				{
					
					for ( qstep = pstep; qstep < ( num_of_pulses + 1 ); qstep ++ )
					{
						
						area_44[qstep] = 0;
						
						area_45[qstep] = 0;
						
						ratio[qstep] = 0;
						
						ratio_corr[qstep] = 0;
						
						pdb[qstep] = 0;
						
						sigma[qstep] = 0;
						
						
					}
						
					break;
					
				}
				
			
				// Find Max Points

				max_point_44 = range_end_point - ( ( linear_reg_points - 1 ) / 2 );

				for ( istep = integration_start_44; istep < ( range_end_point - ( ( linear_reg_points - 1 ) / 2 ) ); istep ++ )
				{

					// Linear Regression on surrounding n points

					for ( kstep = 0; kstep < linear_reg_points; kstep ++ )
					{
			
						linear_reg_data[kstep] = smoothed_pulse_function_44[( istep - ( (linear_reg_points - 1) / 2 ) ) + kstep];

					}

					slope = linear_reg(linear_reg_data, linear_reg_points, software_sampling_time);

					if ( ( slope < 0 ) && ( smoothed_pulse_function_44[istep] < smoothed_pulse_function_44[istep - 1] ) )
					{
			
						pulse_height_44[pstep] = smoothed_pulse_function_44[istep];
			
						max_point_44 = istep;

						break;

					}

				}


				max_point_45 = range_end_point - ( ( linear_reg_points - 1 ) / 2 );

				for ( istep = integration_start_45; istep < ( range_end_point - ( ( linear_reg_points - 1 ) / 2 ) ); istep ++ )
				{

					// Linear Regression on surrounding n points

					for ( kstep = 0; kstep < linear_reg_points; kstep ++ )
					{
			
						linear_reg_data[kstep] = smoothed_pulse_function_45[( istep - ( (linear_reg_points - 1) / 2 ) ) + kstep];

					}

					slope = linear_reg(linear_reg_data, linear_reg_points, software_sampling_time);

					if ( ( slope < 0 ) && ( smoothed_pulse_function_45[istep] < smoothed_pulse_function_45[istep - 1] ) )
					{
			
						pulse_height_45[pstep] = smoothed_pulse_function_45[istep];
			
						max_point_45 = istep;

						break;

					}

				}
			

				// Find End Points

				integration_stop_44 = range_end_point - ( ( linear_reg_points - 1 ) / 2 );

				for ( istep = max_point_44; istep < ( range_end_point - ( ( linear_reg_points - 1 ) / 2 ) ); istep ++ )
				{

					// Linear Regression on surrounding n points

					for ( kstep = 0; kstep < linear_reg_points; kstep ++ )
					{
			
						linear_reg_data[kstep] = smoothed_pulse_function_44[( istep - ( (linear_reg_points - 1) / 2 ) ) + kstep];

					}

					slope = linear_reg(linear_reg_data, linear_reg_points, software_sampling_time);

					if ( ( slope > ( -1 * slope_threshold_end_44[pstep] ) ) && ( smoothed_pulse_function_44[istep] < ( 0.5 * pulse_height_44[pstep] ) )  )
					{
			
						integration_stop_44 = istep;
					
						range_start_point_44 = integration_stop_44 + int_start_stop_offset[pstep];

						break;

					}

				}
				

				integration_stop_45 = range_end_point - ( ( linear_reg_points - 1 ) / 2 );

				for ( istep = max_point_45; istep < ( range_end_point - ( ( linear_reg_points - 1 ) / 2 ) ); istep ++ )
				{

					// Linear Regression on surrounding n points

					for ( kstep = 0; kstep < linear_reg_points; kstep ++ )
					{
			
						linear_reg_data[kstep] = smoothed_pulse_function_45[( istep - ( (linear_reg_points - 1) / 2 ) ) + kstep];

					}

					slope = linear_reg(linear_reg_data, linear_reg_points, software_sampling_time);

					if ( ( slope > ( -1 * slope_threshold_end_45[pstep] ) ) && ( smoothed_pulse_function_45[istep] < ( 0.5 * pulse_height_45[pstep] ) ) )
					{
			
						integration_stop_45 = istep;
					
						range_start_point_45 = integration_stop_45 + int_start_stop_offset[pstep];

						break;

					}

				}
				

				// Determine Baselines and Subtract Off

				if ( baseline_flag == 1 )
				{

					baseline_slope_44[pstep] = ( smoothed_pulse_function_44[integration_stop_44] - smoothed_pulse_function_44[integration_start_44] ) / ( ( integration_stop_44 - integration_start_44 ) * software_sampling_time );

					baseline_slope_45[pstep] = ( smoothed_pulse_function_45[integration_stop_45] - smoothed_pulse_function_45[integration_start_45] ) / ( ( integration_stop_45 - integration_start_45 ) * software_sampling_time );


					baseline_y_int_44[pstep] = ( smoothed_pulse_function_44[integration_start_44] ) - ( baseline_slope_44[pstep] * (integration_start_44) * software_sampling_time );

					baseline_y_int_45[pstep] = ( smoothed_pulse_function_45[integration_start_45] ) - ( baseline_slope_45[pstep] * (integration_start_45) * software_sampling_time );


					for ( istep = integration_start_44; istep < integration_stop_44; istep ++ )
					{

						pulse_function_44[istep] -= ( baseline_slope_44[pstep] * ( istep * software_sampling_time ) + baseline_y_int_44[pstep] );

					}

					for ( istep = integration_start_45; istep < integration_stop_45; istep ++ )
					{

						pulse_function_45[istep] -= ( baseline_slope_45[pstep] * ( istep * software_sampling_time ) + baseline_y_int_45[pstep] );

					}

				}
				
				
				// Allow 45 integration to use 44 times
			
				if ( int_44_45_flag == 1 )
				{
			
					integration_start_45 = integration_start_44 + floor ( 0.5 + ( int_44_45_offset / software_sampling_time ) );
				
					max_point_45 = max_point_44 + floor ( 0.5 + ( int_44_45_offset / software_sampling_time ) );
				
					integration_stop_45 = integration_stop_44 + floor ( 0.5 + ( int_44_45_offset / software_sampling_time ) );
			
				}

				
				// Compute Areas

				area_44[pstep] = 0;
				
				pulse_height_44[pstep] = 0;

				for ( istep = integration_start_44; istep <= integration_stop_44; istep ++ )
				{

					area_44[pstep] = area_44[pstep] + pulse_function_44[istep]; 
					
					
					// Find actual pulse height for estimating STD
					
					if ( pulse_function_44[istep] > pulse_height_44[pstep] )
					{
						
						pulse_height_44[pstep] = pulse_function_44[istep];
						
					}

				}

				area_45[pstep] = 0;

				for ( istep = integration_start_45; istep <= integration_stop_45; istep ++ )
				{
			
					area_45[pstep] = area_45[pstep] + pulse_function_45[istep]; 

				}

				area_44[pstep] = area_44[pstep] * software_sampling_time;

				area_45[pstep] = area_45[pstep] * software_sampling_time;
				
				
				// Estimate Pulse STD based on 44 
				
				sigma[pstep] = area_44[pstep] / ( 2.506628 * pulse_height_44[pstep] );
				
			
				// If Area is too small, reject	
			
				if ( ( area_44[pstep] < area_threshold ) && ( area_45[pstep] < area_threshold )  )
				{
			
					pstep --;
				
					range_start_point_44 = integration_stop_44;
				
					range_start_point_45 = integration_stop_45;
				
				
					// Break out if at end of data
				
					if ( integration_stop_44 == range_end_point - ( ( linear_reg_points - 1 ) / 2 ) )
					{
					
						break;
					
					}
			
				}
				else if ( area_44[pstep] < area_threshold )
				{
			
					pstep --;
				
					range_start_point_44 = integration_stop_44;
				
					range_start_point_45 = orig_range_start_point_45;
			
				}
				else if ( area_45[pstep] < area_threshold )
				{
			
					pstep --;
				
					range_start_point_44 = orig_range_start_point_44;
				
					range_start_point_45 = integration_stop_45;
			
				}
				else
				{
			
					int_start_time_44[pstep] = ( integration_start_44 * software_sampling_time ) / 60;

					int_stop_time_44[pstep] = ( integration_stop_44 * software_sampling_time ) / 60;
				
					int_max_time_44[pstep] = ( max_point_44 * software_sampling_time ) / 60;
				
				
					int_start_time_45[pstep] = ( integration_start_45 * software_sampling_time ) / 60;

					int_stop_time_45[pstep] = ( integration_stop_45 * software_sampling_time ) / 60;
				
					int_max_time_45[pstep] = ( max_point_45 * software_sampling_time ) / 60;
			
				}
			
			}
		
		
			// Derive spillover percentage correction from certified ref value
		
			if ( cert_ref_pdb != 0 )
			{
		
				if ( (jstep == 0 ) && ( oxy_corr_flag == 1 ) )
				{
			
					R = 0.0112372 * ( 1 + ( cert_ref_pdb / 1000 ) );
				
					cert_ref_ratio = ( -0.0007416 - ( R * 0.999258 ) ) / ( R - 1 );
				
					spillover_pct = 1 - ( cert_ref_ratio * 100 * area_44[0] / area_45[0] );
			
				}
				else if ( (jstep == 0 ) && ( oxy_corr_flag == 0 ) )
				{
			
					cert_ref_ratio = 0.0112372 * ( 1 + ( cert_ref_pdb / 1000 ) );
			
					spillover_pct = 1 - ( cert_ref_ratio * 100 * area_44[0] / area_45[0] );
				
				}
			
			}
			else
			{
		
				spillover_pct = 0;
			
			}

		
			for ( pstep = 0; pstep < ( num_of_pulses + 1 ); pstep ++ )
			{

				area_45[pstep] = area_45[pstep] - spillover_pct * area_45[pstep];    // spillover correction
		
				ratio[pstep] = area_45[pstep] / ( 100 * area_44[pstep] );
		
		
				if ( oxy_corr_flag == 1 )
				{
			
					R = ( ratio[pstep] - 0.0007416 ) / ( 0.999258 + ratio[pstep] );
				
					// ratio[pstep] = 1 - R;
				
					// R = R / ratio[pstep];
				
					ratio[pstep] = R;
				
				}
	
			}
		

			if ( jstep == 0 )
			{
				original_ref_ratio = ratio[ref_choice];

			}
		
		
			// Apply Correction Factor and Calculate PDB's from Ratio

			correction_factor = ratio[ref_choice] - original_ref_ratio;
		

			ratio_corr[0] = ratio[0] - correction_factor;

			ratio_corr[1] = ratio[1] - correction_factor;

			ratio_corr[2] = ratio[2] - correction_factor;
			
			ratio_corr[3] = ratio[3] - correction_factor;
		
			
			raw_pdb[0] = 1000 * ( ( ratio[0] / 0.0112372 ) - 1 );

			raw_pdb[1] = 1000 * ( ( ratio[1] / 0.0112372 ) - 1 );
		
			raw_pdb[2] = 1000 * ( ( ratio[2] / 0.0112372 ) - 1 );
		
			raw_pdb[3] = 1000 * ( ( ratio[3] / 0.0112372 ) - 1 );
			

			pdb[0] = 1000 * ( ( ratio_corr[0] / 0.0112372 ) - 1 );

			pdb[1] = 1000 * ( ( ratio_corr[1] / 0.0112372 ) - 1 );
		
			pdb[2] = 1000 * ( ( ratio_corr[2] / 0.0112372 ) - 1 );
		
			pdb[3] = 1000 * ( ( ratio_corr[3] / 0.0112372 ) - 1 );
			
			
			// If no peak was found, set ratios to zero and pdb's to current average
			
			for ( pstep = 0; pstep < ( num_of_pulses + 1 ); pstep ++ )
			{
			
				if ( area_44[pstep] == 0 )
				{
				
					for ( qstep = pstep; qstep < ( num_of_pulses + 1 ); qstep ++ )
					{
						
						ratio[qstep] = 0;
						
						ratio_corr[qstep] = 0;
						
						raw_pdb[qstep] = raw_pdb_avg[qstep] / jstep;
						
						pdb[qstep] = pdb_avg[qstep] / jstep;
						
						zero_signals[qstep] ++;
						
					}
					
					break;
				
				}
				
			}


			// Check if current values are mins or maxs and record and calculate ranges, update sums for calculating averages
			
			for ( pstep = 0; pstep < ( num_of_pulses + 1 ); pstep ++ )
			{
				
				// Raw PDB
				
				if ( raw_pdb[pstep] < raw_pdb_min[pstep] )
				{

					raw_pdb_min[pstep] = raw_pdb[pstep];

				}
			
				if ( raw_pdb[pstep] > raw_pdb_max[pstep] )
				{

					raw_pdb_max[pstep] = raw_pdb[pstep];

				}
			
				raw_pdb_range[pstep] = raw_pdb_max[pstep] - raw_pdb_min[pstep];
				
				
				
				// PDB	
				
				if ( pdb[pstep] < pdb_min[pstep] )
				{

					pdb_min[pstep] = pdb[pstep];

				}
			
				if ( pdb[pstep] > pdb_max[pstep] )
				{

					pdb_max[pstep] = pdb[pstep];

				}
			
				pdb_range[pstep] = pdb_max[pstep] - pdb_min[pstep];
				
				
				// 44 Signal	
				
				if ( area_44[pstep] < sig_min_44[pstep] )
				{

					sig_min_44[pstep] = area_44[pstep];

				}
			
				if ( area_44[pstep] > sig_max_44[pstep] )
				{

					sig_max_44[pstep] = area_44[pstep];

				}
			
				sig_range_44[pstep] = sig_max_44[pstep] - sig_min_44[pstep];
				
				
				// 45 Signal	
				
				if ( area_45[pstep] < sig_min_45[pstep] )
				{

					sig_min_45[pstep] = area_45[pstep];

				}
			
				if ( area_45[pstep] > sig_max_45[pstep] )
				{

					sig_max_45[pstep] = area_45[pstep];

				}
			
				sig_range_45[pstep] = sig_max_45[pstep] - sig_min_45[pstep];
				
				
				// 44 Height	
				
				if ( pulse_height_44[pstep] < height_min_44[pstep] )
				{

					height_min_44[pstep] = pulse_height_44[pstep];

				}
			
				if ( pulse_height_44[pstep] > height_max_44[pstep] )
				{

					height_max_44[pstep] = pulse_height_44[pstep];

				}
			
				height_range_44[pstep] = height_max_44[pstep] - height_min_44[pstep];
				
				
				// 45 Height	
				
				if ( pulse_height_45[pstep] < height_min_45[pstep] )
				{

					height_min_45[pstep] = pulse_height_45[pstep];

				}
			
				if ( pulse_height_45[pstep] > height_max_45[pstep] )
				{

					height_max_45[pstep] = pulse_height_45[pstep];

				}
			
				height_range_45[pstep] = height_max_45[pstep] - height_min_45[pstep];
				
				
				// 44 Start Time	
				
				if ( int_start_time_44[pstep] < start_time_min_44[pstep] )
				{

					start_time_min_44[pstep] = int_start_time_44[pstep];

				}
			
				if ( int_start_time_44[pstep] > start_time_max_44[pstep] )
				{

					start_time_max_44[pstep] = int_start_time_44[pstep];

				}
			
				start_time_range_44[pstep] = start_time_max_44[pstep] - start_time_min_44[pstep];
				
				
				// 45 Start Time	
				
				if ( int_start_time_45[pstep] < start_time_min_45[pstep] )
				{

					start_time_min_45[pstep] = int_start_time_45[pstep];

				}
			
				if ( int_start_time_45[pstep] > start_time_max_45[pstep] )
				{

					start_time_max_45[pstep] = int_start_time_45[pstep];

				}
			
				start_time_range_45[pstep] = start_time_max_45[pstep] - start_time_min_45[pstep];
				
				
				// 44 Stop Time	
				
				if ( int_stop_time_44[pstep] < stop_time_min_44[pstep] )
				{

					stop_time_min_44[pstep] = int_stop_time_44[pstep];

				}
			
				if ( int_stop_time_44[pstep] > stop_time_max_44[pstep] )
				{

					stop_time_max_44[pstep] = int_stop_time_44[pstep];

				}
			
				stop_time_range_44[pstep] = stop_time_max_44[pstep] - stop_time_min_44[pstep];
				
				
				// 45 Stop Time	
				
				if ( int_stop_time_45[pstep] < stop_time_min_45[pstep] )
				{

					stop_time_min_45[pstep] = int_stop_time_45[pstep];

				}
			
				if ( int_stop_time_45[pstep] > stop_time_max_45[pstep] )
				{

					stop_time_max_45[pstep] = int_stop_time_45[pstep];

				}
			
				stop_time_range_45[pstep] = stop_time_max_45[pstep] - stop_time_min_45[pstep];
				
				
				raw_pdb_avg[pstep] += raw_pdb[pstep];
			
				pdb_avg[pstep] += pdb[pstep];
				
				sig_avg_44[pstep] += area_44[pstep];
				
				sig_avg_45[pstep] += area_45[pstep];
				
				height_avg_44[pstep] += pulse_height_44[pstep];
				
				height_avg_45[pstep] += pulse_height_45[pstep];
				
				start_time_avg_44[pstep] += int_start_time_44[pstep];
				
				start_time_avg_45[pstep] += int_start_time_45[pstep];
				
				stop_time_avg_44[pstep] += int_stop_time_44[pstep]; 
				
				stop_time_avg_45[pstep] += int_stop_time_45[pstep]; 
				
					
				// Record values for use in standard deviation calculation at end
			
				raw_pdb_save[pstep][jstep] = raw_pdb[pstep];
				
				pdb_save[pstep][jstep] = pdb[pstep];
				
				area_44_save[pstep][jstep] = area_44[pstep];
				
				area_45_save[pstep][jstep] = area_45[pstep];
				
				pulse_height_44_save[pstep][jstep] = pulse_height_44[pstep];
				
				pulse_height_45_save[pstep][jstep] = pulse_height_45[pstep];  
				
				int_start_time_44_save[pstep][jstep] = int_start_time_44[pstep];
				
				int_start_time_45_save[pstep][jstep] = int_start_time_45[pstep];
				
				int_stop_time_44_save[pstep][jstep] = int_stop_time_44[pstep];
				
				int_stop_time_45_save[pstep][jstep] = int_stop_time_45[pstep];
				
				
				// Convert Units
				
				area_44_convert[pstep] = ( ( area_44[pstep] * 1E-6 ) / 1E8 );

				area_45_convert[pstep] = ( ( area_45[pstep] * 1E-6 ) / 1E10 );

				sig_range_44_convert[pstep] = ( ( sig_range_44[pstep] * 1E-6 ) / 1E8 ); 

				sig_range_45_convert[pstep] = ( ( sig_range_45[pstep] * 1E-6 ) / 1E10 ); 					

			}
			
			
			// 44 Baseline Noise	
				
			if ( baseline_noise_44 < baseline_noise_min_44 )
			{

				baseline_noise_min_44 = baseline_noise_44;

			}
			
			if ( baseline_noise_44 > baseline_noise_max_44 )
			{

				baseline_noise_max_44 = baseline_noise_44;

			}
			
			baseline_noise_range_44 = baseline_noise_max_44 - baseline_noise_min_44;
			
			
			// 45 Baseline Noise	
				
			if ( baseline_noise_45 < baseline_noise_min_45 )
			{

				baseline_noise_min_45 = baseline_noise_45;

			}
			
			if ( baseline_noise_45 > baseline_noise_max_45 )
			{

				baseline_noise_max_45 = baseline_noise_45;

			}
			
			baseline_noise_range_45 = baseline_noise_max_45 - baseline_noise_min_45;
			
			
			// 44 Ref Noise	
				
			if ( ref_noise_44 < ref_noise_min_44 )
			{

				ref_noise_min_44 = ref_noise_44;

			}
			
			if ( ref_noise_44 > ref_noise_max_44 )
			{

				ref_noise_max_44 = ref_noise_44;

			}
			
			ref_noise_range_44 = ref_noise_max_44 - ref_noise_min_44;
			
			
			// 45 Ref Noise	
				
			if ( ref_noise_45 < ref_noise_min_45 )
			{

				ref_noise_min_45 = ref_noise_45;

			}
			
			if ( ref_noise_45 > ref_noise_max_45 )
			{

				ref_noise_max_45 = ref_noise_45;

			}
			
			ref_noise_range_45 = ref_noise_max_45 - ref_noise_min_45; 
			
			
			// Temp	
				
			if ( temp_average < temp_min )
			{

				temp_min = temp_average;

			}
			
			if ( temp_average > temp_max )
			{

				temp_max = temp_average;

			}
			
			temp_range = temp_max - temp_min;
			
			
			baseline_noise_avg_44 += baseline_noise_44;
			
			baseline_noise_avg_45 += baseline_noise_45;
			
			ref_noise_avg_44 += ref_noise_44;
			
			ref_noise_avg_45 += ref_noise_45;
			
			temp_avg += temp_average;
			
		
			// Ouput Single Run Data to File 

			fprintf(ofp, "%i, %i, %s, %s, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.6g, %.6g, %.6g, %.6g, %.6g, %.6g, %.6g, %.6g, %.6g, %.6g, %.6g, %.6g, %.6g, %.6g, %.6g, %.6g, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.2f, %.2f, %.2f, %.2f, %.6f, %.6f, %.6f, %.6f, %.4f \n", jstep + 1, k - 1, date, time, raw_pdb[0], raw_pdb[1], raw_pdb[2], raw_pdb[3], pdb[0], pdb[1], pdb[2], pdb[3], ( area_44[0] * 1E-6 ) / (1E8) , ( area_45[0] * 1E-6) / (1E10), ( area_44[1] * 1E-6 ) / (1E8) , ( area_45[1] * 1E-6) / (1E10), ( area_44[2] * 1E-6 ) / (1E8) , ( area_45[2] * 1E-6) / (1E10), ( area_44[3] * 1E-6 ) / (1E8) , ( area_45[3] * 1E-6) / (1E10), pulse_height_44[0] / 1000, pulse_height_45[0] / 1000, pulse_height_44[1] / 1000, pulse_height_45[1] / 1000, pulse_height_44[2] / 1000, pulse_height_45[2] / 1000, pulse_height_44[3] / 1000, pulse_height_45[3] / 1000, int_start_time_44[0], int_stop_time_44[0], int_start_time_45[0], int_stop_time_45[0],
		    int_start_time_44[1], int_stop_time_44[1], int_start_time_45[1], int_stop_time_45[1], int_start_time_44[2], int_stop_time_44[2], int_start_time_45[2], int_stop_time_45[2], int_start_time_44[3], int_stop_time_44[3], int_start_time_45[3], int_stop_time_45[3], sigma[0], sigma[1], sigma[2], sigma[3], ref_noise_44, ref_noise_45, baseline_noise_44, baseline_noise_45, temp_average);
		
			
			// Plot point on PDB Strip Chart ( Lab Windows )
			
			if ( output_selection == 0 )
			{	
	
				PlotStripChart (display_panel, PDB_PANEL_STRIPCHART, pdb, 4, 0, 0, VAL_DOUBLE);
		
				SetCtrlVal (display_panel, PDB_PANEL_REF_PDB, pdb[0]); 
			
				SetCtrlVal (display_panel, PDB_PANEL_C1_PDB, pdb[1]); 
		
				SetCtrlVal (display_panel, PDB_PANEL_C2_PDB, pdb[2]);  
			
				SetCtrlVal (display_panel, PDB_PANEL_C3_PDB, pdb[3]);
			
				SetCtrlVal (display_panel, PDB_PANEL_REF_PDB_RANGE, pdb_range[0]); 
			
				SetCtrlVal (display_panel, PDB_PANEL_C1_PDB_RANGE, pdb_range[1]); 
		
				SetCtrlVal (display_panel, PDB_PANEL_C2_PDB_RANGE, pdb_range[2]);  
			
				SetCtrlVal (display_panel, PDB_PANEL_C3_PDB_RANGE, pdb_range[3]);
				
			}
			else if ( output_selection == 1 )
			{	
	
				PlotStripChart (display_panel, RPDB_PANEL_STRIPCHART, raw_pdb, 4, 0, 0, VAL_DOUBLE);
		
				SetCtrlVal (display_panel, RPDB_PANEL_REF_RAW_PDB, raw_pdb[0]); 
			
				SetCtrlVal (display_panel, RPDB_PANEL_C1_RAW_PDB, raw_pdb[1]); 
		
				SetCtrlVal (display_panel, RPDB_PANEL_C2_RAW_PDB, raw_pdb[2]);  
			
				SetCtrlVal (display_panel, RPDB_PANEL_C3_RAW_PDB, raw_pdb[3]);
				
				SetCtrlVal (display_panel, RPDB_PANEL_REF_RAW_PDB_RANGE, raw_pdb_range[0]); 
			
				SetCtrlVal (display_panel, RPDB_PANEL_C1_RAW_PDB_RANGE, raw_pdb_range[1]); 
		
				SetCtrlVal (display_panel, RPDB_PANEL_C2_RAW_PDB_RANGE, raw_pdb_range[2]);  
			
				SetCtrlVal (display_panel, RPDB_PANEL_C3_RAW_PDB_RANGE, raw_pdb_range[3]);
				
			}
			else if ( output_selection == 2 )
			{	
	
				PlotStripChart (display_panel, S44_PANEL_STRIPCHART, area_44_convert, 4, 0, 0, VAL_DOUBLE);
		
				SetCtrlVal (display_panel, S44_PANEL_REF_SIG_44, area_44_convert[0]); 
			
				SetCtrlVal (display_panel, S44_PANEL_C1_SIG_44, area_44_convert[1]); 
		
				SetCtrlVal (display_panel, S44_PANEL_C2_SIG_44, area_44_convert[2]);  
			
				SetCtrlVal (display_panel, S44_PANEL_C3_SIG_44, area_44_convert[3]);
				
				SetCtrlVal (display_panel, S44_PANEL_REF_SIG_RANGE_44, sig_range_44_convert[0]); 
			
				SetCtrlVal (display_panel, S44_PANEL_C1_SIG_RANGE_44, sig_range_44_convert[1]); 
		
				SetCtrlVal (display_panel, S44_PANEL_C2_SIG_RANGE_44, sig_range_44_convert[2]);  
			
				SetCtrlVal (display_panel, S44_PANEL_C3_SIG_RANGE_44, sig_range_44_convert[3]);
				
			}
			else if ( output_selection == 3 )
			{	
	
				PlotStripChart (display_panel, S45_PANEL_STRIPCHART, area_45_convert, 4, 0, 0, VAL_DOUBLE);
		
				SetCtrlVal (display_panel, S45_PANEL_REF_SIG_45, area_45_convert[0]); 
			
				SetCtrlVal (display_panel, S45_PANEL_C1_SIG_45, area_45_convert[1]); 
		
				SetCtrlVal (display_panel, S45_PANEL_C2_SIG_45, area_45_convert[2]);  
			
				SetCtrlVal (display_panel, S45_PANEL_C3_SIG_45, area_45_convert[3]);
				
				SetCtrlVal (display_panel, S45_PANEL_REF_SIG_RANGE_45, sig_range_45_convert[0]); 
			
				SetCtrlVal (display_panel, S45_PANEL_C1_SIG_RANGE_45, sig_range_45_convert[1]); 
		
				SetCtrlVal (display_panel, S45_PANEL_C2_SIG_RANGE_45, sig_range_45_convert[2]);  
			
				SetCtrlVal (display_panel, S45_PANEL_C3_SIG_RANGE_45, sig_range_45_convert[3]);
				
			}
			
			
			//SetCtrlVal (display_panel, RPDB_PANEL_C1_SIGNAL, ( area_44[1] * 1E-6 ) / (1E8) ); 
		
			//SetCtrlVal (display_panel, RPDB_PANEL_C2_SIGNAL, ( area_44[2] * 1E-6 ) / (1E8) );  
			
			//SetCtrlVal (display_panel, RPDB_PANEL_C3_SIGNAL, ( area_44[3] * 1E-6 ) / (1E8) ); 
			
			//SetCtrlVal (display_panel, RPDB_PANEL_REF_SIGNAL, ( area_44[0] * 1E-6 ) / (1E8) );  			

		}


		// Calculate Averages and STD's

		for ( pstep = 0; pstep < ( num_of_pulses + 1 ); pstep ++ )
		{
	
			raw_pdb_avg[pstep] = raw_pdb_avg[pstep] / jstep;
			
			pdb_avg[pstep] = pdb_avg[pstep] / jstep; 
				
			sig_avg_44[pstep] = sig_avg_44[pstep] / ( jstep - zero_signals[pstep] );
			
			sig_avg_45[pstep] = sig_avg_45[pstep] / ( jstep - zero_signals[pstep] );
			
			height_avg_44[pstep] = height_avg_44[pstep] / ( jstep - zero_signals[pstep] );
			
			height_avg_45[pstep] = height_avg_45[pstep] / ( jstep - zero_signals[pstep] );
			
			start_time_avg_44[pstep] = start_time_avg_44[pstep] / ( jstep - zero_signals[pstep] ); 
			
			start_time_avg_45[pstep] = start_time_avg_45[pstep] / ( jstep - zero_signals[pstep] );
			
			stop_time_avg_44[pstep] = stop_time_avg_44[pstep] / ( jstep - zero_signals[pstep] );
			
			stop_time_avg_45[pstep] = stop_time_avg_45[pstep] / ( jstep - zero_signals[pstep] ); 
			
			
			for ( qstep = 0; qstep < jstep; qstep++ )
			{
				
				raw_pdb_std[pstep] += ( ( raw_pdb_avg[pstep] - raw_pdb_save[pstep][qstep] ) * ( raw_pdb_avg[pstep] - raw_pdb_save[pstep][qstep] ) );
				
				pdb_std[pstep] += ( ( pdb_avg[pstep] - pdb_save[pstep][qstep] ) * ( pdb_avg[pstep] - pdb_save[pstep][qstep] ) );
				
				sig_std_44[pstep] += ( ( sig_avg_44[pstep] - area_44_save[pstep][qstep] ) * ( sig_avg_44[pstep] - area_44_save[pstep][qstep] ) );
				
				sig_std_45[pstep] += ( ( sig_avg_45[pstep] - area_45_save[pstep][qstep] ) * ( sig_avg_45[pstep] - area_45_save[pstep][qstep] ) );
				
				height_std_44[pstep] += ( ( height_avg_44[pstep] - pulse_height_44_save[pstep][qstep] ) * ( height_avg_44[pstep] - pulse_height_44_save[pstep][qstep] ) );
				
				height_std_45[pstep] += ( ( height_avg_45[pstep] - pulse_height_45_save[pstep][qstep] ) * ( height_avg_45[pstep] - pulse_height_45_save[pstep][qstep] ) );
				
				start_time_std_44[pstep] += ( ( start_time_avg_44[pstep] - int_start_time_44_save[pstep][qstep] ) * ( start_time_avg_44[pstep] - int_start_time_44_save[pstep][qstep] ) );  
				
				start_time_std_45[pstep] += ( ( start_time_avg_45[pstep] - int_start_time_45_save[pstep][qstep] ) * ( start_time_avg_45[pstep] - int_start_time_45_save[pstep][qstep] ) );
				
				stop_time_std_44[pstep] += ( ( stop_time_avg_44[pstep] - int_stop_time_44_save[pstep][qstep] ) * ( stop_time_avg_44[pstep] - int_stop_time_44_save[pstep][qstep] ) );
				
				stop_time_std_45[pstep] += ( ( stop_time_avg_45[pstep] - int_stop_time_45_save[pstep][qstep] ) * ( stop_time_avg_45[pstep] - int_stop_time_45_save[pstep][qstep] ) );
				
			}
			
			
			raw_pdb_std[pstep] = sqrt( raw_pdb_std[pstep] / jstep ); 
			
			pdb_std[pstep] = sqrt( pdb_std[pstep] / jstep );
			
			sig_std_44[pstep] = sqrt( sig_std_44[pstep] / jstep ); 
			
			sig_std_45[pstep] = sqrt( sig_std_45[pstep] / jstep );
			
			height_std_44[pstep] = sqrt( height_std_44[pstep] / jstep );
			
			height_std_45[pstep] = sqrt( height_std_45[pstep] / jstep );
			
			start_time_std_44[pstep] = sqrt( start_time_std_44[pstep] / jstep );
			
			start_time_std_45[pstep] = sqrt( start_time_std_45[pstep] / jstep ); 
			
			stop_time_std_44[pstep] = sqrt( stop_time_std_44[pstep] / jstep ); 
			
			stop_time_std_45[pstep] = sqrt( stop_time_std_45[pstep] / jstep );
		
			
			// Convert Units
			
			sig_range_44[pstep] = ( ( sig_range_44[pstep] * 1E-6 ) / (1E8) );
			
			sig_range_45[pstep] = ( ( sig_range_45[pstep] * 1E-6 ) / (1E10) );
			
			height_range_44[pstep] = height_range_44[pstep] / 1000;
			
			height_range_45[pstep] = height_range_45[pstep] / 1000;
			
			sig_avg_44[pstep] = ( ( sig_avg_44[pstep] * 1E-6 ) / (1E8) ); 
			
			sig_avg_45[pstep] = ( ( sig_avg_45[pstep] * 1E-6 ) / (1E10) ); 
			
			height_avg_44[pstep] = height_avg_44[pstep] / 1000;
			
			height_avg_45[pstep] = height_avg_45[pstep] / 1000;
			
			sig_std_44[pstep] = ( ( sig_std_44[pstep] * 1E-6 ) / (1E8) );
			
			sig_std_45[pstep] = ( ( sig_std_45[pstep] * 1E-6 ) / (1E10) );
			
			height_std_44[pstep] = height_std_44[pstep] / 1000;
			
			height_std_45[pstep] = height_std_45[pstep] / 1000;
						
		}
	
		baseline_noise_avg_44 = baseline_noise_avg_44 / jstep;
			
		baseline_noise_avg_45 = baseline_noise_avg_45 / jstep; 
			
		ref_noise_avg_44 = ref_noise_avg_44 / jstep; 
			
		ref_noise_avg_45 = ref_noise_avg_45 / jstep;
			
		temp_avg = temp_avg / jstep;
	
		
		// Output Averages, Ranges, and STD's to File
		
		fprintf(ofp, "\n\nAverage:,,,, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.6g, %.6g, %.6g, %.6g, %.6g, %.6g, %.6g, %.6g, %.6g, %.6g, %.6g, %.6g, %.6g, %.6g, %.6g, %.6g, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f,,,,, %.6f, %.6f, %.6f, %.6f, %.4f\n", raw_pdb_avg[0], raw_pdb_avg[1], raw_pdb_avg[2], raw_pdb_avg[3], pdb_avg[0], pdb_avg[1], pdb_avg[2], pdb_avg[3], sig_avg_44[0], sig_avg_45[0], sig_avg_44[1], sig_avg_45[1], sig_avg_44[2], sig_avg_45[2], sig_avg_44[3], sig_avg_45[3], height_avg_44[0], height_avg_45[0], height_avg_44[1], height_avg_45[1], height_avg_44[2], height_avg_45[2], height_avg_44[3], height_avg_45[3], start_time_avg_44[0], stop_time_avg_44[0], start_time_avg_45[0], stop_time_avg_45[0], start_time_avg_44[1], stop_time_avg_44[1], start_time_avg_45[1], stop_time_avg_45[1], start_time_avg_44[2], stop_time_avg_44[2], start_time_avg_45[2], stop_time_avg_45[2],
		start_time_avg_44[3], stop_time_avg_44[3],start_time_avg_45[3], stop_time_avg_45[3], ref_noise_avg_44, ref_noise_avg_45, baseline_noise_avg_44, baseline_noise_avg_45, temp_avg);  
		
		fprintf(ofp, "\nSTD:,,,, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.6g, %.6g, %.6g, %.6g, %.6g, %.6g, %.6g, %.6g, %.6g, %.6g, %.6g, %.6g, %.6g, %.6g, %.6g, %.6g, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f\n", raw_pdb_std[0], raw_pdb_std[1], raw_pdb_std[2], raw_pdb_std[3], pdb_std[0], pdb_std[1], pdb_std[2], pdb_std[3], sig_std_44[0], sig_std_45[0], sig_std_44[1], sig_std_45[1], sig_std_44[2], sig_std_45[2], sig_std_44[3], sig_std_45[3], height_std_44[0], height_std_45[0], height_std_44[1], height_std_45[1], height_std_44[2], height_std_45[2], height_std_44[3], height_std_45[3], start_time_std_44[0], stop_time_std_44[0], start_time_std_45[0], stop_time_std_45[0], start_time_std_44[1], stop_time_std_44[1], start_time_std_45[1], stop_time_std_45[1], start_time_std_44[2], stop_time_std_44[2], start_time_std_45[2], stop_time_std_45[2], start_time_std_44[3], stop_time_std_44[3], start_time_std_45[3], stop_time_std_45[3]);  
		
		fprintf(ofp, "\nRange:,,,, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.6g, %.6g, %.6g, %.6g, %.6g, %.6g, %.6g, %.6g, %.6g, %.6g, %.6g, %.6g, %.6g, %.6g, %.6g, %.6g, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f,,,,, %.6f, %.6f, %.6f, %.6f, %.4f\n", raw_pdb_range[0], raw_pdb_range[1], raw_pdb_range[2], raw_pdb_range[3], pdb_range[0], pdb_range[1], pdb_range[2], pdb_range[3], sig_range_44[0], sig_range_45[0], sig_range_44[1], sig_range_45[1], sig_range_44[2], sig_range_45[2], sig_range_44[3], sig_range_45[3], height_range_44[0], height_range_45[0], height_range_44[1], height_range_45[1], height_range_44[2], height_range_45[2], height_range_44[3], height_range_45[3],
		start_time_range_44[0], stop_time_range_44[0], start_time_range_45[0], stop_time_range_45[0], start_time_range_44[1], stop_time_range_44[1], start_time_range_45[1], stop_time_range_45[1], start_time_range_44[2], stop_time_range_44[2], start_time_range_45[2], stop_time_range_45[2], start_time_range_44[3], stop_time_range_44[3], start_time_range_45[3], stop_time_range_45[3], ref_noise_range_44, ref_noise_range_45, baseline_noise_range_44, baseline_noise_range_45, temp_range);
		
		
		// Output Data to Panel
		
		if ( output_selection == 0 )
		{
			
			SetCtrlVal (display_panel, PDB_PANEL_REF_PDB_AVG, pdb_avg[0]);  
		
			SetCtrlVal (display_panel, PDB_PANEL_C1_PDB_AVG, pdb_avg[1]);
	
			SetCtrlVal (display_panel, PDB_PANEL_C2_PDB_AVG, pdb_avg[2]); 
	
			SetCtrlVal (display_panel, PDB_PANEL_C3_PDB_AVG, pdb_avg[3]);
			
			SetCtrlVal (display_panel, PDB_PANEL_REF_PDB_STD, pdb_std[0]);  
		
			SetCtrlVal (display_panel, PDB_PANEL_C1_PDB_STD, pdb_std[1]);
	
			SetCtrlVal (display_panel, PDB_PANEL_C2_PDB_STD, pdb_std[2]); 
	
			SetCtrlVal (display_panel, PDB_PANEL_C3_PDB_STD, pdb_std[3]);		

		}
		else if ( output_selection == 1 )
		{
			
			SetCtrlVal (display_panel, RPDB_PANEL_REF_RAW_PDB_AVG, raw_pdb_avg[0]);  
		
			SetCtrlVal (display_panel, RPDB_PANEL_C1_RAW_PDB_AVG, raw_pdb_avg[1]);
	
			SetCtrlVal (display_panel, RPDB_PANEL_C2_RAW_PDB_AVG, raw_pdb_avg[2]); 
	
			SetCtrlVal (display_panel, RPDB_PANEL_C3_RAW_PDB_AVG, raw_pdb_avg[3]);
			
			SetCtrlVal (display_panel, RPDB_PANEL_REF_RAW_PDB_STD, raw_pdb_std[0]);  
		
			SetCtrlVal (display_panel, RPDB_PANEL_C1_RAW_PDB_STD, raw_pdb_std[1]);
	
			SetCtrlVal (display_panel, RPDB_PANEL_C2_RAW_PDB_STD, raw_pdb_std[2]); 
	
			SetCtrlVal (display_panel, RPDB_PANEL_C3_RAW_PDB_STD, raw_pdb_std[3]);	
			
		}
		else if ( output_selection == 2 )
		{	
		
			SetCtrlVal (display_panel, S44_PANEL_REF_SIG_AVG_44, sig_avg_44[0]); 
			
			SetCtrlVal (display_panel, S44_PANEL_C1_SIG_AVG_44, sig_avg_44[1]); 
		
			SetCtrlVal (display_panel, S44_PANEL_C2_SIG_AVG_44, sig_avg_44[2]);  
			
			SetCtrlVal (display_panel, S44_PANEL_C3_SIG_AVG_44, sig_avg_44[3]);
				
			SetCtrlVal (display_panel, S44_PANEL_REF_SIG_STD_44, sig_std_44[0]); 
			
			SetCtrlVal (display_panel, S44_PANEL_C1_SIG_STD_44, sig_std_44[1]); 
		
			SetCtrlVal (display_panel, S44_PANEL_C2_SIG_STD_44, sig_std_44[2]);  
			
			SetCtrlVal (display_panel, S44_PANEL_C3_SIG_STD_44, sig_std_44[3]);
				
		}
		else if ( output_selection == 3 )
		{	
		
			SetCtrlVal (display_panel, S45_PANEL_REF_SIG_AVG_45, sig_avg_45[0]); 
			
			SetCtrlVal (display_panel, S45_PANEL_C1_SIG_AVG_45, sig_avg_45[1]); 
		
			SetCtrlVal (display_panel, S45_PANEL_C2_SIG_AVG_45, sig_avg_45[2]);  
			
			SetCtrlVal (display_panel, S45_PANEL_C3_SIG_AVG_45, sig_avg_45[3]);
				
			SetCtrlVal (display_panel, S45_PANEL_REF_SIG_STD_45,sig_std_45[0]); 
			
			SetCtrlVal (display_panel, S45_PANEL_C1_SIG_STD_45, sig_std_45[1]); 
		
			SetCtrlVal (display_panel, S45_PANEL_C2_SIG_STD_45, sig_std_45[2]);  
			
			SetCtrlVal (display_panel, S45_PANEL_C3_SIG_STD_45, sig_std_45[3]);
				
		}
		
		 
		//SetCtrlVal (display_panel, RPDB_PANEL_C1_AVG_SIGNAL, sig_avg_44[1]); 
	
		//SetCtrlVal (display_panel, RPDB_PANEL_C2_AVG_SIGNAL, sig_avg_44[2]); 
	
		//SetCtrlVal (display_panel, RPDB_PANEL_C3_AVG_SIGNAL, sig_avg_44[3]); 
		
		//SetCtrlVal (display_panel, RPDB_PANEL_REF_AVG_SIGNAL, sig_avg_44[0]);	
		
	
		fclose(ofp);
	
	}

	return 0;
	
}


int CVICALLBACK ReturnToMain (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	
	switch (event)
	{
		case EVENT_COMMIT:
	
		DiscardPanel ( panel );
	
		break;
		
	}

	return 0;
	
}
	

int CVICALLBACK QuitCallback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
			CloseCVIRTE (); 
			
			QuitUserInterface( 0 );

			break;
	}

	return 0;
}


int CVICALLBACK StartFile44 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
						  
	switch (event)
	{
		case EVENT_COMMIT:
			
		GetCtrlVal (panel, control, &starting_file_num_44);	
			
	}
	
	return 0;
	
}

int CVICALLBACK StartFile45 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
						  
	switch (event)
	{
		case EVENT_COMMIT:
			
		GetCtrlVal (panel, control, &starting_file_num_45);	
			
	}
	
	return 0;
	
}

int CVICALLBACK StartFileTemp (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
						  
	switch (event)
	{
		case EVENT_COMMIT:
			
		GetCtrlVal (panel, control, &starting_file_num_temp);	
			
	}
	
	return 0;
	
}

int CVICALLBACK TotalRuns (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
						  
	switch (event)
	{
		case EVENT_COMMIT:
			
		GetCtrlVal (panel, control, &total_runs);	
			
	}
	
	return 0;
	
}

int CVICALLBACK TotalGCPulses (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
						  
	switch (event)
	{
		case EVENT_COMMIT:
			
		GetCtrlVal (panel, control, &num_of_pulses);	
			
	}
	
	return 0;
	
}

int CVICALLBACK CertREFPdb (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
						  
	switch (event)
	{
		case EVENT_COMMIT:
			
		GetCtrlVal (panel, control, &cert_ref_pdb);	
			
	}
	
	return 0;
	
}

int CVICALLBACK RangeStartTime (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
						  
	switch (event)
	{
		case EVENT_COMMIT:
			
		GetCtrlVal (panel, control, &range_start_time);	
			
	}
	
	return 0;
	
}

int CVICALLBACK AreaThreshold (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
						  
	switch (event)
	{
		case EVENT_COMMIT:
			
		GetCtrlVal (panel, control, &orig_area_threshold);	
			
	}
	
	return 0;
	
}

int CVICALLBACK REFSamplingTime (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
						  
	switch (event)
	{
		case EVENT_COMMIT:
			
		GetCtrlVal (panel, control, &software_sampling_time_ref);	
			
	}
	
	return 0;
	
}

int CVICALLBACK GCSamplingTime (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
						  
	switch (event)
	{
		case EVENT_COMMIT:
			
		GetCtrlVal (panel, control, &software_sampling_time);	
			
	}
	
	return 0;
	
}

int CVICALLBACK REFLinRegPoints (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
						  
	switch (event)
	{
		case EVENT_COMMIT:
			
		GetCtrlVal (panel, control, &linear_reg_points_ref);	
			
	}
	
	return 0;
	
}

int CVICALLBACK GCLinRegPoints (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
						  
	switch (event)
	{
		case EVENT_COMMIT:
			
		GetCtrlVal (panel, control, &linear_reg_points);	
			
	}
	
	return 0;
	
}

int CVICALLBACK REFMvgAvgPoints (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
						  
	switch (event)
	{
		case EVENT_COMMIT:
			
		GetCtrlVal (panel, control, &mvg_avg_points_ref);	
			
	}
	
	return 0;
	
}

int CVICALLBACK GCMvgAvgPoints (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
						  
	switch (event)
	{
		case EVENT_COMMIT:
			
		GetCtrlVal (panel, control, &mvg_avg_points);	
			
	}
	
	return 0;
	
}

int CVICALLBACK REFStart44 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
						  
	switch (event)
	{
		case EVENT_COMMIT:
			
		GetCtrlVal (panel, control, &slope_threshold_start_44[0]);	
			
	}
	
	return 0;
	
}

int CVICALLBACK REFStop44 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
						  
	switch (event)
	{
		case EVENT_COMMIT:
			
		GetCtrlVal (panel, control, &slope_threshold_end_44[0]);	
			
	}
	
	return 0;
	
}

int CVICALLBACK REFStart45 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
						  
	switch (event)
	{
		case EVENT_COMMIT:
			
		GetCtrlVal (panel, control, &slope_threshold_start_45[0]);	
			
	}
	
	return 0;
	
}

int CVICALLBACK REFStop45 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
						  
	switch (event)
	{
		case EVENT_COMMIT:
			
		GetCtrlVal (panel, control, &slope_threshold_end_45[0]);	
			
	}
	
	return 0;
	
}

int CVICALLBACK C1Start44 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
						  
	switch (event)
	{
		case EVENT_COMMIT:
			
		GetCtrlVal (panel, control, &slope_threshold_start_44[1]);	
			
	}
	
	return 0;
	
}

int CVICALLBACK C1Stop44 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
						  
	switch (event)
	{
		case EVENT_COMMIT:
			
		GetCtrlVal (panel, control, &slope_threshold_end_44[1]);	
			
	}
	
	return 0;
	
}

int CVICALLBACK C1Start45 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
						  
	switch (event)
	{
		case EVENT_COMMIT:
			
		GetCtrlVal (panel, control, &slope_threshold_start_45[1]);	
			
	}
	
	return 0;
	
}

int CVICALLBACK C1Stop45 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
						  
	switch (event)
	{
		case EVENT_COMMIT:
			
		GetCtrlVal (panel, control, &slope_threshold_end_45[1]);	
			
	}
	
	return 0;
	
}

int CVICALLBACK C2Start44 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
						  
	switch (event)
	{
		case EVENT_COMMIT:
			
		GetCtrlVal (panel, control, &slope_threshold_start_44[2]);	
			
	}
	
	return 0;
	
}

int CVICALLBACK C2Stop44 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
						  
	switch (event)
	{
		case EVENT_COMMIT:
			
		GetCtrlVal (panel, control, &slope_threshold_end_44[2]);	
			
	}
	
	return 0;
	
}

int CVICALLBACK C2Start45 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
						  
	switch (event)
	{
		case EVENT_COMMIT:
			
		GetCtrlVal (panel, control, &slope_threshold_start_45[2]);	
			
	}
	
	return 0;
	
}

int CVICALLBACK C2Stop45 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
						  
	switch (event)
	{
		case EVENT_COMMIT:
			
		GetCtrlVal (panel, control, &slope_threshold_end_45[2]);	
			
	}
	
	return 0;
	
}

int CVICALLBACK C3Start44 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
						  
	switch (event)
	{
		case EVENT_COMMIT:
			
		GetCtrlVal (panel, control, &slope_threshold_start_44[3]);	
			
	}
	
	return 0;
	
}

int CVICALLBACK C3Stop44 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
						  
	switch (event)
	{
		case EVENT_COMMIT:
			
		GetCtrlVal (panel, control, &slope_threshold_end_44[3]);	
			
	}
	
	return 0;
	
}

int CVICALLBACK C3Start45 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
						  
	switch (event)
	{
		case EVENT_COMMIT:
			
		GetCtrlVal (panel, control, &slope_threshold_start_45[3]);	
			
	}
	
	return 0;
	
}

int CVICALLBACK C3Stop45 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
						  
	switch (event)
	{
		case EVENT_COMMIT:
			
		GetCtrlVal (panel, control, &slope_threshold_end_45[3]);	
			
	}
	
	return 0;
	
}

int CVICALLBACK RefChoice (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
						  
	switch (event)
	{
		case EVENT_COMMIT:
			
		GetCtrlVal (panel, control, &ref_choice);	
			
	}
	
	return 0;
	
}

int CVICALLBACK Auto45IntFlag (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
						  
	switch (event)
	{
		case EVENT_COMMIT:
			
		GetCtrlVal (panel, control, &int_44_45_flag);	
			
	}
	
	return 0;
	
}

int CVICALLBACK Auto45IntOffset (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
						  
	switch (event)
	{
		case EVENT_COMMIT:
			
		GetCtrlVal (panel, control, &int_44_45_offset);	
			
	}
	
	return 0;
	
}

int CVICALLBACK RefNoiseStartTime (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
						  
	switch (event)
	{
		case EVENT_COMMIT:
			
		GetCtrlVal (panel, control, &ref_noise_start_time);	
			
	}
	
	return 0;
	
}

int CVICALLBACK RefNoiseStopTime (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
						  
	switch (event)
	{
		case EVENT_COMMIT:
			
		GetCtrlVal (panel, control, &ref_noise_end_time);	
			
	}
	
	return 0;
	
}

int CVICALLBACK BaselineNoiseStart (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
						  
	switch (event)
	{
		case EVENT_COMMIT:
			
		GetCtrlVal (panel, control, &baseline_noise_start_time);	
			
	}
	
	return 0;
	
}

int CVICALLBACK BaselineNoiseStop (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
						  
	switch (event)
	{
		case EVENT_COMMIT:
			
		GetCtrlVal (panel, control, &baseline_noise_end_time);	
			
	}
	
	return 0;
	
}

int CVICALLBACK OutputSelection (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
						  
	switch (event)
	{
		case EVENT_COMMIT:
			
		GetCtrlVal (panel, control, &output_selection);	
			
	}
	
	return 0;
	
}
