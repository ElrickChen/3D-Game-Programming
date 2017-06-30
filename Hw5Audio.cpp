#include "Hw5Audio.h"
#include <stdio.h>
#pragma warning (disable:4996)
/******************************** OPENAL FUNC *******************************
* These are OpenAL "names" (or "objects"). They store and id of a buffer	*
* or a source object. Generally you would expect to see the implementation	*
* use values that scale up from '1', but don't count on it. The spec does	*
* not make this mandatory (as it is OpenGL). The id's can easily be memory	*
* pointers as well. It will depend on the implementation.					*
*****************************************************************************/
// Buffers to hold sound data.
ALuint Buffers[NUM_BUFFERS];
// Sources are points of emitting sound.
ALuint Sources[NUM_SOURCES];

/* These are 3D cartesian vector coordinates. A structure or class would be
* a more flexible of handling these, but for the sake of simplicity we will
* just leave it as is.
*/
// Position of the source sound.
ALfloat SourcePos[NUM_SOURCES][3] = { 0.0, 0.0, 0.0 };
// Velocity of the source sound.
ALfloat SourceVel[NUM_SOURCES][3] = { 0.0, 0.0, 0.0 };
// Position of the Listener.
ALfloat ListenerPos[] = { 0.0, 0.0, 0.0 };
// Velocity of the Listener.
ALfloat ListenerVel[] = { 0.0, 0.0, 0.0 };

// Orientation of the Listener. (first 3 elements are "at", second 3 are "up")
// Also note that these should be units of '1'.
ALfloat ListenerOri[] = { 0.0, 0.0, -1.0, 0.0, 1.0, 0.0 };

ALint playState;

void setSound(int source) {
	alSourcei(Sources[source], AL_BUFFER, Buffers[source]);
	alSourcef(Sources[source], AL_PITCH, 1.0);
	alSourcef(Sources[source], AL_GAIN, 1.0);
	alSourcefv(Sources[source], AL_POSITION, SourcePos[source]);
	alSourcefv(Sources[source], AL_VELOCITY, SourceVel[source]);
	alSourcei(Sources[source], AL_LOOPING, AL_FALSE);
}
/*
* ALboolean LoadALData()
*
* This function will load our sample data from the disk using the Alut
* utility and send the data into OpenAL as a buffer. A source is then
* also created to play that buffer.
*/
ALboolean LoadALData()
{
	// Variables to load into.
	ALenum format;
	ALsizei size;
	ALsizei freq;

	// Load wav datas into 4 buffers.
	alGenBuffers(NUM_BUFFERS, Buffers);
	if (alGetError() != AL_NO_ERROR)
		return AL_FALSE;
	loadWavFile("../../../Object/walk.wav", &Buffers[SOURCE], &size, &freq, &format);
	loadWavFile("../../../Object/swing.wav", &Buffers[SOURCE1], &size, &freq, &format);
	loadWavFile("../../../Object/jump.wav", &Buffers[SOURCE2], &size, &freq, &format);

	//alutLoadWAVFile("../../../Object/walk.wav", &format, &data, &size, &freq, &loop);
	//alBufferData(Buffers[SOURCE], format, data, size, freq);
	//alutUnloadWAV(format, data, size, freq);

	// Bind the buffer with the source.
	alGenSources(NUM_SOURCES, Sources);

	if (alGetError() != AL_NO_ERROR)
		return AL_FALSE;

	setSound(SOURCE);
	setSound(SOURCE1);
	setSound(SOURCE2);
	//alSourcei(Sources[SOURCE], AL_BUFFER, Buffers[SOURCE]);
	//alSourcef(Sources[SOURCE], AL_PITCH, 1.0);
	//alSourcef(Sources[SOURCE], AL_GAIN, 1.0);
	//alSourcefv(Sources[SOURCE], AL_POSITION, SourcePos[SOURCE]);
	//alSourcefv(Sources[SOURCE], AL_VELOCITY, SourceVel[SOURCE]);
	//alSourcei(Sources[SOURCE], AL_LOOPING, AL_FALSE);

	// Do another error check and return.

	if (alGetError() == AL_NO_ERROR)
		return AL_TRUE;

	return AL_FALSE;
}

/*
* void SetListenerValues()
*
* We already defined certain values for the Listener, but we need
* to tell OpenAL to use that data. This function does just that.
*/
void SetListenerValues()
{
	alListenerfv(AL_POSITION, ListenerPos);
	alListenerfv(AL_VELOCITY, ListenerVel);
	alListenerfv(AL_ORIENTATION, ListenerOri);
}

/*
* void KillALData()
*
* We have allocated memory for our buffers and sources which needs
* to be returned to the system. This function frees that memory.
*/
void KillALData()
{
	alDeleteBuffers(NUM_BUFFERS, Buffers);
	alDeleteSources(NUM_SOURCES, Sources);
	//alutExit();
}

void errorCheck()
{
	alGetError();
}

bool loadWavFile(const char *filename, ALuint* buffer, ALsizei* size, ALsizei* frequency, ALenum* format) {
	//Local Declarations
	FILE* soundFile = NULL;
	WAVE_Format wave_format;
	RIFF_Header riff_header;
	WAVE_Data wave_data;
	unsigned char* data;

	try {
		soundFile = fopen(filename, "rb");
		if (!soundFile)
			throw (filename);

		// Read in the first chunk into the struct
		fread(&riff_header, sizeof(RIFF_Header), 1, soundFile);

		//check for RIFF and WAVE tag in memeory
		if ((riff_header.chunkID[0] != 'R' ||
			riff_header.chunkID[1] != 'I' ||
			riff_header.chunkID[2] != 'F' ||
			riff_header.chunkID[3] != 'F') ||
			(riff_header.format[0] != 'W' ||
			riff_header.format[1] != 'A' ||
			riff_header.format[2] != 'V' ||
			riff_header.format[3] != 'E'))
			throw ("Invalid RIFF or WAVE Header");

		//Read in the 2nd chunk for the wave info
		fread(&wave_format, sizeof(WAVE_Format), 1, soundFile);
		//check for fmt tag in memory
		if (wave_format.subChunkID[0] != 'f' ||
			wave_format.subChunkID[1] != 'm' ||
			wave_format.subChunkID[2] != 't' ||
			wave_format.subChunkID[3] != ' ')
			throw ("Invalid Wave Format");

		//check for extra parameters;
		if (wave_format.subChunkSize > 16)
			fseek(soundFile, sizeof(short), SEEK_CUR);

		//Read in the the last byte of data before the sound file
		fread(&wave_data, sizeof(WAVE_Data), 1, soundFile);
		//check for data tag in memory
		if (wave_data.subChunkID[0] != 'd' ||
			wave_data.subChunkID[1] != 'a' ||
			wave_data.subChunkID[2] != 't' ||
			wave_data.subChunkID[3] != 'a')
			throw ("Invalid data header");

		//Allocate memory for data
		data = new unsigned char[wave_data.subChunk2Size];

		// Read in the sound data into the soundData variable
		if (!fread(data, wave_data.subChunk2Size, 1, soundFile))
			throw ("error loading WAVE data into struct!");

		//Now we set the variables that we passed in with the
		//data from the structs
		*size = wave_data.subChunk2Size;
		*frequency = wave_format.sampleRate;
		//The format is worked out by looking at the number of
		//channels and the bits per sample.
		if (wave_format.numChannels == 1) {
			if (wave_format.bitsPerSample == 8)
				*format = AL_FORMAT_MONO8;
			else if (wave_format.bitsPerSample == 16)
				*format = AL_FORMAT_MONO16;
		}
		else if (wave_format.numChannels == 2) {
			if (wave_format.bitsPerSample == 8)
				*format = AL_FORMAT_STEREO8;
			else if (wave_format.bitsPerSample == 16)
				*format = AL_FORMAT_STEREO16;
		}
		//create our openAL buffer and check for success
		alGenBuffers(1, buffer);
		errorCheck();
		//now we put our data into the openAL buffer and
		//check for success
		alBufferData(*buffer, *format, (void*)data,
			*size, *frequency);
		errorCheck();
		//clean up and return true if successful
		fclose(soundFile);
		return true;
	}
	catch (char *error) {
		//our catch statement for if we throw a string
		printf("%s :trying to load %s\n", error, filename);
		//std::cerr << error << " : trying to load "
		//	<< filename << std::endl;

		//clean up memory if wave loading fails
		if (soundFile != NULL)
			fclose(soundFile);
		//return false to indicate the failure to load wave
		return false;
	}
}

// 讓走路聲循環播放不會被中斷
void playWalkSound(bool flag) {
	alGetSourcei(Sources[SOURCE], AL_SOURCE_STATE, &playState);
	if (flag && (playState != AL_PLAYING)) {
		alSourcePlay(Sources[SOURCE]);
	}
	else if (!flag) {
		alSourceStop(Sources[SOURCE]);
	}
}