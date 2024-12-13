#include "RosComm.h"

RosComm::RosComm() {
    Serial.begin(_baud);
    Serial.setTimeout(1000);
}

RosComm::RosComm(int baud): _baud(baud) {
    Serial.begin(_baud);
    Serial.setTimeout(1000);
}

void RosComm::initPublisher(JsonDocument& msgToSend) {
    _msgTypeSent = msgToSend;
}

void RosComm::publish(JsonDocument& msgToSend) {
    
    //checking for same keys
    for(JsonPair kv : _msgTypeSent.as<JsonObject>())
    {
        const char* key = kv.key().c_str();

        if(!msgToSend.containsKey(key)) return;
    }

    for(JsonPair kv : msgToSend.as<JsonObject>())
    {
        const char* key = kv.key().c_str();

        if(!_msgTypeSent.containsKey(key)) return;
    }

    serializeJson(msgToSend, Serial);
}

void RosComm::initSubscriber(JsonDocument& msgToRecieve) {
    _msgTypeRecieved = msgToRecieve;
}

void RosComm::spin() {
    char * recievedString;
    Serial.readBytes(recievedString, _buffer);
    JsonDocument doc;

    if(deserializeJson(doc, recievedString)) return;

    for(JsonPair kv : _msgTypeRecieved.as<JsonObject>())
    {
        const char* key = kv.key().c_str();

        if(!doc.containsKey(key)) return;
    }

    for(JsonPair kv : doc.as<JsonObject>())
    {
        const char* key = kv.key().c_str();

        if(!_msgTypeRecieved.containsKey(key)) return;
    }

    _msgTypeRecieved = doc;
}

JsonDocument& RosComm::getRecievedMessage() {
    return _msgTypeRecieved;
}