/* Sphere.c */
/*
	Seongwoo Choi
	Winter 2015
	CMPS11
	Sphere.c
	Laboratory Assignment 7
*/
#include<math.h>
#include<stdio.h>

int main() {
	double radius;
	double surface_area, volume;
	const double pi = 3.141592654;

	printf("Enter the radius of the sphere: ");
	scanf("%lf", &radius);
	surface_area = 4 * pi * pow(radius, 2);
	volume = (4.0/3) * pi * pow(radius, 3);
	printf("The volume is: %.3lf", volume);
	printf(" and the surface area is %3lf", surface_area);
	printf("\n");
	return 0;

}

