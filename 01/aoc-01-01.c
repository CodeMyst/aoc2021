#include <stdio.h>
#include <stdlib.h>

/*
 * Count the number of times a depth measurement increases from the previous measurement. (There is no measurement before the first measurement.) In the example above, the changes are as follows:
 * 
 * 199 (N/A - no previous measurement)
 * 200 (increased)
 * 208 (increased)
 * 210 (increased)
 * 200 (decreased)
 * 207 (increased)
 * 240 (increased)
 * 269 (increased)
 * 260 (decreased)
 * 263 (increased)
 * 
 * In this example, there are 7 measurements that are larger than the previous measurement.
 * 
 * How many measurements are larger than the previous measurement?
**/

// path to the input file
const char INPUT_PATH[] = "input";

int main() {
    FILE* fp = fopen(INPUT_PATH, "r");

    if (fp == NULL) return 1;

    // store the contents of every line in the input
    char buffer[10];

    int prev = -1;
    int increments = 0;
    while (fgets(buffer, 10, fp)) {
        int val = atoi(buffer);

        // if prev is -1, that means this is the first measurement
        if (prev != -1 && val > prev) increments++;

        prev = val;
    }

    printf("number of increments: %d\n", increments);

    fclose(fp);

    return 0;
}
