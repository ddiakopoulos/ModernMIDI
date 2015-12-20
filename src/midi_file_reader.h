#pragma comment(user, "license")

#pragma once

#ifndef MODERNMIDI_SEQUENCE_H
#define MODERNMIDI_SEQUENCE_H

#include "modernmidi.h"
#include "midi_message.h"
#include "midi_event.h"

namespace mm 
{
// Read a MIDI-style variable-length integer (big-endian value in groups of 7 bits,
// with top bit set to signify that another byte follows). 
inline uint32_t read_variable_length(uint8_t const *& data)
{
    uint32_t result = 0;
    while (true) 
    {
        uint8_t b = *data++;
        if (b & 0x80) 
        {
            result += (b & 0x7F);
            result <<= 7;
        } 
        else 
        {
            return result + b; // b is the last byte
        }
    }
}
    
inline void read_bytes(std::vector<unsigned char> & buffer, uint8_t const *& data, int num)
{
    for (int i = 0; i < num; ++i)
        buffer.push_back(uint8_t(*data++));
}

inline uint16_t read_uint16_be(uint8_t const *& data)
{
    uint16_t result = int(*data++) << 8;
    result += int(*data++);
    return result;
}
    
inline uint32_t read_uint24_be(uint8_t const *& data)
{
    uint32_t result = int(*data++) << 16;
    result += int(*data++) << 8;
    result += int(*data++);
    return result;
}
    
inline uint32_t read_uint32_be(uint8_t const *& data)
{
    uint32_t result = int(*data++) << 24;
    result += int(*data++) << 16;
    result += int(*data++) << 8;
    result += int(*data++);
    return result;
}

class MidiFileReader 
{
    void parseInternal(const std::vector<uint8_t> & buffer);
public:

    MidiFileReader();
    ~MidiFileReader();
        
    void parse(const std::vector<uint8_t> & buffer);

    double getEndTime();
        
    float ticksPerBeat; // precision (number of ticks distinguishable per second)
    float startingTempo;
    
    bool useAbsoluteTicks = false;
    
    std::vector<MidiTrack> tracks;
};

} // mm

#endif
