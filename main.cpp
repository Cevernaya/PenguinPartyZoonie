#include <iostream>
//#include "penguin_party.h"

using namespace std;

/* R,G,B(8),Y,P*/





//전역변수 시작

unsigned hand[7][6]; //hand [player order] [card color]
unsigned board[9][9]; //board [step] [location]
unsigned penalty_score[7];
unsigned current_player;
unsigned max_player;
unsigned survival_state[7] = {0,0,0,0,0,0,0}; //0: default, 1: survive, 2: dead, 3: waiting

//전역변수 끝





//일반 함수 시작

void total_init();
void round_init();
void print_hand();
void print_board();
void turn_init();
bool current_player_is_defeated();
bool current_player_has_no_card();
void get_penalty();
void score_comp();



void total_init()
{
	//max_player 입력 받기;
	for(unsigned i = 1; i <= max_player; ++i)
	{penalty_score[i] = 0;}
	
	current_player = 0;
	
	round_init();
}


void round_init()
{
	//랜덤 hand 받기
	
	for(unsigned i = 1; i <= 9; ++i) { for(unsigned j = 1; j <= 9; ++j)
	{board[i][j] = 0;}}
	
	player_left = max_player;
	
	for(unsigned i = 1; i <= max_player; ++i)
	{survival_state[i] = 0;}
	
	
	turn_init();
}


void print_hand()
{
	for(unsigned i = 1; i <= 5; ++i)
	{cout << i + 1 << ": " << hand[current_player][i] << " \n";}
}


void print_board()
{
	for(unsigned i = 1; i <= 8; ++i)
	{
		cout << i ; //몇층인지 나타내주는 숫자 인터페이스
		
		for(int k = 8; k >= i; --k)		//가시성을 높이기 위한 공백 입력
		{cout << " ";} 
		
		for(int j = 1; j <= i; ++j)     // 현재 보드의 카드 배치 상태 표시
		{cout << board[i][j] << " ";}
		
		cout << "\n";
	}
}


void turn_init() //플레이어간의 순서
{
	++current_player;
	if(max_player < current_player)
	{current_player = 1;}
	
	if(survival_state[current_player]==1)
	{
		survival_state[current_player]==2;
		get_penalty();
	}
	
	if(survival_state[current_player]==2)
	{	
		cout << current_player <<" 플레이어가 아웃되었으므로 다음 플레이어에게 턴이 넘어갑니다";
		++current_player;
		turn_init();	//다시 턴함수를 실행해야하는데 이렇게 호출하면 되는건지? - 재준
	}
	else
	{
		//여기에 사용자 입력 받는 함수 추가
	}
	
	if(current_player_has_no_card())
	{get_advantage();}
	
	unsigned player_left = 0;
	for(var i = 1; i <= max_player; ++i)
	{
		if(survival_state[i] == true)
		{++player_left;} //수정이 필요해보임
	}
	
	if(player_left == 0)
	{score_comp();}
	else
	{turn_init();}
}


bool current_player_is_defeated()	//현재 턴을 진행중인 플레이어의 패배판정여부
{
	for(unsigned i = 1; i <= 8; ++i){ for(unsigned j = 1; j <= 8; ++j) //비어있는 모든칸에 배치가 가능한지 확인
	{
		if(board[i][j] == 0)
		{
			if(checking() == true)
			{return false;}
		}
	}}
	
	survival_state[current_player] = 1;
	return true;
}

bool current_player_has_no_card()
{
	unsigned temp = 0;
	for(unsigned i = 1; i <= 5; ++i)
	{temp += hand[current_player][i];}
	
	if(temp == 0)
	{return true;}
	return false;
}

void get_penalty()
{
	unsigned cards_left = 0;
	for(unsigned i = 1; i < = 5; ++i)
	{cards_left += hand[current_player][i];}
	
	penalty_score[current_player] += cards_left;
}


void get_advantage()
{}

void score_comp()
{}



//일반 함수 끝





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

//todo

//check whether a rule is violated or not
bool checking(int board[9][9], int step, int place, int kind){

	if(board[step][place] == 0)
	{
		if(step==8)
		{
			return true;
		}
		else
		{
			if(board[step+1][place]!=0 && board[step+1][place+1]!=0)
			{
				if(board[step+1][place]==kind || board[step+1][place+1]==kind)	//ancient main 으로 가기위해서는 -1씩 해주어야합니다.
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
	//코드에서는 8, 1에 카드를 놓으면 왼쪽에 더이상 카드를 놓을 수 없지만 실제게임에서는 가능해야함
	
	int hand[5]={3,3,3,3,3};
	
	printBoard(board);
	cout << "\n";
	
	while(true)
	{	
		
		
		printBoard(board);
		printHands(hand);
		int step, place, kind;
		cout << "step place kind\n";
		cin >> step >> place >> kind;
		
		// check setcard
		if(checking(board, step, place, kind) == 1 && hand[kind-1]!=0)
		{
			board[step-1][place-1]=kind;
			hand[kind-1]=hand[kind-1]-1;
			
			// check win
			if(hand[0]==0 && hand[1] ==0 && hand[2] ==0 && hand[3]==0 && hand[4] ==0)
			{
				cout << "You win!\n";
				break;
			}
		}
		else{
			cout << "다시 시도해주세요\n";
		}
		
	}
	
	return 0;
}

//ⒶⒷⒸⒹⒺ①②③④⑤