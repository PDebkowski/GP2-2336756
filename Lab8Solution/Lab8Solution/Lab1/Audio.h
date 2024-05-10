#pragma once

#include <glm/glm.hpp>
#include <AL/al.h>
#include <AL/alc.h>
#include <vector>
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <SDL/SDL.h>
#include <glm/gtc/type_ptr.hpp>

class Audio {
private:
    struct SoundData {
        unsigned int sourceID;
        unsigned int bufferID;
        std::string name;

        SoundData(unsigned int sID, unsigned int bID, const std::string& n)
            : sourceID(sID), bufferID(bID), name(n) {}
    };

    struct Vector3 {
        float x, y, z;
    };

    std::vector<SoundData> soundDatas;
    ALCcontext* context;
    ALCdevice* device;

    bool IsBigEndian();
    int ConvertToInt(char* buffer, int length);
    char* LoadWAV(const char* filename, int& channels, int& sampleRate, int& bitsPerSample, int& size);

public:
    Audio();
    ~Audio();

    unsigned int LoadSound(const char* filename);
    void DeleteSound(unsigned int id);
    void PlaySound(unsigned int id);
    void PlaySound(unsigned int id, const glm::vec3& pos);
    void StopSound(unsigned int id);
    void SetListener(const glm::vec3& pos, const glm::vec3& camLookAt);
};

