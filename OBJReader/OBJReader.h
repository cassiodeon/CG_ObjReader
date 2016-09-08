#include <iostream>
#include <fstream>
#include <sstream>
#include "Mesh.h"

using namespace std;

class OBJReader {
private:
	Vertex* getVertex(stringstream &streamVertex);
	Face* OBJReader::getFace(stringstream &streamVertex);
	Group* OBJReader::getGroup(stringstream &streamVertex);

public:
	string pathFile;
	OBJReader();
	Mesh* createOBJ();
};