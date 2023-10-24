/*	Kalemkeridis Evangelos Rafail
	20222 2016 00058
	dit16058@uop.gr
	------------------------------
	Mais Spyridon
	2022 2013 00176
	dit13176@uop.gr
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>



int** boardMemoryAllocation();
int tileColorNum();
void boardFill(int **board, int x, int y, int tileColotNumb);
void boardPrint(int **board, int x, int y);
char menu();
void bombing(int **board, int row, int col, int x, int y);
int readX();
int readY();
void dropDown(int **board, int x, int y);
void pushLeft(int **board, int x, int y);
void pushRight(int **board, int x, int y);
void addTile(int **board, int row, int col, int x, int y, int tileColorNumbClone);
int hammerTime(int **board, int row, int col, int x, int y, int *combo);
int finishCheck(int **board, int x, int y);
int fact(int x);

int main(void)
{
	/*Using current time to generate a random seed*/
	srand(time(0));
	
	/*Variables*/
	int i,j, level=0, score=0, row, col, tileTemp, finish, counter=0, combo2=1;
	int x, y, tileColorNumb, tileColorNumbClone;
	int *combo=&combo2;
	int **board;
	char ch='z';
	char inputA[7];
	char inputB[7];
	char inputC[2];
	char inputD[10];
	
	/*functions*/
	x = readX();
	y = readY();
	board = boardMemoryAllocation(x, y);
	tileColorNumb = tileColorNum();
	boardFill(board, x, y, tileColorNumb);
	
	
	while (ch != 'X' && ch != 'x')
	{
		combo2=0;
		if (x==20 && y==20)
			break;
		boardPrint(board, x, y);
		printf("\n\n");
		ch = menu();
		if (ch == 'A')
		{
			printf("Input example: h 1,3\n");
			gets(inputA);
			while ((sscanf(inputA, "h %d,%d", &row, &col) !=2) || (inputA[1] != ' ') || row > x || row < 1 || col > y || col <1)
			{
				printf("Input error - Try again!\n\n");
				gets(inputA);
			}
			row--;
			col--;
			if (row < x-1)
				if (board[row+1][col] == board[row][col])
					counter++;
			if (col < y-1)
				if (board[row][col+1] == board[row][col])
					counter++;
			if (row > 0)
				if (board[row-1][col] == board[row][col])
					counter++;
			if (col > 0)
				if (board[row][col-1] == board[row][col])
					counter++;
		
			
			if (board[row][col] == 0)
			{
				printf("Invalid tile - Try again!\n");
				board[row][col] = tileTemp;
				continue;
			}
			if (counter > 0)
			{
				hammerTime(board, row, col, x, y, combo);	
			}
			else
			{
				printf("This tile has no neighbors. Try again!\n");
				continue;
			}
			for (i=0; i<x; i++)
				for (j=0; j<y; j++)
					if (board[i][j] == -1)
						board[i][j] = 0;
			dropDown(board, x, y);
			combo2=fact(combo2);
			score=score+combo2;
			printf("Score: %d!\n", score);
		}
		if (ch == 'B')
		{	
			printf("Input example: b 3,4\n");
			gets(inputB);
			while ((sscanf(inputB, "b %d,%d", &row, &col) != 2) || (inputB[1] != ' ') || row > x || row < 1 || col > y || col < 1)
			{
				printf("Input error - Try again!\n\n");
				gets(inputB);
			}
			while (board[row-1][col-1] == 0)
			{
				printf("The tile is empty. Try again...\n");
				gets(inputB);
				while ((sscanf(inputB, "b %d,%d", &row, &col) != 2) || (inputB[1] != ' ') || row > x || row < 1 || col > y || col < 1)
				{
				printf("Input error - Try again!\n\n");
				gets(inputB);
				}
			}
			row--;
			col--;
			bombing(board, row, col, x, y);
			dropDown(board, x, y);
			printf("\nBOOM!\n\n");
			score+=-10000;
			printf("Score: %d!\n", score);
		}
		if (ch == 'C')
		{
			printf("Pushing: 'pl' to push left, 'pr' to push right!\n");
			gets(inputC);
			while ((inputC[0] != 'p') || (inputC[1] != 'l') && (inputC[1] != 'r'))
			{
				printf("Input error - Try again!\n\n");
				gets(inputC);
			}
			if (inputC[1] == 'l')
				pushLeft(board, x, y);
			else 
				pushRight(board, x, y);
				
		}
		if (ch == 'D')
		{
			printf("Give dimensions & color of tile (example: a 2,3 5)\n");
			gets(inputD);
			while ((sscanf(inputD, "a %d,%d %d", &row, &col, &tileColorNumbClone) != 3) || (inputD[1] != ' ') || row > x || row < 1 || col > y || col < 1 || tileColorNumbClone > tileColorNumb || tileColorNumbClone < 1)
			{
				printf("Input error - Try again!\n\n");
				gets(inputD);
			}
			while (board[row-1][col-1] != 0)
			{
				printf("Tile space is filled - Try again!\n");
				gets(inputD);
				while ((sscanf(inputD, "a %d,%d %d", &row, &col, &tileColorNumbClone) != 3) || (inputD[1] != ' ') || row > x || row < 1 || col > y || col < 1 || tileColorNumbClone > tileColorNumb || tileColorNumbClone < 1)
				{
					printf("Input error - Try again!\n\n");
					gets(inputD);
				}
			}
			addTile(board, row, col, x, y, tileColorNumbClone);
			dropDown(board, x, y);
			
		}
		counter=0;
		if (finish=finishCheck(board, x, y)==x*y)
		{
			level++;
			break;
		}			
	}
	
	//freeing memory up
	for (i=0;i<x;i++)
		free(board[i]);
	free(board);
	
	if (ch != 'X' && ch != 'x')
	{
		while (x<=20 || y<=20)
		{
			combo=0;
			if (x<20)
				x++;
			if (y<20)
				y++;
			level++;
			
			printf("Level %d!\n", level);
			board = boardMemoryAllocation(x, y);
			boardFill(board, x, y, tileColorNumb);
			boardPrint(board, x, y);
			while (ch != 'X' && ch != 'x')
			{
				ch = menu();
				if (ch == 'A')
				{
					printf("Input example: h 1,3\n");
					gets(inputA);
					while ((sscanf(inputA, "h %d,%d", &row, &col) !=2) || (inputA[1] != ' ') || row > x || row < 1 || col > y || col <1)
					{
						printf("Input error - Try again!\n\n");
						gets(inputA);
					}
					row--;
					col--;
					if (row < x-1)
						if (board[row+1][col] == board[row][col])
							counter++;
					if (col < y-1)
						if (board[row][col+1] == board[row][col])
							counter++;
					if (row > 0)
						if (board[row-1][col] == board[row][col])
							counter++;
					if (col > 0)
						if (board[row][col-1] == board[row][col])
							counter++;
		
					if (board[row][col] == 0)
					{
						printf("Invalid tile - Try again!\n");
						board[row][col] = tileTemp;
						continue;
					}
					if (counter > 0)
					{
						hammerTime(board, row, col, x, y, combo);	
					}
					else
					{
						printf("This tile has no neighbors. Try again!\n");	
						continue;
					}
					for (i=0; i<x; i++)
						for (j=0; j<y; j++)
							if (board[i][j] == -1)
								board[i][j] = 0;
					dropDown(board, x, y);		
					combo2=fact(combo2);
					score=score+combo2;
					printf("Score: %d!\n", score);
				
				}
				if (ch == 'B')
				{	
					printf("Input example: b 3,4\n");
					gets(inputB);
					while ((sscanf(inputB, "b %d,%d", &row, &col) != 2) || (inputB[1] != ' ') || row > x || row < 1 || col > y || col < 1)
					{
						printf("Input error - Try again!\n\n");
						gets(inputB);
					}
					while (board[row-1][col-1] == 0)
					{
						printf("The tile is empty. Try again...\n");
						gets(inputB);
						while ((sscanf(inputB, "b %d,%d", &row, &col) != 2) || (inputB[1] != ' ') || row > x || row < 1 || col > y || col < 1)
						{
						printf("Input error - Try again!\n\n");
						gets(inputB);
						}
					}
					row--;
					col--;
					bombing(board, row, col, x, y);
					dropDown(board, x, y);
					printf("\nBOOM!\n\n");
					score+=-10000;
					printf("Score: %d!\n", score);
				}
				if (ch == 'C')
				{
					printf("Pushing: 'pl' to push left, 'pr' to push right!\n");
					gets(inputC);
					while ((inputC[0] != 'p') || (inputC[1] != 'l') && (inputC[1] != 'r'))
					{
						printf("Input error - Try again!\n\n");
						gets(inputC);
					}
					if (inputC[1] == 'l')
						pushLeft(board, x, y);
					else 
						pushRight(board, x, y);
						
				}
				if (ch == 'D')
				{
					printf("Give dimensions & color of tile (example: a 2,3 5)\n");
					gets(inputD);
					while ((sscanf(inputD, "a %d,%d %d", &row, &col, &tileColorNumbClone) != 3) || (inputD[1] != ' ') || row > x || row < 1 || col > y || col < 1 || tileColorNumbClone > tileColorNumb || tileColorNumbClone < 1)
					{
						printf("Input error - Try again!\n\n");
						gets(inputD);
					}
					while (board[row-1][col-1] != 0)
					{
						printf("Tile space is filled - Try again!\n");
						gets(inputD);
						while ((sscanf(inputD, "a %d,%d %d", &row, &col, &tileColorNumbClone) != 3) || (inputD[1] != ' ') || row > x || row < 1 || col > y || col < 1 || tileColorNumbClone > tileColorNumb || tileColorNumbClone < 1)
						{
							printf("Input error - Try again!\n\n");
							gets(inputD);
						}
					}
					addTile(board, row, col, x, y, tileColorNumbClone);
					dropDown(board, x, y);
					
				}
				counter=0;
				if (finish=finishCheck(board, x, y)==x*y)
				{
					for (i=0;i<x;i++)
						free(board[i]);
					free(board);
					break;
				}
					
			}
			
			if (x==20 && y==20)
			{
				ch='X';
				break;
			}
			
			}


		}
		printf("\nYou've managed to pass %d Level(s)\nFinal Score: %d points\n\nThank you for playing, we hope to see you again!\n", level, score);
	}

















//functions

int** boardMemoryAllocation(int x, int y)
{
	int i, j, **board;
	
	/*Memory allocation & availability check*/
	board = (int**) malloc(x * sizeof(int*));
	if (board == NULL) 
	{
		printf("Not enough memory. Exiting...\n");
		exit(1);
	}
	
	for (i=0; i<x; i++)
	{
		board[i] = (int*) malloc (y * sizeof(int));
		if (board[i] == NULL)
		{
			printf("Not enough memory. Exiting...\n");
			exit(1);
		}
	}
	
	return board;
}

int readX()
{
	int x;
	/*input of X Dimension*/
	printf("Please give board's dimension X\n");
	scanf("%d", &x);
	while(x<6 || x>20)
	{
		printf("The board's dimensions should have a value between 6 & 20\n");
		scanf("%d", &x);
	}
	return x;
}

int readY()
{
	int y;
	/*input of Y Dimension*/
	printf("Please give board's dimension Y\n");
	scanf("%d", &y);	
	while(y<6 || y>20)
	{
		printf("The board's dimensions should have a value between 6 & 20\n");
		scanf("%d", &y);
	}
	return y;
}

int tileColorNum()
{
	int tileColorNum;
	/*Number of tile colors (between 1 & 9)*/
	printf("How many colors should the tiles have? (1-9)\n");
	scanf("%d", &tileColorNum);
	while(tileColorNum<1 || tileColorNum>9)
	{
		printf("Color range: 1-9. Please select an appropriate value.\n");
		scanf("%d", &tileColorNum);
	}
	
	return tileColorNum;
}

void boardFill(int **board, int x, int y, int tileColorNumb)
{
	int i, j;
	for (i=0; i<x; i++)
		for (j=0; j<y; j++)
			board[i][j] = rand() % tileColorNumb + 1;
}

void boardPrint(int **board, int x, int y)
{
	int i, j;
	printf("    ");
	for (i=0; i<y; i++)
	{
		if (i+1 < 10)
			printf("%d  ", i+1);
		else
			printf("%d ", i+1);
	}
	printf("\n");
	printf("  ");
	for (i=0; i<y; i++)
		printf("---");
	printf("-");
	printf("\n");
	
	for (i=0; i<x; i++)
	{
		if (i+1<10)
			printf("%d | ", i+1);
		else
			printf("%d| ", i+1);
		for (j=0; j<y; j++)
		{
			if (board[i][j] == 0)
				printf(".  ");
			else
				printf("%d  ", board[i][j]);
		}
		printf("\n");
	}
	
}

char menu()
{
	/*Main game's options*/
	char ch;
	printf("Choose an option!\n\nA. Hammer\nB. Bomb\nC. Shift Tiles\nD. Add Tile\nX. Exit Game\n");
	scanf(" %c", &ch);
	getchar();
	while (ch != 'A' && ch != 'B' && ch != 'C' && ch != 'D' && ch != 'X' && ch != 'x')
	{
		printf("Invalid option. Try again.\n\n");
		scanf(" %c", &ch);
		getchar();
	}
	
	return ch;
}

void bombing(int **board, int row, int col, int x, int y)
{
	if (row>0 && row<x-1 && col>0 && row<y-1)
	{
		board[row][col]=0;
		board[row][col+1]=0;
		board[row][col-1]=0;
		board[row+1][col]=0;
		board[row+1][col-1]=0;
		board[row+1][col+1]=0;
		board[row-1][col-1]=0;
		board[row-1][col+1]=0;
		board[row-1][col]=0;
	}
	else if (row == 0 && col == 0)
	{
		board[row][col]=0;
		board[row][col+1]=0;
		board[row+1][col]=0;
		board[row+1][col+1]=0;
	}
	else if (row == 0 && col == y-1)
	{
		board[row][col]=0;
		board[row][col-1]=0;
		board[row+1][col]=0;
		board[row+1][col-1]=0;
	}
	else if (row == x-1 && col == 0)
	{
		board[row][col]=0;
		board[row][col+1]=0;
		board[row-1][col]=0;
		board[row-1][col+1]=0;
	}
	else if (row == x-1 && col == y-1)
	{
		board[row][col]=0;
		board[row][col-1]=0;
		board[row-1][col]=0;
		board[row-1][col-1]=0;
	}
	else if (row == 0)
	{
		board[row][col]=0;
		board[row][col-1]=0;
		board[row][col+1]=0;
		board[row+1][col-1]=0;
		board[row+1][col]=0;
		board[row+1][col+1]=0;
		
	}
	else if (row == x-1)
	{
		board[row][col]=0;
		board[row][col-1]=0;
		board[row][col+1]=0;
		board[row-1][col-1]=0;
		board[row-1][col]=0;
		board[row-1][col+1]=0;
	}
	else if (col == 0)
	{
		board[row][col]=0;
		board[row][col+1]=0;
		board[row-1][col]=0;
		board[row-1][col+1]=0;
		board[row+1][col]=0;
		board[row+1][col+1]=0;
	}
	else
	{
		board[row][col]=0;
		board[row][col-1]=0;
		board[row-1][col]=0;
		board[row-1][col-1]=0;
		board[row+1][col]=0;
		board[row+1][col-1]=0;
	}
}

void dropDown(int **board, int x, int y)
{
	int flag =1;
	int i,j;
	
	while (flag == 1)
	{
		flag = 0;
		for (i=0; i<x-1; i++)
			for (j=0;j<y;j++)
				if (board[i+1][j] == 0 && board[i][j] != 0)
				{
					board[i+1][j] = board[i][j];
					board[i][j] = 0;
					flag = 1;
				}
	}
}

void pushLeft(int **board, int x, int y)
{
	int i, j;
	int flag = 1;
	int found = 1;
	int times=0;
	
	while (flag == 1)
	{
		while (found == 1)
		{
			found = 0;
			for (j=0;j<y;j++)
			{
				if (board[x-1][j] == 0 && j < y-1 && times < y*y)
				{	
					flag=1;
					times++;
					found = 1;
					for(i=0; i<x; i++)
					{
						board[i][j] = board[i][j+1];
						board[i][j+1] = 0;
					}
				}
			}
		}
		flag = 0;
	}
	if (times == 0)
		printf("No empty columns - Try again after you destroy one!\n\n");
}

void pushRight(int **board, int x, int y)
{
	int i, j;
	int flag = 1;
	int found = 1;
	int times=0;
	
	while (flag == 1)
	{
		while (found == 1)
		{
			found = 0;
			for (j=0;j<y;j++)
			{
				if (board[x-1][j] == 0 && j > 0 && times < y*y)
				{	
					flag=1;
					times++;
					found = 1;
					for(i=0; i<x; i++)
					{
						board[i][j] = board[i][j-1];
						board[i][j-1] = 0;
					}
				}
			}
		}
		flag = 0;
	}
	if (times == 0)
		printf("No empty columns - Try again after you destroy one!\n\n");
}

void addTile(int **board, int row, int col, int x, int y, int tileColorNumbClone)
{
	if (board[row-1][col-1] == 0)
		board[row-1][col-1] = tileColorNumbClone;
}

int hammerTime(int **board, int row, int col, int x, int y, int *combo)
{
	int temp;
	if (row >= x || row < 0)
	{
		printf("Out of bounds, try again!\n");
		return 0;
	}
	if (col >= y || col < 0)
	{
		printf("Out of bounds, try again!\n");
		return 0;
	}
	temp=board[row][col];
	board[row][col] = -1;
	if ((row-1 >= 0) && (temp == board[row-1][col]))
	{
		if (board[row-1][col] == temp)
			++*combo;
			hammerTime(board, row-1, col, x, y, combo);
	}
	if ((col-1 >= 0) && (temp == board[row][col-1]))
	{
		if (board[row][col-1] == temp)
			++*combo;
			hammerTime(board, row, col-1, x, y, combo);
	}
	if ((row+1 < x) && (temp == board[row+1][col]))
	{
		if (board[row+1][col] == temp)
			++*combo;
			hammerTime(board, row+1, col, x, y, combo);
	}
	if ((col+1 < y) && (temp == board[row][col+1]))
	{
		if (board[row][col+1] == temp)
			++*combo;
			hammerTime(board, row, col+1, x, y, combo);
	}
	
}
int finishCheck(int **board, int x, int y)
{
	int i, j, count=0;
	for (i=0; i<x; i++)
		for (j=0; j<y; j++)
			if (board[i][j] == 0)
				count++;
	return count;
}
int fact(int x)
{
	if (x == 1)
		return 1;
	else if (x > 10)
		return 362880;
	else
		return x*fact(x-1);
}
