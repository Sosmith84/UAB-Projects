/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File: <ProgramName>.c
 * Copy: Copyright (c) 2018 Shawn Smith
 * BlazerID: ssmith84
 * Vers: 2.1.0 <Current Date> SOS - <Description of Minor Modifications/Bugs>
 * Vers: 2.0.0 <Current Date> SOS - <Description of Major Modifications/Features>
 * Vers: 1.0.0 <Current Date> SOS - Original Coding
 * Desc: <A brief explanation of what your program does.>
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
/*
 * 
 */
double numerical_integration_rectangular(char *input_filename, char *output_filename);
double numerical_integration_trapezoidal(char *input_filename, char *output_filename );
int help(void);

int main(int argc, char** argv) {
    int i;
    double results;
    int Valid;
    char function[20];
    char input_filename[30];
    char output_filename[30];
    char space[1];
       
//   argc - number of arguments
     //argv - arguments themselves
    
    printf("Number of Arguments: %i\n", argc); // Number of input arguments
    printf("Value of first Arguments: %s\n", argv[0]); // zero (0) based index
    // starts with the number 0  
    
    printf("Value of all Arguments:\n");
    // Sample from Netbeans, modified - GCM
    for (i = 0; i < argc; i++) {
        printf("\t%i: %s\n", i, argv[i]);        
    }
    
    
    if (argc < 2) {
        // help implicitly called.
        help();
    } else {
        // argc >= 2
        /* Start parsing tier-one arguments.  Assume argument number 2 is a tier 
         * 1 option.  Argument number 3 is a tier 2 option.  Tier 1 options 
         * override tier 3 options (for this example).  For example, calling 
         * help will ignore other parameters.
         */
        if (strcmp( argv[1], "/h" ) == 0) {
            // help explicitly called
            help();
        } 
        else if (strcmp( argv[1], "/i" ) == 0 ) 
        {
            printf("Interactive Mode\n");
            if (strcmp( argv[2], "/rectangle" ) == 0)
            {             
                printf("Please enter the input and output file name with a space in between them:\n");
                scanf(" %s %s", input_filename, output_filename);

                results = numerical_integration_trapezoidal( input_filename,  output_filename);
            }
            if (strcmp( argv[2], "/trapezoidal" ) == 0)
            {
                //Ask the user to enter the function
                
                printf("Please enter the input and output file name with a space in between them:\n");
                scanf(" %s %s", input_filename, output_filename);

                results = numerical_integration_trapezoidal( input_filename,  output_filename);
            }
                
            
            
        } 
    
        else if (strcmp( argv[1], "/p" ) == 0) 
        {
            printf("Parameter mode\n");
            // identify if you have 3 or more arguments
            if (( strcmp( argv[2], "/rectangle") == 0) && ( argc == 5 )) 
            {
                // identify the third argument as /1D
                // /1D --> argc == 4
                strcpy(input_filename, argv[3]);
                strcpy(output_filename, argv[4]);
                
                results = numerical_integration_rectangular(input_filename, output_filename);
                printf("results: %f\n", results);

            }
            else if ((strcmp( argv[2], "/trapezoidal") == 0) && (argc == 5 )){
                
                strcpy(input_filename, argv[3]);
                strcpy(output_filename, argv[4]);
               
                results = numerical_integration_trapezoidal( input_filename, output_filename);
                printf("results: %f\n", results);
            }
        }  
    }
    return (EXIT_SUCCESS);
}


double numerical_integration_rectangular(char *input_filename, char *output_filename){
    int row_count;
    int n;
    int i;
    char number;
    char character;
    char check;
    
    double x;
    double y;
    double x_delta;
    double y_delta;
    double x_mid;
    double Area_Current;
    double Area_Previous;
    double x_min;
    double y_min;
    double y_max;
    double x_max;
    double y_mean;
    double y_currentmax;
    double y_currentmin;
    double y_previous;
    double y_delta_max;
    double y_delta_next;
    double y_delta_min;
    double y_deltaminp;
    double y_deltaminc;
    double y_deltamaxp;
    double y_deltamaxc;
    double x_mean;
    double x_previous;
    double x_delta_max;
    double x_delta_min;
    double x_sum;
    double y_sum;
    int  n_count;
    
    FILE *inputfile;
    FILE *outputfile;
    
    n_count = 0;
    x_previous = 0.0;
    y_previous = 0.0;
    
    inputfile = fopen(input_filename,"r");
    
    if (inputfile == NULL) 
    { 
        printf("Could not open file %s", input_filename); 
        return 0; 
    } 
    
    for (number = getc(inputfile); number != EOF; number = getc(inputfile)){ 
        if (number == ','){ // Increment count if this character is newline 
            n_count = n_count + 1;
        }
    }
    n = n_count;
    
    
    // number of values
    //index to run down the array
    fclose(inputfile);

    //read file into array
    int Number_Table[n][2];

        inputfile = fopen(input_filename,"r");

    
    for (row_count = 0; row_count < n; row_count = row_count + 1)
    { 
        fscanf(inputfile, "%lf ,%lf",&x,&y);
        Number_Table[row_count][0] = x;
        x_sum += x;
        Number_Table[row_count][1] = y;
        y_sum += y;
    }
    
   
    fclose( inputfile );
   
    x_mean = x_sum/row_count;
    y_mean = y_sum/row_count;
    inputfile = fopen(input_filename,"r");
    n = row_count;
    x_min = 0.0;
    y_min = 0.0;
    row_count = 0;
    y_max = Number_Table[row_count][1];
    x_max = Number_Table[row_count][0];
    Area_Current = 0;
    do{
        if (y_max < Number_Table[row_count +1][1]){
            y_max = Number_Table[row_count + 1][1];
        }
        
        if (x_max < Number_Table[row_count +1][0]){
            x_max = Number_Table[row_count + 1][0];
        }
        Area_Current = y_sum/row_count;


        row_count = row_count + 1;
    }while (row_count <= n -2);
    
    x_delta = (x_max - x_min) /n;
    x_delta_max = x_delta ;
    x_delta_min = x_delta ;
    y_deltamaxc = 0;
    y_deltaminc = 0;
    y_currentmax = 0;
    y_currentmin = 0;
    
    y_deltaminc = y_currentmax - (Number_Table[row_count - 1][1]);
    y_deltamaxc = y_currentmin - (Number_Table[row_count - 1][1]);
    y_delta_next = (Number_Table[row_count - 1][1]) - (Number_Table[row_count - 2][1]);
    for (row_count = 0; row_count < n - 2; row_count = row_count + 1)
    {    
        
        Area_Current = Area_Current + ( x_delta * Number_Table[row_count][1] );
        
        if ( y_deltaminc > y_delta_next ){
            y_deltaminp = y_delta_next;
            
        }
        if ( y_deltamaxc < y_delta_next){
            y_deltamaxp = y_delta_next;
           
        }
        
    }
  
 /* Output sample (in output text file):
 * Description                  Value
 * =============================================================================
 * Method                       rectangle
 * Segments                     100
 * Area                         0.67
 * x_min                        0.00
 * x_max                        1.00
 * x_mean                       0.50
 * x_delta_min                  0.01
 * x_delta_max                  0.01
 * y_min                        0.00
 * y_max                        1.00
 * y_mean                       0.67
 * y_delta_min                  0.00
 * y_delta_max                  0.02
 */ 

    outputfile = fopen (output_filename , "w");
    
    fprintf(outputfile,"Description                  Value \n");
    fprintf(outputfile, "========================================= \n");
    fprintf(outputfile, "Method                       rectangle \n");
    fprintf(outputfile, "Segments                     %d \n", n - 1);
    fprintf(outputfile, "Area                         %.2f \n", Area_Current);
    fprintf(outputfile, "x_min                        %.2f \n", x_min);
    fprintf(outputfile, "x_max                        %.2f \n", x_max);
    fprintf(outputfile, "x_mean                       %.2f \n", x_mean);
    fprintf(outputfile, "x_delta_min                  %.2f \n", x_delta_min);
    fprintf(outputfile, "x_delta_max                  %.2f \n", x_delta_max);
    fprintf(outputfile, "y_min                        %.2f \n", y_min);
    fprintf(outputfile, "y_max                        %.2f \n", y_max);
    fprintf(outputfile, "y_mean                       %.2f \n", y_mean);
    fprintf(outputfile, "y_delta_min                  %.2f \n", y_deltaminc);
    fprintf(outputfile, "y_delta_max                  %.2f \n", y_deltamaxc);
    
    fclose( outputfile );
    
    


  
}

double numerical_integration_trapezoidal(char *input_filename, char *output_filename ){
    int row_count;
    int n;
    int i;
    char number;
    
    double x;
    double y;
    double x_delta;
    double Area_Current;
    double x_min;
    double y_min;
    double y_max;
    double x_max;
    double y_mean;
    double y_currentmax;
    double y_currentmin;
    double y_previous;
    double y_delta_next;
    double y_deltaminp;
    double y_deltaminc;
    double y_deltamaxp;
    double y_deltamaxc;
    double x_mean;
    double x_previous;
    double x_delta_max;
    double x_delta_min;
    double x_sum;
    double y_sum;
    int  n_count;
    
    FILE *inputfile;
    FILE *outputfile;
    
    n_count = 0;
    x_previous = 0.0;
    y_previous = 0.0;
    
inputfile = fopen(input_filename,"r");    
    if (inputfile == NULL) 
    { 
        printf("Could not open file %s", input_filename); 
        return 0; 
    } 
    
    for (number = getc(inputfile); number != EOF; number = getc(inputfile)){ 
        if (number == ',') // Increment count if this character is newline 
            n_count = n_count + 1; 
    }
    n = n_count;
    
    
    // number of values
    //index to run down the array
    fclose(inputfile);

    //read file into array
    int Number_Table[n][2];

        inputfile = fopen(input_filename,"r");

    
    for (row_count = 0; row_count < n; row_count = row_count + 1)
    { 
        fscanf(inputfile, "%lf ,%lf",&x,&y);
        Number_Table[row_count][0] = x;
        x_sum += x;
        Number_Table[row_count][1] = y;
        y_sum += y;
    }
    
   
    fclose( inputfile );
   
    x_mean = x_sum/row_count;
    y_mean = y_sum/row_count;
    inputfile = fopen(input_filename,"r");
    n = row_count;
    x_min = 0.0;
    y_min = 0.0;
    row_count = 0;
    y_max = Number_Table[row_count][1];
    x_max = Number_Table[row_count][0];
    Area_Current = 0;
    do{
        if (y_max < Number_Table[row_count +1][1]){
            y_max = Number_Table[row_count + 1][1];
        }
        
        if (x_max < Number_Table[row_count +1][0]){
            x_max = Number_Table[row_count + 1][0];
        }
        
        row_count = row_count + 1;
    }while (row_count <= n -2);
    
    x_delta = (x_max - x_min) /n;
    x_delta_max = x_delta ;
    x_delta_min = x_delta ;
    y_deltamaxc = 0;
    y_deltaminc = 0;
    y_currentmax = 0;
    y_currentmin = 0;
    
    y_deltaminc = y_currentmax - (Number_Table[row_count - 1][1]);
    y_deltamaxc = y_currentmin - (Number_Table[row_count - 1][1]);
    y_delta_next = (Number_Table[row_count - 1][1]) - (Number_Table[row_count - 2][1]);
    for (row_count = 0; row_count < n - 2; row_count = row_count + 1)
    {    
        
        Area_Current = Area_Current + ( x_delta * Number_Table[row_count][1] );
        
        if ( y_deltaminc > y_delta_next ){
            y_deltaminp = y_delta_next;
            
        }
        if ( y_deltamaxc < y_delta_next){
            y_deltamaxp = y_delta_next;
           
        }
        
    }
  
 /* Output sample (in output text file):
 * Description                  Value
 * =============================================================================
 * Method                       rectangle
 * Segments                     100
 * Area                         0.67
 * x_min                        0.00
 * x_max                        1.00
 * x_mean                       0.50
 * x_delta_min                  0.01
 * x_delta_max                  0.01
 * y_min                        0.00
 * y_max                        1.00
 * y_mean                       0.67
 * y_delta_min                  0.00
 * y_delta_max                  0.02
 */ 

    outputfile = fopen ( output_filename, "w");
    
    fprintf(outputfile,"Description                  Value \n");
    fprintf(outputfile, "========================================= \n");
    fprintf(outputfile, "Method                       trapezoidal \n");
    fprintf(outputfile, "Segments                     %d \n", n - 1);
    fprintf(outputfile, "Area                         %.2f \n", Area_Current);
    fprintf(outputfile, "x_min                        %.2f \n", x_min);
    fprintf(outputfile, "x_max                        %.2f \n", x_max);
    fprintf(outputfile, "x_mean                       %.2f \n", x_mean);
    fprintf(outputfile, "x_delta_min                  %.2f \n", x_delta_min);
    fprintf(outputfile, "x_delta_max                  %.2f \n", x_delta_max);
    fprintf(outputfile, "y_min                        %.2f \n", y_min);
    fprintf(outputfile, "y_max                        %.2f \n", y_max);
    fprintf(outputfile, "y_mean                       %.2f \n", y_mean);
    fprintf(outputfile, "y_delta_min                  %.2f \n", y_deltaminc);
    fprintf(outputfile, "y_delta_max                  %.2f \n", y_deltamaxc);
    
    fclose( outputfile );
    
     
}

int help(void){
    printf("========================================\n");
    printf("File: P4.exe\n");
    printf("Copy: Copyright (c) 2018 Shawn Smith \n");
    printf("Vers: 1.0.0 09/19/2018 SOS - First Iteration of a Functioning Calculator\n");
    printf("Desc: Integration Calculator\n");
    printf("========================================\n");
    printf("Usage:\n");
    printf("    /i - Interactive mode\n");//scanf
    printf("        /rectangle - rectangular integration\n");
    printf("            input file name\n");
    printf("            output file name\n");
    printf("        /trapezoidal - trapezoidal integration\n");
    printf("            input file name\n");
    printf("            output file name\n");
    printf("    /p - Parameter mode\n");//batch files
    printf("        /rectangle - rectangular integration\n");
    printf("            requires input file and output file\n");
    printf("        /trapezoidal - trapezoidal integration\n");
    printf("            requires input file and output file\n");
    printf("    /h - Help\n");
    printf("========================================\n");
}
