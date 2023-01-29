/*				
					DESIGN IDEA
		Menu
			PLAY
			EXIT
		GamePlay
			Wall
				4 Wall
			Snake
				Draw
					Head
					Body
				Move
					Up,Down,Right,Left
			Point
				Random in Scence  
				Respawn when eaten ( Don't respawn in Body)
				Upgrade Snake's Body
			GameOver
				Head go to the Wall
				Head eat the Body
*/
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "mylib.h"

#define MAX 100

using namespace std;

//======= MENU =======


//======= GAMEPLAY ===
int count=0;
int toadoX[MAX] = {0,1};
int toadoY[MAX] = {0,1};
int body=4;
int x_p=-1;
int y_p=-1;
int check = 3;
//-------------------
void play();
//--------
void wall();
void snake();
//--------
void draw_snake();
void control(int &,int &,int &);
void move(int ,int);
//--------
void make_Fruit();
void draw_Fruit(int);
void re_Fruit(int);
bool eat_Fruit();
bool check_p();
//--------
bool eat_body();
bool gameover();
//====================


//====== NEW ========
int flag_p=0;
int flag_relife=0;
int life = 0;
int timer=1;
int bodytimer[7]={ 0 };
int counttimer[7]={ 0 };
int checktimer[7]={ 0 };
int count_rate=0;
//---------
int rand_p();
void score();
void life_count();
void effect_p(int);
void save(int &);
void relife(int );
bool f_relife();
void delete_snake();
//int rate(int &,int &);
/*
void score();
void show_timer(int &);
void count_life();
void effect(int);

int effect_point();
*/
//======================

int main(){
	//-------Menu
	
	//---GamePlay
	play();
	_getch();
}
void menu(){
	
}
void play(){
	system("cls");
	srand(time(NULL));
	ShowCur(0);
	int ra=rand_p();
	int flag_ra=0;
	//----BUILD-----
		// Draw Wall
	wall();
		// Make Snake
	snake();
		//Fruit_Zero
	score();
	life_count(); 
	make_Fruit();
	draw_Fruit(ra);
	//----Gameplay--
	int x=toadoX[0];
	int y=toadoY[0];
					/* 	0:Down
					 	1:Up
					 	2:Right
					 	3:Left	*/
	while(true){
		SetColor(14);
		if(f_relife()){
			relife(timer);	
			x=toadoX[0];
			y=toadoY[0];
		}
		//Clear Old Data
		gotoXY(toadoX[body],toadoY[body]);
			cout<<" ";
		// Draw Snake
			draw_snake();
		if(f_relife()){
			int n=0;
			while(n<3){
				delete_snake();
				Sleep(200);
				draw_snake();
				Sleep(200);
				++n;	
			}
			flag_relife=0;
		}	
		//Control
		control(check,x,y);
		//Respawn Fruit
		effect_p(flag_p);
		if(flag_ra>0&&eat_Fruit())
			ra=rand_p();
		flag_ra=1;
		re_Fruit(ra);
		//Gameover
		if(gameover()&&life==0)
			break;
		if(gameover()&&life>0){
			delete_snake();
			wall();
			Sleep(200);
			flag_relife=1;
		}
		//Move
		if(!f_relife()){
			move(x,y);
			save(timer);
			//Speed
			if(check==0||check==1)
				Sleep(110);
			else
				Sleep(100);
		}
	}
}

void wall(){
	SetColor(11);
	for(int x=11;x<110;++x){
		gotoXY(x,1);
		cout<<char(196);
		gotoXY(x,27);
		cout<<char(196);
	}
	for(int y=2;y<=26;++y){
		gotoXY(10,y);
		cout<<char(179);
		gotoXY(110,y);
		cout<<char(179);
	}
	gotoXY(10,1);
	cout<<char(218);
	gotoXY(110,1);
	cout<<'+';
	gotoXY(10,27);
	cout<<'+';
	gotoXY(110,27);
	cout<<char(217);
}
void snake(){
	int x0=55;
	int y0=13;
	for(int i=0;i<body;++i){
		toadoX[i]=x0--;
		toadoY[i]=y0;
	}
}
void draw_snake(){
	for(int i=0;i<body;++i){
		gotoXY(toadoX[i],toadoY[i]);
		if(i==0)
			cout<<'O';
		else
			cout<<char(4);
	}
}
void control(int &check,int &x,int &y){
	if(_kbhit()){
		char c= _getch();
		if(c== -32){
			c= _getch();
			if(c==72&&check!=1)
				check =0;
			else if(c==80&&check!=0)
				check=1;
			else if(c==75&&check!=3)
				check=2;
			else if(c==77&&check!=2)
				check=3;
		}
	}
	if(check==0)
		--y;
	else if(check==1)
		++y;
	else if(check==2)
		--x;
	else if(check==3)
		++x;	
}
void move(int x,int y){
	for(int i=body;i>0;--i){
		toadoX[i]=toadoX[i-1];
		toadoY[i]=toadoY[i-1];
	}
	toadoX[0]=x;
	toadoY[0]=y;
}
void make_Fruit(){
	do{
		x_p=rand()%(109-11+1)+11;
		y_p=rand()%(26-2+1)+2;
	}while(check_p());
}
void draw_Fruit(int rand_p){
	gotoXY(x_p,y_p);
	SetColor(12);
	switch(rand_p){
		case 1:{
			SetColor(10 );
			cout<<char(5);
			flag_p=1;
			break;
		}
		case 2:{
			SetColor(14);
			cout<<char(4);
			flag_p=2;
			break;
		}
		case 3:{
			SetColor(12);
			cout<<char(3);
			flag_p=3;
			break;
		}
	}
}
bool check_p(){
	for(int i=0;i<body;++i){
		return x_p==toadoX[i]&&y_p==toadoY[i];
	}
}
void re_Fruit(int rand_p){
	int ra=rand_p;
	if(eat_Fruit()){
		make_Fruit();
		draw_Fruit(ra);
	}	
}
bool eat_body(){
	for(int i=1;i<body;++i){
		if(toadoX[i]==toadoX[0]&&toadoY[i]==toadoY[0])
			return true;
	}return false;
}
bool gameover(){
	if(toadoY[0]==1||toadoY[0]==27||toadoX[0]==10||toadoX[0]==110){
		return true;
	}return eat_body();
}
bool eat_Fruit(){
	return toadoX[0]==x_p&&toadoY[0]==y_p;
}

void score(){
	gotoXY(10,0);
	cout<<"POINT : "<<count;
}
void life_count(){
	gotoXY(107,0);
	cout<<char(3)<<" : "<<life/10<<life%10;
}
int rand_p(){
	return rand()%3+1;
}
void effect_p(int flag_p){
	if(eat_Fruit()){
		switch(flag_p){
			case 1:{
				++count;
				score();
				break;
			}
			case 2:{
				++body;
				break;
			}
			case 3:{
				++life;
				life_count();
				break;
			}
		}
	}
}
void save(int &timer){
	bodytimer[timer]=body;
	counttimer[timer]=count;
	checktimer[timer]=check;
	++timer;
	if(timer==3){
		timer=1;
	}
}
void relife(int timer){
	--life;
	life_count();
	int temp;
	if(timer==1)
		temp=2;
	else
		temp=1;
	for(int i=0;i<body;++i){
		toadoX[i]=toadoX[i+1];
		toadoY[i]=toadoY[i+1];
	}
	body=bodytimer[temp];
	count=counttimer[temp];
	check=checktimer[temp];	
}
bool f_relife(){
	return flag_relife==1;
}
void delete_snake(){
	for(int i=0;i<body;++i){
		gotoXY(toadoX[i],toadoY[i]);
		cout<<" ";
	}
}
/*
int rate(int &rand_p,int &count_rate){
	switch(rand_p){
		case 3:{
			int temp=rand()%2;
			if(temp==1&&count_rate<6)
				count_rate++;
			if(count_rate==5){
				count_rate=0;
				return 3;
			}else
				rand_p=rand()%3+1;
			break;
		}
	}
}
*/
