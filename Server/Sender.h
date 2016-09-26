#ifndef SENDER_H
#define SENDER_H

///////////////////////////////////////////////////////////////////
// Sender.h -Package for sending messages through sockets//
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
* This package is intended to send the messages through sockets.
*
* Required Files:
* ---------------
*   MessageInterpreter.h Cpp11-BlockingQueue.h
*   AppHelpers.h Sockets.h Sender.h Sender.cpp
*
* Public Interfaces:
* -----------------
*	Sender();
*	void send(MessageInterpreter& msg);
*	void sendMessage();
*	bool sendHeader(MessageInterpreter& msg);
*	bool sendFile(MessageInterpreter& msg);
*	bool connect(int portNo);
*	bool disconnect();
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

#include"Sockets.h"
#include"AppHelpers.h"

#include"MessageInterpreter.h"
#include"Cpp11-BlockingQueue.h"

#include<string>

using namespace ApplicationHelpers;

namespace Server
{
	class Sender
	{
	public:
		Sender();
		void send(MessageInterpreter& msg);
		void sendMessage();
		bool sendHeader(MessageInterpreter& msg);
		bool sendFile(MessageInterpreter& msg);
		bool connect(int portNo);
		bool disconnect();

	private:

		SocketSystem ss;
		SocketConnecter si;
		BlockingQueue<MessageInterpreter> senderQue;


	};
}

#endif