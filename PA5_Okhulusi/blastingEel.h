
#ifndef BLASTING_EEL_H
#define BLASTING_EEL_H

#include "gameItem.h"
#include "eelBlast.h"

/**	The Blasting Eel class is the only immobile object in the game.  It waits three seconds, and then emits signals
*	to fire eelBlasts.  The amount of shots increases once as the game reaches a gamespeed of 3.
*	@author Omar Khulusi
*/
class BlastingEel : public GameItem {
	Q_OBJECT
	public:
		/**	Constructor for Blasting Eel.  Takes in an x and y location, along with a pixmap to set the image.
		*	@param x X location
		*	@param y Y Location
		*	@param pixmap Pointer to the pixmap containing Eel image	
		*/
		BlastingEel(int x, int y, QPixmap *pixmap);
		
		/**	Destructor for Eel
		*/
		~BlastingEel();
		
		/**	Emits a signal to fire eelBlasts on certain intervals.  It fires more missile if gameSpeed reaches 3.
		*	This character is the only immobile character.
		*	@return nothing	
		*/
		void act();
		
		/**	Sets the gamespeed to react to.  Gamespeed is equal across all classes. Since eel is immobile,
		*	instead of getting faster, it fires 3 more eel blasts across the screen Once gameSpeed passes
		*	3.
		*	@param gameSpeed Sets gamespeed_.
		*	@return nothing
		*/
		void setSpeed(int gameSpeed);
		
		/**	Returns the string BlastingEel so that the class type can be determined externally
		*	@return string "BlastingEel"
		*/
		string getType();
		
		/**	Used to know when to fire blasts.
		*	@return int counter_, which increments by the timer in the main window.
		*/
		int getCounter();
	
	signals:
		/**	Signal sends location of eel, used when creating blasts to fire out of its mouth.
		*	@param	x X Coordinate of Eel
		*	@param	y Y Coordinate of Eel
		*	@return nothing
		*/
		void firing(int, int);
	private:
		int counter_;
		string type_;
};
#endif

