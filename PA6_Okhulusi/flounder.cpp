#include "flounder.h"

using namespace std;

Flounder:: Flounder(int x, int y, QPixmap *pixmap, Player *player) : GameItem(x, y, pixmap){
	player_ = player;
	vx_ = -1;
	vy_ = 0;
	
	yDistToMove_ = abs(player->y() - y);
	
	if(player->y()-y > 0){
		newvy_ = yDistToMove_/450.0;
	} else if(player->y()-y < 0){
		newvy_ = -1*yDistToMove_/450.0;
	} else{
		newvy_ = 0;
	}
	
	counter_ = 0;
	moving_ = false;
	
	type_ = "Flounder";
}

Flounder:: ~Flounder(){
}

void Flounder:: act(){
	counter_++;
	moving_ = true;
	setPos(x() + vx_, y() + newvy_);
}

void Flounder::setSpeed(int gameSpeed){
	gameSpeed_ = gameSpeed;
}

string Flounder:: getType(){
	return type_;
}

bool Flounder:: isMoving(){
	return moving_;
}
