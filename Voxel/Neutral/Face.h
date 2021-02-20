#pragma once
#include "VertexAndNormals.h"

struct Face{

	Face() = default;
	
	Face(const VertexAndNormals& bottom_left_corner, 
		 const VertexAndNormals& bottom_right_corner, 
		 const VertexAndNormals& top_left_corner, 
		 const VertexAndNormals& top_right_corner)
		 :m_bottom_left_corner{ bottom_left_corner },
		  m_bottom_right_corner{ bottom_right_corner },
		  m_top_left_corner{ top_left_corner },
		  m_top_right_corner{ top_right_corner }{		
	}

	[[nodiscard]] VertexAndNormals get_bottom_left() const{
		return m_bottom_left_corner;
	}

	[[nodiscard]] VertexAndNormals get_bottom_right() const{
		return m_bottom_right_corner;
	}

	[[nodiscard]] VertexAndNormals get_top_left() const{
		return m_top_left_corner;
	}

	[[nodiscard]] VertexAndNormals get_top_right() const{
		return m_top_right_corner;
	}

	[[nodiscard]] unsigned char get_type() const{
		return m_bottom_left_corner.m_w;
	}

	void set_bottom_left(const VertexAndNormals& bottom_left) {
		m_bottom_left_corner = bottom_left;
	}

	void set_bottom_right(const VertexAndNormals& bottom_right){
		m_bottom_right_corner = bottom_right;
	}

	void set_top_left(const VertexAndNormals& top_left){
		m_top_left_corner = top_left;
	}

	void set_top_right(const VertexAndNormals& top_right){
		m_top_right_corner = top_right;
	}	
		
	VertexAndNormals m_bottom_left_corner;
	VertexAndNormals m_bottom_right_corner;
	VertexAndNormals m_top_left_corner;
	VertexAndNormals m_top_right_corner;		
};