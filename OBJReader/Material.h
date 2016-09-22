#include "Includes.h"

using namespace std;

class Material {
private:

public:
	Material();
	string name;
	float ka[3];
	float kd[3];
	float ks[3];
	float ns;
	void setKa(float* k);
	void setKd(float* k);
	void setKs(float* k);

	int ID;
};
