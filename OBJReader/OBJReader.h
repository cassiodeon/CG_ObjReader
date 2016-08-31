#include <iostream>
#include <fstream>
#include <sstream>
#include "Mesh.h"

using namespace std;

class OBJReader {
private:
	Vertex* getVertex(stringstream &streamVertex);

public:
	string pathFile;
	OBJReader();
	Mesh* createOBJ();
};