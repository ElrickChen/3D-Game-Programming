#ifndef HW5_AUDIO_H
#define HW5_AUDIO_H
#include <AL/al.h>
#include <AL/alc.h>

// Maximum data buffers we will need.
#define NUM_BUFFERS 3
// Maximum emissions we will need.
#define NUM_SOURCES 3
// These index the buffers and sources.
#define SOURCE  0
#define SOURCE1 1
#define SOURCE2 2

// Sources are points of emitting sound.
extern ALuint Sources[NUM_SOURCES];

/*
* Struct that holds the RIFF data of the Wave file.
* The RIFF data is the meta data information that holds,
* the ID, size and format of the wave file
*/
struct RIFF_Header {
	char chunkID[4];
	long chunkSize;//size not including chunkSize or chunkID
	char format[4];
};

/*
* Struct to hold fmt subchunk data for WAVE files.
*/
struct WAVE_Format {
	char subChunkID[4];
	long subChunkSize;
	short audioFormat;
	short numChannels;
	long sampleRate;
	long byteRate;
	short blockAlign;
	short bitsPerSample;
};

/*
* Struct to hold the data of the wave file
*/
struct WAVE_Data {
	char subChunkID[4]; //should contain the word data
	long subChunk2Size; //Stores the size of the data block
};

// function
/*
* Load wave file function. No need for ALUT with this
*/
bool loadWavFile(const char *filename, ALuint* buffer,
	ALsizei* size, ALsizei* frequency,
	ALenum* format);
ALboolean LoadALData();
void SetListenerValues();
void KillALData();
void playWalkSound(bool flag);

#endif