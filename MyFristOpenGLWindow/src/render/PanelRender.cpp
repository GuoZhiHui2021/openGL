#include "render/PanelRender.h"
#include "TextureManager.h"

void PanelRender::initialize()
{
	Render::initialize();
}

void PanelRender::render()
{
	if (!m_initialized)
		return;
	if (m_program)
		m_program->use();
	glUniform1i(glGetUniformLocation(m_program->getProgramID(), "texture0"), 0);
	glUniform1i(glGetUniformLocation(m_program->getProgramID(), "texture1"), 1);
	//glUniform1i(glGetUniformLocation(m_program->getProgramID(), "texture2"), 2);
	//glUniform1i(glGetUniformLocation(m_program->getProgramID(), "texture3"), 3);
	for (auto iter = renderDatas.begin(); iter != renderDatas.end(); iter++)
	{
		auto data = iter->second;
		for (int i = 0; i < data->textureSize; i++)
		{
			TextureData textureData = data->textures[i];
			std::string textureName(textureData.texture, strlen(textureData.texture));
			uint16_t* options = textureData.options;
			Texture* texture = TextureManager::Instance()->getOrCreateTexture(textureName);
			if (texture)
			{
				texture->use(textureData.textureUnit, options);
			}
		}
		glBindVertexArray(data->VAO);
		glPolygonMode(m_face, m_mode);
		glDrawElements(GL_TRIANGLES, data->element_count, GL_UNSIGNED_INT, 0);
	}
	glBindVertexArray(0);
}

