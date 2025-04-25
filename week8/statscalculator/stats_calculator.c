// C Statistics Calculator

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Calculate the mean of the numbers
double get_mean(int numbers[], int count) {
    if (count == 0) {
        // Handle empty array
        return NAN;
    }
    double sum = 0;
    for (int i = 0; i < count; i++) {
        sum += numbers[i];
    }
    return sum / count;
}

// Compare numbers for sorting.
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// Calculate the median of the numbers
double get_median(int numbers[], int count) {
    if (count == 0) {
        // Handle empty array
        return NAN;
    }
    // Sort the numbers
    qsort(numbers, count, sizeof(int), compare);
    if (count % 2 == 0) {
        // If even, return the average of the two middle numbers
        return (numbers[count / 2 - 1] + numbers[count / 2]) / 2.0;
    } else {
        // If odd, return the middle number
        return numbers[count / 2];
    }
}

// Calculate the mode of the numbers
int *get_mode(int numbers[], int count, int *modeCount) {
    if (count == 0) {
        // Handle empty array
        *modeCount = 0;
        return NULL;
    }
    // Sort the numbers to group equal numbers together.
    qsort(numbers, count, sizeof(int), compare);
    int maxCount = 0;
    int currentCount = 1;
    int *modes = NULL;
    int modesCount = 0;

    for (int i = 1; i < count; i++) {
        if (i > 0 && numbers[i] == numbers[i - 1]) {
            currentCount++;
        } else {
            currentCount = 1;
        }

        if (currentCount > maxCount) {
            maxCount = currentCount;
            // Allocate memory, free old.
            free(modes);
            modesCount = 1;
            modes = (int *)malloc(sizeof(int));
            modes[0] = numbers[i - 1];
        } else if (currentCount == maxCount) {
            // Allocate more memory and add the new mode.
            modes = (int *)realloc(modes, sizeof(int) * (modesCount + 1));
            modes[modesCount] = numbers[i];
            modesCount++;
        }
    }
    *modeCount = modesCount;
    return modes;
}

// Main Function, show the original numbers and calculated mean, median, and mode.
int main() {
    int numbers[] = {1, 2, 2, 2, 3, 5, 5, 5, 5, 7};
    int count = sizeof(numbers)/sizeof(numbers[0]);

    double mean = get_mean(numbers, count);
    double median = get_median(numbers, count);

    int modeCount = 0;
    int *modes = get_mode(numbers, count, &modeCount);

    printf("Numbers: ");
   for (int i = 0; i < count; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    if(isnan(mean)) {
        printf("Mean: No numbers provided. Empty list.\n");
    } else {
        printf("Mean: %.f\n", mean);
    }

    if(isnan(median)) {
        printf("Median: No numbers provided. Empty list.\n");
    } else {
        printf("Median: %.f\n", median);
    }

    if(modeCount == 0) {
        printf("Mode: No numbers provided. Empty list.\n");
    } else {
        printf("Mode(s): ");
        for (int i = 0; i < modeCount; i++) {
            printf("%d ", modes[i]);
        }
        printf("\n");
        // Free the allocated memory for modes.
        free(modes);
    }
    return 0;
}