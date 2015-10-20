#include<iostream>
#include<ctime>
#include<cstdlib>
#include"colormod.h"
using namespace std;

Color::Modifier border(Color::FG_GREEN);
Color::Modifier given(Color::FG_BLUE);
Color::Modifier wrong(Color::FG_RED);
Color::Modifier def(Color::FG_DEFAULT);
Color::Modifier puzzle(Color::FG_PUZZLE);

bool checkCell(int board[9][9],int guess,int row,int col);
bool checkRow(int board[9][9],int guess,int row);
bool checkCol(int board[9][9],int guess,int col);
bool checkSquare(int board[9][9],int guess,int row,int col);
void outputBoard(int[9][9],bool[9][9]);
void shuffleBoard(int[9][9]);
void removeNumbers(int[9][9],bool[9][9]);
void play(int[9][9],bool[9][9]);
int main()
{

	srand(time(0));
	int board[9][9]={{8,1,2,3,7,9,6,5,4},
                     {5,9,4,1,2,6,3,7,8},
                     {6,7,3,5,8,4,2,1,9},
                     {4,3,1,8,9,5,7,6,2},
                     {9,2,5,4,6,7,1,8,3},
                     {7,8,6,2,3,1,9,4,5},
                     {1,5,9,6,4,3,8,2,7},
                     {2,6,7,9,5,8,4,3,1},
                     {3,4,8,7,1,2,5,9,6}};
    
	bool reference[9][9]={false};
	int randy=static_cast<int>(rand())%10;
    for(int i=0;i<randy;i++)
        shuffleBoard(board);
    int answer[9][9]={0};
    for(int i=0;i<9;i++)
        for(int w=0;w<9;w++)
                answer[i][w]=board[i][w];
    removeNumbers(board,reference);
    bool gameOver=false;
    while(!gameOver)
    {
        for(int i=0;i<9;i++)
            for(int w=0;w<9;w++)
                gameOver&=(answer[i][w]==board[i][w]);
        play(board,reference);
    }
    cout<<"YOU WIN!!!"<<endl<<endl<<endl;
}
void play(int board[9][9],bool reference[9][9])
{
    	int col,row,guess;
        outputBoard(board,reference);
        cout<<"Enter the row, column, and guess you have for the puzzle, separated by spaces. They are numbered 1-9 top to bottom and left to right.\n";
        cin>>row;
        cin>>col;
        cin>>guess;
        if(!(col<1||col>9||row<0||row>9||guess<0||guess>9)&&!reference[row-1][col-1])
        {
            board[row-1][col-1]=guess;
        }
        if(reference[row-1][col-1])
        {
            cout<<"You can't change a given number!"<<endl;
        }
}

void outputBoard(int board[9][9],bool reference[9][9])
{
	cout<<def<<puzzle;
    for(int i=0;i<41;i++)
		cout<<border<<'_';
	cout<<endl<<'|';
	for(int i=0;i<39;i++)
		cout<<'_';
	cout<<'|';
	cout<<endl;
	for(int i=0;i<9;i++)
	{
        cout<<border<<"|| ";
		for(int w=0; w<9;w++)
		{
			cout<<(reference[i][w]?given:def);
            (board[i][w]?cout<<board[i][w]:cout<<" ")<<(w%3==2?border:def)<<" |";
			if(w%3!=2)
				cout<<' ';
			if(w%3==2)
				cout<<border<<"| "<<def;
		}
		cout<<endl;
		cout<<border<<"||";
		for(int w=0;w<37;w++)
			cout<<(i%3==2?border:def)<<'_'<<border;
		cout<<"||"<<endl;
		if(i%3==2)
		{
			if(i<8)
                cout<<"||";
			for(int w=0;w<(i==8?41:37);w++)
				cout<<'_';
            if(i<8)
                cout<<"||";
			cout<<endl;
		}
		cout<<def<<endl;
	}
	
}
void shuffleBoard(int board[9][9])
{
	
	int temp[9][9]={0};
	for(int i=0;i<9;i++)
		for(int w=0;w<9;w++)
			temp[i][w]=board[i][w];
	int randy;
    randy = (static_cast<int>(rand()))%3;
	for(int i=0;i<9;i++)
		for(int w=0;w<9;w++)
			board[i][w]=temp[(i+randy*3)%9][w];
    for(int i=0;i<9;i++)
		for(int w=0;w<9;w++)
			temp[i][w]=board[i][w];
	randy = (static_cast<int>(rand()))%3;
	for(int i=0;i<9;i++)
		for(int w=0;w<9;w++)
			board[i][w]=temp[i][(w+randy*3)%9];
	randy = (static_cast<int>(rand()))%2;
	if(randy)
	{
		int num=0;
		for(int i=0;i<9;i++)
		{
			for(int w=0;w<9/2;w++)
			{
				num = board[i][w];
				board[i][w]=board[i][8-w];
				board[i][8-w]=num;
			}
		}		
	}
	randy = (static_cast<int>(rand()))%2;
	if(randy)
	{
		int num=0;
		for(int i=0;i<9/2;i++)
		{
			for(int w=0;w<9;w++)
			{
				num = board[i][w];
				board[i][w]=board[8-i][w];
				board[8-i][w]=num;
			}
		}		
	}
}
bool checkCell(int board[9][9],int guess, int row, int col)
{
	return(checkRow(board,guess,col)&&checkCol(board,guess,col)&&checkSquare(board,guess,row,col));
}
bool checkRow(int board[9][9],int guess, int row)
{	
	bool clear=true;
	for(int i=0; i<9;i++)
		if(guess==board[row][i])
			clear=false;
	return clear;
}
bool checkCol(int board[9][9],int guess, int col)
{
	bool clear=true;
	for(int i=0; i<9;i++)
		if(guess==board[i][col])
			clear=false;
	return clear;
}
bool checkSquare(int board[9][9],int guess, int row, int col)
{
	bool clear=true;
	for(int i=row/3*3;i<row/3*3+3;i++)
		for(int w=col/3*3;w<col/3*3+3;w++)
			if(board[i][w]==guess)
				 clear=false;
	return clear;
}
void removeNumbers(int board[9][9],bool reference[9][9])
{
    int randy = static_cast<int>(rand())%8;
    int randolf = static_cast<int>(rand())%8;
    for(int i=0;i<(randy+1)*(randolf+1)+30;i++)
        board[static_cast<int>(rand())%9][static_cast<int>(rand())%9]=0;
    for(int i=0;i<9;i++)
        for(int w=0;w<9;w++)
                reference[i][w]=board[i][w];
}
