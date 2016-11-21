/*

	Copyright 2011 Etay Meiri

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Tutorial 22 - Loading models using the Open Assert Import Library
*/

#include <math.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "ogldev_util.h"
#include "ogldev_app.h"
#include "ogldev_pipeline.h"
#include "ogldev_camera.h"
#include "ogldev_basic_lighting.h"
#include "ogldev_glut_backend.h"
#include "mesh.h"

#define WINDOW_WIDTH  1920
#define WINDOW_HEIGHT 1200

static float FieldDepth = 10.0f;

class Tutorial22 : public ICallbacks
{
public:

    Tutorial22()
    {
        m_pGameCamera = NULL;
        m_pEffect = NULL;
        m_scale = 0.0f;
        m_directionalLight.Color = Vector3f(1.0f, 1.0f, 1.0f);
        m_directionalLight.AmbientIntensity = 1.0f;
        m_directionalLight.DiffuseIntensity = 0.01f;
        m_directionalLight.Direction = Vector3f(1.0f, -1.0, 0.0);

        m_persProjInfo.FOV = 60.0f;
        m_persProjInfo.Height = WINDOW_HEIGHT;
        m_persProjInfo.Width = WINDOW_WIDTH;
        m_persProjInfo.zNear = 1.0f;
        m_persProjInfo.zFar = 50.0f;        
    }

    ~Tutorial22()
    {
        delete m_pEffect;
        delete m_pGameCamera;
        delete m_pMesh;
    }

    bool Init()
    {
        Vector3f Pos(3.0f, 7.0f, -10.0f);
        Vector3f Target(0.0f, -0.2f, 1.0f);
        Vector3f Up(0.0, 1.0f, 0.0f);

        m_pGameCamera = new Camera(WINDOW_WIDTH, WINDOW_HEIGHT, Pos, Target, Up);
      
        m_pEffect = new BasicLightingTechnique();

        if (!m_pEffect->Init()) {
            printf("Error initializing the lighting technique\n");
            return false;
        }

        m_pEffect->Enable();

        m_pEffect->SetColorTextureUnit(0);

        m_pMesh = new Mesh();

        return m_pMesh->LoadMesh("../Content/phoenix_ugv.md2");
    }

    void Run()
    {
        GLUTBackendRun(this);
    }

    virtual void RenderSceneCB()
    {
        m_scale += 0.01f;

        m_pGameCamera->OnRender();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        PointLight pl[2];
        pl[0].DiffuseIntensity = 0.25f;
        pl[0].Color = Vector3f(1.0f, 0.5f, 0.0f);
        pl[0].Position = Vector3f(3.0f, 1.0f, FieldDepth * (cosf(m_scale) + 1.0f) / 2.0f);
        pl[0].Attenuation.Linear = 0.1f;
        pl[1].DiffuseIntensity = 0.25f;
        pl[1].Color = Vector3f(0.0f, 0.5f, 1.0f);
        pl[1].Position = Vector3f(7.0f, 1.0f, FieldDepth * (sinf(m_scale) + 1.0f) / 2.0f);
        pl[1].Attenuation.Linear = 0.1f;
        m_pEffect->SetPointLights(2, pl);

        SpotLight sl;
        sl.DiffuseIntensity = 0.9f;
        sl.Color = Vector3f(0.0f, 1.0f, 1.0f);
        sl.Position = m_pGameCamera->GetPos();
        sl.Direction = m_pGameCamera->GetTarget();
        sl.Attenuation.Linear = 0.1f;
        sl.Cutoff = 10.0f;

        m_pEffect->SetSpotLights(1, &sl);

        Pipeline p;
        p.Scale(0.1f, 0.1f, 0.1f);
        p.Rotate(0.0f, m_scale, 0.0f);
        p.WorldPos(0.0f, 0.0f, 10.0f);
        p.SetCamera(m_pGameCamera->GetPos(), m_pGameCamera->GetTarget(), m_pGameCamera->GetUp());
        p.SetPerspectiveProj(m_persProjInfo);
        m_pEffect->SetWVP(p.GetWVPTrans());
        m_pEffect->SetWorldMatrix(p.GetWorldTrans());
        m_pEffect->SetDirectionalLight(m_directionalLight);
        m_pEffect->SetEyeWorldPos(m_pGameCamera->GetPos());
        m_pEffect->SetMatSpecularIntensity(0.0f);
        m_pEffect->SetMatSpecularPower(0);

        m_pMesh->Render();

        glutSwapBuffers();
    }



    void KeyboardCB(OGLDEV_KEY OgldevKey, OGLDEV_KEY_STATE State)
    {
        switch (OgldevKey) {
        case OGLDEV_KEY_ESCAPE:
        case OGLDEV_KEY_q:
            GLUTBackendLeaveMainLoop();
            break;
        case OGLDEV_KEY_a:
            m_directionalLight.AmbientIntensity += 0.05f;
            break;
        case OGLDEV_KEY_s:
            m_directionalLight.AmbientIntensity -= 0.05f;
            break;
        case OGLDEV_KEY_z:
            m_directionalLight.DiffuseIntensity += 0.05f;
            break;
        case OGLDEV_KEY_x:
            m_directionalLight.DiffuseIntensity -= 0.05f;
            break;
        default:
            m_pGameCamera->OnKeyboard(OgldevKey);				
        }
    }


    virtual void PassiveMouseCB(int x, int y)
    {
        m_pGameCamera->OnMouse(x, y);
    }

private:

    BasicLightingTechnique* m_pEffect;
    Camera* m_pGameCamera;
    float m_scale;
    DirectionalLight m_directionalLight;
    Mesh* m_pMesh;
    PersProjInfo m_persProjInfo;	
};


int main(int argc, char** argv)
{
//    Magick::InitializeMagick(*argv);
    GLUTBackendInit(argc, argv, true, false);

    if (!GLUTBackendCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, false, "Tutorial 22")) {
        return 1;
    }

    Tutorial22* pApp = new Tutorial22();

    if (!pApp->Init()) {
        return 1;
    }

    pApp->Run();

    delete pApp;
 
    return 0;
}
