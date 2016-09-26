#ifndef RECEIVER_H
#define RECEIVER_H

///////////////////////////////////////////////////////////////////
// Receiver.h -Package for receiving messages through sockets//
// Ver 1.0                                                      //
// Language:    Visual C++, Visual Studio 2013					//
// Platform:    Lenovo V570, Core i5, Windows 7 SP2	           //
// Application: Object Oriented Design,Project-4 2015          //
// Author:      Tanmay Fadnavis, Syracuse University		   //
//				315-560-3370, tfadnavi@syr.edu				  //
// Date: 25/04/2015											//
///////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package is intended to initialize the client handler and socket.
*
* Required Files:
* ---------------
* Sockets.h AppHelpers.h WindowsHelpers.h MessageInterpreter.h
* Cpp11-BlockingQueue.h ClientHandler.h Receiver.h Receiver.cpp
* MockChannel.h
* Public Interfaces:
* -----------------
*
*	Receiver(int port);
*   void enqueue(MessageInterpreter msg);
*
* Build Process:
* --------------
*   devenv CppCli-WPF-App.sln /debug rebuild
*
* Maintenance History:
* --------------------
*
* Ver 1.0 : 25 April 15
* - first release
*/

#include "MockChannel.h"
#include "Cpp11-BlockingQueue.h"
#include "Sockets.h"
#include "MessageInterpreter.h"
#include"ClientHandler.h"
#include <string>
#include <thread>
#include <iostream>
#include <mutex>
#include<ostream>
#include<fstream>
#include<sstream>
#include<exception>

namespace Client
{
	class Recvr : public IRecvr
	{
	public:
		std::string getMessage();
		//BQueue& queue();
		void enqueue(MessageInterpreter msg);
		Recvr(int port);
		Recvr();
		void operator()(Socket& socket_);
		MessageInterpreter receiveHeader(Socket& socket_);

		//Recvr(MessageInterpreter);
	private:

		SocketSystem ss;
		SocketListener *sl;
		BlockingQueue<MessageInterpreter> recvQ_;
		//ClientHandler cp;
		//SocketConnecter si; 
		
	};
}

#endif