// this is a text file made in case the S function on simulink does not retain the code
// if that is the case please copy this file in display_adaptive_output_demo_wrapper.c
/*
 * Include Files
 *
 */
#if defined(MATLAB_MEX_FILE)
#include "tmwtypes.h"
#include "simstruc_types.h"
#else
#define SIMPLIFIED_RTWTYPES_COMPATIBILITY
#include "rtwtypes.h"
#undef SIMPLIFIED_RTWTYPES_COMPATIBILITY
#endif

/* %%%-SFUNWIZ_wrapper_includes_Changes_BEGIN --- EDIT HERE TO _END */
#ifndef MATLAB_MEX_FILE
#include <libpynq.h>
#include <fontx.h>
#endif
/* %%%-SFUNWIZ_wrapper_includes_Changes_END --- EDIT HERE TO _BEGIN */
#define u_width 1
#define u_1_width 1
#define u_2_width 1
#define u_3_width 1
#define u_4_width 1

/*
 * Create external references here.
 *
 */
/* %%%-SFUNWIZ_wrapper_externs_Changes_BEGIN --- EDIT HERE TO _END */
#ifndef MATLAB_MEX_FILE
display_t d;
FontxFile fontF[2];
real_T prev_v;
real_T prev_v_ref;
boolean_T prev_cc_enabled;

uint8_t static_hi[] = "Reference distance: ";
uint8_t curr_velocity[] = "Current speed: ";
uint8_t curr_distance[] = "Current distance: ";
uint8_t ccontrol[] = "Cruise control is turned off";
uint8_t ccontrolon[] = "Cruise control is turned on";
uint8_t print_time[] = "Reference time: ";
uint8_t zer0[] = "0.00";

// real_T time_check = -1;
// real_T vel_check = -1;
// real_T dist_check = -1;
// real_T dist_ref_check;

real_T vel = -1;
real_T dist = -1;
real_T ref = -1;
real_T time = -11;

real_T last_time = -1;
real_T last_ref = -1;
real_T last_dist = -1;
real_T last_vel = -1;

char print_vel[6] = "\0";
char print_ref_time[6] = "\0";
char print_ref_dist[6] = "\0";
char print_dist[6] = "\0";

char print_last_vel[6] = "\0";
char print_ref_last_time[6] = "\0";
char print_ref_last_dist[6] = "\0";
char print_last_dist[6] = "\0";

int last_cc;

int c; // counter of executions
#endif
/* %%%-SFUNWIZ_wrapper_externs_Changes_END --- EDIT HERE TO _BEGIN */

/*
 * Start function
 *
 */
void Display_output_demo_adaptive_Start_wrapper(void)
{
/* %%%-SFUNWIZ_wrapper_Start_Changes_BEGIN --- EDIT HERE TO _END */
#ifndef MATLAB_MEX_FILE
    pynq_init();
    display_init(&d);
    c = 0;
    prev_v = -1;
    prev_v_ref = -1;
    prev_cc_enabled = false;

    // Loading the font
    InitFontx(fontF, "../../fonts/ILGH16XB.FNT", "");
    displaySetFontDirection(&d, TEXT_DIRECTION0);

    // Drawing a warning triangle on the screen
    displayFillScreen(&d, RGB_RED);
    uint8_t static_warning_l1[] = "Simulation";
    uint8_t static_warning_l2[] = "not running";
    displayDrawString(&d, fontF, 80, 110, static_warning_l1, RGB_BLACK);
    displayDrawString(&d, fontF, 75, 140, static_warning_l2, RGB_BLACK);
    displayDrawTriangle(&d, 10, 160, 230, 160, 120, 50, RGB_YELLOW);
#endif
    /* %%%-SFUNWIZ_wrapper_Start_Changes_END --- EDIT HERE TO _BEGIN */
}
/*
 * Output function
 *
 */
void Display_output_demo_adaptive_Outputs_wrapper(const real_T *velocity,
                                                  const real_T *distance_ref,
                                                  const real_T *cc_ref,
                                                  const real_T *distance,
                                                  const real_T *ref_time)
{
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_BEGIN --- EDIT HERE TO _END */
#ifndef MATLAB_MEX_FILE
    // printf("First print\n");
    if (time != *ref_time)
    {
        strcpy(print_ref_last_time, print_ref_time);
        sprintf(print_ref_time, "%.0f", *ref_time);
        last_time = time;
        time = *ref_time;
        // time = (int)*ref_time;
        // printf("Try to print here for time\n");
    }
    if (vel != *velocity)
    {
        strcpy(print_last_vel, print_vel);
        sprintf(print_vel, "%.0f", *velocity);
        last_vel = vel;

        vel = *velocity;
        // printf("Try to print here for vel\n");
    }
     if (dist != *distance)
     {
        strcpy(print_last_dist, print_dist);
        sprintf(print_dist, "%.0f", *distance);
        last_dist = dist;
        dist = *distance;
        // printf("Try to print here for dist\n");
    }
    if (ref != *distance_ref)
    {
        strcpy(print_ref_last_dist, print_ref_dist);
        sprintf(print_ref_dist, "%.0f", *distance_ref);
        last_ref = ref;
        ref = *distance_ref;
        // ref = (int)*distance_ref;
        // printf("Try to print here for dist_ref\n");
    }

    if (c == 0)
    {
        display_init(&d); //!!! Extra init in the first loop. Display does not work without it.
        displayFillScreen(&d, RGB_YELLOW);
        last_cc = *cc_ref;
        c = 1;
    }
    if (c == 1)
    {
        c = 2;
        displayFillScreen(&d, RGB_GREEN);
        if (*cc_ref == 0)
        {

            displayDrawString(&d, fontF, 10, 30, ccontrol, RGB_BLACK);
            displayDrawString(&d, fontF, 180, 60, zer0, RGB_BLACK);
            displayDrawString(&d, fontF, 10, 60, static_hi, RGB_BLACK);
            // printf("try to print here\n");
        }
        else
        {
            displayDrawString(&d, fontF, 10, 30, ccontrolon, RGB_BLACK);

            displayDrawString(&d, fontF, 10, 60, static_hi, RGB_BLACK);

            displayDrawString(&d, fontF, 180, 60, (uint8_t *)print_ref_dist, RGB_BLACK);

            displayDrawString(&d, fontF, 10, 220, print_time, RGB_BLACK);

            displayDrawString(&d, fontF, 180, 220, (uint8_t *)print_ref_time, RGB_BLACK);

            // printf("try to print here again\n");
        }

        displayDrawString(&d, fontF, 10, 110, curr_velocity, RGB_BLACK);

        displayDrawString(&d, fontF, 180, 110, (uint8_t *)print_vel, RGB_BLACK);

        displayDrawString(&d, fontF, 10, 160, curr_distance, RGB_BLACK);

        displayDrawString(&d, fontF, 180, 160, (uint8_t *)print_dist, RGB_BLACK);

        // printf("This means the pynq does start ok\n");
        // the code never prints the line under this one but it prints the one above
        //  i get make: *** [../end.mk:40: run] Segmentation fault (core dumped) error
        ;
    }
    if (c == 2)
    {

        if (*cc_ref == 0 && last_cc == 0)
        {

            if (last_vel != vel)
            {
                displayDrawString(&d, fontF, 180, 110, (uint8_t *)print_last_vel, RGB_GREEN);
                displayDrawString(&d, fontF, 180, 110, (uint8_t *)print_vel, RGB_BLACK);
            }
            if (last_dist != dist)
            {
                displayDrawString(&d, fontF, 180, 160, (uint8_t *)print_last_dist, RGB_GREEN);
                displayDrawString(&d, fontF, 180, 160, (uint8_t *)print_dist, RGB_BLACK);
            }
        }
        else if (*cc_ref == 1 && last_cc == 1)
        {

            if (last_ref != ref)
            {
                displayDrawString(&d, fontF, 180, 60, (uint8_t *)print_ref_last_dist, RGB_GREEN);
                displayDrawString(&d, fontF, 180, 60, (uint8_t *)print_ref_dist, RGB_BLACK);
            }

            if (last_vel != vel)
            {
                displayDrawString(&d, fontF, 180, 110, (uint8_t *)print_last_vel, RGB_GREEN);
                displayDrawString(&d, fontF, 180, 110, (uint8_t *)print_vel, RGB_BLACK);
            }

            if (last_dist != dist)
            {
                displayDrawString(&d, fontF, 180, 160, (uint8_t *)print_last_dist, RGB_GREEN);
                displayDrawString(&d, fontF, 180, 160, (uint8_t *)print_dist, RGB_BLACK);
            }
            if (last_time != time)
            {
                displayDrawString(&d, fontF, 180, 220, (uint8_t *)print_ref_last_time, RGB_GREEN);
                displayDrawString(&d, fontF, 180, 220, (uint8_t *)print_ref_time, RGB_BLACK);
            }
        }
        else if (*cc_ref == 0 && last_cc == 1)
        {

            displayDrawString(&d, fontF, 180, 60, (uint8_t *)print_ref_last_dist, RGB_GREEN);
            displayDrawString(&d, fontF, 180, 60, zer0, RGB_BLACK);

            displayDrawString(&d, fontF, 10, 30, ccontrolon, RGB_GREEN);
            displayDrawString(&d, fontF, 10, 30, ccontrol, RGB_BLACK);

            displayDrawString(&d, fontF, 10, 220, print_time, RGB_GREEN);
            displayDrawString(&d, fontF, 180, 220, (uint8_t *)print_ref_time, RGB_GREEN);
            if (last_vel != vel)
            {
                displayDrawString(&d, fontF, 180, 110, (uint8_t *)print_last_vel, RGB_GREEN);
                displayDrawString(&d, fontF, 180, 110, (uint8_t *)print_vel, RGB_BLACK);
            }

            if (last_dist != dist)
            {
                displayDrawString(&d, fontF, 180, 160, (uint8_t *)print_last_dist, RGB_GREEN);
                displayDrawString(&d, fontF, 180, 160, (uint8_t *)print_dist, RGB_BLACK);
            }
        }
        else if (*cc_ref == 1 && last_cc == 0)
        {
            displayDrawString(&d, fontF, 180, 60, zer0, RGB_GREEN);
            displayDrawString(&d, fontF, 10, 30, ccontrol, RGB_GREEN);
            displayDrawString(&d, fontF, 10, 30, ccontrolon, RGB_BLACK);
            displayDrawString(&d, fontF, 10, 220, print_time, RGB_BLACK);

            if (last_ref != ref)
            {
                displayDrawString(&d, fontF, 180, 60, (uint8_t *)print_ref_last_dist, RGB_GREEN);
                displayDrawString(&d, fontF, 180, 60, (uint8_t *)print_ref_dist, RGB_BLACK);
            }

            if (last_time != time)
            {
                displayDrawString(&d, fontF, 180, 220, (uint8_t *)print_ref_last_time, RGB_GREEN);
                displayDrawString(&d, fontF, 180, 220, (uint8_t *)print_ref_time, RGB_BLACK);
            }
            else
            {
                displayDrawString(&d, fontF, 180, 220, (uint8_t *)print_ref_time, RGB_BLACK);
            }
        }

        last_cc = *cc_ref;
    }

#endif
    /* %%%-SFUNWIZ_wrapper_Outputs_Changes_END --- EDIT HERE TO _BEGIN */
}

/*
 * Terminate function
 *
 */
void Display_output_demo_adaptive_Terminate_wrapper(void)
{
/* %%%-SFUNWIZ_wrapper_Terminate_Changes_BEGIN --- EDIT HERE TO _END */
#ifndef MATLAB_MEX_FILE
    display_destroy(&d);
    pynq_destroy();
#endif
    /* %%%-SFUNWIZ_wrapper_Terminate_Changes_END --- EDIT HERE TO _BEGIN */
}
