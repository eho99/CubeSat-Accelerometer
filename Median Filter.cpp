#include <stdio.h>

int re;

void ask()
{
  printf("How many times would you like to read the data for each axis?/n/n");
  scanf("%d", &re);
}

float median(float arr[re])
{
	for(int i = 0; i < re; i++) {
		for(int n; n < re; n++) {
			if (arr[i] < acc_x[n]) {
			for (int q = --re; q > n; q--) acc_x[q] = acc_x[q-1];
				acc_x[n] = arr[i];
				break;
			} else if (n == 4) acc_x[n] = arr[i];
		}
	}
	return acc_x[3]; 
}
 
