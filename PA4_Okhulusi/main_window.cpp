#include <QtGui/QApplication>
#include "main_window.h"

MainWindow::MainWindow()  {
  boardExists = false;
  
  timer = new QTimer();
  timer->setInterval(10);
  
  scene = new QGraphicsScene();
  view = new QGraphicsView(scene);
  layout = new QGridLayout();
  style = new QPlastiqueStyle();
  
  fieldLayout = new QVBoxLayout();
  fieldLayoutBox = new QGroupBox();
  
  errorBoxLayout = new QVBoxLayout();
  errorBoxLayoutBox = new QGroupBox();
  
  cheatLayout = new QVBoxLayout();
  cheatLayoutBox = new QGroupBox();
    
  qApp->setStyle(style);

  view->setFixedSize( WINDOW_MAX_X*2, WINDOW_MAX_Y*2 );
  view->setWindowTitle("Game Time");

  //Start Button
  startButton = new QPushButton();
  startButton->setText("Start Game");
  connect(startButton, SIGNAL(clicked()), this, SLOT(handleStartButton()));
  startButton->show();
  fieldLayout->addWidget(startButton); 
    
  //Quit Button
  quitButton = new QPushButton();
  quitButton->setText("Quit Game");
  connect(quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
  quitButton->show();
  layout->addWidget(quitButton, 60, 10, 5, 50);
  
  //Size Field
  sizeLabel = new QLabel("Board Size:");
  fieldLayout->addWidget(sizeLabel);
  sizeField = new QLineEdit();
  fieldLayout->addWidget(sizeField);
  
  //Initial Moves Field
  initMovesLabel = new QLabel("Initial Number of Moves:");
  fieldLayout->addWidget(initMovesLabel);
  initMovesField = new QLineEdit();
  fieldLayout->addWidget(initMovesField);
  
  //Seed Field
  seedLabel = new QLabel("Seed:");
  fieldLayout->addWidget(seedLabel);
  seedField = new QLineEdit();
  fieldLayout->addWidget(seedField);
  
  //Error Box
  errorBox = new QTextEdit();
  errorBox->setReadOnly(true);
  errorBoxLayout->addWidget(errorBox);
  
  
//CHEAT BOX 

  //Cheat Button
  cheatButton = new QPushButton();
  cheatButton->setText("Cheat");
  connect(cheatButton, SIGNAL(clicked()), this, SLOT(handleCheatButton()));
  cheatButton->show(); 
  cheatLayout->addWidget(cheatButton);
  
  //Manhattan Heuristic Button
  mhButton = new QRadioButton("Manhattan Heuristic");
  cheatLayout->addWidget(mhButton); 
  
  //Out Of Place Heuristic Button
  oophButton = new QRadioButton("Out of Place Heuristic");
  cheatLayout->addWidget(oophButton); 
  
  //Solution Moves Display Box
  solutionMovesDisplayBox = new QTextEdit();
  cheatLayout->addWidget(solutionMovesDisplayBox);


//BOARD AND GENERAL VIEW BOX
  layout->addWidget(view, 0, 10, 50, 50);

//SET BOX NAMES
   fieldLayoutBox->setTitle("Start Game");
   errorBoxLayoutBox->setTitle("Console");
   cheatLayoutBox->setTitle("Cheat");
   
//LINKING GROUP BOXES TO LAYOUTS
   fieldLayoutBox->setLayout(fieldLayout);
   errorBoxLayoutBox->setLayout(errorBoxLayout);
   cheatLayoutBox->setLayout(cheatLayout);
 
//LINKING LAYOUTS TO MASTER LAYOUT  
   layout->addWidget(fieldLayoutBox, 0,0, 20, 5);
   layout->addWidget(errorBoxLayoutBox, 50, 10, 10, 50);
   layout->addWidget(cheatLayoutBox, 25, 0, 40, 5); 
   setLayout(layout);
    
}

MainWindow:: ~MainWindow() {}		//Destructor, memory cleanup no longer needed

void MainWindow::handleStartButton(){
	errorBox->clear();
	if(boardExists){
		delete b_;

		for(int i = 0; i < size; i++){
			delete guiTiles_[i];
		}
		delete [] guiTiles_;
		errorBox->clear();
		solutionMovesDisplayBox->clear();
		boardExists = false;
	}
	bool error = false;
	bool NoError1 = true;
	bool NoError2 = true;
	bool NoError3 = true;
						
	size = sizeField->text().toInt(&NoError1, 10);
	initMoves = initMovesField->text().toInt(&NoError2, 10);
	seed = seedField->text().toInt(&NoError3, 10);
	
	if(NoError1 == false){
		error = true;
		errorBox->append("Error: Invalid size.");
	}
	if(NoError2 == false){
		error = true;
		errorBox->append("Error: Invalid Number of Initial Moves.");
	}
	if(NoError3 == false){
		error = true;
		errorBox->append("Error: Invalid Seed.");
	}
	if(error == true) { return; }
	
	if(sizeField->text() == ""){
		error = true;
		errorBox->append("Error: Please input a board size");
	} else if(!(size == 9 || size == 16)){
		error = true;
		errorBox->append("Error: Size of board must be 9 (3x3) or 16 (4x4)");
	} else {}
	
	if(initMovesField->text() == ""){
		error = true;
		errorBox->append("Error: Please input a number of Initial Moves"); 
	} else if(initMoves < 0){
		error = true;
		errorBox->append("Error: Number of Initial Moves must be a positive integer");
	} else{}

	if(seedField->text() == ""){
		error = true;
		errorBox->append("Error: Please input a seed value");
	} else {}
	 
	if(error == false){
		b_ = new Board(size, initMoves, seed);
		guiTiles_ = new GUITile*[size];
		for(int i = 0; i < (int)sqrt(size); i++){
			for(int j = 0; j < (int)sqrt(size); j++){
				GUITile *guiTile = new GUITile(b_->getTiles()[j+i*(int)sqrt(size)], j*50, i*50);
				guiTiles_[j + i*(int)sqrt(size)] = guiTile;
				connect(guiTiles_[j + i*(int)sqrt(size)], SIGNAL(signal(int)), this, SLOT(mainWindowMoveTile(int)));
				scene->addItem(guiTiles_[j + i*(int)sqrt(size)]);
			}
		}
		view->show();
		boardExists = true;
	} else{ }
}

void MainWindow::handleCheatButton(){
	if(!boardExists){
		errorBox->append("Error: The game hasn't been started yet, so you can't cheat!");
		return;
	}
	solver_ = new PuzzleSolver(*b_);
	
	if(mhButton->isChecked()){
		ph_ = new ManhattanHeuristic();
	} else if(oophButton->isChecked()) {
		ph_ = new OutOfPlaceHeuristic();
	} else{
		errorBox->append("Please select a Heuristic if you wish to cheat. ");
		return;
	}
	
	ph_->compute(b_->getTiles(), b_->getSize());
	solver_->run(ph_); 
	
	solutionMovesDisplayBox->append("Try this sequence:");
  	for(int i = (solver_->getSolutionList()).size()-1; i >= 0; i--){	//Prints out backwards because solution pushed back
  		QString s;
  		s.setNum(solver_->getSolutionList()[i]);
  		solutionMovesDisplayBox->append(s);
  	}
	//display cheat sequence to box
}

void MainWindow::mainWindowMoveTile(int tileVal){
	if(timer->isActive()){return;}
	
	int tileLoc = -1;
	int blankLoc = -1;
	if((!(b_->solved())) && b_->move(tileVal)){
		for(int i = 0; i < b_->getSize(); i++){
			if(guiTiles_[i]->getVal() == tileVal){
				tileLoc = i;
				break;
			}
		}
		
		for(int i = 0; i < b_->getSize(); i++){
			if(guiTiles_[i]->getVal() == 0){
				blankLoc = i;
				break;
			}
		}
		
		guiTiles_[tileLoc]->setTarget(guiTiles_[blankLoc]->getX(), guiTiles_[blankLoc]->getY());
		
		connect(timer, SIGNAL(timeout()), guiTiles_[tileLoc], SLOT(moveTileAnimate()));
		connect(guiTiles_[tileLoc], SIGNAL(doneMoving(int)), this, SLOT(timerStop(int)));
		//visually swap
		timer->start();
		
		int tempx = guiTiles_[tileLoc]->getX();
		int tempy = guiTiles_[tileLoc]->getY();
		

		//guiTiles_[tileLoc]->moveTile(guiTiles_[blankLoc]->getX(), guiTiles_[blankLoc]->getY());
		guiTiles_[blankLoc]->moveTile(tempx, tempy);
		
		
		GUITile *temp = guiTiles_[blankLoc];
		guiTiles_[blankLoc] = guiTiles_[tileLoc];
		guiTiles_[tileLoc] = temp;
	}
	
	if(b_->solved()){
		errorBox->setText("YOU WIN!!!");
		solutionMovesDisplayBox->clear();
	}
}

void MainWindow::timerStop(int val){
	timer->stop();
	for(int i = 0; i < b_->getSize(); i++){
		if(guiTiles_[i]->getVal() == val){
			disconnect(timer, SIGNAL(timeout()), guiTiles_[i], SLOT(moveTileAnimate()));
			break;
		}
	}
}
