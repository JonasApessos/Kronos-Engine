#pragma once

#include <iostream>
#include <vector>

#include "glm/glm.hpp"

#include "Primitives.h"
#include "InputManager.h"

using std::string, std::hash, std::to_string, std::vector;

using glm::vec3, glm::mat4;

using KronosPrim::uint64;

class ObjectBase
{
public:
    string sName;

    ObjectBase();

    inline void SetName(string const& InsName);

    constexpr inline uint64 GetHash() const; //!< Get Hash ID of object, this will be changed in the future
    inline string GetName() const;

    bool SetParent(ObjectBase* InrBase);
    
    bool AddChild(ObjectBase* InrBase);
    bool AddChildren(vector<ObjectBase*>* InrBaseList);

protected:
    
private:

    static uint64 iID;
    const uint64 iHash;

    ObjectBase* rParent = nullptr;

    vector<ObjectBase*> rChildren;
};

inline void ObjectBase::SetName(string const& InsName) { sName=InsName; }

constexpr inline uint64 ObjectBase::GetHash() const { return iHash; }
inline string ObjectBase::GetName() const { return sName; }

class Object3D : public ObjectBase
{
public:
    Object3D();

    inline void SetPosition(vec3 const& InrPosition) noexcept;
    inline void SetPosition(float InfX, float InfY, float InfZ) noexcept;
    inline void SetPosition(float InfVal) noexcept;

    inline void SetRotation(vec3 const& InrRotation) noexcept;
    inline void SetRotation(float InfX, float InfY, float InfZ) noexcept;
    inline void SetRotation(float InfVal) noexcept;

    inline void SetScale(vec3 const& InrScale) noexcept;
    inline void SetScale(float InfX, float InfY, float InfZ) noexcept;
    inline void SetScale(float InfVal) noexcept;

    constexpr inline vec3 GetPosition() const noexcept;
    constexpr inline vec3 GetRotation() const noexcept;
    constexpr inline vec3 GetScale() const noexcept;

    void Test();

protected:

private:
    vec3 rPosition;
    vec3 rRotation;
    vec3 rScale;
    mat4 rBasis = mat4(1.0f);
};


inline void Object3D::SetPosition(vec3 const& InrPosition) noexcept { rPosition = InrPosition; }
inline void Object3D::SetPosition(float InfX, float InfY, float InfZ) noexcept 
{ 
    rPosition.x = InfX;
    rPosition.y = InfY;
    rPosition.z = InfZ;
}

inline void Object3D::SetPosition(float InfVal) noexcept 
{ 
    rPosition.x = InfVal;
    rPosition.y = InfVal;
    rPosition.z = InfVal; 
}

inline void Object3D::SetRotation(vec3 const& InrRotation) noexcept { rRotation = InrRotation; }
inline void Object3D::SetRotation(float InfX, float InfY, float InfZ) noexcept 
{
    rRotation.x = InfX;
    rRotation.y = InfY;
    rRotation.z = InfZ;
}

inline void Object3D::SetRotation(float InfVal) noexcept
{
    rRotation.x = InfVal;
    rRotation.y = InfVal;
    rRotation.z = InfVal;
}

inline void Object3D::SetScale(vec3 const& InrScale) noexcept { rScale = InrScale; }
inline void Object3D::SetScale(float InfX, float InfY, float InfZ) noexcept
{
    rScale.x = InfX;
    rScale.y = InfY;
    rScale.z = InfZ;
}

inline void Object3D::SetScale(float InfVal) noexcept
{
    rScale.x = InfVal;
    rScale.y = InfVal;
    rScale.z = InfVal;
}

constexpr inline vec3 Object3D::GetPosition() const noexcept { return rPosition; }
constexpr inline vec3 Object3D::GetRotation() const noexcept { return rRotation; }
constexpr inline vec3 Object3D::GetScale() const noexcept { return rScale; }