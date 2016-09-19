#define _CRT_SECURE_NO_WARNINGS
#include "OBJReader.h"

OBJReader::OBJReader() {

}

Mesh* OBJReader::createOBJ(string fileName)
{
	Mesh *mesh = new Mesh();
	
	//Abre arquivo setado
	ifstream file(path+fileName);
	
	char line[1024];
	string lineIdentifier;
	if (file.is_open())
	{
		//enquanto end of file for false continua
		Group* currentGroup;
		while (!file.eof())
		{
			file.getline(line,512);
			stringstream streamLine(line);
			lineIdentifier = "";
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
				Group* g = getGroup(streamLine);
				mesh->addGroup(g);
				currentGroup = g;
			}else if (lineIdentifier == "f") { //Face
				Face *f = getFace(streamLine);
				currentGroup->groupFace.push_back(f);
			}
			else if (lineIdentifier == "mtllib") { //Arquivo com as configurações do material
				//string nameMaterial = "";
				streamLine >> mesh->fileNameMaterial;
			}
		}
		file.close();
	}

	return mesh;
}

map<string*, Material*> OBJReader::getMaterialLib(string fileNameMaterial)
{
	map<string*, Material*> matLib;
	ifstream file(path + fileNameMaterial);

	char line[1024];
	string lineIdentifier;
	if (file.is_open()) {
		Material* currentMat = new Material();
		while (!file.eof())
		{
			file.getline(line, 512);
			stringstream streamLine(line);
			lineIdentifier = "";
			streamLine >> lineIdentifier;

			if (lineIdentifier == "newmtl") { //Nome
				Material* m = new Material();
				streamLine >> m->name;
				//REVISAR!!
				if (currentMat != nullptr) {
					matLib[&m->name] = currentMat;
				}
				
				currentMat = m;
				
			}
			else if (lineIdentifier == "Kd") {
				//pegar as 3 informações
				//currentMat->kd;
			}
			else if (lineIdentifier == "Ka") {
				//pegar as 3 informações
				//currentMat->ka;
			}
			else if (lineIdentifier == "Ks") {
				//pegar as 3 informações
				//currentMat->ks;
			}
			else if (lineIdentifier == "Ns") {
				//pegar 1 informação
				//currentMat->Ns;
			}
//map_Kd??????
		}
	}
	return matLib;
}

Vertex* OBJReader::getVertex(stringstream &streamVertex) {
	
	int index = 0;
	float c[3];

	while (streamVertex.good() && index < 4)  //Verifica se a stream pode ser usada no io
	{
		string auxCoord;
		streamVertex >> auxCoord;
		
		c[index] = atof(auxCoord.c_str());
		index++;
	}
	Vertex* v = new Vertex(c[0], c[1], c[2]);
	return v;
}

Face* OBJReader::getFace(stringstream &streamVertex) {
	/**
		Somente vértices :
			f v1 v2 v3
		Completo :
			f v1/t1/n1 v2/t2/n2 v3/t3/n3
		Vértices e normais :
			f v1//n1 v2//n2 v3//n3 
		Vértices e texturas :
			f v1/t1 v2/t2 v3/t3
	*/
	
	Face* f = new Face();
	while (streamVertex.good())  //Verifica se a stream pode ser usada no io
	{
		//Obtem as informações de um vertice
		string auxCoord = "";
		streamVertex >> auxCoord;
		
		string infoIndex = "";
		//Array que irá conter as as informações do vertice (indice do vertice [0], indice da normal [1] e indice da textura [2])
		int indexs[3];
		indexs[0] = indexs[1] = indexs[2] = -1;

		int currentIndex = 0;
		for (int i = 0; i < auxCoord.size(); i++)
		{
			if (auxCoord[i] == '/') {
				if (infoIndex != "") {
					//atribui o indice da informação
					indexs[currentIndex] = atoi(infoIndex.c_str()) - 1; //Index do obj começa em 1
				}
				
				//Vai para a proxima informação do vertice (limpa as variáveis)
				currentIndex++;
				infoIndex = "";
			}
			else {
				infoIndex += auxCoord[i];
			}
		}
		
		//Pega ultima informação ou caso nao tenha '/'
		if (infoIndex != "") {
			indexs[currentIndex] = atoi(infoIndex.c_str()) - 1; //Index do obj começa em 1
		}
		
		//Adiciona o index do vertice
		if (indexs[0] > -1) {
			f->vertex.push_back(indexs[0]);
		}

		///////// PODE NÃO TER NORMAL OU NÃO TER A TEXTURA!! TRATAR ISSO!!!!
		//Adiciona o index da textura
		if (indexs[1] > -1 ) {
			f->mappings.push_back(indexs[1]);
		}

		//Adiciona o index da normal
		if (indexs[2] > -1) {
			f->normals.push_back(indexs[2]);
		}
	}

	return f;
}

Group * OBJReader::getGroup(stringstream &streamVertex)
{
	Group* g = new Group(streamVertex.str());
	return g;
}
