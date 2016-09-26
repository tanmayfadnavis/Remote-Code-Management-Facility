///////////////////////////////////////////////////////////////////
// ClientHandler.cpp -Package for Client Handler which is sent as a functor to socket //
// version 1.0													//
// Language:    Visual C++, Visual Studio 2013                   //
// Platform:    Lenovo V570, Core i5, Windows 7 SP2	              //
// Application: Object Oriented Design,Project-4 2015             //
// Author:      Tanmay Fadnavis, Syracuse University				//
//				315-560-3370, tfadnavi@syr.edu						//
////////////////////////////////////////////////////////////////////// 
///////////////////////////////////////////////////////////////////

#include"ClientHandler.h"
#include"AppHelpers.h"
#include"MessageInterpreter.h"
#include"Cpp11-BlockingQueue.h"
#include"FileSystem.h"
#include"Receiver.h"
#include <iostream>
#include <thread>
#include <mutex>
#include<string>
#include<ostream>
#include<fstream>
#include<sstream>
#include<exception>

using namespace ApplicationHelpers;
using namespace FileSystem;
using namespace Server;

//--------------------------------------<Parameterized Constructor>--------------------------------------
ClientHandler::ClientHandler(Receiver* rev)
{
	myReceiver = rev;
}

//----------------<Function which will be called whenever Receiver initializes a socket>---------------------
void ClientHandler::operator()(Socket& socket_)
{
	Verbose v(true);
	try
	{
		std::cout << "In client handler";
		while (true)
		{
			MessageInterpreter msg = receiveHeader(socket_);

			if (msg.getMessage()["commandType"] == "File_Upload")
			{
				std::cout << "In File Upload";
				if (receiveFile(msg, socket_))
				{
					myReceiver->enqueue(msg);
					Verbose::show("File:"+msg.getMessage()["filePath"]+" Uploaded Successfully at path /DownloadedFiles  on Peer:"+msg.getMessage()["receiverPort"]+" Received From Peer:"+msg.getMessage()["senderPort"] +"\n");
				}
				else
					Verbose::show("\nFile Upload Failed!\n");
			}
			else if (msg.getMessage()["commandType"] == "File_Search")
			{
				std::cout << "In File Search";
				myReceiver->enqueue(msg);
			}
			else if (msg.getMessage()["commandType"] == "Text_Search")
			{
				std::cout << "In Text Search";
				myReceiver->enqueue(msg);
			}
			else if (msg.getMessage()["commandType"] == "File_Download")
			{
				std::cout << "In File Download";
				myReceiver->enqueue(msg);
			}
		}
	}
	catch (std::exception ex)
	{
		std::string s = ex.what();
		Verbose::show("\n In Client Handler: " + s);
	}
}

//------------------------< Function to receiver the header>------------------------------
MessageInterpreter ClientHandler::receiveHeader(Socket& s)
{
	std::vector<std::string> parts;

	while (true)
	{
		std::string command = s.recvString('\n');
		if (command == "\n" || command.size() == 0)
		{
			command = s.recvString('\n');
			break;			
		}
		parts.push_back(command);
	}

	MessageInterpreter msg;
	msg.buildMessage(parts);
	return msg;
}

//----------------------------<Function to receive the file and save it>----------------------
bool ClientHandler::receiveFile(MessageInterpreter msg,Socket& s)
{
	std::string path = "../Server/DownloadedFiles/";
	std::ofstream file(path + msg.getMessage()["filePath"], std::ios::binary);
	Socket::byte maxBuffer[500];
	size_t msgLength = 500;
	msgLength = std::stoi(msg.getMessage()["contentLength"]);
	bool flag;
	if (s.bytesWaiting() == 0)
	{
		return false;
	}
	while (true)
	{
		flag = s.recv(msgLength, maxBuffer);

		if (s == INVALID_SOCKET || !flag)
			return false;

		file.write(maxBuffer, msgLength);

		if (msgLength < 500)
		{
			file.close();
			return true;
		}
		else if (s.bytesWaiting() != 0)
		{
			msg = receiveHeader(s);
			msgLength = std::stoi(msg.getMessage()["contentLength"]);
		}
	}
	return false;
}

#ifdef TEST_CLIENTHANDLER

int main()
{
	Receiver r(9080);
	MessageInterpreter msg("File_Upload","9080","9081","../Client/Testing");
	Sender s;
	s.send(msg);
}

#endif
