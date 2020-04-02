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
int row = 0;
int P; 
int max;
int total = 0;

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

void poptable(int ID, int burst, int table[max][P], int respt[])
{
	int stopPoint = row + burst;
	if(respt[ID] == -1 || respt[P-1] == 1)
	{
		respt[ID] = row;
		//printf("respt[%d] = %d\n",ID,respt[ID]);
	}
	for(; row < stopPoint; row++)
	{
		//printf("poptable[%d][%d]", row, ID);
		table[row][ID] = 1;
		//printf(" = %d\n", table[row][ID]);	
	}
	//printf("\n");
}

void fixTable(int table[max][P])
{
	int first1 = 0;
	int last1 = 0;
	int one = 0;
	int count = 0;
	
	for(int i = 0; i < P; i++) // col
	{
		count = 0;
		first1 = 0;
		last1 = 0;
		one = 0;

		for(int x = 0; x < total; x++) // row
		{
			if(table[x][i] == 1) // this sets the flag for the first ID
			{
				one = 1;
			}
			// this if fills in the first1 if it didnt start first
			if(table[x][i] == 0 && one == 0)
			{
				table[x][i] = 1;
				one = 1;
				first1 = x; // should always be 0;
				//printf("ID = %d, first1 = %d\n", i, first1);
			}
			// this if finds last 1
			if(table[x][i] == 1 && one == 1)  // error here
			{				
				last1 = x;
				//printf("ID = %d, last1 = %d\n", i, last1);
			}
			else
			{
				count++; // only kept for troubleshooting
			}
			
		}
		
		for(int z = first1; z < last1 - 1; z++)
		{
			table[z][i] = 1; // error here
			//printf("fixing table[%d][%d]\n", z, i);
		}
		
		
	}
}

void printtable(int table[max][P])
{
	for(int i = 0; i < total; i++)
	{
		for(int y = 0; y < P; y++)
		{
			printf(" %d ", table[i][y]);
		}
		printf("\n");
	}
}

int main(int argc, char** argv)
{
	// setup
	fp = fopen(argv[1], "r");
	
	fscanf(fp, "%d", &P); // numb processes. in this project always = 1
	fscanf(fp, "%d", &P); // numb of execution elements
	int lines;
	fscanf(fp, "%d", &lines);
	
	int temp[3];
	int master[P];
	int switchArray[P];
	int respT[P];	
	for(int a = 0; a < P; a++) // init both
	{
		master[a] = 0; 
		switchArray[a] = 0;
		respT[a] = -1;
	}
	max = P * 1024;
	int myTable[max][P];
	for(int b = 0; b < max; b++)
	{
		for(int pop = 0; pop < P; pop++)
		{
			myTable[b][pop] = 0;
		}
	}


	// build
	int pre = 0;
	int cur;	
	
	for(int i = 0; i < lines; i++) 
	{
		next3(temp); // gets numbers
		
		poptable(temp[0]-1, temp[1],myTable, respT); // pops table

		master[temp[0]-1] += temp[1];

		total += temp[1];
		// now counting switches
		cur = temp[0];
		if(cur != pre)
		{
			if(switchArray[temp[0]-1] == 0) // if first time increase  vcon
			{
				switchArray[pre - 1] = 1;
				vcon++; 	
			}
			else if(switchArray[temp[0]-1] == 1)
			{
				invcon++;
			}
		}
		pre = cur;
	}
	
	fixTable(myTable);	
	//printtable(myTable);
	int sum = 0;
	//stats
	for(int t = 0; t < total; t++)
	{
		for(int r = 0; r < P; r++)
		{
			if(myTable[t][r] == 1)
			{
				sum++;
			}
		}
	}
	
	// calc
	turnaround = (double) sum / P;
	waiting = (double) (sum - total) / P;
	thrput = (double) P / total;
	sum = 0;
	for(int g = 0; g < P; g++)
	{
		sum += respT[g];
		//printf("sum = %d, why = %d\n",sum, respT[g]);
	}
	response = (double) sum / P;
	// print
	printAll();

	return 0;
}
