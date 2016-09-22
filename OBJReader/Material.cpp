#include "Material.h"

Material::Material()
{
	name = "";
}

void Material::setKa(float* k)
{
	ka[0] = k[0];
	ka[1] = k[1];
	ka[2] = k[2];
}

void Material::setKd(float* k)
{
	kd[0] = k[0];
	kd[1] = k[1];
	kd[2] = k[2];
}

void Material::setKs(float* k)
{
	ks[0] = k[0];
	ks[1] = k[1];
	ks[2] = k[2];
}
