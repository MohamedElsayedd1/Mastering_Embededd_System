#include <stdio.h>
#include <string.h>

#define PI 3.14
#define GET_AREA_CIRCLE(r) (PI * r * r)

int main() {
    float radius; 
    printf("Enter the radius : ");
    scanf("%f", &radius);
    printf("Area of circe : %f\n", GET_AREA_CIRCLE(radius));
    return 0;
}
