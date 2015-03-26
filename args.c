#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "args.h"



bool isValidNumber(char* string) {
    if(*string == '-')
        string++;
    if(!*string) 
        return false; // no character at start of string
    while(*string) {
        if((*string < '0' || *string > '9'))
            return false;
        string++;
    }
    return true;
}

bool areArgRequirementsMet(int *argc, char *argv[], struct arg_requirements *reqs, int req_count) {
    int i;
    int invalidArgumentIndex = -1; 
    // Loop through each requirement
    for(int i=0;i<req_count && invalidArgumentIndex == -1;i++) {
        // if the argument does not exist or is empty, break.
        if(reqs[i].argument_position >= *argc || argv[reqs[i].argument_position][0]==0) {
            invalidArgumentIndex = i;
        // check valid number if arg is a number
        } else if(reqs[i].is_numeric) {
            // if is not valid number, break.
            if(!isValidNumber(argv[reqs[i].argument_position])) { 
                invalidArgumentIndex = i;
            } else { 
                int num = atoi(argv[reqs[i].argument_position]);
                // check range of number
                if(num > reqs[i].max_inclusive || num < reqs[i].min_inclusive) {
                    invalidArgumentIndex = i;
                }
            } // end is valid number
        } // end is numeric
    } // end for

    // if bad argument
    if(invalidArgumentIndex != -1) {
        struct arg_requirements *badReq = &reqs[invalidArgumentIndex];
        // give the user enough information to fix their mistake.
        if(badReq->is_numeric == NUMERIC_ARG) {
            printf("Error: %s (arg #%d) must be between %d and %d (inclusive)\n", 
                badReq->name, badReq->argument_position, badReq->min_inclusive, badReq->max_inclusive);
        } else {
            printf("Error: Missing %s (arg #%d)\n", 
                badReq->name, badReq->argument_position);
        }
    }
    
    return invalidArgumentIndex == -1;
}
