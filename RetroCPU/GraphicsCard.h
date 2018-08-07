#pragma once

#include "Device.h"

class CGraphicsCard : public IDevice
{
private:
public:
	byte ReceiveByteFrom(word Port);
	void SendByteTo(word Port, byte Value);
	short ReceiveWordFrom(word Port);
	void SendWordTo(word Port, short Value);
};