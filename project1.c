#include <stdlib.h>
#include <stdio.h>


int vcon = 0;
int invcon = 0;
float cpu = 100.00;
float thrput;
float turnaround = 0.00;
float waiting;
float response;


void printAll()
{
	printf("%d\n", vcon);
	printf("%d\n", invcon);
	printf("%.2f\n", cpu);
	printf("%.2f\n", thrput);	
	printf("%.2f\n", turnaround);
	printf("%.2f\n", waiting);
	printf("%.2f\n", response);
}

void next3(int* temp)
{
	int next;
	for(int i = 0; i < 3; i++)
	{
		scanf("%d",&next);
		//printf("next3 = %d\n", next);
		temp[i] = next;
	}
}

int main(int argc, char** argv)
{
	// setup
	int P;
	scanf("%d", &P); // numb processes. in this project always = 1
	scanf("%d", &P); // numb of execution elements
	int lines;
	scanf("%d", &lines);
	
	int temp[3];
	int master[P];
	for(int a = 0; a < P; a++)
	{
		master[a] = 0; 
	}

	// build
	int pre = 0; 
	int total = 0;
	for(int i = 0; i < lines; i++) 
	{
		next3(temp);
		master[temp[0]-1] += temp[1];
		total += temp[1];
		turnaround += temp[1];
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
	}
	
	// calc
	response = (float) turnaround / P; 
	turnaround = (float) (total + turnaround)  / P;		
	thrput = (float) P / total;
	waiting = (float) total / P;
	
	// print
	printAll();

	return 0;
}
