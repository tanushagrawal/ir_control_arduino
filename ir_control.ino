#include <IRremote.h>
#include <IRremoteInt.h>

//#include<iostream.h>
int RECV_PIN = 3; //declared for receiving pulses
int c = 0;        // declared if you want to control with a single button
IRrecv irrecv(RECV_PIN);
bool on = false;
decode_results results;

class Led
{

public:
  int pin;
  unsigned long ir_code;
  bool isOn;
  Led(int pin, unsigned long ir_code)
  {
    this->pin = pin;
    this->ir_code = ir_code;
    this->isOn = false;
  }
};

Led leds[] = {Led(13, 3772784863), Led(12, 3772817503), Led(11, 3772801183), Led(10, 3772780783), Led(9, 3772813423)};

void setup()
{
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  Serial.begin(9600);
  irrecv.enableIRIn();
  //  Serial.println(led1.ir_code);
  // Start the receiver
}

void loop()
{

  if (irrecv.decode(&results))
  {
    if (leds[0].isOn == true || leds[1].isOn == true || leds[2].isOn == true || leds[3].isOn == true || leds[4].isOn == true)
    {
      on = true;
    }
    else if (leds[0].isOn == false && leds[1].isOn == false && leds[2].isOn == false && leds[3].isOn == false && leds[4].isOn == false)
    {
      on = false;
    }

    Serial.println(results.value);
    delay(500);
    irrecv.resume();

    for (int i = 0; i < 5; i++)
    {
      if (results.value == leds[i].ir_code)
      {

        if (leds[i].isOn == false)
        {
          digitalWrite(leds[i].pin, HIGH);
          leds[i].isOn = true;
        }

        else
        {
          digitalWrite(leds[i].pin, LOW);
          leds[i].isOn = false;
        }
      }
    };

    if (results.value == 3772793023)
    {
      if (on)
      {
        for (int i = 0; i < 5; i++)
        {
          digitalWrite(leds[i].pin, LOW);
          leds[i].isOn = false;
        };
      }

      else
      {
        for (int i = 0; i < 5; i++)
        {
          digitalWrite(leds[i].pin, HIGH);
          leds[i].isOn = true;
        };
      }
    }
  }
}