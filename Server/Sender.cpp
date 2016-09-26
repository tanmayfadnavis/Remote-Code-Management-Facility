///////////////////////////////////////////////////////////////////
// Sender.cpp -Package for sending messages through Sockets		//
// version 1.0													//
// Language:    Visual C++, Visual Studio 2013                   //
// Platform:    Lenovo V570, Core i5, Windows 7 SP2	              //
// Application: Object Oriented Design,Project-4 2015             //
// Author:      Tanmay Fadnavis, Syracuse University				//
//				315-560-3370, tfadnavi@syr.edu						//
////////////////////////////////////////////////////////////////////// 
///////////////////////////////////////////////////////////////////

#include"Sender.h"
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
#include "FileSystem.h"

using namespace Server;
using namespace FileSystem;

//----------------<Default constructor, starts the sender thread on the sender queue>----------------
Sender::Sender()
{
	Verbose v(true);
	std::thread sendThread(&Sender::sendMessage,this);
	sendThread.detach();
}

//---------------<Function used by the client to send messages>----------------------------
void Sender::send(MessageInterpreter& msg)
{
	//std::string s = msg.toString();
	//std::cout << s;
	senderQue.enQ(msg);
	//sendMessage();
}

//--------------------------< Function which sends the message/File to the peer>------------------------
void Sender::sendMessage()
{
	do{
		try
		{
			MessageInterpreter msg = senderQue.deQ();
			std::map<std::string, std::string> message = msg.getMessage();
			if (message["commandType"] == "File_Download")
			{
				if (connect(std::stoi(message["senderPort"])))	//Connected to the peer.
				{
					if (sendFile(msg))
					{
						Verbose::show("File:" + msg.getMessage()["filePath"] + " Sent from Server: ");
					}
				}
				else
				{
					Verbose::show("Connection Failed");
				}
			}
			else
			{
				if (connect(std::stoi(message["senderPort"])))
				{
					sendHeader(msg);
					Verbose::show("sent from the server response.");
				}
				else
				{
					Verbose::show("Connection Failed");
				}
			}
		}
		catch (std::exception ex)
		{
			std::string s = ex.what();
			Verbose::show("\n In send Thread: " + s);
		}
	} while (1);
}

//---------------------------<Function to connect to the peer>-------------------------------
bool Sender::connect(int port)
{
	while (!si.connect("localhost", port))
	{
		Verbose::show("client waiting to connect");
		::Sleep(100);
	}
	return true;

}

//----------------------------<Function to send the header to the peer>------------------------
bool Sender::sendHeader(MessageInterpreter& msg)
{
	//std::cout << "IN SEND HEADRER\n";
	for (auto iterator : msg.getMessage())
	{
		std::string str = "";
		str += iterator.first + ":" + iterator.second;
		si.sendString(str, '\n');
	}
	si.sendString("\n", '\n');
	return true;
}




//----------------------<Function to send the file to the peer>-----------------------------
bool Sender::sendFile(MessageInterpreter& msg)
{
	//std::cout << "In send file\n";
	std::string path = msg.getMessage()["filePath"];
	FileSystem::FileInfo fileInfo(path);
	std::string name;
	if (fileInfo.good())
		name = fileInfo.name();
	else
	{
		Verbose::show("\nFile to be uploaded is not accessible!\n");
		return false;
	}
	Socket::byte maxBuffer[500];
	std::streamoff bytesRead;
	std::ifstream file(msg.getMessage()["filePath"], std::ios::in | std::ios::binary);
	if (file.is_open())
	{
		file.seekg(0, std::ios::end);
		std::streamoff remainingBytes = file.tellg();
		file.seekg(0, std::ios::beg);
		while (file.good())
		{

			file.read(maxBuffer, min(500, remainingBytes));
			bytesRead = min(500, remainingBytes);
			msg.setContentLength((int)bytesRead);
			msg.setFilePath(name);
			//msg.getMessage()["contentLength"] = (int)bytesRead;
			//msg.getMessage()["filePath"] = name;
			sendHeader(msg);
			si.send((size_t)bytesRead, maxBuffer);
			remainingBytes -= bytesRead;
			if (bytesRead < 500)
				break;
		}
		file.close();
		return true;
	}
	return false;
}

#ifdef TEST_SENDER
int main()
{
	Sender *s();
	MessageInterpreter msg("File_Upload","9080","9081","../ClientFiles/Testing.txt");
	s->send(msg);
	s->connect(9080);
	s->sendMessage(msg);
}


#endif