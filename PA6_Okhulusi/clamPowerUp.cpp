#include "clamPowerUp.h"

ClamPowerUp:: ClamPowerUp(int x, int y, QPixmap *pixmap, Player *player) : GameItem(x,y,pixmap){
	vx_ = -1;
	vy_ = 0;
	
	counter_ = 0;
	type_ = "Clam";
	
	player_ = player;
	yDistToMove_ = abs(player_->y()-y);
	
	if(player->y()-y > 0){
		newvy_ = yDistToMove_/400.0;
	} else if(player->y()-y < 0){
		newvy_ = -1*yDistToMove_/400.0;
	} else{
		newvy_ = 0;
	}
}

ClamPowerUp:: ~ClamPowerUp(){

}

void ClamPowerUp:: act(){
	counter_++;
	setPos(x() + vx_, y() + newvy_);
}

void ClamPowerUp::setSpeed(int gameSpeed){
	gameSpeed_ = gameSpeed;
}

string ClamPowerUp:: getType(){
	return type_;
}
