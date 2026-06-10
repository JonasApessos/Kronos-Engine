#include "Object.h"

uint64 ObjectBase::iID = 0;

ObjectBase::ObjectBase() : 
sName("Object_"+to_string(iID)),
iHash(static_cast<uint64>(hash<string>{}(std::to_string(++iID)))) {}

bool ObjectBase::SetParent(ObjectBase* InrParent)
{
    if(InrParent != nullptr)
        rParent = InrParent;
    else
        return false;

    return true;
}

bool ObjectBase::AddChild(ObjectBase* InrBase)
{
    if(InrBase != nullptr)
        rChildren.push_back(InrBase);
    else
        return false;

    return true;
}

bool ObjectBase::AddChildren(vector<ObjectBase*>* InrList)
{
    if(InrList != nullptr)
    {
        rChildren.resize(rChildren.size() + InrList->size());

        rChildren.insert(rChildren.end(), InrList->begin(), InrList->end());
    }
    else
        return false;

    return true;
}

Object3D::Object3D() {}