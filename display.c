// this is a text file made in case the S function on simulink does not retain the code
// if that is the case please copy this file in display_output_demo_wrapper.c
/*
 * Include Files
 *
 */
#if defined(MATLAB_MEX_FILE)
#include "tmwtypes.h"
#include "simstruc_types.h"
#include <stdio.h>
#else
#define SIMPLIFIED_RTWTYPES_COMPATIBILITY
#include "rtwtypes.h"
#undef SIMPLIFIED_RTWTYPES_COMPATIBILITY
#endif



/* %%%-SFUNWIZ_wrapper_includes_Changes_BEGIN --- EDIT HERE TO _END */
# ifndef MATLAB_MEX_FILE
#include <libpynq.h>
#include <fontx.h>
#endif
/* %%%-SFUNWIZ_wrapper_includes_Changes_END --- EDIT HERE TO _BEGIN */
#define u_width 1
#define u_1_width 1
#define u_2_width 1

/*
 * Create external references here.  
 *
 */
/* %%%-SFUNWIZ_wrapper_externs_Changes_BEGIN --- EDIT HERE TO _END */
uint8_t static_hi[] = "Reference speed: "; 
uint8_t curr_velocity[] = "Current speed: ";
uint8_t ccontrol[] = "Cruise control is turned off"; 
uint8_t ccontrolon[] = "Cruise control is turned on"; 
uint8_t zer0[] = "0.00";
        
char vel[6];
char ref[6]; 

char last_ref[6];
char last_vel[6];
int last_cc;








# ifndef MATLAB_MEX_FILE
display_t d;
FontxFile fontF[2];
real_T prev_v;
real_T prev_v_ref;
boolean_T prev_cc_enabled;
int c; //counter of executions
# endif
/* %%%-SFUNWIZ_wrapper_externs_Changes_END --- EDIT HERE TO _BEGIN */

/*
 * Start function
 *
 */
void Display_output_demo_Start_wrapper(void)
{
/* %%%-SFUNWIZ_wrapper_Start_Changes_BEGIN --- EDIT HERE TO _END */
# ifndef MATLAB_MEX_FILE
pynq_init();
display_init(&d);
c = 0;
prev_v = -1;
prev_v_ref = -1;
prev_cc_enabled = false;

//Loading the font
InitFontx(fontF, "../../fonts/ILGH16XB.FNT", "");
displaySetFontDirection(&d, TEXT_DIRECTION0);

//Drawing a warning triangle on the screen 
displayFillScreen(&d, RGB_RED);
uint8_t static_warning_l1[] = "Simulation";
uint8_t static_warning_l2[] = "not running";
displayDrawString(&d, fontF, 80, 110,static_warning_l1, RGB_BLACK);  
displayDrawString(&d, fontF, 75, 140,static_warning_l2, RGB_BLACK);  
displayDrawTriangle(&d, 10, 160, 230, 160, 120, 50, RGB_YELLOW);
# endif
/* %%%-SFUNWIZ_wrapper_Start_Changes_END --- EDIT HERE TO _BEGIN */
}
/*
 * Output function
 *
 */
void Display_output_demo_Outputs_wrapper(const real_T *velocity,
                                         const real_T *velocity_ref,
                                         const real_T *cc_ref)
{
/* Output_BEGIN */
# ifndef MATLAB_MEX_FILE
     sprintf(vel,"%.2f",*velocity);
    sprintf(ref,"%.2f",*velocity_ref); 
    

    if(c==0){
		display_init(&d); //!!! Extra init in the first loop. Display does not work without it.
		displayFillScreen(&d, RGB_YELLOW);
        last_cc=*cc_ref;
		c=1;
	}
    if(c==1){
        c=2;
        displayFillScreen(&d, RGB_GREEN);
        if(*cc_ref == 0){
            
            displayDrawString(&d, fontF, 10, 30,ccontrol, RGB_BLACK);
            displayDrawString(&d, fontF,  140 , 60, zer0, RGB_BLACK);
            displayDrawString(&d, fontF, 10, 60,static_hi, RGB_BLACK);
            //displayDrawChar(&d, fontF,  140 , 60, (uint8_t)(0), RGB_BLACK);
        }else{
            displayDrawString(&d, fontF, 10, 30,ccontrolon, RGB_BLACK);
            displayDrawString(&d, fontF, 10, 60,static_hi, RGB_BLACK);
            displayDrawString(&d, fontF,  140 , 60, (uint8_t*)ref, RGB_BLACK);
        }

        displayDrawString(&d, fontF,  10 , 130, curr_velocity, RGB_BLACK);
        displayDrawString(&d, fontF,  120 , 130, (uint8_t*)vel, RGB_BLACK);
    }
     if(c==2){
    
    if(*cc_ref == 0 && last_cc==0){
        
        if(strcmp(last_vel,vel)!=0){
            displayDrawString(&d, fontF,  120 , 130, (uint8_t*)last_vel, RGB_GREEN);
            displayDrawString(&d, fontF,  120 , 130, (uint8_t*)vel, RGB_BLACK);
        }

        
    }else if(*cc_ref == 1 && last_cc==0){
        displayDrawString(&d, fontF,  140 , 60, zer0, RGB_GREEN);
        displayDrawString(&d, fontF, 10, 30,ccontrol, RGB_GREEN);
        displayDrawString(&d, fontF, 10, 30,ccontrolon, RGB_BLACK);
        
        if(strcmp(last_ref,ref)!=0){
            displayDrawString(&d, fontF,  140 , 60, (uint8_t*)last_ref, RGB_GREEN);
            displayDrawString(&d, fontF,  140 , 60, (uint8_t*)ref, RGB_BLACK);
        }
        
 }else if(*cc_ref == 1 && last_cc==1){
        
        if(strcmp(last_ref,ref)!=0){
            displayDrawString(&d, fontF,  140 , 60, (uint8_t*)last_ref, RGB_GREEN);
            displayDrawString(&d, fontF,  140 , 60, (uint8_t*)ref, RGB_BLACK);
        }
        
        if(strcmp(last_vel,vel)!=0){
            displayDrawString(&d, fontF,  120 , 130, (uint8_t*)last_vel, RGB_GREEN);
            displayDrawString(&d, fontF,  120 , 130, (uint8_t*)vel, RGB_BLACK);
        }

        
    }else if(*cc_ref == 0 && last_cc==1){
        
        displayDrawString(&d, fontF,  140 , 60, (uint8_t*)last_ref, RGB_GREEN);
        displayDrawString(&d, fontF,  140 , 60, zer0, RGB_BLACK);
        displayDrawString(&d, fontF, 10, 30,ccontrolon, RGB_GREEN);
        displayDrawString(&d, fontF, 10, 30,ccontrol, RGB_BLACK);
        
        
       
        
        
        if(strcmp(last_vel,vel)!=0){
            displayDrawString(&d, fontF,  120 , 130, (uint8_t*)last_vel, RGB_GREEN);
            displayDrawString(&d, fontF,  120 , 130, (uint8_t*)vel, RGB_BLACK);
        }
    }

    printf("%s %s \n", ref, last_ref);
    printf("%s %s \n", vel, last_vel);
    printf("%f %d \n", *cc_ref, last_cc);

    last_cc=*cc_ref;
    strcpy(last_ref,ref);
    strcpy(last_vel,vel);


	

    }

	# endif
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_END --- EDIT HERE TO _BEGIN */
}

/*
 * Terminate function
 *
 */
void Display_output_demo_Terminate_wrapper(void)
{
/* %%%-SFUNWIZ_wrapper_Terminate_Changes_BEGIN --- EDIT HERE TO _END */
# ifndef MATLAB_MEX_FILE
display_destroy(&d);
pynq_destroy();
# endif
/* %%%-SFUNWIZ_wrapper_Terminate_Changes_END --- EDIT HERE TO _BEGIN */
}

