#include "GraphicsCard.h"

byte CGraphicsCard::ReceiveByteFrom(word Port)
{
    return Port;
}

void CGraphicsCard::SendByteTo(word Port, byte Value)
{
    exit(Value);
}

short CGraphicsCard::ReceiveWordFrom(word Port)
{
    return Port;
}

void CGraphicsCard::SendWordTo(word Port, short Value)
{

}
