// C standard headers
#include <stdlib.h>
// Local headers
#include <challenge.h>
#include <feed.h>

#include <stdio.h>

const char delimiter = ',';
const char *dataFileName = "./data/day_02.txt";

ErrorData evaluate(InputData *input, Answer *result) {
    *result = (Answer) { "Password", 0 };

    LineFeed feed = create_linefeed(input);
    for(char *line = get_linefeed(&feed); line != NULL; line = get_linefeed(&feed)) {
        printf("%s\n", line);
    }
    return emptySuccess;
}