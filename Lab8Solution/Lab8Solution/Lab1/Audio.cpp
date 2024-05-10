#include "Audio.h"

Audio::Audio() {
    device = alcOpenDevice(nullptr); // Open sound card
    if (device == nullptr) {
        std::cerr << "Cannot open sound card" << std::endl;
    }

    context = alcCreateContext(device, nullptr);
    if (context == nullptr) {
        std::cerr << "Cannot open context" << std::endl;
    }

    alcMakeContextCurrent(context);
}

Audio::~Audio() {
    for (auto& data : soundDatas) {
        alDeleteSources(1, &data.sourceID);
        if (data.bufferID != 0) {
            alDeleteBuffers(1, &data.bufferID);
        }
    }
    alcDestroyContext(context);
    alcCloseDevice(device);
}

bool Audio::IsBigEndian() {
    int a = 1;
    return !reinterpret_cast<char*>(&a)[0];
}

int Audio::ConvertToInt(char* buffer, int length) {
    int a = 0;
    if (!IsBigEndian()) {
        for (int i = 0; i < length; i++)
            reinterpret_cast<char*>(&a)[i] = buffer[i];
    }
    else {
        for (int i = 0; i < length; i++)
            reinterpret_cast<char*>(&a)[3 - i] = buffer[i];
    }
    return a;
}

char* Audio::LoadWAV(const char* filename, int& chan, int& samplerate, int& bps, int& size) {
    std::ifstream in(filename, std::ios::binary);
    if (!in) {
        std::cerr << "Failed to open WAV file: " << filename << std::endl;
        return nullptr;
    }

    char buffer[4];
    in.read(buffer, 4); // "RIFF"
    in.read(buffer, 4); // File size
    in.read(buffer, 4); // "WAVE"
    in.read(buffer, 4); // "fmt "
    in.read(buffer, 4); // Size of format chunk
    in.read(buffer, 2); // Audio format
    in.read(buffer, 2); // Number of channels
    chan = ConvertToInt(buffer, 2);
    in.read(buffer, 4); // Sample rate
    samplerate = ConvertToInt(buffer, 4);
    in.read(buffer, 4); // Byte rate
    in.read(buffer, 2); // Block align
    in.read(buffer, 2); // Bits per sample
    bps = ConvertToInt(buffer, 2);
    in.read(buffer, 4); // "data"
    in.read(buffer, 4); // Size of data chunk
    size = ConvertToInt(buffer, 4);

    char* soundData = new char[size];
    in.read(soundData, size);
    return soundData;
}

unsigned int Audio::LoadSound(const char* filename) {
    for (const auto& data : soundDatas) {
        if (data.name == filename && data.bufferID != 0) {
            return data.sourceID;
        }
    }

    int channel, sampleRate, bps, size;
    char* soundData = LoadWAV(filename, channel, sampleRate, bps, size);
    if (!soundData) {
        return 0;
    }

    unsigned int bufferID;
    alGenBuffers(1, &bufferID);
    unsigned int format = AL_FORMAT_MONO8;
    if (channel == 1) {
        format = (bps == 8) ? AL_FORMAT_MONO8 : AL_FORMAT_MONO16;
    }
    else {
        format = (bps == 8) ? AL_FORMAT_STEREO8 : AL_FORMAT_STEREO16;
    }
    alBufferData(bufferID, format, soundData, size, sampleRate);

    unsigned int sourceID;
    alGenSources(1, &sourceID);
    alSourcei(sourceID, AL_BUFFER, bufferID);
    alSourcef(sourceID, AL_REFERENCE_DISTANCE, 1.0f);

    soundDatas.push_back({ sourceID, bufferID, filename });

    delete[] soundData;
    return sourceID;
}

void Audio::DeleteSound(unsigned int id) {
    auto it = std::find_if(soundDatas.begin(), soundDatas.end(), [id](const auto& data) {
        return data.sourceID == id;
        });

    if (it != soundDatas.end()) {
        alDeleteSources(1, &it->sourceID);
        if (it->bufferID != 0) {
            alDeleteBuffers(1, &it->bufferID);
        }
        soundDatas.erase(it);
    }
}

void Audio::PlaySound(unsigned int id) {
    alSourcePlay(id);
}

void Audio::PlaySound(unsigned int id, const glm::vec3& pos) {
    alSource3f(id, AL_POSITION, pos.x, pos.y, pos.z);
    alSourcePlay(id);
}

void Audio::StopSound(unsigned int id) {
    alSourceStop(id);
}

void Audio::SetListener(const glm::vec3& pos, const glm::vec3& camLookAt) {
    alListener3f(AL_POSITION, pos.x, pos.y, -pos.z);
    float orientation[] = { camLookAt.x, camLookAt.y, camLookAt.z, 0, 1, 0 };
    alListenerfv(AL_ORIENTATION, orientation);
}