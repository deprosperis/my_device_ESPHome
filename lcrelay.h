#include "esphome.h"

using namespace esphome;
 
class LCRelay : public Component, public UARTDevice, public switch_::Switch {
 
 public:
    int relayId;
    LCRelay(UARTComponent *parent, int relay): UARTDevice(parent) {
        relayId = relay;
    }
 
  void setup() override {
 
  }
 
  void write_state(bool state) override {
    uint8_t msg[4];
    msg[0] = 0xA0;
    msg[1] = relayId;
    msg[2] = state;
    msg[3] = msg[0] + msg[1] + msg[2];
    /* There are no ack/nack packets. 
       Let's send the payload twice to be sure */
    this-&gt;write_array(msg, sizeof(msg));
    this-&gt;write_array(msg, sizeof(msg));
    publish_state(state);    
  }
};

