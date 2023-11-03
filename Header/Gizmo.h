#pragma once

#include "glm/glm.hpp"

#include "Model.h"
#include "ShapePrimitives.h"

using glm::vec3;

class GizmoBase : public Model
{
public:
    GizmoBase();

protected:

    virtual void ConstructGizmo() = 0;

private:
    vec3 rTransformVector;

};

class GizmoTranslate : public GizmoBase
{
public:
    GizmoTranslate();

protected:
    void ConstructGizmo() override;

private:
};


class GizmoRotate : public GizmoBase
{
public:
    GizmoRotate();

protected:
    void ConstructGizmo() override;

private:
};


class GizmoScale : public GizmoBase
{
public:
    GizmoScale();

protected:
    void ConstructGizmo() override;

private:
};


class GizmoTransform : public GizmoBase
{
public:
    GizmoTransform();

protected:
    void ConstructGizmo() override;

    void ConstructTranslate();
    void ConstructRotate();
    void ConstructScale();

private:
};
