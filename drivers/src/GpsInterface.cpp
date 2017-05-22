
#include "GpsInterface.h"

GpsInterface::GpsInterface()
{
    //Set this to the file to which the GPS is mounted to
    string device = "/dev/ttyACM0";
    //open file ifstrem to GPS device
    msgStream.open(device);

}

GpsInterface::GpsInterface(std::string device)
{
    //open ifstream to GPS device
    msgStream.open(device);
}

void GpsInterface::storeData()
{
    union bit16_Data {
        uint16_t l;
        char msg[2];
    }

    bit16_Data msgID;
    bit16_Data msgLen.i = 0;

    syncMsg();
    
    //get id fields
    msgStream.get(msgID.msg[0]);
    msgStream.get(msgID.msg[1]);

    //get msg length
    msgStream.get(msgLen.msg[0]);
    msgStream.get(msgLen.msg[1]);
    
    switch (msgID.i)
    {
        case 257:
            msgStream(msg[0], msgLen.i);
            break;
    }

}

int* GpsInterface::getECEFPOS()
{
    union posData {
        int data[3];
        char db[12];
    }

    posData position;

    for(int i = 0; i < 12; i++) {
        postition[i] = msg[0][i];
    }

    return postition.data;
}

void GpsInterface::syncMsg()
{
    char h[2];

    while(1)
    {
        msgStream.get(h[0]);
        if(h[0] == msgHeader[0])
        {
            msgStream.get(h[1]);
            if(h[1] == msgHeader[1])
            {
                return;
            }
        }
    }
}

