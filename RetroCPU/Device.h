#pragma once

#include <functional>

#include "Byte.h"

class IDevice
{
public:
    virtual byte ReceiveByteFrom(word Port) = 0;
    virtual void SendByteTo(word Port, byte Value) = 0;
    virtual short ReceiveWordFrom(word Port) = 0;
    virtual void SendWordTo(word Port, short Value) = 0;
};

struct DeviceRecord
{
    IDevice* pDevice = nullptr;
    word Port = 0;
    bool IsRightBound = false;
};
