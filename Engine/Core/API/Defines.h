#pragma once
#include <stdio.h>
#include <iostream>
#define LOG(x, ...) printf(x, __VA_ARGS__);
#ifdef GAME
	#define UVK_API __declspec(dllimport)
#else
	#define UVK_API __declspec(dllexport)
#endif
#define Legacy

