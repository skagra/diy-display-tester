#include <Arduino.h>
#line 1 "E:\\Development\\diy-display-tester\\diy-display-tester.ino"
#define PIN_INTERRUPT 2
#define PIN_ADDR_LOW 3
#define PIN_ADDR_HIGH 4
#define PIN_VAL_MIN 5
#define PIN_VAL_MAX 12

#define OP_VALUE_ONE 0x00
#define OP_VALUE_TWO 0x01
#define OP_MESSAGE 0x02

#line 11 "E:\\Development\\diy-display-tester\\diy-display-tester.ino"
void setup();
#line 23 "E:\\Development\\diy-display-tester\\diy-display-tester.ino"
void pulseClock();
#line 32 "E:\\Development\\diy-display-tester\\diy-display-tester.ino"
void setAddr(byte addr);
#line 38 "E:\\Development\\diy-display-tester\\diy-display-tester.ino"
void setVal(byte val);
#line 47 "E:\\Development\\diy-display-tester\\diy-display-tester.ino"
void doWriteByteVal(byte val, byte op);
#line 55 "E:\\Development\\diy-display-tester\\diy-display-tester.ino"
void doWriteString(const char *val);
#line 64 "E:\\Development\\diy-display-tester\\diy-display-tester.ino"
void loop();
#line 11 "E:\\Development\\diy-display-tester\\diy-display-tester.ino"
void setup()
{
    Serial.begin(9600);
    pinMode(PIN_INTERRUPT, OUTPUT);
    pinMode(PIN_ADDR_LOW, OUTPUT);
    pinMode(PIN_ADDR_HIGH, OUTPUT);
    for (byte pin = PIN_VAL_MIN; pin <= PIN_VAL_MAX; pin++)
    {
        pinMode(pin, OUTPUT);
    }
}

void pulseClock()
{
    digitalWrite(PIN_INTERRUPT, LOW);
    delay(1);
    digitalWrite(PIN_INTERRUPT, HIGH);
    delay(1);
    digitalWrite(PIN_INTERRUPT, LOW);
}

void setAddr(byte addr)
{
    digitalWrite(PIN_ADDR_LOW, (addr & 0x01) ? HIGH : LOW);
    digitalWrite(PIN_ADDR_HIGH, ((addr >> 1) & 0x01) ? HIGH : LOW);
}

void setVal(byte val)
{
    for (byte pin = PIN_VAL_MIN; pin <= PIN_VAL_MAX; pin++)
    {
        digitalWrite(pin, (val & 0x01) ? HIGH : LOW);
        val >>= 1;
    }
}

void doWriteByteVal(byte val, byte op)
{
    setAddr(op);
    setVal(val);
    pulseClock();
    delay(50);
}

void doWriteString(const char *val)
{
    while (*val != 0)
    {
        doWriteByteVal(*val, OP_MESSAGE);
        val++;
    }
}

void loop()
{
    doWriteByteVal(0, OP_VALUE_ONE);
    doWriteByteVal(0, OP_VALUE_TWO);

    doWriteString("Testing message ... ");
    delay(1000);
    for (byte letter = 'A'; letter <= 'z'; letter++)
    {
        doWriteByteVal(letter, OP_MESSAGE);
    }
    doWriteString(" ... done. ");
    delay(1000);

    doWriteString("Testing value 1... ");
    delay(1000);
    for (int val1 = 0; val1 <= 255; val1++)
    {
        doWriteByteVal(val1, OP_VALUE_ONE);
    }
    doWriteString("done. ");
    delay(1000);

    doWriteString("Testing value 2... ");
    for (int val2 = 0; val2 <= 255; val2++)
    {
        doWriteByteVal(val2, OP_VALUE_TWO);
    }
    doWriteString("done. ");
    delay(1000);
}

