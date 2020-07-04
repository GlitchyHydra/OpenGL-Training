#include "Skybox.h"

namespace My_OpenGL {

    Skybox::Skybox(Camera* pCamera)
    {
        m_Camera = pCamera;
        m_CubemapTex = nullptr;
        m_Mesh = nullptr;
        skyboxShader = nullptr;
    }

    Skybox::~Skybox()
    {
        delete m_CubemapTex;
        delete m_Mesh;
    }

    bool Skybox::Init(const std::string& Directory,
        const std::string& PosXFilename,
        const std::string& NegXFilename,
        const std::string& PosYFilename,
        const std::string& NegYFilename,
        const std::string& PosZFilename,
        const std::string& NegZFilename)
    {
        m_CubemapTex = new CubemapTexture(Directory,
            PosXFilename,
            NegXFilename,
            PosYFilename,
            NegYFilename,
            PosZFilename,
            NegZFilename);

        m_Mesh = new Model("res/skybox/box.obj");
        m_Mesh->ClearTextures();
        m_CubemapTex->Load();
        m_Mesh->SetScale(scale);
        return true;
    }

    void Skybox::SetShader(Shader* shader)
    {
        skyboxShader = shader;
    }

    void Skybox::Render(const glm::mat4& proj, const Renderer& pRenderer)
	{
        skyboxShader->Bind();
        GLint OldCullFaceMode;
        glGetIntegerv(GL_CULL_FACE_MODE, &OldCullFaceMode);
        GLint OldDepthFuncMode;
        glGetIntegerv(GL_DEPTH_FUNC, &OldDepthFuncMode);

        glCullFace(GL_FRONT);
        glDepthFunc(GL_LEQUAL);

        glm::vec3 cameraPos = m_Camera->GetPosition();
        m_Mesh->SetTranslation(cameraPos);

        glm::mat4 ts = glm::translate(glm::mat4(1.0f), m_Mesh->GetTranslation());
        glm::mat4 scale = glm::scale(ts, m_Mesh->GetScale());

        glm::mat4 mvp = proj * m_Camera->GetView() * scale;
        skyboxShader->SetUniformMat4f("gMVP", mvp);

        int slot = 0;

        m_CubemapTex->Bind(GL_TEXTURE0 + slot); 
        skyboxShader->SetUniform1i("gCubemapTexture", slot);
        pRenderer.DrawSkybox(*m_Mesh, *skyboxShader);

        glCullFace(OldCullFaceMode);
        glDepthFunc(OldDepthFuncMode);
        skyboxShader->Unbind();
	}
};