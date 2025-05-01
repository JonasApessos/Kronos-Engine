#pragma once

#include "glm/glm.hpp"

#include "Standard.h"
#include "Model.h"
#include "ShapePrimitives.h"

using glm::vec3;

class GizmoBase : public Model
{
public:
    GizmoBase();
    virtual void ConstructGizmo() = 0;

protected:

private:
    vec3 rTransformVector;

};

class GizmoTranslate : public GizmoBase
{
public:
    void ConstructGizmo() override;

protected:

private:
};


class GizmoRotate : public GizmoBase
{
public:
    void ConstructGizmo() override;

protected:

private:
};


class GizmoScale : public GizmoBase
{
public:
    void ConstructGizmo() override;

protected:

private:
};


class GizmoTransform : public GizmoBase
{
public:
    void ConstructGizmo() override;

protected:

    void ConstructTranslate();
    void ConstructRotate();
    void ConstructScale();

private:
};
