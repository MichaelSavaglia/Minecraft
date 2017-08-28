#pragma once
#include "Label.h"
#include <functional>

class Button : public iUIElement
{
public:
	Button(const char* texturePath, int x, int y, int width, int height, std::string text);
	~Button();

	void Update();
	virtual void Draw();
	inline void BindOnClick(std::function<void()> onClickFunc)		{ mOnClick = std::bind(onClickFunc); };
	inline void BindOnRelease(std::function<void()> onReleaseFunc)	{ mOnRelease = std::bind(onReleaseFunc); };
	inline void ChangeTextSize(int size)							{ mWidth, mHeight = size;mBufferNeedsUpdate = true; };
	inline void ChangeText(char* text)								{ mLabel->ChangeText(text); };
	inline void ChangeText(const char* text)						{ mLabel->ChangeText(text); };
	inline void ChangeText(std::string text)						{ mLabel->ChangeText(text); };

	inline std::string GetText() const { return mLabel->GetText(); };

private:
	std::function<void()> mOnClick;
	std::function<void()> mOnRelease;
	Label* mLabel;
};

