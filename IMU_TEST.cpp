#include <iostream>
#include <vector>
#include <stdio.h>
#include <sidekiq_api.h>
#include <cmath>
//delta time should be 10 ms
#define DELTA_TIME 10
#define CONSTANT_1 0.98
#define CONSTANT_2 0.02

float compFilter(angleComp, accel_data, gyro_data)
{
	finalAngle = CONSTANT_1 * (angleComp + gyro_data) + CONSTANT_2 * (accel_data)
}

float median(vector<int> arr)
{
  sort(arr.begin(), arr.end());
  if int % 5 == 0
  {
      if(re.size() % 2 == 1) return arr[re.size()-1 / 2];
      else (re % 2 == 0) return ((arr[re.size()/2] + arr[re/2-1]) / 2);
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
  vector<int> acc_x, acc_y, acc_z, gyro_x, gyro_y, gyro_z; //raw_values
  int median_ax, median_ay, median_az, median_gx, median_gy, median_gz;
  int angle_ax, angle_ay, angle_az;
  int angle_gx, angle_gy, angle_gz;
	for(int i = 0; i < 360000; i++) // 100HZ of data samples for 1 hr
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
      angle_gx += (gyro_x.at(i) - gyro_x.at(i-1)) * DELTA_TIME;
      angle_gy += (gyro_y.at(i) - gyro_y.at(i-1)) * DELTA_TIME;
      angle_gz += (gyro_z.at(i) - gyro_z.at(i-1)) * DELTA_TIME;
    }
    
      //complimentary filter

      finalAngle_x += compFilter(angle_gx, accel_x, gyro_x)
      finalAngle_y += compFilter(angle_gy, accel_y, gyro_y)
      finalAngle_z += compFilter(angle_gz, accel_z, gyro_z)
		 

    //output for excel data table -> graph.
	` 
    usleep(DELTA_TIME);
	}
}
