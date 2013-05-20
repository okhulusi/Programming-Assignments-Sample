
#ifndef CLAM_POWERUP_H
#define CLAM_POWERUP_H

#include "gameItem.h"
#include "player.h"
#include <QPixmap>
#include <cmath>

/**	The ClamPowerUp class gives the player an extra life upon collision.  It's moving pattern is design to be tricky
*	so that it may or may not move away from the user before swiftly crossing the screen, depending on game speed.
*	It is a rare spawn, chances being 1/50.
*	@author Omar Khulusi
*/
class ClamPowerUp : public GameItem {
	public:
		/**	Constructor for Clam.  Takes in an x and y location, along with a pixmap to set the image. It
		*	also takes in a pointer to the player for Artificial intelligence implementation.
		*	@param x X location
		*	@param y Y Location
		*	@param pixmap Pointer to the pixmap containing clam image
		*	@param player Pointer to the player for AI	
		*/
		ClamPowerUp(int x, int y, QPixmap *pixmap, Player *player);
		
		/**	Destructor for Clam Power Up
		*/
		~ClamPowerUp();
		
		/**	Moves quickly towards the player's location.  If the player catches it, he/she receives
		*	an extra life.
		*	@return nothing
		*/
		void act();
		
		/**	Sets the gamespeed to react to.  Gamespeed is equal across all classes.
		*	@param gameSpeed Sets gamespeed_.
		*	@return nothing
		*/
		void setSpeed(int gameSpeed);
		
		/**	Returns the string Clam so that the class type can be determined externally
		*	@return string "Clam"
		*/
		string getType();
		
	private:
		int counter_;
		int yDistToMove_;

		double newvy_;
		Player *player_;
};	
#endif

