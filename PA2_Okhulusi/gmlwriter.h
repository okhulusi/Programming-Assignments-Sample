#ifndef GML_WRITER_H
#define GML_WRITER_H

#include <iostream>
#include <string>
#include <vector>
#include "user.h"
#include "bcuser.h"

using namespace std;

class GMLWriter{
	public:
		GMLWriter();
		~GMLWriter();
		void write(char *oFilename, MyList<BCUser*> &list);	
		void write(char *oFilename, MyList<User*> &list);	
	private:
	
};

#endif
