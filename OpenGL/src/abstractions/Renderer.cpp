#include "Renderer.h"
#include <iostream>


#include "Scene/Scene.h"

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL Error] (" << error << "): " << function <<
            " " << file << ":" << line << std::endl;
        return false;
    }
    return true;
}

Renderer::Renderer()
{
    frameBuffer = new My_OpenGL::OpenGLFramebuffer();
}

void Renderer::Clear() const
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.Bind();
    //va.Bind();
    //what draw, number of indicies,type
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Draw(My_OpenGL::Scene& scene, Shader& shader)
{
    shader.Bind();

    Model* model = scene.GetModels()[0];
    {
        model->SetModelTrans(shader);
        scene.setView(model->GetTransform(), shader);
    }

    const std::vector<Texture*>& textures = model->GetTextures();

    for (auto& mesh : model->GetMeshes()) {
        mesh.Bind();
        if (textures.size() > 0) {
            textures[mesh.matInd]->Bind();
            textures[mesh.matInd]->SetTexture(shader);
        }
        Draw(mesh.va, mesh.ib, shader);
        //Draw(mesh.ib);
        mesh.va.Unbind();
    }
    shader.Unbind();
}

void Renderer::DrawSkybox(Model& model, Shader& shader) const
{
    shader.Bind();

    const Mesh* mesh = (&model.GetMeshes()[0]);

    mesh->va.Bind();
    Draw(mesh->ib);
    mesh->va.Unbind();

    shader.Unbind();
}

void Renderer::Draw(const IndexBuffer& ib) const
{
    
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
    
}


