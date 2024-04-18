#include "Renderer.h"
#include <glad/glad.h>

Renderer::Renderer(std::shared_ptr<Shader> shader) {
	this->shader = shader;
	glGenVertexArrays(1, &vaoId);
	view = glm::mat4(1.0f);
	projection = glm::mat4(1.0f);
}

void Renderer::Allocate(const std::vector<std::shared_ptr<GraphicsObject>>& objects) {
	glBindVertexArray(vaoId);
	for (auto& object : objects) {
		object->AllocateBuffers();
	}
	glBindVertexArray(0);
}

void Renderer::RenderObject(GraphicsObject& object)
{
	shader->SendMat4Uniform("world", object.GetReferenceFrame());

	Material material = object.GetMaterial();
	shader->SendFloatUniform("materialAmbientIntensity", material.ambientIntensity);
	shader->SendFloatUniform("materialSpecularIntensity", material.specularIntensity);
	shader->SendFloatUniform("materialShininess", material.shininess);

	auto& buffer = object.GetVertexBuffer();
	buffer->Select();
	if (buffer->HasTexture()) {
		shader->SendIntUniform("texUnit", buffer->GetTextureUnit());
		buffer->GetTexture()->SelectToRender();
	}
	buffer->SetUpAttributeInterpretration();
	if (object.IsIndexed()) {
		auto indexBuffer = object.GetIndexBuffer();
		indexBuffer->SelectBuffer();
		if (buffer->IsDynamic()) {
			glBufferSubData(GL_ARRAY_BUFFER, 0, buffer->GetMaxData(), &buffer->GetData().front());
			buffer->SetUpAttributeInterpretration();
		}
		glDrawElements(buffer->GetPrimitiveType(), indexBuffer->GetSize(), GL_UNSIGNED_SHORT, (void*)0);
	}
	else {
		if (buffer->IsDynamic()) {
			glBufferSubData(GL_ARRAY_BUFFER, 0, buffer->GetMaxData(), &buffer->GetData().front());
			buffer->SetUpAttributeInterpretration();
		}
		glDrawArrays(buffer->GetPrimitiveType(), 0, buffer->GetNumberOfVertices());
	}

	// Recursively render the children
	auto& children = object.GetChildren();
	for (auto& child : children) {
		RenderObject(*child);
	}
}

void Renderer::RenderScene(Camera& camera) {
	glUseProgram(shader->GetShaderProgram());
	shader->SendMat4Uniform("projection", projection);
	Light globalLight = scene->GetGlobalLight();
	Light localLight = scene->GetLocalLight();
	shader->SendVec3Uniform("globalLightPosition", globalLight.position);
	shader->SendVec3Uniform("globalLightColor", globalLight.color);
	shader->SendFloatUniform("globalLightIntensity", globalLight.intensity);
	shader->SendVec3Uniform("localLightPosition", localLight.position);
	shader->SendVec3Uniform("localLightColor", localLight.color);
	shader->SendFloatUniform("localLightIntensity", localLight.intensity);
	shader->SendFloatUniform("localLightAttenuationCoef", localLight.attenuationCoef);
	shader->SendVec3Uniform("viewPosition", camera.GetPosition());
	glBindVertexArray(vaoId);
	shader->SendMat4Uniform("view", view);
	auto& objects = scene->GetObjects();
	// Render the objects in the scene
	for (auto& object : objects) {
		RenderObject(*object);
	}
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glUseProgram(0);
	glBindVertexArray(0);
}
