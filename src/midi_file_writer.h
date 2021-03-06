/*
Copyright (c) 2015, Dimitri Diakopoulos All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#pragma once

#ifndef MODERNMIDI_FILE_IO_H
#define MODERNMIDI_FILE_IO_H

#include "modernmidi.h"
#include "midi_message.h"
#include "midi_event.h"
#include <stdint.h>

namespace mm
{
  
class MidiFileWriter
{
    std::vector<MidiTrack> tracks;
    int ticksPerQuarterNote = 120;

public:

    MidiFileWriter();
    ~MidiFileWriter();

    size_t getNumTracks() { return tracks.size(); }
    int getTicksPerQuarterNote() { return ticksPerQuarterNote; }

    void addEvent(int tick, int track, std::shared_ptr<MidiMessage> m);
    void addEvent(int track, std::shared_ptr<TrackEvent> m);
    
    void setTicksPerQuarterNote(int tpqn) { ticksPerQuarterNote = tpqn; }
    
    void addTrack(); 

    void write(std::ostream & out);
    
    std::vector<MidiTrack> & getTracks() { return tracks; }
    
    bool useAbsoluteTicks = false;
    
};
    
} // mm

#endif