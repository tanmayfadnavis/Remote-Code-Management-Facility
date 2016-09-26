///////////////////////////////////////////////////////////////////
// Receiver.cpp -Package for receiving messages through Sockets		//
// version 1.0													//
// Language:    Visual C++, Visual Studio 2013                   //
// Platform:    Lenovo V570, Core i5, Windows 7 SP2	              //
// Application: Object Oriented Design,Project-4 2015             //
// Author:      Tanmay Fadnavis, Syracuse University				//
//				315-560-3370, tfadnavi@syr.edu						//
////////////////////////////////////////////////////////////////////// 
///////////////////////////////////////////////////////////////////


#include"Receiver.h"
#include"ClientHandler.h"
#include <condition_variable>
#include <mutex>
#include <thread>
#include <queue>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include<ostream>
#include<fstream>
#include<exception>

using namespace ApplicationHelpers;
using namespace Client;

//------------------------------------------------------<Default Constructor>----------------------------------------
Recvr::Recvr()
{
	//std::thread dispatcher(&Recvr::getMessage, this);
	//dispatcher.detach();
}

//-----------------------------------------------------<Parameterized Constructor>-----------------------------------
Recvr::Recvr(int port)
{
	std::cout << "Client starting for port" << port;
	Verbose v(true);
	//SocketSystem ss;
	//SocketListener sl(port, Socket::IP4);

	//ClientHandler cp(this);
	
  ClientHandler	*cp = new ClientHandler(this);

	sl = new SocketListener(port, Socket::IP6);

	sl->start(*cp);


}

//-------------------------------------------------------<Function to dequeue messages from the queue>---------------------------
std::string Recvr::getMessage()
{
	do{
		std::cout << "In get message func\n";
		return recvQ_.deQ().getMessage()["filePath"];
	} while (1);
}

//----------------------------------------------------------<Function to enqueue messages to the queue>-------------------------
void Recvr::enqueue(MessageInterpreter msg)
{
	recvQ_.enQ(msg);


}

#ifdef TEST_RECEIVER
int main()
{
	Receiver *r(9080);
	r->enqueue(Msg);
	std::string s=r->getmessage();
}
#endif