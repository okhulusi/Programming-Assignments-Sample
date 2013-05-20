#ifndef BUBBLE_POWERUP_H
#define BUBBLE_POWERUP_H

#include "gameItem.h"
#include <QPixmap>

/**	The BubblePowerUp class grants the player ten seconds of invulnerability with colliding with the player.
*	It lasts ten seconds, but if the players moves too quickly it will fly away behind him/her.
*	Its image will stick around the player otherwise.  Its moving pattern is an oscillating pattern in the vertical
*	direction and a quick horizontal velocity.  It is a rare spawn, chances being 1/50.
*	@author Omar Khulusi
*/
class BubblePowerUp : public GameItem {
	public:
		/**	Constructor for Bubble.  Takes in an x and y location, along with a pixmap to set the image.
		*	@param x X location
		*	@param y Y Location
		*	@param pixmap Pointer to the pixmap containing bubble image	
		*/
		BubblePowerUp(int x, int y, QPixmap *pixmap);
		
		/**	Destructor for Bubble Power Up
		*/
		~BubblePowerUp();
		
		/**	The bubble has the most difficult moving pattern to read.
		*	It oscillates in the vertical direction, so it is hard to catch.
		*	If the player collides with the bubble, he/she receives invulnerability for 10 seconds.
		*	However, if the player moves too fast using W and S, the bubble is designed to "fall off".
		*	@return nothing
		*/
		void act();
		
		/**	Sets the gamespeed to react to.  Gamespeed is equal across all classes.
		*	@param gameSpeed Sets gamespeed_.
		*	@return nothing
		*/
		void setSpeed(int gameSpeed);
		
		/**	Returns the string Bubble so that the class type can be determined externally
		*	@return string "Bubble"
		*/
		string getType();
		
	private:
		bool velocitySwitch_;
		int counter_;
};
#endif

