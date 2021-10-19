#include "VertexArray.h"
#include "Vertex.h"

#include "GL/glew.h"

namespace RTE {
	VertexArray::VertexArray() : m_VAO(0), m_VBO(0) {
		glCreateVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);
	}

	VertexArray::~VertexArray() {
		if (m_VBO) {
			glDeleteBuffers(1, &m_VBO);
		}

		if (m_VAO) {
			glDeleteVertexArrays(1, &m_VAO);
		}
	}

	VertexArray::VertexArray(const std::vector<Vertex>& vertices, bool updateable) : VertexArray() {
		Create(vertices, updateable);
	}

	void VertexArray::Create(const std::vector<Vertex> &vertices, bool updateable) {
		m_Vertices = vertices;
		glBindVertexArray(m_VAO);
		if (!vertices.empty()) {
			glBindBuffer(GL_VERTEX_ARRAY, m_VBO);
			glBufferData(GL_VERTEX_ARRAY, vertices.size() * sizeof(Vertex), vertices.data(), updateable ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(offsetof(Vertex, pos)));
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(offsetof(Vertex, texUV)));
			glVertexAttribPointer(2, 4, GL_UNSIGNED_INT, GL_TRUE, sizeof(Vertex), (void *)(offsetof(Vertex, color)));
		}
		glBindVertexArray(0);
	}

	void VertexArray::Bind() {
		glBindVertexArray(m_VAO);
	}
}
