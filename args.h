/**
 * args.h
 * Checks for simple valid arguments to main.
 * @author Michael Vartan
 */
#ifndef args_h
#define args_h
struct arg_requirements {
    char *name;
    int argument_position;
    bool is_numeric;
    int min_inclusive;
    int max_inclusive;
};
enum arg_type {
    NON_NUMERIC_ARG,
    NUMERIC_ARG
};

/**
 * Is Valid Number
 * @param  string String to test
 * @return        True if the string is a decimal number, false otherwise
 */
bool isValidNumber(char* string);

/**
 * Checks if argument requirements have been met. 
 * @param  argc      argc from main
 * @param  argv      argv from main
 * @param  reqs      array of requirement struct
 * @param  req_count number of requirement struct
 * @return           true if arguments are met
 */
bool areArgRequirementsMet(int *argc, char *argv[], struct arg_requirements *reqs, int req_count);
#endif