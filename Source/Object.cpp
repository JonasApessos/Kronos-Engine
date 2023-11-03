#include "Object.h"

uint64 ObjectBase::iID = 0;

ObjectBase::ObjectBase() : 
iHash(static_cast<uint64>(hash<string>{}(std::to_string(++iID)))),
sName("Object_"+to_string(iID)) {}

Object3D::Object3D() {}