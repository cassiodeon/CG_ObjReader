#include "OBJReader.h"

OBJReader::OBJReader() {

}

Mesh* OBJReader::createOBJ()
{
	Mesh *mesh = new Mesh();
	
	//Abre arquivo setado
	ifstream file(pathFile);
	
	char line[1024];
	string lineIdentifier;
	if (file.is_open())
	{
		//enquanto end of file for false continua
		while (!file.eof())
		{
			file.getline(line,512);
			stringstream streamLine(line);
			
			streamLine >> lineIdentifier;
			
			if (lineIdentifier == "v") { //Vertex
				Vertex *v = getVertex(streamLine);
				mesh->addVertex(v);
			}else if (lineIdentifier == "vt") { //TextureMapping
				//mesh->addTextureMapping(v);
				//Somente 2 coordenadas????
			}else if (lineIdentifier == "vn") { //Normal
				Vertex *v = getVertex(streamLine);
				mesh->addNormal(v);
			}else if (lineIdentifier == "g") { //Group
				//g = new Group(name)
				//mesh.addGroup
				//currentGroup = g
			}else if (lineIdentifier == "f") { //Face
				//f = new Face(...)
				//mesh.group[currentGroup].addFace(f);
			}
		}
		file.close();
	}

	return mesh;
}

Vertex* OBJReader::getVertex(stringstream &streamVertex) {
	
	int index = 0;
	float c[3];

	while (streamVertex.good() && index < 4)  //Verifica se a stream pode ser usada no io
	{
		string auxCoord;
		streamVertex >> auxCoord;
		
		c[index] = atof(auxCoord.c_str());
	}
	Vertex* v = new Vertex(c[0], c[1], c[2]);
	return v;
}