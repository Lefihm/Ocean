
#include "convert.hpp"
//
void sonar::convert::allocatebuffer(std::string name, IPLAudioBuffer &buff){

    IPLAudioBuffer* buffer = &buff;
    IPLerror err =iplAudioBufferAllocate(*sonar::steamaudio::context, buffer->numChannels, buffer->numSamples, buffer);
    sonar::audioerror(err);
    sonar::global_audio_context::tmpbuffer[name.c_str()] = Ref<IPLAudioBuffer>(buffer);

}
//
//places it out on the outbuffer
void sonar::convert::deinterleave(std::string name, float* indata, int channels, int samples){
    IPLAudioBuffer* buffer = new IPLAudioBuffer;
    buffer->numChannels = channels;
    buffer->numSamples = samples;

    Ref temp = Ref<IPLAudioBuffer>(buffer);
    sonar::global_audio_context::outbuffer[name.c_str()] =temp;
    iplAudioBufferDeinterleave(*sonar::steamaudio::context, indata, temp.get());
}
//places it out on the outbuffer
void sonar::convert::deinterleave(std::string name, float* indata, IPLAudioBuffer* buff){
    Ref temp = Ref<IPLAudioBuffer>(buff);

    sonar::global_audio_context::outbuffer[name.c_str()] = temp;
    iplAudioBufferDeinterleave(*sonar::steamaudio::context, indata, temp.get());
}
//places it on the inbuffer
void sonar::convert::interleave(std::string name, float* outdata){
        
    iplAudioBufferInterleave(*sonar::steamaudio::context, sonar::global_audio_context::inbuffers[name.c_str()].get(), outdata);

}
