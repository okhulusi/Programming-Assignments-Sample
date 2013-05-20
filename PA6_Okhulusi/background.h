#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "gameItem.h"
#include <QPixmap>

/**	The background class extends GameItem, but acts much differently from other child objects.  It is only meant
*	to set and scroll the background.  When the level increases any level past level 2, the screen will flash red for
*	a brief moment.
*	@author Omar Khulusi
*/
class Background : public GameItem{
	public:
	
	/**	Constructor for background.  Takes in an x and y location in addition to the background image in the form
	*	of a QPixmap.
	*	@param x X location of background
	*	@param y Y location of background
	*	@param pixmap Pointer to the QPixmap containing the background
	*/
	Background(int x, int y, QPixmap *pixmap);
	
	/**	Destructor for background
	*/
	~Background();
	
	/**	Sets scrolling speed equal to gamespeed
	*	@param gameSpeed
	*	@return nothing
	*/
	void setSpeed(int);
	
	/**	Simply scrolls the image with a horizontal velocity
	*	@return nothing
	*/
	void act();
	
	/**	Return the string of the object, "Background"
	*	@return string Background
	*/
	string getType();
	
	private:
};
#endif 
