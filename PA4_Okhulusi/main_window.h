#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QTimeLine>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QRadioButton>
#include <QListView>
#include <QtGui/QApplication>
#include <QGridLayout>
#include <QPlastiqueStyle>
#include <QStyle>
#include <QBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QPointF>
#include <QRectF>
#include <QListWidget>
#include <cmath>
#include "board.h"
#include "gui_tile.h"
#include "puzzle_solver.h"
#include "puzzle_heur.h"

#define WINDOW_MAX_X 250
#define WINDOW_MAX_Y 250

/** The MainWindow class is the basis for the visualization of the board.  It has three major components: the board
*   initialization/start section, the cheat-implementation section, and the actual board, composed of GUITiles.  These
*   three components have other components in them, but overall the purpose of the class is to display the main window 
*   that a user can play the puzzle game on. 
*/
class MainWindow : public QWidget {
	Q_OBJECT
	
public:
	/** Constructor for the main window.  This is where all of the Q items are instantiated, all of them being
	*   dynamically allocated pointers.  Furthermore, logic of buttons, along with most signals and slots,
	*    are connected here.
	*/
	explicit MainWindow();
	
	/** Destructor for MainWindow.  Memory cleanup not required for this assignment
	*/
	~MainWindow();
	
public slots:
	/** Handles the case where a user clicks the start button.  This will print out an error in the console
	*   (errorBox) if any of the three fields below it are invalid or nonexistant, and will otherwise initialize
	*   a board and array of GUITile pointers with the given data.  Also, if a board is already on the screen
	*   it will delete that board and make a new one, provided valid data.
	*/
	void handleStartButton();
	
	/** Handles the case where a user clicks the cheat button.  This will print out an error to the console
	*   (errorBox) if a Heuristic is not selected, and will otherwise display a cheat in the box 
	*   (solutionMovesDisplayBox) below it.
	*/
	void handleCheatButton();
	
	/** Handles all of the pieces of the moving of a tile.  It essentially connects moving a tile visually, moving
	*   a tile through animation, and keeping track of the tile swap in the model (in the board).
	*   @param tileVal Value of the tile to be moved
	*   @return nothing
	*/
	void mainWindowMoveTile(int tileVal);
	
	/** Handles the completion of the animation of a moving tile.  It will stop the timer and disconnect the timer
	*   from the moved GUITile so that it can reconnect to the next moving tile.
	*   @param val Value of the tile to disconnect
	*   @return nothing
	*/
	void timerStop(int val);
	
private:
	int size;	/** Parameters for Starting Game */
	int initMoves;
	int seed;
	
	bool boardExists; /** Pieces of the Model */
	bool isMoving;
	Board *b_;
	PuzzleSolver *solver_;
	PuzzleHeuristic *ph_;
	GUITile** guiTiles_;
	
	QGraphicsScene *scene;	/** Widgets of the main view */
	QGraphicsView *view;
	QGridLayout *layout;
	QPlastiqueStyle *style;
	
	QVBoxLayout *fieldLayout;	/** Field Layout and the box surrounding it */
	QGroupBox *fieldLayoutBox;
	
	QVBoxLayout *errorBoxLayout;	/** Error Box Layout and the box surrounding it */
	QGroupBox *errorBoxLayoutBox;
	
	QVBoxLayout *cheatLayout;	/** Cheat Box Layout and the box surrounding it */
	QGroupBox *cheatLayoutBox;
	
	QTimer *timer;			/** Timer for animation */
	
	QTextEdit *solutionMovesDisplayBox;	/** Solution moves displayed in this box */
	
	QLineEdit *sizeField;		/** Fields that take in pieces needed to populate model data, and the console */
	QLineEdit *initMovesField;
	QLineEdit *seedField;
	QTextEdit *errorBox;
	
	QPushButton *startButton;	/** Start, Quit, And Cheat buttons */
	QPushButton *quitButton;
	QPushButton *cheatButton;
	
	QRadioButton *mhButton;	/** Heuristic buttons. No heuristic should be set by default */
	QRadioButton *oophButton;
	
	QLabel *sizeLabel;		/** Labels for data member input fields */
	QLabel *initMovesLabel;
	QLabel *seedLabel;	
};
#endif
