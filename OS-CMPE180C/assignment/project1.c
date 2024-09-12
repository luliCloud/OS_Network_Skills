#include <stdio.h>
#include <string.h>
#include <time.h>  // for generating random time
#include <stdlib.h> // for generating random num

// prototype 
int generate_lottery(int nums_generatem, int max_num, int max_powerball_num,
int num_set_gen);

int main (int argc, char** argv) {
    if (argc != 7 && argc != 9) { // 7 is not including -p as -p is optional
        printf("Please enter all required arguments, ");
        printf("include -r, -n, -p (optional) and -N\n");
        return 1;
    }

    // set variables for each args
    int nums_generate = -1, max_num = -1, max_powerball_num = -1, num_set_gen = -1;

    // read all input from argv
    int i;  // first argv is function name itself
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-n") == 0) {  // == 0 indicating same
            nums_generate = atoi(argv[++i]); // ++i, move to next argv
        } else if (strcmp(argv[i], "-r") == 0) {
            max_num = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-p") == 0) {
            max_powerball_num = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-N") == 0) {  // -N
            num_set_gen = atoi(argv[++i]);
        } else {
            printf("Invalid input!\n");
            return 1;
        }
    }

    if (argc == 9 && max_powerball_num <0) {
        printf("No negative input is allowed for the arguments\n");
        return 1;
    }

    int error = generate_lottery(nums_generate, max_num, 
    max_powerball_num, num_set_gen);
    if (error == 1) {
        return 1;
    }
    return 0;
}

int generate_lottery(int nums_gen, int max_num, int max_p_num, int num_set_gen) {
    if (num_set_gen < 0 || nums_gen < 0 || max_num < 0) {
        printf("No negative input is allowed for the arguments\n");
        return 1;
    }

    if (nums_gen > max_num) {
        printf("Numbers to be generated should no more than the max number!\n");
        return 1;
    }

    // initialize random seed
    srand(time(NULL));
    
    // iterate the set
    int i;
    for (i = 0; i < num_set_gen; i++) {
        printf("set %d numbers:", i);
        int j;
        int nums[max_num + 1]; // initialize nums array to keep track generated num
        for (j = 0; j <= max_num; j++) {
            nums[j] = 0;
        }
        // fill the nums by random num
        j = 0;
        for (; j < nums_gen; j++) {
            int n = rand() % max_num + 1; // lottery cannot be 0
            while (nums[n] == 1) {
                // keep generate until find one not duplicate
                n = rand() % max_num + 1; 
            }
            nums[n] = 1;
            printf(" %d", n);
        }
        printf("; ");

        if (max_p_num >= 0) {
            int p_num = rand() % max_p_num + 1;
            printf("PowerBall number: %d\n", p_num);
        } else {
            printf("\n");
        }
    }
    return 0;
}
