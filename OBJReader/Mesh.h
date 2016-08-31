#include "Group.h"
#include "TextureMapping.h"

using namespace std;

class Mesh {
private:
	vector<Vertex*> allVertex;
	vector<Vertex*> allNormals;
	vector<TextureMapping*> allMappings;
	vector<Group*> groups;

public:
	Mesh();
	void addVertex(Vertex* v);
	vector<Vertex*> getAllVertex();
};
