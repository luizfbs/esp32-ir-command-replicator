#include <IRremote.hpp>

int SERIAL_SPEED = 9600;
int IR_RECEIVE_PIN = 15;
int IR_SEND_PIN = 23;
int IR_SEND_DELAY = 100;

void setup() {
  Serial.begin(SERIAL_SPEED);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  IrSender.begin(IR_SEND_PIN); 
}

void sendCommand(String label, uint16_t command){
  Serial.println(label);
  IrSender.sendSamsung(0x2C2C, command, 1);  
  delay(IR_SEND_DELAY);
  IrSender.sendSamsungLGRepeat();
  delay(IR_SEND_DELAY);
}

void loop() {
  if (IrReceiver.decode())
  {
    if(IrReceiver.decodedIRData.protocol == NEC) {
      switch(IrReceiver.decodedIRData.command){
        case (2): {
            sendCommand("Volume up", 0x17);            
            break;        
        }
        case (3): {
            sendCommand("Volume down", 0x16);   
            break;        
        }
        case (9): {
            sendCommand("Turn on/off (Mute)", 0x1E);
            break;        
        }
        case (8): {
            sendCommand("Turn on/off", 0x1E);
            break;        
        }
      } 
    } else {
      Serial.println("Ops, the protocol is not NEC.");
    }
    
    IrReceiver.printIRResultShort(&Serial);
    IrReceiver.resume();
  }
}
