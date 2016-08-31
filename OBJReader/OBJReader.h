#include <iostream>
#include <fstream>
#include <sstream>
#include "Mesh.h"

using namespace std;

class OBJReader {
private:
	
public:
	string pathFile;
	OBJReader();
	Mesh* createOBJ();
};