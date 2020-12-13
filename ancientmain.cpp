#include <iostream>
#include <cstdlib>
using namespace std;

/* R,G,B(8),Y,P*/
int turnorder = 0; // defalut = 0; player = 1; computer = 2;
//print out player's hand state
void printHands(int hands[5]){
	for(int i=0; i<5; i++)
	{
		cout<<i+1<<" : "<<hands[i]<<" "<<"\n";
	}
}

//to make a board in initial state
void printBoard(int board[8][8]){
	
	for(int i=0; i<8; i++){
		cout << i+1;
		for(int k=8; k>i; k--)
		{
			cout << " ";
		}
		for(int j=0; j<=i; j++){
			cout << board[i][j] << " ";
		}
		cout << "\n";
	}
}


//check whether a rule is violated or not
bool checking(int board[8][8], int step, int place, int kind){
	
	if(kind<0 || kind>6)
	{
		return false;
	}
	
	if(board[step-1][place-1] == 0)
	{
		if(step==8)
		{
			return true;
		}
		else
		{
			if(board[step][place-1]!=0 && board[step][place]!=0)
			{
				if(board[step][place-1]==kind || board[step][place]==kind)
				{
					return true;
				}
			}
		}
	}
	return false;
}

int main(){
	
	int board[8][8]={0,0};
	
	int hand[5]={3,3,3,3,3};
	int comhand[5]={3,3,3,3,3};
	printBoard(board);
	cout << "\n";
	cout << "\n" << "Choose 1st player. Player first : 1 , Computer first : 2";
	int temp = 0;
	cin >> temp;
	while(temp!=1 && temp!=2) //잘못된 값이 입력될경우 걸러내기
	{
		cout << "\n다시 입력해주세요.\n";
		cin >> temp;
	}
	turnorder = temp;
	
	while(true)
	{	
		printBoard(board);
		int step, place, kind;
		if(turnorder == 1) //player choose a card
		{
			printHands(hand);
			cout << "Player's turn\n";
			cout << "step place kind\n";
			cin >> step >> place >> kind;
	
			// check setcard
			if(checking(board, step, place, kind) == 1 && hand[kind-1]!=0)
			{
				board[step-1][place-1]=kind;
				hand[kind-1]=hand[kind-1]-1;
				turnorder = 2;
			}
			else{
				cout << "다시 시도해주세요\n";
			}

			// check win
			if(hand[0]==0 && hand[1] ==0 && hand[2] ==0 && hand[3]==0 && hand[4] ==0)
			{
				cout << "You win!\n";
				break;
			}

			// check that is next player (computer) lose?
			bool canSet = false;
			for(int i=1; i<=8; i++)//i=step
			{
				for(int j=1; j<=i; j++)//j=place
				{
					for(int k = 1; k<=5; k++) //k=kind
					{
						if(checking(board, i, j, k) == 1 && comhand[k-1] != 0)
						{
							canSet = true;
						}
					}
				}
			}
			if(!canSet)
			{
				cout << "Computer Lose...!\n";
				break;
			}
		}
		
		else if(turnorder == 2) //Computer choose a card
		{
			printHands(comhand);
			int tempstep, tempplace, tempkind;
			while(true) //to get appropriate info about card
			{
				tempstep = rand()%8+1;
				tempplace = rand()%8+1;
				tempkind = rand()%5+1;
				if(checking(board, tempstep, tempplace, tempkind) == 1 && comhand[tempkind-1]!=0)
				{
					step = tempstep;
					place = tempplace;
					kind = tempkind;
					cout << "Computer Set: " << step << ", " << place << ", " << kind << "\n";
					break;
				}
			}
			// check setcard
			if(checking(board, step, place, kind) == 1 && comhand[kind-1]!=0)
			{
				board[step-1][place-1]=kind;
				comhand[kind-1]=comhand[kind-1]-1;
				turnorder = 1;
			}
			
			//check com's win
			
			if(comhand[0]==0 && comhand[1] ==0 && comhand[2] ==0 && comhand[3]==0 && comhand[4] ==0)
			{
				cout << "Computer win!\n";
				break; // <- 전체 while문 탈출?
			}
			
			//check that if next player (player) lose?
			bool canSet = false;
			for(int i=1; i<=8; i++)//i=step
			{
				for(int j=1; j<=i; j++)//j=place
				{
					for(int k = 1; k<=5; k++) //k=kind
					{
						if(checking(board, i, j, k) == 1 && hand[k-1] != 0)
						{
							canSet = true;
						}
					}
				}
			}
			if(!canSet)
			{
				cout << "Player Lose...!\n";
				break;
			}
		}
		
	}
	
	return 0;
}

//ⒶⒷⒸⒹⒺ①②③④⑤