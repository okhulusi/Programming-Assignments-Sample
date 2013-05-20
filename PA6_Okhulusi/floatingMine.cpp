#include "floatingMine.h"

using namespace std;

FloatingMine:: FloatingMine(int x, int y, QPixmap *pixmap) : GameItem(x,y,pixmap){
	vx_ = -1;
	vy_ = 0;
	
	id_ = -1;
	readyToExplode_ = false;
	doneExploding_ = false;
	type_ = "Mine";
}

FloatingMine:: ~FloatingMine(){

}

void FloatingMine:: act(){
	counter_++;
	if(counter_%10 == 0){
		setPos(x() + vx_, y() + vy_*gameSpeed_);
	}
}

void FloatingMine:: mousePressEvent(QGraphicsSceneMouseEvent *event){
	if(event->button() == Qt::LeftButton){
		event = event;
		readyToExplode_ = true;
		emit minePressed(this);
	}
}

bool FloatingMine:: isReadyToExplode(){
	return readyToExplode_;
}

bool FloatingMine:: isDoneExploding(){
	return doneExploding_;
}

void FloatingMine:: setIsDoneExploding(bool isDoneExploding){
	doneExploding_ = isDoneExploding;
}

void FloatingMine:: setSpeed(int gameSpeed){
	gameSpeed_ = gameSpeed;
}

string FloatingMine:: getType(){
	return type_;
}

int FloatingMine:: getID(){
	return id_;
}

void FloatingMine:: setID(int newID){
	id_ = newID;
}
