
#ifndef PLAYER_H
#define PLAYER_H

#include "gameItem.h"
#include <QtGui>
#include <QKeyEvent>

using namespace std;

/** This is the player class. The player can be controlled using the W and S keys to go up and down, respectively.
*    Also, the player can click floating mines to destroy them.  The objective of the game is to keep the player alive
*	as long as possible.  Only one player object is made.
*	@author Omar Khulusi
*/
class Player : public GameItem{
	Q_OBJECT
	public:
		/**	Constructor for Player.
		*	@param x X location
		*	@param y Y location
		*	@param pixmap Pointer to Pixmap of the player image
		*/
		Player(int x, int y, QPixmap *pixmap);
		
		/**	Destructor for player
		*/
		~Player();
		
		/**	Simply animates the player and checks to see if she is alive/invincible/able to move.
		*	@return nothing
		*/
		void act();
		
		/**	Sets the gamespeed.  Gamespeed is equal in all classes
		*	@param gameSpeed
		*	@return nothing
		*/
		void setSpeed(int);
		
		/**	Returns the number of lives of the player.
		*	@return int value lives_;
		*/
		int getLives();
		
		/**	Returns the type "Player" in the form of a string
		*	@return string "Player"
		*/
		string getType();
		
		/**	Adds a life to the player. Only called by when a clam collides with player.
		*	@return nothing
		*/
		void addLife();
		
		/**	Subtracts a life from the player
		*	@return nothing
		*/
		void loseLife();
		
		/** Makes the player flash when she loses a life so the user knows that a life is lost.
		*	@param didLoseLife Bool to check if they did actually lose a life
		*	@return nothing
		*/
		void lostLifeAnimation(bool didLoseLife);
		
		/**	Returns whether or not lilla lost a life recently. Used for the 1 second invincibility after
		*	a life is lost.
		*	@return true if a life was lost, false otherwise
		*/
		bool getLostLife();
		
		/**	Returns whether or not lilla is invincible.  Used in collision checking.
		*	@return true if invincible, false otherwise
		*/
		bool isInvincible();
		
		/**	Starts lilla's invincibility period
		*	@return nothing
		*/
		void startInvincibility();
		
		/**	Returns whether or not Lilla is dead.
		*	@return true is lives_ is 0, false otherwise
		*/
		bool isDead();
		
		/*	Tracks invicibility from a bubble, which lasts much longer.
		*	@return nothing
		*/
		void bubbleTime();
	
	/**	Tracks a key press.  Used to move the character.
	*	@param e Event where a key is pressed
	*	@return nothing
	*/	
	void keyPressEvent(QKeyEvent *e);
	
	/**	Tracks a key release.
	*	@param e Even where a key is released
	*	@return nothing
	*/
	void keyReleaseEvent(QKeyEvent *e);
	
	signals:
		/** Emits a signal that the bubble invincibility period is over
		*	@return nothing
		*/
		void bubbleTimeOver();
		
	public slots:
		/** Stops invincibility.
		*	@return nothing
		*/
		void stopInvincibility();
	
	private:
		int counter_;
		int imageNum_;
		int gameSpeed_;
		
		int lives_;
		bool invincible_;
		bool bubbleInvincibility_;
		bool lostLife_;
		
};
#endif
