#include "AudioController.h"

AudioController::AudioController(uint8_t rx, uint8_t tx)
    : rxPin(rx), 
      txPin(tx), 
      audioSerial(rx, tx) {}

void AudioController::begin() {
    audioSerial.begin(9600);
    delay(500); // Wait for DFPlayer boot sequence
    reset();
    delay(500); // Wait for reset stabilization
}

void AudioController::sendCommand(uint8_t command, uint8_t parameterMSB, uint8_t parameterLSB) {
    // DFPlayer standard 10-byte serial packet structure
    uint8_t packet[10];
    packet[0] = 0x7E; // Start Byte
    packet[1] = 0xFF; // Version Info
    packet[2] = 0x06; // Data Length (excluding start/end bytes)
    packet[3] = command;
    packet[4] = 0x00; // Feedback flag (0x00 = No Feedback)
    packet[5] = parameterMSB;
    packet[6] = parameterLSB;
    
    // Checksum calculation: - (Version + Length + Command + Feedback + ParameterMSB + ParameterLSB)
    uint16_t checksum = 0 - (packet[1] + packet[2] + packet[3] + packet[4] + packet[5] + packet[6]);
    packet[7] = (uint8_t)(checksum >> 8);   // Checksum High Byte
    packet[8] = (uint8_t)(checksum & 0xFF);  // Checksum Low Byte
    packet[9] = 0xEF; // End Byte

    for (uint8_t i = 0; i < 10; i++) {
        audioSerial.write(packet[i]);
    }
}

void AudioController::sendCommand(uint8_t command, uint16_t parameter) {
    uint8_t msb = (uint8_t)(parameter >> 8);
    uint8_t lsb = (uint8_t)(parameter & 0xFF);
    sendCommand(command, msb, lsb);
}

void AudioController::setVolume(uint8_t volume) {
    volume = constrain(volume, 0, 30);
    sendCommand(0x06, 0, volume);
}

void AudioController::playTrack(uint16_t folderNumber, uint16_t trackNumber) {
    // 0x0F is the DFPlayer command to play a file from a specific folder
    sendCommand(0x0F, (uint8_t)folderNumber, (uint8_t)trackNumber);
}

void AudioController::stop() {
    sendCommand(0x16, 0, 0); // 0x16 = Pause / Stop command
}

void AudioController::reset() {
    sendCommand(0x0C, 0, 0); // 0x0C = Reset module command
}
