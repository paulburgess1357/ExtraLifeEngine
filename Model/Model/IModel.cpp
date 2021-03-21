#include "IModel.h"
#include "../../Utility/Print.h"

IModel::IModel() = default;

const std::vector<std::shared_ptr<IMesh>>& IModel::get_mesh_vector() const{
	return m_mesh_vector;
}

void IModel::destroy_mesh_vector(){
	Print::print("	- Destroying Mesh Vector");
	m_mesh_vector.clear();
}