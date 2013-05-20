
#ifndef SHARK_H
#define SHARK_H

#include "gameItem.h"

using namespace std;

/**	The Shark is a GameItem object that spawns at a random y location on the right side of the screen,
*	 waits three seconds, and then charges towards the left.  If it hits the mermaid, she loses a life.
*	@author Omar Khulusi
*/
class Shark : public GameItem{

	public:
		/**	Constructor for Shark.  Takes in an x and y location, along with a pixmap to set the image.
		*	@param x X location
		*	@param y Y Location
		*	@param pixmap Pointer to the pixmap containing shark image	
		*/
		Shark(int x, int y, QPixmap *pixmap);
		
		/**	Destructor for Shark
		*/
		~Shark();
		
		/**	Shark waits three seconds and then charges towards the right with a specific velocity that
		*	increases with faster game speed.  Also, shark animates with images if it is charging.
		*	@return nothing
		*/
		void act();
		
		/**	Sets the gamespeed to react to.  Gamespeed is equal across all classes.
		*	@param gameSpeed Sets gamespeed_.
		*	@return nothing
		*/
		void setSpeed(int);
		
		/**	Determines whether or not the shark is moving for animation to start.
		*	@return true if moving, false otherwise
		*/
		bool isMoving();
		
		/**	Returns the string Shark so that the class type can be determined externally
		*	@return string "Shark"
		*/
		string getType();
	
	private:
		int counter_;
		bool moving_;
		
};
#endif

