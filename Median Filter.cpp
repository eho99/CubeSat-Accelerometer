#include <iostream>
#include <vector>

sort(acc_x.begin(), acc_x.end() ) // include with the accelerometer code to sort the values from least to greatest. 

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
	return acc_x[acc_x.size() / 2]; 
}
 
