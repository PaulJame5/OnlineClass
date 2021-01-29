#pragma once
#include "Component.h"




class PlayerComponent : public Component
{
public:
	PlayerComponent();
	~PlayerComponent();

	void init();
	void increasePebblesAte();
	void resetPebbles(); 
	void setAsChaser();
	void setBeingChased();
	bool isChaser();
	int getPebblesAte();
	
	void setAsCaught();
	bool isCaught();
private:

	int pebblesAte;
	bool chaser;
	bool caught = false;


};