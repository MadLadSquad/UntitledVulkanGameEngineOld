#pragma once
#include <ios>
#include <iostream>
#include <fstream>
#include "../../Core/API/Types.hpp"
#include "../../Core/API/Defines.h"
#include "../../ThirdParty/OpenAL/include/AL/al.h"
#include "../../ThirdParty/OpenAL/include/AL/alc.h"

namespace UVK
{
	class UVK_API AudioRenderer
	{
	public:
		int32_t PlaySimpleAudio(String Location);

		void Play3DAudio();
	
	
	private:
		char* OpenAudioFile(String fn, int32_t& chan, int32_t& samplerate, int32_t& bps, int32_t& size);
		bool isBigEndian();
		int32_t convertToint32_t(char* buffer, int32_t len);
		
	};
}


