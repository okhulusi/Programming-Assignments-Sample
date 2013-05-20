#include "blastingEel.h"

using namespace std;

BlastingEel:: BlastingEel(int x, int y, QPixmap *pixmap) : GameItem(x,y,pixmap){
	vx_ = 0;
	vy_ = 0;
	counter_ = 0;
	
	type_ = "BlastingEel";
}

BlastingEel:: ~BlastingEel(){

}

int BlastingEel:: getCounter(){
	return counter_;
}

void BlastingEel:: act(){
	counter_++;
	if(counter_%1000 == 0){
		vy_*=-1;
	}
	if(counter_ == 3000){
		emit firing(x(), y());
	}
	if(counter_ == 3300){
		emit firing(x(), y());
	}
	if(counter_ == 3600){
		emit firing(x(), y());
	}
	if(counter_ == 3900){
		emit firing(x(), y());
	}
	
	if(gameSpeed_ >=3){
		if(counter_ == 4200){
			emit firing(x(), y());
		}
		if(counter_ == 4500){
			emit firing(x(), y());
		}
		if(counter_ == 4800){
			emit firing(x(), y());
		}
		if(counter_ == 5100){
			emit firing(x(), y());
		}
	}
	setPos(x() + vx_, y() + vy_);
}

void BlastingEel:: setSpeed(int gameSpeed){
	gameSpeed_ = gameSpeed;
}

string BlastingEel:: getType(){
	return type_;
}

