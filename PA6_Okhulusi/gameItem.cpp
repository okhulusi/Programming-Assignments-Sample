#include "gameItem.h"

GameItem:: GameItem(int x, int y, QPixmap *pixmap) : QObject(), QGraphicsPixmapItem(){
	vx_ = 0;
	vy_ = 0;
	gameSpeed_ = 1;
	setPos(x, y);
	setPixmap(*pixmap);
	type_ = "none";
}

GameItem:: ~GameItem(){
	
}
