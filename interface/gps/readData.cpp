



#include <iostream>
#include <unistd.h>
#include <fstream>
//#include <ios.h>

int getHeader(char *header, std::ifstream& stream);

char printASCII(std::ifstream& stream);

int main(int argc, char* argv[])
{
   char msgHeader[1] = {0xB5};
   char msgID[2];
   char msgLength[1];
   char *msg;

   std::ifstream msgStream;

   msgStream.open("/dev/ttyACM0");

   int m = 0;

   for(;;)
   {

	  getHeader(msgHeader, msgStream);
  	  //msgStream.read(msgHeader, 2);
 			  
	  std::cout << "message " << m++ << std::endl;

          //std::cout << (char) (msgHeader[1]) << (char) (msgHeader[2]) << "  ";
 
	  //if((unsigned int) msgHeader[1] == 0xB || msgHeader[2] == 0xB)
	  //{
	  //	std::cout << "\n" << std::endl;	  
          //}
   }



}


int getHeader(char *header, std::ifstream& stream)
{
    char h[1];

    while(1)
    {
        stream.get(h[0]);
	
	if(h[0] == header[0])
	{
    	   return 1;
	}
	
    }
}

char* getID(std::ifstream& stream)
{
   char c;

   stream.get(c);

   switch(c)
   {


   }

}

void getData()
{


}
