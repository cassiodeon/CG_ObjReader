#pragma once

using namespace std;

class Material {
private:
public:
	string name;
	float ka[3];
	float kd[3];
	float ks[3];
	float Ns;
};
