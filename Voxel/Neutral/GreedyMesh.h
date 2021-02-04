#pragma once
#include "../Neutral/VertexAndNormals.h"
#include "../Neutral/FaceType.h"
#include "../Neutral/Face.h"
#include <vector>

class GreedyMesh{
	
public:
	static std::vector<Face> convert_vertex_vector_to_face_vector(const std::vector<VertexAndNormals>& vertex);
	static std::vector<VertexAndNormals> convert_faces_vertor_to_vertexnormals(const std::vector<Face>& faces);
	
protected:
	static Face get_face(const std::vector<VertexAndNormals>& vertex, const size_t start_idx);
	static void pushback_face(std::vector<VertexAndNormals>& fill_vector, const Face& face);
	
	static bool types_match(const Face& start_face, const Face& next_face);
	static bool depths_match(const Face& start_face, const Face& next_face, const FaceType face_type);
	static bool heights_match(const Face& start_face, const Face& next_face, const FaceType face_type);
	static bool widths_match(const Face& start_face, const Face& next_face, const FaceType face_type);	
					
};

// front and back sort
struct less_than_front_faces {
	inline bool operator() (const Face& start_face, const Face& next_face) {

		VertexAndNormals start_bl = start_face.get_bottom_left();
		VertexAndNormals next_bl = next_face.get_bottom_left();

		if (start_bl.m_z == next_bl.m_z) {

			if(start_bl.m_y == next_bl.m_y){
				return start_bl.m_x < next_bl.m_x;
			}
			
			return start_bl.m_y < next_bl.m_y;						
		}
		
		return start_bl.m_z < next_bl.m_z;				
	}
	
};


struct less_than_top_bottom_faces{
	inline bool operator() (const Face& start_face, const Face& next_face){

		VertexAndNormals start_bl = start_face.get_bottom_left();
		VertexAndNormals next_bl = next_face.get_bottom_left();

		if(start_bl.m_y == next_bl.m_y){

			if(start_bl.m_z == next_bl.m_z){
				return start_bl.m_x < next_bl.m_x;				
			}

			return start_bl.m_z < next_bl.m_z;
			
		}
		
		return start_bl.m_y < next_bl.m_y;
				
	}
};