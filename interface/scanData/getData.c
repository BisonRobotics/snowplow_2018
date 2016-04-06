#include <stdlib.h>
#include <stdio.h>

char sickData[3000];

int main(int argc, char* argv[]) {
	int i, j, k;
	char c = 0;
	int scan = 1; //flag used for exiting scan loop

	printf("Initializing data array to NULL\n");
	for(i = 0; i < 3000; i++) {
		sickData[i] = 0;
	}

	//scan actual data
	printf("Scanning data\n");
	for(j = 0; scan == 1 && j < 3000; j++) {
		c = getchar();
		if(c != 3) {
			sickData[j] = c;
		} else {
			sickData[j] = c;
			scan = 0;
		}
	}

	printf("Printing SICK data\n");
	for(k = 0; k < 3000 && sickData[k] != 0; k++) {
		printf("%c", sickData[k]);
	}
}
