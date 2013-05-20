
#include "shark.h"

using namespace std;

Shark:: Shark(int x, int y, QPixmap *pixmap) : GameItem(x, y, pixmap){
	vx_ = -1;
	vy_ = 0;
	counter_ = 0;
	moving_ = false;
	
	type_ = "Shark";
}

Shark:: ~Shark(){
}

void Shark:: act(){
	counter_++;
	if(counter_ > 3000){
		moving_ = true;
		if(counter_%(2/gameSpeed_ + 1) == 0){
			setPos(x() + vx_*gameSpeed_, y() + vy_*gameSpeed_);
		}
	}
}

void Shark::setSpeed(int gameSpeed){
	gameSpeed_ = gameSpeed;
}

string Shark:: getType(){
	return type_;
}

bool Shark:: isMoving(){
	return moving_;
}

