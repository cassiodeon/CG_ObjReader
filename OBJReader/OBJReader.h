#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "Mesh.h"
#include "Material.h"

using namespace std;

class OBJReader {
private:
	Vertex* getVertex(stringstream &streamVertex);
	Face* OBJReader::getFace(stringstream &streamVertex);
	Group* OBJReader::getGroup(stringstream &streamVertex);
	
public:
	string path;
	OBJReader();
	Mesh* createOBJ(string fileName);
	map<string*, Material*> getMaterialLib(string fileNameMaterial);
};