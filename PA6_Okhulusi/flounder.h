#ifndef FLOUNDER_H
#define FLOUNDER_H

#include "gameItem.h"
#include "player.h"
#include <cmath>

using namespace std;

/**	Flounder is a GameItem object that spawns at a random y location on the right side of the screen.  It implements
*	AI to home towards the player, giving the player 10 bonus points upon collision.
*	
*	@author Omar Khulusi
*/
class Flounder : public GameItem{

	public:
		/**	Constructor for Flounder.  Takes in an x and y location, along with a pixmap to set the image.
		*	Also takes a pointer to the player.
		*	@param x X location
		*	@param y Y Location
		*	@param pixmap Pointer to the pixmap containing flounder image	
		*	@param player Pointer to the player for AI
		*/
		Flounder(int x, int y, QPixmap *pixmap, Player *player);
		
		/**	Destructor for Flounder
		*/
		~Flounder();
		
		/**	Flounder swims towards the player's current position.  It does not adjust if the player moves.
		*	@return nothing
		*/
		void act();
		
		/**	Sets the gamespeed to react to.  Gamespeed is equal across all classes.
		*	@param gameSpeed Sets gamespeed_.
		*	@return nothing
		*/
		void setSpeed(int);
		
		/**	Determines whether or not flounder is moving.
		*	@return true if moving, false otherwise
		*/
		bool isMoving();
		
		/**	Returns the string Flounder so that the class type can be determined externally
		*	@return string "Flounder"
		*/
		string getType();
	
	private:
		int counter_;
		bool moving_;
		double newvy_;
		int yDistToMove_;
		Player *player_;
		
};
#endif
