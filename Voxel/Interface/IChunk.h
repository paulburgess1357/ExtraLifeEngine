#pragma once
#define CX 1
#define CY 20
#define CZ 20

#include "../Neutral/WorldPosition.h"
#include "../Neutral/VertexAndNormals.h"
#include "../../Environment/Interfaces/Shader/IShaderProgram.h"
#include <memory>
#include <vector>

#include "../../Utility/Print.h"

class IChunk {

public:
	IChunk(const WorldPosition& starting_world_position, 
		const std::shared_ptr<IShaderProgram>& shader_program);
	virtual ~IChunk();

	[[nodiscard]] signed char get(const signed char x, const signed char y, const signed char z) const;
	void set(const signed char x, const signed char y, const signed char z, const signed char type);
	virtual void update() = 0;
	virtual void render() const = 0;
	void print_world_position(){
		Print::print(std::to_string(m_world_position.x) + "," + std::to_string(m_world_position.y) + "," + std::to_string(m_world_position.z));
	}
	
protected:
	void initialize_types();
	static void emplace_left_face(std::vector<VertexAndNormals>& vertex, signed char x, signed char y, signed char z, signed char type);
	static void emplace_right_face(std::vector<VertexAndNormals>& vertex, signed char x, signed char y, signed char z, signed char type);

	static void emplace_front_face(std::vector<VertexAndNormals>& vertex, signed char x, signed char y, signed char z, signed char type);
	static void emplace_back_face(std::vector<VertexAndNormals>& vertex, signed char x, signed char y, signed char z, signed char type);
	
	static void emplace_top_face(std::vector<VertexAndNormals>& vertex, signed char x, signed char y, signed char z, signed char type);
	static void emplace_bottom_face(std::vector<VertexAndNormals>& vertex, signed char x, signed char y, signed char z, signed char type);


	static std::vector<VertexAndNormals> merge_left_faces(std::vector<VertexAndNormals>& vertex);
	
	

	signed char m_block_types[CX][CY][CZ];

	int m_vertex_qty;
	bool m_update_required;

	glm::mat4 m_model_matrix;
	glm::mat3 m_normal_matrix;
	WorldPosition m_world_position;
	std::shared_ptr<IShaderProgram> m_shader_program;	
};
