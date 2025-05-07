#include "Gizmo.h"

//-------------<GIZMO BASE>-------------//
GizmoBase::GizmoBase()
{
}

//-------------<GIZMO TRANSLATE>-------------//
void GizmoTranslate::ConstructGizmo()
{
    SShapePrimCone rCone(4, 0.1f, 0.2f);
    SShapePrimLine rLine(1.0f);
    SShapePrimPlane rPlane(0.5f);

    Mesh rMesh = rLine.GetMesh();

    rMesh.SetDrawMode(EGLDrawMode::EGLDM_LineStrip);

    AddMesh(rMesh);

    rMesh.RotateOffset(HALF_PI_F, vec3(0.f, 0.f, 1.f));

    AddMesh(rMesh);

    rMesh.RotateOffset(HALF_PI_F, vec3(1.f, 0.f, 0.f));

    AddMesh(rMesh);

    rMesh = rCone.GetMesh();

    rMesh.RotateOffset(HALF_PI_F, vec3(0.f, 0.f, -1.f));
    rMesh.TranslateOffset(vec3(1.f, 0.f, 0.f));

    AddMesh(rMesh);

    rMesh.RotateOffset(HALF_PI_F, vec3(0.f, -1.f, 0.f));

    AddMesh(rMesh);

    rMesh.RotateOffset(HALF_PI_F, vec3(-1.f, 0.f, 0.f));

    AddMesh(rMesh);

    rMesh = SShapePrimCube(0.1f, 0.1f).GetMesh();

    rMesh.TranslateOffset(vec3(-0.05f, -0.05f, -0.05f));

    rMesh.SetDrawMode(EGLDrawMode::EGLDM_TriangleStrip);

    AddMesh(rMesh);

    rMesh = rPlane.GetMesh();

    rMesh.SetDrawMode(EGLDrawMode::EGLDM_TriangleStrip);

    rMesh.RotateOffset(PI_F, vec3(1.f, 0.f, 0.f));
    rMesh.TranslateOffset(vec3(0.f, 0.f, 0.5f));

    AddMesh(rMesh);

    rMesh.RotateOffset(HALF_PI_F, vec3(0.f, 0.f, 1.f));
    rMesh.RotateOffset(HALF_PI_F, vec3(0.f, 1.f, 0.f));

    AddMesh(rMesh);

    rMesh.RotateOffset(HALF_PI_F, vec3(0.f, 0.f, 1.f));
    rMesh.RotateOffset(HALF_PI_F, vec3(0.f, 1.f, 0.f));

    AddMesh(rMesh);
    
}


//-------------<GIZMO ROTATE>-------------//
void GizmoRotate::ConstructGizmo()
{
    SShapePrimCircle rCircle(64, 1.f);
    SShapePrimSphere rSphere(16,16,0.05f,1.0f);
    SShapePrimCone rCone(8,0.05f,0.1f);

    //Circle Y
    Mesh rMesh(rCircle.GetMesh());

    rMesh.SetDrawMode(EGLDrawMode::EGLDM_LineLoop);

    AddMesh(rMesh);

    //Circle X
    rMesh.RotateOffset(HALF_PI_F, vec3(1.f, 0.f, 0.f));

    AddMesh(rMesh);

    //Circle Z
    rMesh.RotateOffset(HALF_PI_F, vec3(0.f, 1.f, 0.f));

    AddMesh(rMesh);

    //Cyrcle Control Y
    rMesh = rSphere.GetMesh();

    rMesh.SetDrawMode(EGLDrawMode::EGLDM_Triangles);

    Mesh rMesh2 = rCone.GetMesh();

    rMesh2.RotateOffset(HALF_PI_F, vec3(1.f, 0.f, 0.f));
    rMesh2.TranslateOffset(vec3(0.f, 0.05f, 0.05f));

    rMesh.Merge(rMesh2);

    rMesh2.RotateOffset(PI_F, vec3(-1.f, 0.f, 0.f));
    rMesh2.TranslateOffset(vec3(0.f, 0.1f, 0.f));

    rMesh.Merge(rMesh2);

    rMesh.TranslateOffset(vec3(0.f, 1.f, 0.f));

    AddMesh(rMesh);

    rMesh.RotateOffset(HALF_PI_F, vec3(1.f, 0.f, 0.f));

    AddMesh(rMesh);

    rMesh.RotateOffset(HALF_PI_F, vec3(0.f, 1.f, 0.f));
    rMesh.TranslateOffset(vec3(0.f, -1.f, 0.f));
    rMesh.RotateOffset(HALF_PI_F, vec3(1.f, 0.f, 0.f));
    rMesh.TranslateOffset(vec3(0.f, 0.f, 1.f));

    AddMesh(rMesh);

}

//-------------<GIZMO SCALE>-------------//
void GizmoScale::ConstructGizmo()
{
    SShapePrimCube rCube(0.1f, 0.1f);
    SShapePrimLine rLine(1.f);

    Mesh rMesh = rCube.GetMesh();

    rMesh.SetDrawMode(EGLDrawMode::EGLDM_TriangleStrip);
    
    rMesh.TranslateOffset(vec3(-0.05));

    AddMesh(rMesh);

    rMesh.TranslateOffset(vec3(1.f, 0.f, 0.f));

    AddMesh(rMesh);

    rMesh.RotateOffset(HALF_PI_F, vec3(0.f, -1.f, 0.f));

    AddMesh(rMesh);

    rMesh.RotateOffset(HALF_PI_F, vec3(-1.f, 0.f, 0.f));

    AddMesh(rMesh);


    rMesh = rLine.GetMesh();

    rMesh.SetDrawMode(EGLDrawMode::EGLDM_LineStrip);

    AddMesh(rMesh);

    rMesh.RotateOffset(HALF_PI_F, vec3(0.f, -1.f, 0.f));

    AddMesh(rMesh);

    rMesh.RotateOffset(HALF_PI_F, vec3(-1.f, 0.f, 0.f));

    AddMesh(rMesh);

    rMesh.RotateOffset(HALF_PI_F/2, vec3(-1.f, 0.f, 0.f));
    rMesh.TranslateOffset(vec3(0.f, 0.f, 0.707f));

    AddMesh(rMesh);

    rMesh.RotateOffset(HALF_PI_F, vec3(0.f, 1.f, 0.f));

    AddMesh(rMesh);

    rMesh.TranslateOffset(vec3(-0.707f, 0.f, 0.f));
    rMesh.RotateOffset(HALF_PI_F, vec3(1.f, 0.f, 0.f));
    rMesh.TranslateOffset(vec3(0.707f, 0.f, 0.f));

    AddMesh(rMesh);
}

//-------------<GIZMO TRANSFORM>-------------//
void GizmoTransform::ConstructGizmo()
{
    ConstructTranslate();
    ConstructRotate();
    ConstructScale();
}

void GizmoTransform::ConstructTranslate()
{
    SShapePrimCone rCone(4, 0.1f, 0.2f);
    SShapePrimLine rLine(1.0f);
    SShapePrimPlane rPlane(0.25f);

    Mesh rMesh = rLine.GetMesh();

    rMesh.SetDrawMode(EGLDrawMode::EGLDM_LineStrip);

    AddMesh(rMesh);

    rMesh.RotateOffset(HALF_PI_F, vec3(0.f, 0.f, 1.f));

    AddMesh(rMesh);

    rMesh.RotateOffset(HALF_PI_F, vec3(1.f, 0.f, 0.f));

    AddMesh(rMesh);

    rMesh = rCone.GetMesh();

    rMesh.RotateOffset(HALF_PI_F, vec3(0.f, 0.f, -1.f));
    rMesh.TranslateOffset(vec3(1.15f, 0.f, 0.f));

    AddMesh(rMesh);

    rMesh.RotateOffset(HALF_PI_F, vec3(0.f, -1.f, 0.f));

    AddMesh(rMesh);

    rMesh.RotateOffset(HALF_PI_F, vec3(-1.f, 0.f, 0.f));

    AddMesh(rMesh);

    rMesh = SShapePrimCube(0.1f, 0.1f).GetMesh();

    rMesh.TranslateOffset(vec3(-0.05f, -0.05f, -0.05f));

    rMesh.SetDrawMode(EGLDrawMode::EGLDM_TriangleStrip);

    AddMesh(rMesh);

    rMesh = rPlane.GetMesh();

    rMesh.SetDrawMode(EGLDrawMode::EGLDM_TriangleStrip);

    rMesh.RotateOffset(PI_F, vec3(1.f, 0.f, 0.f));
    rMesh.TranslateOffset(vec3(0.f, 0.f, 0.25f));

    AddMesh(rMesh);

    rMesh.RotateOffset(HALF_PI_F, vec3(0.f, 0.f, 1.f));
    rMesh.RotateOffset(HALF_PI_F, vec3(0.f, 1.f, 0.f));

    AddMesh(rMesh);

    rMesh.RotateOffset(HALF_PI_F, vec3(0.f, 0.f, 1.f));
    rMesh.RotateOffset(HALF_PI_F, vec3(0.f, 1.f, 0.f));

    AddMesh(rMesh);
}

void GizmoTransform::ConstructRotate()
{
    SShapePrimCircle rCircle(64, 1.f);
    SShapePrimSphere rSphere(16,16,0.05f,1.0f);
    SShapePrimCone rCone(8,0.05f,0.1f);

    //Circle Y
    Mesh rMesh(rCircle.GetMesh());

    rMesh.SetDrawMode(EGLDrawMode::EGLDM_LineLoop);

    AddMesh(rMesh);

    //Circle X
    rMesh.RotateOffset(HALF_PI_F, vec3(1.f, 0.f, 0.f));

    AddMesh(rMesh);

    //Circle Z
    rMesh.RotateOffset(HALF_PI_F, vec3(0.f, 1.f, 0.f));

    AddMesh(rMesh);

    //Cyrcle Control Y
    rMesh = rSphere.GetMesh();

    rMesh.SetDrawMode(EGLDrawMode::EGLDM_Triangles);

    Mesh rMesh2 = rCone.GetMesh();

    rMesh2.RotateOffset(HALF_PI_F, vec3(1.f, 0.f, 0.f));
    rMesh2.TranslateOffset(vec3(0.f, 0.05f, 0.05f));

    rMesh.Merge(rMesh2);

    rMesh2.RotateOffset(PI_F, vec3(-1.f, 0.f, 0.f));
    rMesh2.TranslateOffset(vec3(0.f, 0.1f, 0.f));

    rMesh.Merge(rMesh2);

    rMesh.TranslateOffset(vec3(0.f, 1.05f, 0.f));

    AddMesh(rMesh);

    rMesh.RotateOffset(HALF_PI_F, vec3(1.f, 0.f, 0.f));

    AddMesh(rMesh);

    rMesh.RotateOffset(HALF_PI_F, vec3(0.f, 1.f, 0.f));
    rMesh.TranslateOffset(vec3(0.f, -1.f, 0.f));
    rMesh.RotateOffset(HALF_PI_F, vec3(1.f, 0.f, 0.f));
    rMesh.TranslateOffset(vec3(0.f, 0.f, 1.f));

    AddMesh(rMesh);
}

void GizmoTransform::ConstructScale()
{
    SShapePrimCube rCube(0.1f, 0.1f);
    SShapePrimLine rLine(1.f);

    Mesh rMesh = rCube.GetMesh();

    rMesh.SetDrawMode(EGLDrawMode::EGLDM_TriangleStrip);
    
    rMesh.TranslateOffset(vec3(-0.05));

    AddMesh(rMesh);

    rMesh.TranslateOffset(vec3(1.f, 0.f, 0.f));

    AddMesh(rMesh);

    rMesh.RotateOffset(HALF_PI_F, vec3(0.f, -1.f, 0.f));

    AddMesh(rMesh);

    rMesh.RotateOffset(HALF_PI_F, vec3(-1.f, 0.f, 0.f));

    AddMesh(rMesh);


    rMesh = rLine.GetMesh();

    rMesh.SetDrawMode(EGLDrawMode::EGLDM_LineStrip);

    rMesh.RotateOffset(HALF_PI_F, vec3(0.f, -1.f, 0.f));

    rMesh.RotateOffset(HALF_PI_F, vec3(-1.f, 0.f, 0.f));

    rMesh.RotateOffset(HALF_PI_F/2, vec3(-1.f, 0.f, 0.f));
    rMesh.TranslateOffset(vec3(0.f, 0.f, 0.707f));

    AddMesh(rMesh);

    rMesh.RotateOffset(HALF_PI_F, vec3(0.f, 1.f, 0.f));

    AddMesh(rMesh);

    rMesh.TranslateOffset(vec3(-0.707f, 0.f, 0.f));
    rMesh.RotateOffset(HALF_PI_F, vec3(1.f, 0.f, 0.f));
    rMesh.TranslateOffset(vec3(0.707f, 0.f, 0.f));

    AddMesh(rMesh);
}