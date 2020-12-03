#include "AudioRenderer.h"

bool UVK::AudioRenderer::isBigEndian()
{
	int32_t a = 1;
	return !((char*)&a)[0];
}

int32_t UVK::AudioRenderer::convertToint32_t(char* buffer, int32_t len)
{
	int32_t a = 0;
	if (!isBigEndian())
		for (int32_t i = 0; i < len; i++)
			((char*)&a)[i] = buffer[i];
	else
		for (int32_t i = 0; i < len; i++)
			((char*)&a)[3 - i] = buffer[i];
	return a;
}

int32_t UVK::AudioRenderer::PlaySimpleAudio(String Location)
{
	uint32_t sourceID = 0;
	
	int32_t channel, sampleRate, bps, size;
	char* data = OpenAudioFile(Location, channel, sampleRate, bps, size);
	ALCdevice* device = alcOpenDevice(NULL);
	if (device == NULL)
	{
		std::cout << "cannot open sound card" << std::endl;
		return 0;
	}
	ALCcontext* context = alcCreateContext(device, NULL);
	if (context == NULL)
	{
		std::cout << "cannot open context" << std::endl;
		return 0;
	}
	alcMakeContextCurrent(context);

	uint32_t bufferid, format;
	alGenBuffers(1, &bufferid);
	if (channel == 1)
	{
		if (bps == 8)
		{
			format = AL_FORMAT_MONO8;
		}
		else {
			format = AL_FORMAT_MONO16;
		}
	}
	else {
		if (bps == 8)
		{
			format = AL_FORMAT_STEREO8;
		}
		else {
			format = AL_FORMAT_STEREO16;
		}
	}
	alBufferData(bufferid, format, data, size, sampleRate);
	
	alGenSources(1, &sourceID);
	alSourcei(sourceID, AL_BUFFER, bufferid);
	alSourcePlay(sourceID);
	
	while (true)
	{

	}

	alDeleteSources(1, &sourceID);
	alDeleteBuffers(1, &bufferid);

	alcDestroyContext(context);
	alcCloseDevice(device);
	delete[] data;
	return 0;
}

void UVK::AudioRenderer::Play3DAudio()
{

}

char* UVK::AudioRenderer::OpenAudioFile(String fn, int32_t& chan, int32_t& samplerate, int32_t& bps, int32_t& size)
{
	char buffer[4];
	std::ifstream in(fn, std::ios::binary);
	in.read(buffer, 4);
	if (strncmp(buffer, "RIFF", 4) != 0)
	{
		std::cout << "this is not a valid WAVE file" << std::endl;
		return NULL;
	}
	in.read(buffer, 4);
	in.read(buffer, 4);      //WAVE
	in.read(buffer, 4);      //fmt
	in.read(buffer, 4);      //16
	in.read(buffer, 2);      //1
	in.read(buffer, 2);
	chan = convertToint32_t(buffer, 2);
	in.read(buffer, 4);
	samplerate = convertToint32_t(buffer, 4);
	in.read(buffer, 4);
	in.read(buffer, 2);
	in.read(buffer, 2);
	bps = convertToint32_t(buffer, 2);
	in.read(buffer, 4);      //data
	in.read(buffer, 4);
	size = convertToint32_t(buffer, 4);
	char* data = new char[size];
	in.read(data, size);
	return data;
}
