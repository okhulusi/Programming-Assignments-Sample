#include <QtGui/QApplication>
#include "mainwindow.h"
#include <iostream>
#include <cmath>

using namespace std;

MainWindow::~MainWindow(){

}

MainWindow::MainWindow(){
	srand(time(NULL));
	
	setWindowTitle("Under The Deep Blue Sea");
	itemVec = new vector<GameItem*>();
	counter_ = 0;
	gameSpeed_ = 1;
	score_ = 0;
	mineIDCount_ = 1;
	scoreBox = new QLabel();
	scoreLabel = new QLabel("SCORE:");
	levelLabel = new QLabel(QString::number(1));
	levelDisplay = new QLabel("Level:");
	scoreBox->setText(QString::number(score_));
	
	scrollSwitch_ = true;
	gameStarted = false;
	gamePaused = false;
	
	timer = new QTimer();
	timer->setInterval(1);
	connect(timer, SIGNAL(timeout()), this, SLOT(handleTimer()));
	
	mainLayout = new QGridLayout();
	scene = new QGraphicsScene(0, 0, 500, 500);
	view = new QGraphicsView(scene);
	
	mainLayout->addWidget(scoreLabel, 10, 50, 10, 10);
	mainLayout->addWidget(scoreBox, 15, 50, 10, 10);
	mainLayout->addWidget(levelDisplay, 30, 50, 10, 10);
	mainLayout->addWidget(levelLabel, 35, 50, 10, 10);
	
	numLivesLabel = new QLabel("Number of Lives: ");
	livesLabel = new QLabel();
	livesLabel->setText(QString::number(3));
	mainLayout->addWidget(numLivesLabel, 20, 50, 10, 10);
	mainLayout->addWidget(livesLabel, 25, 50, 10, 10);
	
	view->setFixedSize(505, 505);
	view->setWindowTitle("Under the Deep Blue Sea");
	
	style = new QPlastiqueStyle();
	qApp->setStyle(style);
	
	startMenuLayout = new QVBoxLayout();
	
	nameLabel = new QLabel("Enter Your Name Below!");
	startMenuLayout->addWidget(nameLabel);
	nameField = new QLineEdit();
	startMenuLayout->addWidget(nameField);
	usernameDisplay = new QLabel(nameField->text());
	startMenuLayout->addWidget(usernameDisplay);
	
	//Start Button
	startButton = new QPushButton();
	startButton->setText("Start Game");
	connect(startButton, SIGNAL(clicked()), this, SLOT(handleStartButton()));
	startMenuLayout->addWidget(startButton); 
	
	//Pause Button
	pauseButton = new QPushButton();
	pauseButton->setText("Pause Button");
	connect(pauseButton, SIGNAL(clicked()), this, SLOT(handlePauseButton()));
	startMenuLayout->addWidget(pauseButton);
	
	//Quit Button
	quitButton = new QPushButton();
	quitButton->setText("Quit Game");
	connect(quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
	startMenuLayout->addWidget(quitButton);
	
	//background
	backgroundPixmap = new QPixmap("./GamePictures/Background.png");
	*backgroundPixmap = backgroundPixmap->scaled(500, 500);
	background = new Background(0,0, backgroundPixmap);
	background2 = new Background(500, 0, backgroundPixmap);
	scene->addItem(background);
	scene->addItem(background2);
	scene->setBackgroundBrush(QBrush(Qt::red));
	itemVec->push_back(background);
	itemVec->push_back(background2);
	
	mainLayout->addLayout(startMenuLayout, 0, 50, 10, 10);
	setLayout(mainLayout);	
	mainLayout->addWidget(view, 0, 0, 50, 50);
	
	sharkPixmap = new QPixmap("./GamePictures/Shark/Shark3.png");
	bubblePixmap = new QPixmap("./GamePictures/Bubble/Bubble.png");
	*bubblePixmap = bubblePixmap->scaled(150, 150);
	minePixmap = new QPixmap("./GamePictures/Mine/Mine.png");
	*minePixmap = minePixmap->scaled(100, 100);
	clamPixmap = new QPixmap("./GamePictures/Clam/Clam.png");
	*clamPixmap = clamPixmap->scaled(50, 50);
	eelPixmap = new QPixmap("./GamePictures/Eel/Eel3.png");
	*eelPixmap = eelPixmap->scaled(200, 200);
	
	playerPixmap4 = new QPixmap("./GamePictures/Mermaid/Mermaid4.png");
	playerPixmap3 = new QPixmap("./GamePictures/Mermaid/Mermaid3.png");
	playerPixmap2 = new QPixmap("./GamePictures/Mermaid/Mermaid2.png");
	playerPixmap1 = new QPixmap("./GamePictures/Mermaid/Mermaid5.png");
	
	sharkPixmap2 = new QPixmap("./GamePictures/Shark/Shark5");
	sharkPixmap3 = new QPixmap("./GamePictures/Shark/Shark4");
	sharkPixmap4 = new QPixmap("./GamePictures/Shark/Shark3");
	
	blastPixmap1 = new QPixmap("./GamePictures/EelBlast/EelBlast1.png");
	*blastPixmap1 = blastPixmap1->scaled(50, 50);
	
	expPixmap10 = new QPixmap("./GamePictures/MineExplosion/Explosion10.png");
	expPixmap9 = new QPixmap("./GamePictures/MineExplosion/Explosion9.png");
	expPixmap8 = new QPixmap("./GamePictures/MineExplosion/Explosion8.png");
	expPixmap7 = new QPixmap("./GamePictures/MineExplosion/Explosion7.png");
	expPixmap6 = new QPixmap("./GamePictures/MineExplosion/Explosion6.png");
	expPixmap5 = new QPixmap("./GamePictures/MineExplosion/Explosion5.png");
	expPixmap4 = new QPixmap("./GamePictures/MineExplosion/Explosion4.png");
	expPixmap3 = new QPixmap("./GamePictures/MineExplosion/Explosion3.png");
	
	setFocus();
}

void MainWindow:: keyPressEvent(QKeyEvent *e){
	if(gameStarted && !gamePaused && !player->isDead()){
		player->keyPressEvent(e);
	}
}

void MainWindow:: generateRandomItem(){
	int random = rand()%50;
	int randomYSharkLoc = rand()%425 - 20;
	int randomYBubbleLoc = rand()%425 - 20;
	int randomYMineLoc = rand()%425 - 20;
	int randomYClamLoc = rand()%425 - 20;
	int randomYEelLoc = rand()%425 - 20;
	if(random <= 20){
		Shark *shark = new Shark(450, randomYSharkLoc, sharkPixmap);
		scene->addItem(shark);
		itemVec->push_back(shark);
	} else if(random == 21){
		BubblePowerUp *bubble = new BubblePowerUp(450, randomYBubbleLoc, bubblePixmap);
		scene->addItem(bubble);
		itemVec->push_back(bubble);
	} else if(random <= 36){
		FloatingMine *mine = new FloatingMine(450, randomYMineLoc, minePixmap);
		mine->setID(mineIDCount_);
		mineIDCount_++;
		scene->addItem(mine);
		itemVec->push_back(mine);
		mineLocation = itemVec->size()-1;
		connect(mine, SIGNAL(minePressed(FloatingMine*)), this, SLOT(explode(FloatingMine*)));
	} else if(random == 37){
		ClamPowerUp *clam = new ClamPowerUp(400, randomYClamLoc, clamPixmap);
		scene->addItem(clam);
		itemVec->push_back(clam); 
	} else if(random <= 49){
		BlastingEel *eel = new BlastingEel(425, randomYEelLoc, eelPixmap);
		connect(eel, SIGNAL(firing(int, int)), this, SLOT(handleEel(int, int)));
		scene->addItem(eel);
		itemVec->push_back(eel); 
	} else {}
}
void MainWindow:: handleStartButton(){
	if(!gameStarted){
		gamePaused = false;
		usernameDisplay->setText(nameField->text());
		nameField->setMaxLength(10);
		if(nameField->text() == ""){
			usernameDisplay->setText("Please Enter a Name.");
			return;
		} else{
			usernameDisplay->setText(nameField->text() + ", Have Fun!");
			timer->start();
	
			playerPixmap = new QPixmap("./GamePictures/Mermaid/Mermaid5.png");
			player = new Player(0,200,playerPixmap);
			connect(player, SIGNAL(bubbleTimeOver()), this, SLOT(deleteBubble()));
			scene->addItem(player);
			itemVec->push_back(player);
	
			for(int i = 0; i < 3; i++){
				generateRandomItem();
			}	
			gameStarted = true;
		}
	} else{
		gamePaused = false;
		score_ = 0;
		gameSpeed_ = 1;
		scoreBox->setText(QString::number(score_));
		livesLabel->setText(QString::number(3));
		levelLabel->setText(QString::number(1));
		numLivesLabel->setText("Number of Lives: ");
		scoreLabel->setText("Score: ");
		disconnect(player, SIGNAL(bubbleTimeOver()), this, SLOT(deleteBubble()));
		scene->removeItem(player);
		while(itemVec->size() > 2){
			GameItem *temp = itemVec->at(itemVec->size()-1);
			itemVec->pop_back();
			delete temp;
		}
		
		itemVec = new vector<GameItem*>;
		itemVec->push_back(background);
		itemVec->push_back(background2);
		
		if(nameField->text() == ""){
			usernameDisplay->setText("Please Enter a Name.");
			return;
		} else{
			usernameDisplay->setText(nameField->text() + ", Have Fun!");
			timer->start();
	
			playerPixmap = new QPixmap("./GamePictures/Mermaid/Mermaid5.png");
			player = new Player(0,200,playerPixmap);
			connect(player, SIGNAL(bubbleTimeOver()), this, SLOT(deleteBubble()));
			scene->addItem(player);
			itemVec->push_back(player);
	
			for(int i = 0; i < 3; i++){
				generateRandomItem();
			}	
			gameStarted = true;
		}
		
		//restart
	}
}

void MainWindow:: handlePauseButton(){
	if(gameStarted && !player->isDead()){
		if(timer->isActive()){
			timer->stop();
			gamePaused = true;
		} else {
			timer->start();
			gamePaused = false;
		}
	}
}

void MainWindow:: scrollBackground(){
	if(counter_%(500/gameSpeed_) == 0 && scrollSwitch_){
		background->setPos(500, 0);
		scrollSwitch_ = false;
	} else if(counter_%(500/gameSpeed_) == 0 && !scrollSwitch_){
		background2->setPos(500,0);
		scrollSwitch_ = true;
	}
}

void MainWindow:: incrementScore(int add){
	score_+=add;
	scoreBox->setText(QString::number(score_));
}

void MainWindow:: displayGameOver(){
	livesLabel->setText(QString::number(0));
	scoreLabel->setText("GAME OVER! Final Score: ");
}

void MainWindow:: handleTimer(){
	counter_++;
	scrollBackground();
	
	if(counter_%(3500/gameSpeed_) == 0){
		generateRandomItem();
	}
	if(counter_%1000 == 0 && gameSpeed_ >= 3 && counter_ > 90000){	//Becomes Impossible
		generateRandomItem();
		generateRandomItem();	
	}
	if(counter_%(1000/gameSpeed_) == 0){
		incrementScore(1);
	} 
	
	livesLabel->setText(QString::number(player->getLives()));
	
	
	if(counter_%20000 == 0){
		//cout << "GameSpeed: " << gameSpeed_ << endl;
		gameSpeed_++;
		levelLabel->setText(QString::number(gameSpeed_));
	}
	for(unsigned int i = 0; i < itemVec->size(); i++){
		string s = (*itemVec)[i]->getType();
		
		(*itemVec)[i]->setSpeed(gameSpeed_);
		(*itemVec)[i]->act();
		 
		if(s == "Player"){
			controlPlayer(dynamic_cast<Player*>((*itemVec)[i]));
		} else if(s == "Shark"){
			controlShark(dynamic_cast<Shark*>((*itemVec)[i]));
		} else if(s == "BlastingEel"){
			controlEel(dynamic_cast<BlastingEel*>((*itemVec)[i]), i);
		} else if (s == "Blast"){
			controlEelBlast(dynamic_cast<Blast*>((*itemVec)[i]), i);
		} else if(s == "Mine"){
			explode(dynamic_cast<FloatingMine*>((*itemVec)[i]));
		} else if(s == "Clam"){
			//controlClam(dynamic_cast<ClamPowerUp*>((*itemVec)[i]));
		} else if(s == "Bubble"){
			//controlBubble(dynamic_cast<BubblePowerUp*>((*itemVec)[i]));
		} else{}
		//cout << "Type: " << s << endl;
	}
}

void MainWindow:: controlPlayer(Player *player){
	if(!player->getLostLife()){
		if(counter_%2000 == 0){
			player->setPixmap(*playerPixmap4);
		} else if(counter_%1500 == 0){
			player->setPixmap(*playerPixmap3);
		} else if(counter_%1000 == 0){
			player->setPixmap(*playerPixmap2);
		} else if(counter_%500 == 0){
			player->setPixmap(*playerPixmap1);
		}
	}
		for(unsigned int i = 0; i < itemVec->size(); i++){
			if(player->isDead()){
			timer->stop();
			score_ = 0;
			displayGameOver();
		}
		
		if((*itemVec)[i]->getType() != "Background" && player->collidesWithItem((*itemVec)[i])){
			if((*itemVec)[i]->getType() == "Bubble"){
				controlBubble(dynamic_cast<BubblePowerUp*>((*itemVec)[i]));
			} else if((*itemVec)[i]->getType() == "Clam"){
				controlClam(dynamic_cast<ClamPowerUp*>((*itemVec)[i]), i);
			} else if((*itemVec)[i]->getType() == "Shark"){
				if(!player->isInvincible()){
					player->startInvincibility();
					player->loseLife();
				}
			} else if((*itemVec)[i]->getType() == "Blast"){
				if(!(player->isInvincible())){
					player->startInvincibility();
					player->loseLife();
				}
			} else if((*itemVec)[i]->getType() == "Clam"){
				player->addLife();
			} else if((*itemVec)[i]->getType() == "Mine"){
				if(!player->isInvincible()){
					player->loseLife();
					player->startInvincibility();
				}
			}	
		}
	}
	//cout << "Player Lives: " << player->getLives() << endl;
}

void MainWindow:: controlShark(Shark *shark){
	if(shark->isMoving()){
		if(counter_%300 == 0){
			shark->setPixmap(*sharkPixmap2);
		} else if(counter_%200 == 0){
			shark->setPixmap(*sharkPixmap3);
		} else if(counter_%100 == 0){
			shark->setPixmap(*sharkPixmap4);
		}
		
		if(shark->x() < -1000){
			unsigned int loc = 0;
			while(loc < itemVec->size()){
				if(itemVec->at(loc)->getType() == "Shark"){
					GameItem *temp = itemVec->at(loc);
					itemVec->erase(itemVec->begin() + loc);
					delete temp;
					return;
				}
				loc++;
			}
				
		}
	}
}

void MainWindow:: handleEel(int x, int y){
	Blast *blast1 = new Blast(x, y + 85, blastPixmap1);
	scene->addItem(blast1);
	itemVec->push_back(blast1); 
}
void MainWindow:: controlEel(BlastingEel *eel, int loc){
	if(eel->getCounter() == 5000){
		GameItem *temp = itemVec->at(loc);
		itemVec->erase(itemVec->begin() + loc);
		delete temp;
	}
}

void MainWindow:: controlEelBlast(Blast *blast, int loc){
	if(blast->x() < -1000){
		GameItem *temp = itemVec->at(loc);
		itemVec->erase(itemVec->begin() + loc);
		delete temp;
	}
}

void MainWindow:: explode(FloatingMine *mine){
	if(mine->isReadyToExplode()){
		if(counter_%400 == 0){
			mine->setPixmap(*expPixmap10);
			mine->setIsDoneExploding(true);
		} else if(counter_%350 == 0){
			mine->setPixmap(*expPixmap9);
		} else if(counter_%300 == 0){
			mine->setPixmap(*expPixmap8);
		} else if(counter_%250 == 0){
			mine->setPixmap(*expPixmap7);
		} else if(counter_%200 == 0){
			mine->setPixmap(*expPixmap6);
		} else if(counter_%150 == 0){
			mine->setPixmap(*expPixmap5);
		} else if(counter_%100 == 0){
			mine->setPixmap(*expPixmap4);
		} else if(counter_%50 == 0){
			mine->setPixmap(*expPixmap3);
		}
	}
	
	if(mine->isDoneExploding()){
		deleteMine(mine);
	}
}
void MainWindow:: deleteMine(FloatingMine *mine){
	score_+=(5*gameSpeed_);
	unsigned int loc = 0;
	while(loc < itemVec->size()){
		if(itemVec->at(loc)->getType() == "Mine" && mine->getID() == dynamic_cast<FloatingMine*>(itemVec->at(loc))->getID()){
			GameItem *temp = itemVec->at(loc);
			itemVec->erase(itemVec->begin() + loc);
			delete temp;
			return;
		}
		loc++;
	}
}

void MainWindow:: controlClam(ClamPowerUp *clam, int loc){
	clam = clam;
	player->addLife();
	GameItem *temp = itemVec->at(loc);
	itemVec->erase(itemVec->begin() + loc);
	delete temp;
}

void MainWindow:: controlBubble(BubblePowerUp *bubble){
	player->bubbleTime();
	bubble->setPos(player->x() - 30, player->y() - 30);
}

void MainWindow:: deleteBubble(){
	unsigned int loc = 0;
	while(loc < itemVec->size()){
		if(itemVec->at(loc)->getType() == "Bubble"){
			GameItem *temp = itemVec->at(loc);
			itemVec->erase(itemVec->begin() + loc);
			delete temp;
			return;
		}
		loc++;
	}
}
