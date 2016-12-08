#pragma once

class iCharacter
{
public:
	virtual ~iCharacter();
	virtual void Setup() = 0;
	virtual bool GetHeight(IN float x, OUT float& y, IN float z) = 0;
	virtual void Render() = 0;
};

