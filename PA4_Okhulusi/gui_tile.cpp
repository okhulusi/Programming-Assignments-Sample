#include "gui_tile.h"

GUITile::GUITile(int val,int x, int y): QGraphicsRectItem(x,y,50,50){
	x_ = x;
	y_ = y;
	value_ = val;
	if(val == 0){
		QString s = " ";
		setVisible(false);
		face_ = new QGraphicsSimpleTextItem(s,this);
		face_->setX(x_ + 25);
		face_->setY(y_ + 25);
	} else{
		QString s;
		s.setNum(value_);
		face_ = new QGraphicsSimpleTextItem(s, this);

		if(log10(val) < 1){
			face_->setX(x_ + 21);
			face_->setY(y_ + 18);
		} else {
			face_->setX(x_ + 15);
			face_->setY(y_ + 18);
		}
	}
}

GUITile::~GUITile(){
	delete face_;
}

void GUITile::moveTile(int x, int y){
	x_= x;
	y_= y;
	
	QPointF p(x_, y_);
    	QRectF r(rect());
    	r.moveTo(p);
    	setRect(r);
    	
    	if(log10(value_) < 1){
		face_->setX(x_ + 21);
		face_->setY(y_ + 18);
	} else {
		face_->setX(x_ + 15);
		face_->setY(y_ + 18);
	}
}

void GUITile::moveTileAnimate(){
	if(targetx_ == x_ && targety_ == y_){
		emit doneMoving(value_);
		return;	
	}
	
	if(targetx_ < x_){
		x_--;
	} else if(targetx_ > x_){
		x_++;
	} else if(targety_ < y_){
		y_--;
	} else if(targety_ > y_){
		y_++;
	} else {}
	
	QPointF p(x_, y_);
    	QRectF r(rect());
    	r.moveTo(p);
    	setRect(r);
    	
    	if(log10(value_) < 1){
		face_->setX(x_ + 21);
		face_->setY(y_ + 18);
	} else {
		face_->setX(x_ + 15);
		face_->setY(y_ + 18);
	}
}

void GUITile::mousePressEvent(QGraphicsSceneMouseEvent *event){
	event = event;
	emit signal(value_);
}

int GUITile:: getX() const{
	return x_;
}

int GUITile:: getY() const{
	return y_;
}
int GUITile:: getVal() const{
	return value_;
}

void GUITile:: setTarget(int newx, int newy) {
	targetx_ = newx;
	targety_ = newy;
}
