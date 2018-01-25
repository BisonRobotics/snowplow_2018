



#include <iostream>
#include <unistd.h>
#include <fstream>


int getHeader(char *header, std::ifstream& stream);

char printASCII(std::ifstream& stream);

union data16
{
   uint16_t i;
   char[2] msg;
};

union ECEF_data {
    int data[4];
    char msg[16];
};


int main(int argc, char* argv[])
{
   const char msgHeader[] = {0xB5, 0x62};
   char msgID[2];
   data16 msgLength;
   ECEF_Data posData;
   char *msg;
   char chkSum;

   std::ifstream msgStream;

   msgStream.open("/dev/ttyACM0");

   int m = 0;

   for(;;)
   {

	 getHeader(msgHeader, msgStream)

	 std::cout << "message " << m++ << std::endl;
         
         msgStream.get(msgID[0]);
         msgStream.get(msgID[1]);

         msgStream.get(msgLength.msg[0]);
         msgStream.get(msgLength.msg[1]);

         msgStream.read(posData, 16);

         for(int i = 1; i < 4; i++) 
         { // change encoding of integers
                ECEF_Data datum;
                datum.data = posData.data[i];

                datum.db[3] = datum.db[3] ^ datum.db[0];
                datum.db[0] = datum.db[3] ^ datum.db[0];
                datum.db[3] = datum.db[3] ^ datum.db[0];

                datum.db[2] = datum.db[2] ^ datum.db[1];
                datum.db[1] = datum.db[2] ^ datum.db[1];
                datum.db[2] = datum.db[2] ^ datum.db[1];

                myMsg.data[i] = datum.data;
          }

          msgStream.get(chkSum);

   }



}


int getHeader(char *header, std::ifstream& stream)
{
    //sync message

    char h[2];

    while(1)
    {
        stream.get(h[0]);

	if(h[0] == header[0])
	{
           stream.get(h[1]);
    	   if(h[1] == header[1])
           {
	       return 1;
	   }
	}

    }
}

void ecefPOS()
{


}
