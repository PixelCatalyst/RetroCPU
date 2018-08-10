#pragma once

#include <functional>

#include "Byte.h"

class Device
{
public:
    virtual byte ReceiveByteFrom(word port) = 0;
    virtual void SendByteTo(word port, byte value) = 0;
    virtual short ReceiveWordFrom(word port) = 0;
    virtual void SendWordTo(word port, short value) = 0;
};

struct DeviceRecord
{
    Device* device = nullptr;
    word port = 0;
    bool isRightBound = false;
};
