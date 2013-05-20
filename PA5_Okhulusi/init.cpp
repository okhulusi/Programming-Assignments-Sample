#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{

	/** @mainpage Under the Deep Blue Sea, Side Scroller
	*
	*   @section purpose Purpose/Overview
	*	The Purpose of this Assignment is to learn how to make a basic yet interesting and fun
	*	video game using Qt in C++.  The purpose of this specific game is to survive as long as possible,
	*	given three lives to start.  Guide Lilla the mermaid for as long as you can through the deep blue sea.
	*
	*   @section requirements Requirements
	*	A mouse is recommended, but a trackpad can be used.  Furthermore, a keyboard is needed.
	*/
	
    QApplication a(argc, argv);
    MainWindow w;
	
    w.show();

    return a.exec();
}
