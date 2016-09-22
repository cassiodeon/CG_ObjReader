#include "Includes.h"
#include "Group.h"
#include "TextureMapping.h"

using namespace std;

class Mesh {
private:
	
public:
	Mesh();
	vector<Vertex*> allVertex;
	vector<Vertex*> allNormals;
	vector<TextureMapping*> allMappings;
	vector<Group*> groups;
	string fileNameMaterial;

	void addVertex(Vertex* v);
	void addTextureMapping(TextureMapping* tm);
	void addNormal(Vertex* v);
	void addGroup(Group* g);

};
