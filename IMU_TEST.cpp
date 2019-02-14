#include <iostream>
#include <vector>
#include <stdio.h>
#include <sidekiq_api.h>
sort(acc_x.begin(), acc_x.end() ) // include with the accelerometer code to sort the values from least to greatest. 
//delta time should be 10 ms
#define DELTA_TIME 10
double accel_reading = 0, prev_accel_reading = 0;
void ask()
{
  cout << "Choose an ODD number of times to read the data for each axis?" << end1;
  cin >> re;
	std::vector<int> reps(re);
}

float median(float arr[re]) 
{
	for(int i = 0; i < reps; i++) {
		for(int n; n < reps; n++) {
			if (arr[i] < acc_x.at(n) ) {
			for (int q = --reps; q > n; q--) acc_x.at(q) = acc_x.at(q-1);
				acc_x.at(n) = arr[i];
				break;
			} else if (n == (reps-1) acc_x.at(n) = arr[i];
		}
	}
	return acc_x[acc_x.size() / 2]; // produces middle value. 
}
void integrate(double &value) 
{
	//integrates whatever you want the value variable to be when you put into main 
	//make sure the angle inputted is the filtered angle and not the raw angle
	value+= (accel_reading - prev_accel_reading) * DELTA_TIME;
}
void read_imu( uint8_t card, uint8_t reg, int *val) //reads the raw values
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
        *val = result;
    }
    else
    {
        printf("Error: unable to read register 0x%x (%" PRIi32 ")\n", reg, status);
    }
}

int main(int argc, char *argv[])
{
	uint_8t card = 0;
	int acc_x, acc_y, acc_z, gyro_x, gyro_y, gyro_z;
	for(int time = 0; i <= 3600000; i+=DELTA_TIME) // 100HZ of data samples for 1 hr
	{
		read_imu(card, 0x3b, &acc_x);
		read_imu(card, 0x3d, &acc_y);
		read_imu(card, 0x3f, &acc_z);
		read_imu(card, 0x43, &gyro_x);
		read_imu(card, 0x45, &gyro_y);
		read_imu(card, 0x47, &gyro_z);
		
	`	usleep(DELTA_TIME);
	}
}
