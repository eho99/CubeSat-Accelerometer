#include <iostream>
#include <vector>
#include <stdio.h>
#include <cmath>
#include <algorithm>
#include <string.h>
#include <string>
#include <fstream>

using namespace std;

#define DELTA_TIME 0.1
#define KGYRO 0.5
#define KACCEL 0.5
#define RAD_TO_DEGREES 180/3.141592653589793238463

float compFilter(float accel_data, float gyro_data)
{
	return KGYRO * gyro_data + KACCEL * accel_data;
}

int main()
{
	double gyro_y;  //raw_value
	double median_ay, median_az;
	double angle_ay = 0;
	double angle_gy = 0;
	double finalAngle_y = 0;

	string fgyro_y, faccel_y, faccel_z;
	ifstream test("path_to_file.csv");

	for (int i = 0; i < 49; i++) // 49 samples from ashwins data
	{
		getline(test, fgyro_y, ','); //reads gyro y data
		getline(test, faccel_y, ','); //reads accel y data
		getline(test, faccel_z, '\n'); //reads accel z data

		gyro_y = stod(fgyro_y);
		median_ay = stod(faccel_y);
		median_az = stod(faccel_z);
    
    printf("\n"); //make look sexy
		printf("Iteration %d\n", i);

		//arctan A for accel
		angle_ay += (atan2(median_ay, median_az) * RAD_TO_DEGREES); //filtered theta
		printf("accel angle y is %.9f\n", angle_ay);

		//integrate gyro values into angle
		angle_gy = (gyro_y * DELTA_TIME) + finalAngle_y; // added up delta thetas
		printf("gyro angle y is %.9f\n", finalAngle_y);

		//complementary filter
		finalAngle_y += compFilter(angle_gy, angle_ay); //needed to help calculate delta theta 
		printf("final angle y is %.9f\n", finalAngle_y);
		printf("------------------"); //make look sexy
		
		//output
		fstream data("output.csv")
		data << "Accel Y, Accel Z, Gyro Y, Delta Theta Y, Accel Angle Y, Final Angle Y" << endl;
		for(int i = 0; i < 49; i++)
		{
			data << ("%f, %f, %f, %f, %f, %f", median_ay, median_az, gyro_y, angle_gy, angle_ay, finalAngle_y) << endl
		}
		usleep(

	}
}

