#include "eelBlast.h"

using namespace std;

Blast:: Blast(int x, int y, QPixmap *pixmap) : GameItem(x,y,pixmap){
	vx_ = -1;
	vy_ = 0;
	type_ = "Blast";
}

Blast:: ~Blast(){

}

void Blast:: act(){
	setPos(x() + vx_, y() + vy_);
}

void Blast:: setSpeed(int gameSpeed){
	gameSpeed_ = gameSpeed;
}

string Blast:: getType(){
	return type_;
}
