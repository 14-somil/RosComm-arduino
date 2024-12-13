# RosComm

## Setup Instruction 
Clone the the repo in your `Arduino/libraries` folder.

## Example code

```cpp
#include <RosComm>

RosComm node(115200);

JsonDocument msgToSend;
msgToSend["data"] = "Hello";

JsonDocument msgToRecieve;
msgToRecieve["data"] = 1200;

void setup() {
    node.initPublisher(msgToSend);
    node.initSubsriber(msgToRecieve);
}

void loop() {
    node.spin();

    msgToSend["data"] = "New data";
    node.publish(msgToSend);

    msgToRecieve = node.getRecievedMessage();
}
```