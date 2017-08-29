#pragma once
#include "Label.h"
#include <functional>

class Input;
class Button : public iUIElement
{
public:
	Button(const char* texturePath, int x, int y, int width, int height, std::string text);
	~Button();

	void Update();
	virtual void Draw() override;
	inline void BindOnClick(std::function<void()> onClickFunc) { mOnClick = std::bind(onClickFunc); };
	inline void BindOnRelease(std::function<void()> onReleaseFunc) { mOnRelease = std::bind(onReleaseFunc); };
	inline void ChangeTextSize(int size) { mWidth, mHeight = size; mBufferNeedsUpdate = true; };
	inline void ChangeText(char* text) { mLabel->ChangeText(text); mBufferNeedsUpdate = true; };
	inline void ChangeText(const char* text) { mLabel->ChangeText(text); mBufferNeedsUpdate = true; };
	inline void ChangeText(std::string text) { mLabel->ChangeText(text); mBufferNeedsUpdate = true; };

	inline std::string GetText() { return mLabel->GetText(); };

private:
	std::function<void()> mOnClick;
	std::function<void()> mOnRelease;
	bool mShouldRelease;
	virtual void SetAllignment(int8_t anchor) override;
	Label* mLabel;
	Input* mInput;
};

