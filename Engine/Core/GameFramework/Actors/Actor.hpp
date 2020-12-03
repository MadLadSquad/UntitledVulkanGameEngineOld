#pragma once
#include "../../API/Entity.hpp"

namespace UVK
{
	class UVK_API AActor : public Entity
	{
	public:
		bool bTickEnabled;

		AActor();
		~AActor();

		virtual void Tick() = 0;

		virtual void BeginPlay() = 0;

		virtual void EndPlay() = 0;
	};
}


