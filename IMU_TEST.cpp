#include <iostream>
#include <vector>
#include <stdio.h>
//#include <sidekiq_api.h>
#include <cmath>
#include<algorithm>
//#include <unistd.h>
using namespace std;
//delta time should be 10 ms
#define DELTA_TIME 10
#define GYRO_CONST 0.98
#define ACCEL_CONST 0.02
#define PULL_NUMBER 360000
#define SPLIT_MARKER 5

/* 
so basically the entire process in int main can run when there are enough received values from
the accel to match the SPLIT_MARKER and to produce a median filter. Whenever a median filter cannot be produced
the "ready" variable is set to 0 so the other functions do not try to run without a median of the accel values
*/
int ready;

float compFilter(float accel_data, float gyro_data)
{
	return GYRO_CONST * gyro_data + ACCEL_CONST * accel_data;
}

float median(vector<float> arr)
{


		//While vector size / 1 >= 1
		//Take last five values of vector
		//Take 2nd index
	if(SPLIT_MARKER % 2 == 0 )
		while (1)
		{
			if (arr.size() >= (SPLIT_MARKER + 1))
			{
				arr.clear();
			}
			if (arr.size() == SPLIT_MARKER)
			{
				sort(arr.end() - SPLIT_MARKER, arr.end());
				return ((arr[arr.size() / 2 - 1]) + arr[arr.size() / 2 - 1]) / 2;
				arr.clear();
				break;
			}
			else
				ready = 0;
				break;

	
		}
	else
		while (1)
		{
			if (arr.size() >= (SPLIT_MARKER + 1))
			{
				arr.clear();
			}
			if (arr.size() == SPLIT_MARKER)
			{
				sort(arr.end() - SPLIT_MARKER, arr.end());
				return arr[arr.size() / 2];
				arr.clear();
				break;
			}
			else
				ready = 0;
				break;
		}

	
}

int read_imu(uint8_t card, uint8_t reg) //reads the raw values
{
	int32_t status = 0;
	uint8_t low_byte = 0, high_byte = 0;
	int result;
	status = skiq_read_accel_reg(card, reg, &high_byte, 1);
	if (status == 0) status = skiq_read_accel_reg(card, reg + 1, &low_byte, 1);
	if (status == 0)
	{
		result = (((int)high_byte) << 8) | low_byte;
		if (result >= 0x8000) result = result - 0x10000;
		return result;
	}
}
int main(int argc, char *argv[])
{
	uint_8t card = 0;
	vector<float> acc_x, acc_y, acc_z, gyro_x, gyro_y, gyro_z; //raw_values
	float median_ax = 0, median_ay = 0, median_az = 0, median_gx = 0, median_gy = 0, median_gz = 0;
	float angle_ax = 0, angle_ay = 0, angle_az = 0;
	float angle_gx = 0, angle_gy = 0, angle_gz = 0;
	float finalAngle_x = 0, finalAngle_y = 0, finalAngle_z = 0;
	for (int i = 0; i < PULL_NUMBER; i++) // 100HZ of data samples for 1 hr
	{
		//acc_x.push_back(read_imu(card, 0x3b));
		//acc_y.push_back(read_imu(card, 0x3d));
		//acc_z.push_back(read_imu(card, 0x3f));
		//gyro_x.push_back(read_imu(card, 0x43));
		//gyro_y.push_back(read_imu(card, 0x45));
		//gyro_z.push_back(read_imu(card, 0x47));

		//median filter for accel
		median_ax = median(acc_x);
		median_ay = median(acc_y);
		median_az = median(acc_z);

		//arctan A for accel
		if (ready != 0)
		{
			angle_ax += atan2(median_ay, median_ax);
			angle_ay += atan2(median_az, median_ax);
			angle_az += atan2(median_az, median_ay);
		}

		//integrate gyro values into angle
		if (ready != 0)
		{
			if (i != 0)
			{
				angle_gx += ((gyro_x.at(i) - gyro_x.at(i - 1)) / 2) * DELTA_TIME;
				angle_gy += ((gyro_y.at(i) - gyro_y.at(i - 1)) / 2) * DELTA_TIME;
				angle_gz += ((gyro_z.at(i) - gyro_z.at(i - 1)) / 2) * DELTA_TIME;
			}
		}

		
		//complimentary filter
		if (ready = 0)
		{
			finalAngle_x += compFilter(angle_gx, angle_ax);
			finalAngle_y += compFilter(angle_gy, angle_ay);
			finalAngle_z += compFilter(angle_gz, angle_az);
		}

		//output for excel data table -> graph.
		usleep(DELTA_TIME);
	}
}
