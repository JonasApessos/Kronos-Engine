#pragma once

#include <vector>

#include "Texture.h"
#include "Shader.h"

using std::vector;

/** @class MaterialBase
*   @brief base class for material objects*/
class MaterialBase
{
public:
    MaterialBase();

    virtual inline void SetShader(Shader* InShader) noexcept = 0;
    virtual inline void SetTextureList(vector<Texture> const& InTextureList) noexcept = 0;

    virtual inline void AddTexture(Texture const& InTexture) noexcept = 0;

    virtual inline void ClearTextureList() noexcept = 0;

    virtual inline Shader* GetShader() const noexcept = 0;
    virtual inline vector<Texture> GetTextureList() const noexcept = 0;

    virtual void Draw() = 0;


protected:
    Shader* rShader;
    vector<Texture> rTextureList;

private:

};

/** @class Material
*   @brief Material object for rednering on geometry
*	@todo Logic for different types of textures (albedo, specular, etc.)
*	@todo Handle shader code by combining the shader with textures*/
class Material : MaterialBase
{
    Material();

    inline void SetShader(Shader* InShader) noexcept;
    inline void SetTextureList(vector<Texture> const& InTextureList) noexcept;

    inline void AddTexture(Texture const& InTexture) noexcept;

    inline void ClearTextureList() noexcept;

    inline Shader* GetShader() const noexcept;
    inline vector<Texture> GetTextureList() const noexcept;

    void Draw();

};


inline void Material::SetShader(Shader* InShader) noexcept {rShader = InShader;}
inline void Material::SetTextureList(vector<Texture> const& InTextureList) noexcept {rTextureList = InTextureList;}

inline void Material::AddTexture(Texture const& InTexture) noexcept {rTextureList.push_back(InTexture);}

inline void Material::ClearTextureList() noexcept {rTextureList.clear();}

inline Shader* Material::GetShader() const noexcept {return rShader;}
inline vector<Texture> Material::GetTextureList() const noexcept {return rTextureList;}
