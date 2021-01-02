#include "Block.h"

bool Block::is_active() const {
	return m_active;
}

void Block::set_active(const bool active){
	m_active = active;
}

