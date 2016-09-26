///////////////////////////////////////////////////////////////////
// Executive.cpp -Package for sending messages through sockets//
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
* This is the entry point for the application, Remote Code Management.
* It initiates a receiver, so that a peer can receive message.
* It initiates a sender and sendes message to another peer.
*
* Required Files:
* ---------------
*   MessageInterpreter.h Sender.h Receiver.h
*
* Public Interfaces:
* -----------------
*	int main(int argc,char *argv[])
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

#include"MessageInterpreter.h"
#include"Sender.h"
#include"Receiver.h"

using namespace Server;


int main(int argc,char *argv[])
{
	int port = std::stoi(argv[1]);
	//std::cout << "The port is" << port;
	Receiver r(port);
	//Sender *s = new Sender();
	std::getchar();
	
}