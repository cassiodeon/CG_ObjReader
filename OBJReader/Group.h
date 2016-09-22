#include "Includes.h"
#include "Face.h"

using namespace std;

class Group
{
private:
	
public:
	vector<Face*> groupFace;
	string name;
	string nameMaterial;

	Group();
	Group(string name);
};
