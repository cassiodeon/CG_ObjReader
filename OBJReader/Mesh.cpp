#include "Mesh.h"

Mesh::Mesh() {

};

void Mesh::addVertex(Vertex* v) {
	allVertex.push_back(v);
}

void Mesh::addTextureMapping(TextureMapping * tm)
{
	allMappings.push_back(tm);
}

void Mesh::addNormal(Vertex * v)
{
	allNormals.push_back(v);
}

void Mesh::addGroup(Group * g)
{
	groups.push_back(g);
}
