#pragma once
#include "../../API/Defines.h"

class UVK_API PlayerState
{

public:
	virtual void BeginPlay();
	virtual void Tick(float DeltaTime);
};

