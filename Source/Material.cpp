#include "Material.h"

MaterialBase::MaterialBase()
{

}

Material::Material()
{

}

void Material::Draw()
{
    rShader->Use();
}
