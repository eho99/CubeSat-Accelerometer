#include <iostream>
#include <vector>
#include <stdio.h>
#include <sidekiq_api.h>
sort(acc_x.begin(), acc_x.end() ) // include with the accelerometer code to sort the values from least to greatest. 

#define DELTA_TIME 30
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
int main(int argc, char *argv[])
{
	
}
