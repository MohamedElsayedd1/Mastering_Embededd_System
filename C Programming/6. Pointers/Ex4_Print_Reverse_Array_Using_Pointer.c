#include <stdio.h>

int countMaxOnesBetweenZeros(int num) {
    int maxCount = 0;
    int currentCount = 0;
    int inSequence = 0; // Flag to indicate if we're between zeros

    while (num > 0) {
        if (num & 1) { // Check if the least significant bit is 1
            if (inSequence) {
                currentCount++;
            } else {
                currentCount = 1;
                inSequence = 1;
            }
        } else { // The bit is 0
            if (inSequence) {
                if (currentCount > maxCount) {
                    maxCount = currentCount;
                }
                currentCount = 0;
                inSequence = 0;
            }
        }
        num >>= 1; // Right shift to process the next bit
    }
    
    return maxCount;
}

int main() {
    int num;

    // Test Case 1
    num = 14; // Binary: 01110
    printf("Max number of ones between zeros for %d: %d\n", num, countMaxOnesBetweenZeros(num)); // Output: 3

    // Test Case 2
    num = 110; // Binary: 01101110
    printf("Max number of ones between zeros for %d: %d\n", num, countMaxOnesBetweenZeros(num)); // Output: 3

    return 0;
}
