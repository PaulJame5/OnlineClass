#pragma once
#include "Component.h"



class SmallDotComponent : public Component
{
public:
	SmallDotComponent();
	~SmallDotComponent();
	void Kill();
	void SetAcive();
	void init();
	bool isActive();
private:
	bool active;
};