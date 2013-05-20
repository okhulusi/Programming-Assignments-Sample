#include "bubblePowerUp.h"
BubblePowerUp:: BubblePowerUp(int x, int y, QPixmap *pixmap) : GameItem(x,y,pixmap) {
	vx_ = -20;
	vy_ = -10;
	counter_ = 0;
	
	type_ = "Bubble";
}

BubblePowerUp:: ~BubblePowerUp(){

}

void BubblePowerUp:: act(){
	counter_++;
	if(counter_%40 == 0){
		setPos(x() + vx_, y() + vy_);
	
		if(counter_%200 == 0){
			vy_*= -1;
		}
	}
}

void BubblePowerUp:: setSpeed(int gameSpeed){
	gameSpeed_ = gameSpeed;
}

string BubblePowerUp:: getType(){
	return type_;
}
