#ifndef GAME_ITEM_H
#define GAME_ITEM_H

#include <QtGui>
#include <string>

using namespace std;

/** The GameItem class is an abstract class inherited by all 6 "things" in the game in addition to the player and the 
*	background class (total of 8 game items).  It extends QGraphicsPixmapItem and QObject such that it is used 
*	to track movement and collisions of an image along the screen.
*	@author Omar Khulusi
*/
class GameItem : public QObject, public QGraphicsPixmapItem {
	Q_OBJECT
	public:
		/**	Constructor for GameItem.  Takes in an x and y location, in addition to a QPixmap.
		*	These parameters are passed in through the calls of its 8 child classes (Background, Player,
		*	eelBlast, Shark, BlastingEel, FloatingMine, BubblePowerUp, ClamPowerUp).
		*	@param x X location of object
		*	@param y Y location of object
		*	@param pixmap Pointer to the QPixmap that will serve as the image of the object
		*/
		GameItem(int x, int y, QPixmap *pixmap);
		
		/**	Destructor for GameItem
		*/
		~GameItem();
		
		/** Pure virtual function that is used in all base classes. Every time the timer times out in the mainwindow,
		*	it calls act, this method, on every object in the scene, acting accordingly for each type of GameItem.
		*	@return nothing
		*/
		virtual void act() = 0;
		
		/**	Pure virtual function that is used in all base classes.  This is used to set the game speed to be equal
		*	in all classes.  When it is incremented, this is called in all classes.
		*	@param gameSpeed the gamespeed as determined in the main window
		*	@return nothing	
		*/
		virtual void setSpeed(int gameSpeed) = 0;
		
		/**	Pure virtual function that returns the type of the child object.  This is used to determine what to do
		*	upon collision with each item to the player.
		*	@return string Specific to the child class it is called on.
		*/
		virtual string getType() = 0;
	
	protected:
	
		/** Type specific to child class*/
		string type_;
		
		/** speed of the game*/
		int gameSpeed_;
		
		/** Horizontal velocity of the item*/
		int vx_;
		
		/** Vertical velocity of the item*/
		int vy_;	
};
#endif
