#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<bios.h>
#define SNAKE 178
#define RIGHT 19712
#define LEFT 19200
#define UP 18432
#define DOWN 20480
#define TLT 218
#define TRT 191
#define HL 196
#define BLT 192
#define VL 179
#define BRT 217
#define SP 32
#define FOOD 176
struct snakeNode
{
	struct snakeNode * prev;
	int col;
	int row;
	struct snakeNode * next;
};
struct snakeNode * START, * END;
int row, col;
struct snakeNode * createSnakeNode(int r, int c)
{
	struct snakeNode * newnode = (struct snakeNode * )malloc(sizeof(struct snakeNode));
	newnode -> next = NULL;
	newnode -> col = c;
	newnode -> row = r;
	newnode -> prev = NULL;
	return newnode;
}
void createSnake(int r, int c)
{
	struct snakeNode * newnode ;
	newnode = createSnakeNode(r,c);
	if(START == NULL)
		START = END = newnode;
	else
	{
		END -> next = newnode;
		newnode -> prev = END;
		END = newnode;
	}
}
void drawBorder()
{
	int row = 1, col = 1;
	gotoxy(col,row);
	printf("%c",TLT);
	col++;
	for(; col < 79; gotoxy(col++,row) , printf("%c", HL));
	gotoxy(col,row);
	printf("%c",TRT);
	for(row = row + 1,col = 1; row < 25; row++,col = 1)
	{
		gotoxy(col, row);
		printf("%c", VL);
		for(; col < 79; gotoxy(++col,row) , printf("%c", SP));
		gotoxy(col,row);
		printf("%c", VL);

	}
	gotoxy(col,row);
	printf("%c", BLT);
	col++;
	for(; col < 79; gotoxy(col++,row) , printf("%c", HL));
	gotoxy(col,row);
	printf("%c",BRT);
}
void gameOver(int score)
{
	int r = 12, c = 30;
	gotoxy(c,r++);
	printf("GAME OVER");
	gotoxy(c,r);
	printf("Your score is: %d ", score);
}
void generateFood(int scol, int srow, int * fcol, int * frow)
{
	while(1)
	{
		* fcol = rand()%80;
		* frow = rand()%25;
		if((* fcol != scol || * frow != srow ) && ( * frow > 1 && * frow < 25 && * fcol > 1 && * fcol < 79 ))
			break;
	}
	gotoxy(* fcol,* frow);
	printf("%c",FOOD);
}
void display()
{
	struct snakeNode *tptr;
	for(tptr=START;tptr;tptr=tptr->next)
	{
		gotoxy(tptr -> col, tptr -> row);
		printf("%c", SNAKE);
	}
	row = END -> row;
	col = END -> col;
}
void moveStart()
{
	struct snakeNode *temp;
	temp = START;
	if(START != END)
	{
		START -> next -> prev = NULL;
		START = START -> next;
	}
	else
	{
		START = END = NULL;
	}
	gotoxy(temp -> col, temp -> row);
	printf("%c", SP);
	free(temp);
}
void playGame()
{
	int key, score = 0;
	int drow, dcol,LF = 0,RF = 0,UF = 0,DF = 0;
	int * fcol, * frow;
	struct snakeNode * temp;
	struct snakeNode * newnode;
	col = rand()%80;
	row = rand()%25;
	createSnake(row,col);
	display();
	generateFood(col,row, fcol, frow);
	do
	{
		while(bioskey(1) == 0);
		key = (bioskey(0));
		gotoxy(col,row);
		printf("%c",SP);
		switch(key)
		{
			case RIGHT :
				if(RF == 0)
				{
					moveStart();
					col++;
					dcol = col + 1;
					drow = row;
					createSnake(row,col);
					UF = DF = 0;
					LF = 1;
				}
				break;
			case LEFT:
				if(LF == 0)
				{
					moveStart();
					col--;
					dcol = col - 1;
					drow = row;
					createSnake(row,col);
					DF = UF = 0;
					RF = 1;
				}
				break;
			case UP:
				if(UF == 0)
				{
					moveStart();
					row--;
					drow = row - 1;
					dcol = col;
					createSnake(row,col);
					RF = LF = 0;
					DF = 1;
				}
				break;
			case DOWN:
				if(DF == 0)
				{
					moveStart();
					row++;
					drow = row + 1;
					dcol = col;
					createSnake(row,col);
					RF = LF = 0;
					UF = 1;
				}
				break;
		}
		if(* fcol == col && * frow == row)
		{
			score+=5;
			createSnake(drow,dcol);
			generateFood(col,row, fcol, frow);
		}
		if(row <= 1 || row >= 25 || col <= 1 || col >= 80)
		{
			gameOver(score);
			return;
		}
		display();
	}while(key != 283);
}

int main()
{
	int scol, srow, fcol, frow;
	clrscr();
	drawBorder();
	playGame();
	getch();
	return 0;
}