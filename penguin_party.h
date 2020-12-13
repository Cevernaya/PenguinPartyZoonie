#ifndef __PENGUIN_PARTY_H__
#define __PENGUIN_PARTY_H__

void total_init();
void round_init();
void print_hand();
void print_board();
void turn_init();
bool current_player_is_defeated();
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
	
	for(unsigned i = 1; i <= 6; ++i)
	{survival_state[i] = true;}
	
	
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
	
	if(current_player_is_defeated())
	{get_penalty();}
	else
	{
		//여기에 사용자 입력 받는 함수 추가
	}
	
	if(player_left == 0)
	{score_comp();}
	else
	{turn_init();}
}


bool current_player_is_defeated()
{
	bool flag = false;
	for(unsigned i = 1; i <= 8; ++i){ for(unsigned j = 1; j <= 8; ++j) //비어있는 모든칸에 배치가 가능한지 확인
	{
		if(board[i][j] == 0)
		{
			if(checking() == true)
			{return false;}
		}
	}}
	
	survival_state[current_player] = false;
	return true;
}


void get_penalty()
{
	unsigned cards_left = 0;
	for(unsigned i = 1; i < = 5; ++i)
	{cards_left += hand[current_player][i];}
	
	penalty_score[current_player] += cards_left;
}


void score_comp()
{}

#endif