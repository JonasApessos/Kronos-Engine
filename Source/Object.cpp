#include "Object.h"

uint64 ObjectBase::iID = 0;

ObjectBase::ObjectBase() : 
iHash(static_cast<uint64>(hash<string>{}(std::to_string(++iID)))),
sName("Object_"+to_string(iID)) {}

bool ObjectBase::SetParent(ObjectBase* InrBase)
{
    if(InrBase != nullptr)
        rParent = InrBase;
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

bool ObjectBase::AddChildren(vector<ObjectBase*>* InrBaseList)
{
    if(InrBaseList != nullptr)
    {
        vector<ObjectBase*>::iterator It = InrBaseList->begin();

        while(It != InrBaseList->end())
        {
            if(*It != nullptr)
                rChildren.push_back(*It);

            ++It;
        }
    }
    else
        return false;

    return true;
}

void Object3D::Test()
{
    std::cout << "test";
}


Object3D::Object3D() 
{
    //string a = "TestHandle";
    //InputKeyHandler<Object3D, this> rTest(a, EGLFWInputKey::EGLFWIK_0, 21);
}