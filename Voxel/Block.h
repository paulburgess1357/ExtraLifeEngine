#pragma once

class Block{
	
public:
	Block() = default;
	~Block() = default;

	[[nodiscard]] bool is_active() const;
	void set_active(const bool active);
		
private:
	bool m_active;
};

