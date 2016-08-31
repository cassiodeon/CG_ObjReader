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
			cout << lineIdentifier << endl;

			if (lineIdentifier == "v") { //Vertex
				string aux;
				streamLine >> aux;
				cout << aux ;
				//Setar o vertice no allVertex
				//v = new Vertex(x, y, z)
				//mesh.addVertex(v);
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
	}

	return mesh;
}
