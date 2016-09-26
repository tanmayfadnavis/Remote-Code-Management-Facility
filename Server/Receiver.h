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
* Public Interfaces:
* -----------------
*
*	Receiver(int port);
*	void enqueue(MessageInterpreter);
*	bool textSearch(const std::string& filespec, const std::string& searchText);
*	std::string fileSearch(std::map<std::string, std::string> m);
*	std::string textSrc(std::map<std::string, std::string> m);
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
#include"Cpp11-BlockingQueue.h"
#include"Sockets.h"
#include"AppHelpers.h"
#include"MessageInterpreter.h"
#include"ClientHandler.h"
#include<iostream>

namespace Server
{
	class Receiver
	{
	public:
		Receiver();
		Receiver(int port);
		void receiverMessage();
		void enqueue(MessageInterpreter);
		bool textSearch(const std::string& filespec, const std::string& searchText);
		std::string fileSearch(std::map<std::string, std::string> m);
		std::string textSrc(std::map<std::string, std::string> m);
	private:
		//Verbose v(true);

		SocketSystem ss;
		SocketListener *sl;
		//SocketConnecter si; 
		//ClientHandler cp;
		BlockingQueue<MessageInterpreter> receiverQue;

	};
}

#endif