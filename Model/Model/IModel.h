#pragma once
#include "../Mesh/IMesh.h"
#include <vector>
#include <memory>

class IModel{
	
public:
	IModel();
	virtual ~IModel() = default;	
	virtual void destroy() = 0;
	void destroy_mesh_vector();
	[[nodiscard]] const std::vector<std::unique_ptr<IMesh>>& get_mesh_vector() const;

protected:
	std::vector<std::unique_ptr<IMesh>> m_mesh_vector;
};
