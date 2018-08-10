#include "GraphicsCard.h"

byte GraphicsCard::ReceiveByteFrom(word port)
{
    return port;
}

void GraphicsCard::SendByteTo(word port, byte value)
{
    exit(value);
}

short GraphicsCard::ReceiveWordFrom(word port)
{
    return port;
}

void GraphicsCard::SendWordTo(word port, short value)
{

}
