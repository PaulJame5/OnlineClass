#pragma once
#include "I_ComponentSystem.h"
#include "PathsComponent.h"
#include "TransformSystem.h"

class PathSystem : public I_ComponentSystem<PathComponent>
{
public:
	PathSystem();
	~PathSystem();
	void update() override;
	static int getClosestPathID(TransformComponent& playerTransform);
private:
};