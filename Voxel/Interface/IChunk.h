#pragma once
#define CX 16
#define CY 16
#define CZ 16

#include "../Neutral/WorldPosition.h"
#include "../../Environment/Interfaces/Shader/IShaderProgram.h"
#include <memory>

class IChunk {

public:
	IChunk(const WorldPosition& starting_world_position, const std::shared_ptr<IShaderProgram>& shader_program);
	virtual ~IChunk();

	[[nodiscard]] signed char get(const signed char x, const signed char y, const signed char z) const;
	void set(const signed char x, const signed char y, const signed char z, const signed char type);
	virtual void update() = 0;
	virtual void render() const = 0;
	
protected:
	void initialize_types();

	signed char m_block_types[CX][CY][CZ];

	int m_vertex_qty;
	bool m_update_required;

	glm::mat4 m_model_matrix;
	glm::mat3 m_normal_matrix;
	WorldPosition m_world_position;
	std::shared_ptr<IShaderProgram> m_shader_program;	
};
