#ifndef FLOATING_MINE_H
#define FLOATING_MINE_H

#include "gameItem.h"
#include <QPixmap>
#include <QGraphicsSceneMouseEvent>

/**	Floating Mines are spawned often throughout the game. A floating mine will explode if the player clicks it.
*	However, if the player is hit by the explosion he/she will still lose a life.  If the player collides with the mine
*	without detonation, he/she will also lose a life.  The mine does not detonate on collision, only on a left mouse click.
*	@author Omar Khulusi
*/
class FloatingMine: public GameItem {
	Q_OBJECT
	public:
		/**	Constructor for Floating Mine.  Takes in an x and y location, along with a pixmap to set the image.
		*	@param x X location
		*	@param y Y Location
		*	@param pixmap Pointer to the pixmap containing mine image, or an explosion image, depending on state.	
		*/
		FloatingMine(int x, int y, QPixmap *pixmap);
		
		/**	Destructor for Floating Mine
		*/
		~FloatingMine();
		
		/**	The Mine checks to see if it is exploding or has exploded.  It moves slowly from right to left,
		*	starting at the right side of the screen, moving to the left.  It's movement pattern is slower than
		*	other objects so that the player can click it for bonus points even if the game speed is faster.
		*	@return nothing
		*/
		void act();
		
		/**	Sets the gamespeed to react to.  Gamespeed is equal across all classes.
		*	@param gameSpeed Sets gamespeed_.
		*	@return nothing
		*/
		void setSpeed(int gameSpeed);
		
		/**	Returns the string Mine so that the class type can be determined externally
		*	@return string "Mine"
		*/
		string getType();
		
		/**	Returns the ID of the mine. Each mine is given an ID in the order it is created in the main window.
		*	This is used to track it when it is to be deleted by a click-explosion.
		*	@return id_ ID of the mine.
		*/
		int getID();
		
		/**	Sets the ID of the mine. This is done just after the mine is created.  This ID is used to track the
		*	mine when it is to be deleted by a click-explosion.
		*	@param id int value
		*	@return nothing
		*/
		void setID(int);
		
		/**	Returns whether or not the mine is ready to commence an explosion animation.
		*	@return readyToExplode_, bool value.
		*/
		bool isReadyToExplode();
		
		/**	Returns whether or not the mine is done exploding so that it can be deleted.
		*	@return doneExploding_, bool value.
		*/
		bool isDoneExploding();
		
		/**	Sets doneExploding_ value.
		*	@param isDoneExploding bool value
		*	@return nothing
		*/
		void setIsDoneExploding(bool);
		
	protected:
		/**	Registers when the mine is clicked with a left click, emitting a signal appropriately
		*	@param event Mouse Click Event, handled mostly by Qt
		*	@return nothing
		*/
		void mousePressEvent(QGraphicsSceneMouseEvent *event);
	signals:
		/**	Sends the signal that the mine is pressed, handled in main window.
		*	@param this Pointer to the mine itself.
		*	@return nothing
		*/
		void minePressed(FloatingMine*);	
	private:
		int counter_;
		int id_;
		bool readyToExplode_;
		bool doneExploding_;
};
#endif


