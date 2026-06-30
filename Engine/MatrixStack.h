#ifndef MatrixStack_H
#define MatrixStack_H

#include <SDL3/SDL_opengl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

class MatrixStack {
	std::vector<glm::mat4> m_stack;
	glm::mat4 m_current;
	GLenum m_glMode;
	bool m_dirty;

public:
	MatrixStack(GLenum mode)
		: m_current(1.0f)
		, m_glMode(mode)
		, m_dirty(true)
	{
		m_stack.reserve(8);
	}

	void push()
	{
		m_stack.push_back(m_current);
	}
	void pop()
	{
		m_current = m_stack.back();
		m_stack.pop_back();
		m_dirty = true;
	}

	void loadIdentity()
	{
		m_current = glm::mat4(1.0f);
		m_dirty = true;
	}
	void load(const glm::mat4 &m)
	{
		m_current = m;
		m_dirty = true;
	}
	void multiply(const glm::mat4 &m)
	{
		m_current *= m;
		m_dirty = true;
	}

	void translate(float x, float y, float z)
	{
		m_current = glm::translate(m_current, glm::vec3(x, y, z));
		m_dirty = true;
	}
	void rotate(float angle, float x, float y, float z)
	{
		m_current = glm::rotate(m_current, glm::radians(angle),
					glm::vec3(x, y, z));
		m_dirty = true;
	}
	void scale(float x, float y, float z)
	{
		m_current = glm::scale(m_current, glm::vec3(x, y, z));
		m_dirty = true;
	}

	void apply()
	{
		if (!m_dirty)
			return;
		glMatrixMode(m_glMode);
		glLoadMatrixf(glm::value_ptr(m_current));
		m_dirty = false;
	}

	const glm::mat4 &top() const
	{
		return m_current;
	}
};

extern MatrixStack modelview;
extern MatrixStack projection;

#endif
