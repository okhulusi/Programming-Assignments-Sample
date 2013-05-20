#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QtGui>
#include <vector>
#include "gameItem.h"
#include "shark.h"
#include "blastingEel.h"
#include "bubblePowerUp.h"
#include "clamPowerUp.h"
#include "floatingMine.h"
#include "background.h"
#include "player.h"
#include <QString>

/** The main window is the base class where everything connects.  It also keeps track of spawning, so it controls the view.
*	@author Omar Khulusi
*/
class MainWindow: public QWidget{
	Q_OBJECT

	public:
		/**	Constructor for MainWindow.  Most QPixmaps are initialized here, as 
		*	well as the buttons, view, and scene.
		*/
		explicit MainWindow();
		
		/**	Destructor for MainWindow.
		*/
		~MainWindow();
		
		/**	Scrolls the background such that it increases speed as the game gets harder, also flashing
		*	red for a second between levels.
		*	@return nothing
		*/
		void scrollBackground();
	protected:
		/**	Handles the key press event to move the player.
		*	@param e Key event where a key is pressed.
		*	@return nothing
		*/
		void keyPressEvent(QKeyEvent *e);
	
	public slots:
		/**	Handles the start of the game.  If the game is already started, the game will restart instead.
		*	@return nothing
		*/
		void handleStartButton();
		
		/**	Handles the timeout() of the timer.  This is where all the GameItem act() methods are called.
		*	@return nothing
		*/
		void handleTimer();
		
		/**	Handles the pause of a game.  If the game is paused, the player can't move.
		*	@return nothing
		*/
		void handlePauseButton();
		
		/**	Handles the firing of an eel blast.  It receives the x and y location of an eel to fire
		*	blasts from.
		*	@param x X location of eel to fire from
		*	@param y Y location of eel to fire from
		*	@return nothing
		*/
		void handleEel(int x, int y);
		
		/**	Deletes the bubble on the player
		*	@return nothing
		*/
		void deleteBubble();
		
		/**	Handles the exploding animation of a mine
		*	@param mine Pointer to mine being detonated.
		*	@return nothing
		*/
		void explode(FloatingMine *mine);
		
		/**	Handles basic gameplay.  Items are generated every certain interval of time, which becomes
		*	smaller as the difficulty increases.  The objects are weighted such as power ups and much less
		*	likely to spawn than sharks, eels, and mines.
		*	@return nothing
		*/
		void generateRandomItem();
	
	private:
		int mineLocation;
		int mineIDCount_;
		Player *player;
		QPixmap *playerPixmap;
		bool gameStarted;
		bool gamePaused;
		vector<GameItem*> *itemVec;
		QTimer *timer;
		int counter_;
		int gameSpeed_;
		bool scrollSwitch_;
		
		void incrementScore(int);
		void controlPlayer(Player *player);
		void controlShark(Shark *shark);
		void controlEel(BlastingEel *eel, int loc);
		void controlEelBlast(Blast *blast, int loc);
		void controlClam(ClamPowerUp *clam, int loc);
		void controlBubble(BubblePowerUp *bubble);
		void deleteMine(FloatingMine*);
		void displayGameOver();
		
		QLabel *usernameDisplay;
		int score_;
		QLabel *scoreLabel;
		QLabel *scoreBox;
		QLabel *levelLabel;
		QLabel *levelDisplay;
		
		QLabel *livesLabel;
		QLabel *numLivesLabel;
		
		QGridLayout *mainLayout;
		
		QPixmap *backgroundPixmap;
		Background *background;
		Background *background2;

		QVBoxLayout *startMenuLayout;
		QLabel *nameLabel;
		QLineEdit *nameField;
		QPushButton *startButton;
		QPushButton *quitButton;
		QPushButton *pauseButton;
		
		QPlastiqueStyle *style;
		QGraphicsScene *scene;
		QGraphicsView *view;

		QPixmap *sharkPixmap;
		QPixmap *bubblePixmap;
		QPixmap *minePixmap;
		QPixmap *clamPixmap;
		QPixmap *eelPixmap;
		
		QPixmap *playerPixmap4;
		QPixmap *playerPixmap3;
		QPixmap *playerPixmap2;
		QPixmap *playerPixmap1;
		
		QPixmap *sharkPixmap2;
		QPixmap *sharkPixmap3;
		QPixmap *sharkPixmap4;
		
		QPixmap *blastPixmap1;
		
		QPixmap *expPixmap10;
		QPixmap *expPixmap9;
		QPixmap *expPixmap8;
		QPixmap *expPixmap7;
		QPixmap *expPixmap6;
		QPixmap *expPixmap5;
		QPixmap *expPixmap4;
		QPixmap *expPixmap3;

};
#endif


