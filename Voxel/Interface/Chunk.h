#pragma once
#define CX 1
#define CY 1
#define CZ 1

#include "../Neutral/WorldPosition.h"
#include "../Neutral/VertexAndNormals.h"
#include "../../Environment/Interfaces/Shader/IShaderProgram.h"
#include <memory>
#include <vector>

class AdjacentChunkAddress;

class Chunk {

public:
	Chunk(const WorldPosition& starting_world_position, 
		  const std::shared_ptr<IShaderProgram>& shader_program);
	virtual ~Chunk();

	[[nodiscard]] signed char get(const signed char x, const signed char y, const signed char z) const;
	void set(const signed char x, const signed char y, const signed char z, const signed char type);
	virtual void update() = 0;
	virtual void render() const = 0;

	// Adjacent Chunks
	void set_left_chunk(const std::shared_ptr<Chunk>& chunk);
	void set_right_chunk(const std::shared_ptr<Chunk>& chunk);
	void set_top_chunk(const std::shared_ptr<Chunk>& chunk);
	void set_bottom_chunk(const std::shared_ptr<Chunk>& chunk);
	void set_front_chunk(const std::shared_ptr<Chunk>& chunk);
	void set_back_chunk(const std::shared_ptr<Chunk>& chunk);
	
protected:
	void initialize_types();
	std::vector<VertexAndNormals> load_chunk_data();
	
	static void emplace_left_face(std::vector<VertexAndNormals>& vertex, signed char x, signed char y, signed char z, signed char type);
	static void emplace_right_face(std::vector<VertexAndNormals>& vertex, signed char x, signed char y, signed char z, signed char type);
	static void emplace_front_face(std::vector<VertexAndNormals>& vertex, signed char x, signed char y, signed char z, signed char type);
	static void emplace_back_face(std::vector<VertexAndNormals>& vertex, signed char x, signed char y, signed char z, signed char type);	
	static void emplace_top_face(std::vector<VertexAndNormals>& vertex, signed char x, signed char y, signed char z, signed char type);
	static void emplace_bottom_face(std::vector<VertexAndNormals>& vertex, signed char x, signed char y, signed char z, signed char type);
	
	signed char m_block_types[CX][CY][CZ];
	int m_vertex_qty;
	bool m_update_required;

	glm::mat4 m_model_matrix;
	glm::mat3 m_normal_matrix;
	WorldPosition m_world_position;
	std::shared_ptr<IShaderProgram> m_shader_program;

	// Adjacent Chunks
	std::shared_ptr<Chunk> m_left_chunk = nullptr;
	std::shared_ptr<Chunk> m_right_chunk = nullptr;
	std::shared_ptr<Chunk> m_top_chunk = nullptr;
	std::shared_ptr<Chunk> m_bottom_chunk = nullptr;
	std::shared_ptr<Chunk> m_front_chunk = nullptr;
	std::shared_ptr<Chunk> m_back_chunk = nullptr;

private:
	void print_world_position(const WorldPosition& starting_world_positio) const;
};
