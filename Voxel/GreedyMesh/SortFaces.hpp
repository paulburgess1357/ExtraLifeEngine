#pragma once
#include "../Neutral/Face.h"
#include "../Neutral/VertexAndNormals.h"

struct sort_front_back_faces {
	bool operator() (const Face& start_face, const Face& next_face) const {

		const VertexAndNormals start_bl = start_face.get_bottom_left();
		const VertexAndNormals next_bl = next_face.get_bottom_left();

		if (start_bl.m_z == next_bl.m_z) {
			if (start_bl.m_y == next_bl.m_y) {
				return start_bl.m_x < next_bl.m_x;
			}
			return start_bl.m_y < next_bl.m_y;
		}
		return start_bl.m_z < next_bl.m_z;
	}

};

struct sort_top_bottom_faces {
	bool operator() (const Face& start_face, const Face& next_face) const {

		const VertexAndNormals start_bl = start_face.get_bottom_left();
		const VertexAndNormals next_bl = next_face.get_bottom_left();

		if (start_bl.m_y == next_bl.m_y) {
			if (start_bl.m_z == next_bl.m_z) {
				return start_bl.m_x < next_bl.m_x;
			}
			return start_bl.m_z < next_bl.m_z;
		}
		return start_bl.m_y < next_bl.m_y;
	}
};
