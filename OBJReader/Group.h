#include "Face.h"

using namespace std;

class Group
{
private:
	
public:
	vector<Face*> groupFace;
	string name;

	Group();
	Group(string name);
};
