#include "Includes.h"
#include "Mesh.h"
#include "Material.h"

using namespace std;

class OBJReader {
private:
	Vertex* getVertex(stringstream &streamVertex);
	Face* OBJReader::getFace(stringstream &streamVertex);
	Group* OBJReader::getGroup(stringstream &streamVertex);
	float* OBJReader::getInfoMaterial(stringstream &streamVertex);

public:
	string path;
	OBJReader();
	Mesh* createOBJ(string fileName);
	map<string, Material*> getMaterialLib(string fileNameMaterial);
};