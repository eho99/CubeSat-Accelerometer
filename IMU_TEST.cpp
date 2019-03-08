#include <iostream>
#include <vector>
#include <stdio.h>
#include <sidekiq_api.h>
#include <cmath>
#include <unistd.h>
using namespace std;
//delta time should be 10 ms
#define DELTA_TIME 10
#define GYRO_CONST 0.98
#define ACCEL_CONST 0.02
#define PULL_NUMBER 360000
#define SPLIT_MARKER 5

void compFilter(float accel_data, float gyro_data)
{
	float finalAngle;
	finalAngle = GYRO_CONST * gyro_data + ACCEL_CONST * (accel_data);
}

float median(vector<float> arr)
{
	//While vector size / 1 >= 1
	//Take last five values of vector
	//Take 2nd index
	//Pushback value into vector
	while(1)
		{
			if( arr.size() == SPLIT_MARKER)
			{
				sort(arr.end()-SPLIT_MARKER, arr.end())
				return arr[re.size() / 2];
				arr.clear();
			}
			elif( arr.size() >= 6)
			{
				arr.clear()
			}
		}
}

void read_imu( uint8_t card, uint8_t reg) //reads the raw values
{
  int32_t status = 0;
  uint8_t low_byte, high_byte;
  int result;
  status = skiq_read_accel_reg( card, reg, &high_byte, 1 );
  if( status == 0) status = skiq_read_accel_reg( card, reg+1, &low_byte, 1);
  if ( status == 0 )
  {
      result = (((int)high_byte)<<8) | low_byte;
      if (result >= 0x8000) result = result - 0x10000;
      return result;
  }
}
int main(int argc, char *argv[])
{
	uint_8t card = 0;
  vector<float> acc_x, acc_y, acc_z, gyro_x, gyro_y, gyro_z; //raw_values
  float median_ax, median_ay, median_az, median_gx, median_gy, median_gz;
  float angle_ax, angle_ay, angle_az;
  float angle_gx, angle_gy, angle_gz;
	float finalAngle_x, finalAngle_y, finalAngle_z;
	for(int i = 0; i < PULL_NUMBER; i++) // 100HZ of data samples for 1 hr
	{
		acc_x.insert(read_imu(card, 0x3b));
		acc_y.insert(read_imu(card, 0x3d));
		acc_z.insert(read_imu(card, 0x3f));
		gyro_x.insert(read_imu(card, 0x43));
		gyro_y.insert(read_imu(card, 0x45));
		gyro_z.insert(read_imu(card, 0x47));

    //median filter for accel
    median_ax = median(acc_x);
    median_ay = median(acc_y);
    median_az = median(acc_z);

    //arctan A for accel
    angle_ax += atan2(median_ay, median_ax);
    angle_ay += atan2(median_az, median_ax);
    angle_az += atan2(median_az, median_ay);

		//integrate gyro values into angle
    if(i != 0)
    {
      angle_gx += ((gyro_x.at(i) - gyro_x.at(i-1)) / 2) * DELTA_TIME;
      angle_gy += ((gyro_y.at(i) - gyro_y.at(i-1)) / 2) * DELTA_TIME;
      angle_gz += ((gyro_z.at(i) - gyro_z.at(i-1)) / 2) * DELTA_TIME;
    }

      //complimentary filter
      finalAngle_x += compFilter(angle_gx, acc_x);
      finalAngle_y += compFilter(angle_gy, acc_y);
      finalAngle_z += compFilter(angle_gz, acc_z);

    //output for excel data table -> graph.
    usleep(DELTA_TIME);
	}
}
