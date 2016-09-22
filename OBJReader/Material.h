#pragma once
using namespace std;

class Material {
private:

public:
	Material();
	char* name;
	float ka[3];
	float kd[3];
	float ks[3];
	float ns;
	void setKa(float* k);
	void setKd(float* k);
	void setKs(float* k);
};
