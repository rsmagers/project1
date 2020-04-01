#include <stdlib.h>
#include <stdio.h>


int vcon = 0;
int invcon = 0;
float cpu = 100.00;
double thrput;
double turnaround = 0.00;
double waiting;
double response;
FILE *fp;

void printAll()
{
	// waiting and response time are mixed up
	printf("%d\n", vcon);
	printf("%d\n", invcon);
	printf("%.02f\n", cpu);
	printf("%.02f\n", thrput);	
	printf("%.02f\n", turnaround);;
	printf("%.02f\n", waiting);
	printf("%.02f\n", response);
	
}

void next3(int* temp)
{
	int next;
	for(int i = 0; i < 3; i++)
	{
		fscanf(fp, "%d",&next);
		//printf("next3 = %d\n", next);
		temp[i] = next;
	}
}

int main(int argc, char** argv)
{
	// setup
	fp = fopen(argv[1], "r");
	
	int P;
	fscanf(fp, "%d", &P); // numb processes. in this project always = 1
	fscanf(fp, "%d", &P); // numb of execution elements
	int lines;
	fscanf(fp, "%d", &lines);
	
	int temp[3];
	int master[P];
	int switchArray[P];
	for(int a = 0; a < P; a++) // init both
	{
		master[a] = 0; 
		switchArray[a] = 0;
	}

	// build
	int pre = 0;
	int cur;	
	int total = 0;
	for(int i = 0; i < lines; i++) 
	{
		next3(temp);
		master[temp[0]-1] += temp[1];
		cur = temp[0];

		if(pre == 0) // this sets up pre, prob delete
		{
			//pre = cur;
		}

		total += temp[1];
		//turnaround += temp[1];

		if(cur != pre) // a switch happens
		{
			if(switchArray[temp[0]-1] == 0) // if first time increase  vcon
			{
				switchArray[pre - 1] = 1;
				printf("switchArray change = %d\n", switchArray[pre - 1]);
				vcon++; 
				//response += total;
				//printf("response = %f\n", response);
			}
			else if(switchArray[temp[0]-1] == 1)
			{
				printf("invcon switch = %d\n", switchArray[pre - 1]);
				invcon++;
				
			}

		}
		
		/*  Old switch counter
		// count switches	
		if(pre < temp[0])
		{
			pre = temp[0];
			vcon++;
		}
		else if(pre > temp[0])
		{
			pre = temp[0];
			invcon++;
			turnaround += temp[1];
		}
		//printf("total = %d\n", total);
		//printf("turnaround = %f\n", turnaround);
		*/
		printf("pre = %d, cur = %d\n", pre, cur);
		
		pre = cur;
	}
	for(int x = 0; x < P; x++)
	{
		turnaround += master[x] * (P - x);
	}


	//stats
	printf("total = %d\n", total);
	printf("turnaround = %f\n", turnaround);
	printf("response = %f\n", response);	
	// calc
	waiting = (double) (turnaround - total) / P; 

	response = (double) (turnaround - total) / P; // this is wrong

	turnaround = (double) turnaround  / P;		
	
	thrput = (double) P / total;
	
	
	// print
	printAll();

	return 0;
}
