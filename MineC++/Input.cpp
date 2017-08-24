#include "Input.h"

Input::Input()
{

}

Input::~Input()
{

}

Input * Input::Instance()
{
	if (_instance == nullptr)
		_instance = new Input();
	return _instance;
}
