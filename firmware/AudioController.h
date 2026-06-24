#ifndef AUDIO_CONTROLLER_H
#define AUDIO_CONTROLLER_H

#include <Arduino.h>
#include <SoftwareSerial.h>

class AudioController {
private:
    uint8_t rxPin;
    uint8_t txPin;
    SoftwareSerial audioSerial;
    
    void sendCommand(uint8_t command, uint8_t parameterMSB, uint8_t parameterLSB);
    void sendCommand(uint8_t command, uint16_t parameter);

public:
    AudioController(uint8_t rx, uint8_t tx);
    void begin();
    void setVolume(uint8_t volume); // Volume range 0 to 30
    void playTrack(uint16_t folderNumber, uint16_t trackNumber);
    void stop();
    void reset();
};

#endif
