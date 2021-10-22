#include "PanelRender.h"

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
	for (auto iter = renderDatas.begin(); iter != renderDatas.end(); iter++)
	{
		auto data = iter->second;
		glBindVertexArray(data->VAO);
		glPolygonMode(m_face, m_mode);
		glDrawElements(GL_TRIANGLES, data->element_count, GL_UNSIGNED_INT, 0);
	}
	glBindVertexArray(0);
}

