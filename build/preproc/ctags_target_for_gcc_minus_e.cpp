# 1 "E:\\Development\\diy-display-tester\\diy-display-tester.ino"
# 11 "E:\\Development\\diy-display-tester\\diy-display-tester.ino"
void setup()
{
    Serial.begin(9600);
    pinMode(2, 0x1);
    pinMode(3, 0x1);
    pinMode(4, 0x1);
    for (byte pin = 5; pin <= 12; pin++)
    {
        pinMode(pin, 0x1);
    }
}

void pulseClock()
{
    digitalWrite(2, 0x0);
    delay(1);
    digitalWrite(2, 0x1);
    delay(1);
    digitalWrite(2, 0x0);
}

void setAddr(byte addr)
{
    digitalWrite(3, (addr & 0x01) ? 0x1 : 0x0);
    digitalWrite(4, ((addr >> 1) & 0x01) ? 0x1 : 0x0);
}

void setVal(byte val)
{
    for (byte pin = 5; pin <= 12; pin++)
    {
        digitalWrite(pin, (val & 0x01) ? 0x1 : 0x0);
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
        doWriteByteVal(*val, 0x02);
        val++;
    }
}

void loop()
{
    doWriteByteVal(0, 0x00);
    doWriteByteVal(0, 0x01);

    doWriteString("Testing message ... ");
    delay(1000);
    for (byte letter = 'A'; letter <= 'z'; letter++)
    {
        doWriteByteVal(letter, 0x02);
    }
    doWriteString(" ... done. ");
    delay(1000);

    doWriteString("Testing value 1... ");
    delay(1000);
    for (int val1 = 0; val1 <= 255; val1++)
    {
        doWriteByteVal(val1, 0x00);
    }
    doWriteString("done. ");
    delay(1000);

    doWriteString("Testing value 2... ");
    for (int val2 = 0; val2 <= 255; val2++)
    {
        doWriteByteVal(val2, 0x01);
    }
    doWriteString("done. ");
    delay(1000);
}
