#include <stdlib.h>
#include <stdio.h>


int vcon = 0;
int invcon = 0;
float cpu = 100.00;
double thrput;
float turnaround = 0.00;
double waiting;
double response;
FILE *fp;

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
	response = (double) turnaround / P; 
	turnaround = (double) (total + turnaround)  / P;		
	thrput = (double) P / total;
	waiting = (double) total / P;
	
	// print
	printAll();

	return 0;
}
