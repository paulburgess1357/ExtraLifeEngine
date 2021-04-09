#pragma once
#include "../Neutral/WorldPosition.h"
#include "../Neutral/VertexAndNormals.h"
#include <memory>
#include <vector>

constexpr unsigned char x_block_qty = 16;
constexpr unsigned char y_block_qty = 12;
constexpr unsigned char z_block_qty = 16;

class Chunk {

public:
	Chunk(const WorldPosition& starting_world_position);
	virtual ~Chunk();

	[[nodiscard]] bool is_empty() const;	
	[[nodiscard]] bool update_required() const;
	[[nodiscard]] unsigned char get_block_type(const unsigned char x, const unsigned char y, const unsigned char z) const;
	[[nodiscard]] WorldPosition get_starting_world_position() const;
	[[nodiscard]] std::vector<VertexAndNormals> load_chunk_data();

	[[nodiscard]] int get_vertex_qty() const;
	[[nodiscard]] virtual unsigned int get_vao() const = 0;
	[[nodiscard]] virtual unsigned int get_vbo() const = 0;	
	
	void set_block_type(const unsigned char x, const unsigned char y, const unsigned char z, const unsigned char type);
	void set_update_required(const bool update_required);
	
	void set_left_adjacent_chunk(const std::shared_ptr<Chunk>& chunk);
	void set_right_adjacent_chunk(const std::shared_ptr<Chunk>& chunk);
	void set_top_adjacent_chunk(const std::shared_ptr<Chunk>& chunk);
	void set_bottom_adjacent_chunk(const std::shared_ptr<Chunk>& chunk);
	void set_front_adjacent_chunk(const std::shared_ptr<Chunk>& chunk);
	void set_back_adjacent_chunk(const std::shared_ptr<Chunk>& chunk);
	
private:	
	void initialize_types();
	
	void load_left_face(std::vector<VertexAndNormals>& left_faces, const unsigned char x, const unsigned char y, const unsigned char z, const unsigned char type);
	void load_right_face(std::vector<VertexAndNormals>& right_faces, const unsigned char x, const unsigned char y, const unsigned char z, const unsigned char type);
	void load_front_face(std::vector<VertexAndNormals>& front_faces, const unsigned char x, const unsigned char y, const unsigned char z, const unsigned char type);
	void load_back_face(std::vector<VertexAndNormals>& back_faces, const unsigned char x, const unsigned char y, const unsigned char z, const unsigned char type);
	void load_top_face(std::vector<VertexAndNormals>& top_faces, const unsigned char x, const unsigned char y, const unsigned char z, const unsigned char type);
	void load_bottom_face(std::vector<VertexAndNormals>& bottom_faces, const unsigned char x, const unsigned char y, const unsigned char z, const unsigned char type);

	static void emplace_left_face(std::vector<VertexAndNormals>& vertex, const unsigned char x, const unsigned char y, const unsigned char z, const unsigned char type);
	static void emplace_right_face(std::vector<VertexAndNormals>& vertex, unsigned char x, unsigned char y, unsigned char z, unsigned char type);
	static void emplace_front_face(std::vector<VertexAndNormals>& vertex, const unsigned char x, const unsigned char y, const unsigned char z, const unsigned char type);
	static void emplace_back_face(std::vector<VertexAndNormals>& vertex, const unsigned char x, const unsigned char y, const unsigned char z, const unsigned char type);
	static void emplace_top_face(std::vector<VertexAndNormals>& vertex, const unsigned char x, const unsigned char y, const unsigned char z, const unsigned char type);
	static void emplace_bottom_face(std::vector<VertexAndNormals>& vertex, const unsigned char x, const unsigned char y, const unsigned char z, const unsigned char type);
	
	void print_world_position(const WorldPosition& starting_world_position) const;

	int m_vertex_qty;
	bool m_update_required;
	
	// Adjacent Chunks
	std::shared_ptr<Chunk> m_left_chunk = nullptr;
	std::shared_ptr<Chunk> m_right_chunk = nullptr;
	std::shared_ptr<Chunk> m_top_chunk = nullptr;
	std::shared_ptr<Chunk> m_bottom_chunk = nullptr;
	std::shared_ptr<Chunk> m_front_chunk = nullptr;
	std::shared_ptr<Chunk> m_back_chunk = nullptr;

	unsigned char m_block_types[x_block_qty][y_block_qty][z_block_qty];
	WorldPosition m_starting_world_position;
};
