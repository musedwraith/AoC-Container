// C standard headers
#include <stdlib.h>
#include <stdio.h> 
#include <ctype.h>
#include <time.h>

// Local headers
#include <challenge.h>
#include <feed.h>

const char delimiter = '\n';
const char *dataFileName = "./data/sample.txt";

ErrorData evaluate(InputData *input, Answer *result) {
    struct timespec start, end;
    timespec_get(&start, TIME_UTC);

    // initialize new number
    int total_output_joltage = 0;
    LineFeed feed = create_linefeed(input);
    
    for(char *line = get_linefeed(&feed); line != NULL; line = get_linefeed(&feed)) {    
        int max_bank_joltage = 0;

        // first battery in the 10s place
        for (int i = 0; line[i] != '\0'; i++) {
            // skip non-digit characters
            if (!isdigit(line[i])) continue;
            // second battery in the 1s place
            // j starts at i + 1 because the second battery must beeeee AFTER the first
            for (int j = i + 1; line[j] != '\0'; j++) {
                if (!isdigit(line[j])) continue;

                // char to int 
                int tens = line[i] - '0';
                int ones = line[j] - '0';

                int current_joltage = (tens * 10) + ones;

                // check
                if (current_joltage > max_bank_joltage) {
                    max_bank_joltage = current_joltage;
                }
            }
        }

        // add this bank's max to the total
        total_output_joltage += max_bank_joltage;
    }
    result->name = "Total Output Joltage";
    result->output = total_output_joltage; 

    timespec_get(&end, TIME_UTC);

    printf("sec diff: %lld, nsec diff: %ld\n", end.tv_sec - start.tv_sec, end.tv_nsec - start.tv_nsec);

    return emptySuccess;
}