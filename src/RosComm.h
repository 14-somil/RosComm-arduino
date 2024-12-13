#ifndef ROSCOMM_H
#define ROSCOMM_H   

#include <Arduino.h>
#include <ArduinoJson.h>

class RosComm{
    private:
        int _baud = 115200;
        JsonDocument _msgTypeSent;
        JsonDocument _msgTypeRecieved;
        int _buffer = 256;

    public:
        RosComm();
        RosComm(int baud);
        void initPublisher(JsonDocument& msgToSend);
        void publish(JsonDocument& msgToSend);
        void initSubscriber(JsonDocument& msgToRecieve);
        void spin();
        JsonDocument getRecievedMessage();
};

#endif