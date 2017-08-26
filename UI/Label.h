#pragma once
#include "iUIElement.h"

class Label final : public iUIElement
{
public:
	Label(char* text, int x, int y, int size);
	~Label();
	virtual void Draw();
	inline void ChangePosition(int x, int y) { mX = x; mY = y; SetBuffers(); };
	inline void ChangeSize(int size) { mSize = size; SetBuffers(); };
	inline void ChangeText(char* text) { mText = text; SetBuffers(); };

private:
	char* mText;
	int mX, mY, mSize;
	void SetBuffers();
};

