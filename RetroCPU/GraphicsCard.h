#pragma once

#include "Device.h"

class GraphicsCard : public Device
{
private:
public:
    byte ReceiveByteFrom(word port);
    void SendByteTo(word port, byte value);
    short ReceiveWordFrom(word port);
    void SendWordTo(word port, short value);
};
