#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * --- Part Two ---
 * 
 * Next, you should verify the life support rating, which can be determined by multiplying the oxygen generator rating by the CO2 scrubber rating.
 * 
 * Both the oxygen generator rating and the CO2 scrubber rating are values that can be found in your diagnostic report - finding them is the tricky part. Both values are located using a similar process that involves filtering out values until only one remains. Before searching for either rating value, start with the full list of binary numbers from your diagnostic report and consider just the first bit of those numbers. Then:
 * 
 *     Keep only numbers selected by the bit criteria for the type of rating value for which you are searching. Discard numbers which do not match the bit criteria.
 *     If you only have one number left, stop; this is the rating value for which you are searching.
 *     Otherwise, repeat the process, considering the next bit to the right.
 * 
 * The bit criteria depends on which type of rating value you want to find:
 * 
 *     To find oxygen generator rating, determine the most common value (0 or 1) in the current bit position, and keep only numbers with that bit in that position. If 0 and 1 are equally common, keep values with a 1 in the position being considered.
 *     To find CO2 scrubber rating, determine the least common value (0 or 1) in the current bit position, and keep only numbers with that bit in that position. If 0 and 1 are equally common, keep values with a 0 in the position being considered.
 * 
 * For example, to determine the oxygen generator rating value using the same example diagnostic report from above:
 * 
 *     Start with all 12 numbers and consider only the first bit of each number. There are more 1 bits (7) than 0 bits (5), so keep only the 7 numbers with a 1 in the first position: 11110, 10110, 10111, 10101, 11100, 10000, and 11001.
 *     Then, consider the second bit of the 7 remaining numbers: there are more 0 bits (4) than 1 bits (3), so keep only the 4 numbers with a 0 in the second position: 10110, 10111, 10101, and 10000.
 *     In the third position, three of the four numbers have a 1, so keep those three: 10110, 10111, and 10101.
 *     In the fourth position, two of the three numbers have a 1, so keep those two: 10110 and 10111.
 *     In the fifth position, there are an equal number of 0 bits and 1 bits (one each). So, to find the oxygen generator rating, keep the number with a 1 in that position: 10111.
 *     As there is only one number left, stop; the oxygen generator rating is 10111, or 23 in decimal.
 * 
 * Then, to determine the CO2 scrubber rating value from the same example above:
 * 
 *     Start again with all 12 numbers and consider only the first bit of each number. There are fewer 0 bits (5) than 1 bits (7), so keep only the 5 numbers with a 0 in the first position: 00100, 01111, 00111, 00010, and 01010.
 *     Then, consider the second bit of the 5 remaining numbers: there are fewer 1 bits (2) than 0 bits (3), so keep only the 2 numbers with a 1 in the second position: 01111 and 01010.
 *     In the third position, there are an equal number of 0 bits and 1 bits (one each). So, to find the CO2 scrubber rating, keep the number with a 0 in that position: 01010.
 *     As there is only one number left, stop; the CO2 scrubber rating is 01010, or 10 in decimal.
 * 
 * Finally, to find the life support rating, multiply the oxygen generator rating (23) by the CO2 scrubber rating (10) to get 230.
 * 
 * Use the binary numbers in your diagnostic report to calculate the oxygen generator rating and CO2 scrubber rating, then multiply them together. What is the life support rating of the submarine? (Be sure to represent your answer in decimal, not binary.)
**/

const char INPUT_FILE[] = "input";

/**
 * filters all binary numbers in the array based on the most common bit
 */
int filter(char** c, int* indices, int indices_len, int bit, int invert) {
    int valid_indices = 0;
    int valid_index = 0;

    // check how many valid indices are left
    // and keep track of the last valid index
    for (int i = 0; i < indices_len; i++) {
        if (indices[i] != -1) {
            valid_indices++;
            valid_index = indices[i];
        }
    }

    // only one index left, this is the result
    if (valid_indices == 1) return strtol(c[valid_index], NULL, 2);

    // keep track of the most common bit
    int c0 = 0;
    int c1 = 0;

    for (int i = 0; i < indices_len; i++) {
        // if index is -1, ignore this number
        if (indices[i] == -1) continue;

        if (c[i][bit] == '0') c0++;
        else if (c[i][bit] == '1') c1++;
    }

    // get the common bit as a char
    // invert for c02 rating if needed
    char common = c0 > c1 ? '0': '1';
    if (invert) common = c0 > c1 ? '1' : '0';

    // go through each number and if the first bit is not the common one, remove it
    for (int i = 0; i < indices_len; i++) {
        // if index is -1, ignore this number
        if (indices[i] == -1) continue;

        // remove from list
        if (c[i][bit] != common) {
            indices[i] = -1;
        }
    }

    return filter(c, indices, indices_len, bit + 1, invert);
}

int main() {
    FILE* fp = fopen(INPUT_FILE, "r");

    if (fp == NULL) return 1;

    // count how many new lines
    char c;
    int newlines = 0;
    while ((c = getc(fp)) != EOF) {
        if (c == '\n') newlines++;
    }
    rewind(fp);

    // allocate contents and indices to number of newlines
    char** contents = (char**) malloc(newlines * sizeof(char*));
    int* indices = (int*) malloc(newlines * sizeof(int));

    int size = 0;
    char buffer[15];

    for (int i = 0; i < newlines; i++) {
        // get the number into the buffer
        fgets(buffer, 15, fp);

        // check the size only once, all numbers have the same number of bits
        // -1 because of newline
        if (size == 0) size = strlen(buffer) - 1;

        // allocate char* to hold the single binary number
        contents[i] = (char*) malloc(size * sizeof(char));

        // copy the first `size` bits from the buffer into the allocated char*
        strncpy(contents[i], buffer, size);

        // reset all indices
        indices[i] = i;
    }

    int oxygen_rating = filter(contents, indices, newlines, 0, 0);

    // reset all indices
    for (int i = 0; i < newlines; i++) {
        indices[i] = i;
    }

    int c02_rating = filter(contents, indices, newlines, 0, 1);

    int life_support_rating = oxygen_rating * c02_rating;

    printf("oxygen generator rating: %d\n", oxygen_rating);
    printf("c02 scrubber rating: %d\n", c02_rating);
    printf("life support rating: %d\n", life_support_rating);

    for (int i = 0; i < newlines; i++) {
        free(contents[i]);
    }
    free(contents);

    free(indices);

    return 0;
}
