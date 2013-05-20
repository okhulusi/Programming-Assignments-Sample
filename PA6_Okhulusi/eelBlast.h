
#ifndef BLAST_H
#define BLAST_H

#include "gameItem.h"

/** The Blast class is a game object that extends GameItem, serving as a projectile to come from the mouth of the BlastingEel,
*	another game object.  The Blast has two different graphics, and will make the player lose a life upon collision.
*	@author Omar Khulusi
*/
class Blast : public GameItem {

	public:
		/**	Constructor for Eel Blast.  Takes in an x and y location, along with a pixmap to set the image.
		*	@param x X location
		*	@param y Y Location
		*	@param pixmap Pointer to the pixmap containing projectile's image	
		*/
		Blast(int x, int y, QPixmap *pixmap);
		
		/**	Destructor for Eel Blast
		*/
		~Blast();
		
		/**	Serves as a projectile, firing across the screen as soon as it spawns.
		*	@return nothing
		*/
		void act();
		
		/**	Sets the gamespeed to react to.  Gamespeed is equal across all classes. Blasts do not vary with
		*	speed because framerate causes collision issues.  Instead, the blasting eel fires more blasts.
		*	@param gameSpeed Sets gamespeed_.
		*	@return nothing
		*/
		void setSpeed(int gameSpeed);
		
		/**	Returns the string Blast so that the class type can be determined externally
		*	@return string "Blast"
		*/
		string getType();
		
	private:
};
#endif

