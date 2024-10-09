#include <stdio.h>
#include <string.h>

struct Distance {
    int feet;
    float inch;
};



int main() {
    struct Distance d1, d2, sum;

    printf("\nEnter information for 1st Distance \n");
    printf("Enter 1st distance in feets : ");
    scanf("%d", &d1.feet);
    printf("Enter 1st distance in inches : ");
    scanf("%f", &d1.inch);

    printf("\nEnter information for 2nd Distance \n");
    printf("Enter 1st distance in feets : ");
    scanf("%d", &d2.feet);
    printf("Enter 1st distance in inches : ");
    scanf("%f", &d2.inch);

    sum.feet = d1.feet + d2.feet;
    sum.inch = d1.inch + d2.inch;

    while(sum.inch > 12.0){
        sum.inch -= 12.0;
        sum.feet++;
    }

    printf("Sum of Distances = %d\'-%.1f\"", sum.feet, sum.inch);
    return 0;
}
