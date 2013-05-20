#include "clamPowerUp.h"

ClamPowerUp:: ClamPowerUp(int x, int y, QPixmap *pixmap) : GameItem(x,y,pixmap){
	vx_ = -1;
	vy_ = -1;
	counter_ = 0;
	type_ = "Clam";
}

ClamPowerUp:: ~ClamPowerUp(){

}

void ClamPowerUp:: act(){
	counter_++;
	if(counter_ % 40 == 0){
		if(counter_ > 400*40){
			vx_ = -5;
		} else if(counter_ > 200*40){
			vx_ = 1;
		}
	
		if(counter_%100*40 == 0){
			vy_*=-1;
		}
		setPos(x() + vx_*gameSpeed_, y() + vy_*gameSpeed_);
	}
}

void ClamPowerUp::setSpeed(int gameSpeed){
	gameSpeed_ = gameSpeed;
}

string ClamPowerUp:: getType(){
	return type_;
}
