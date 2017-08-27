#pragma once
#include "iUIElement.h"
#include <functional>

class Button : public iUIElement
{
public:
	Button(const char* texturePath, std::function<void()> func);
	~Button();

	void Update();
	virtual void Draw();

private:
	std::function<void()> mOnClick;

};

