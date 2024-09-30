#pragma once
class IUpdate 
{
public:
	virtual void update(float deltatime) = 0;
	
	// TODO: check if this is needed and how this works
	// 
	//virtual ~IUpdate() = default;
};

