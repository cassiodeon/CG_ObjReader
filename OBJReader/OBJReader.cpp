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
			//cout << lineIdentifier;

			if (lineIdentifier == "v") { //Vertex
				Vertex *v = getVertex(streamLine);
				mesh->addVertex(v);
			}else if (lineIdentifier == "vt") { //TextureMapping
				//v = new Vertex(x, y, z)
				//mesh.addTextureMapping
			}else if (lineIdentifier == "vn") { //Normal
				//v = new Vertex(x, y, z)
				//mesh.addNormal
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
		cout << "--------------" << endl;
		cout << "--------------" << endl;
		for (int i = 0; i < mesh->getAllVertex().size(); i++)
		{
			//for (int j = 0; j < (sizeof(mesh->getAllVertex()[i]->coord) / sizeof(*mesh->getAllVertex()[i]->coord)); i++)
			//{
			//	cout << mesh->getAllVertex()[i]->coord[j] << " | ";
			//}
			//cout << i << endl;
			//cout << mesh->getAllVertex()[i]->coord[0] << " | ";
			//cout << mesh->getAllVertex()[i]->coord[1] << " | ";
			//cout <<  mesh->getAllVertex()[i]->coord[2] << " | ";
			//cout << endl;
		}
	}

	return mesh;
}

Vertex* OBJReader::getVertex(stringstream &streamVertex) {
	
	int index = 0;
	float c[3];

	while (streamVertex.good() && index < 4)  //Verifica se a stream pode ser usada no io
	{
		int coord;
		string auxCoord;
		streamVertex >> auxCoord;
		c[index] = atof(auxCoord.c_str());
	}
	//cout << endl;
	//cout << c[0] << " | ";
	//cout << c[1] << " | ";
	//cout << c[2] << " | ";
	//cout << endl;
	Vertex* v = new Vertex(c[0], c[1], c[2]);
	return v;
}