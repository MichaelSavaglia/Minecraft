#pragma once
#include "iUIElement.h"

class Label final : public iUIElement
{
public:
	Label(char* text, int x, int y, int size);
	Label(std::string text, int x, int y, int size);
	~Label();
	virtual void Draw();
	inline void ChangeSize(int size) { mWidth, mHeight = size; mBufferNeedsUpdate = true;};
	inline void ChangeText(char* text) { mText = text; mBufferNeedsUpdate = true; };
	inline void ChangeText(const char* text) { mText = const_cast<char*>(text); mBufferNeedsUpdate = true; };
	inline void ChangeText(std::string text) { mText = text; mBufferNeedsUpdate = true; };

	inline std::string GetText() { return mText; }

private:
	std::string mText;
	void SetBuffers();
};

