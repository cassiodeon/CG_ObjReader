#include "Mesh.h"

Mesh::Mesh() {

};

void Mesh::addVertex(Vertex* v) {
	allVertex.push_back(v);
}

vector<Vertex*> Mesh::getAllVertex()
{
	return allVertex;
}
