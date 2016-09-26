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
#include"MessageInterpreter.h"
#include"Sender.h"
#include"FileManager.h"
#include"DataStore.h"
#include <condition_variable>
#include <mutex>
#include <thread>
#include <queue>
#include <string>
#include <iostream>
#include <sstream>
#include <thread>
#include <map>

using namespace ApplicationHelpers;
using namespace Server;

//--------------------------------------------------------<Default Constructor>---------------------------------------
Receiver::Receiver()
{
	
}

//--------------<The parameterized constructor for receiver. It takes the port number as input and initiates
//				 ClientHandler>---------------------------------------------------------------------------
Receiver::Receiver(int port)
{
	std::cout << "Receiver starting for port" << port;
	Verbose v(true);
	//SocketSystem ss;
	//SocketListener sl(port, Socket::IP4);

	ClientHandler *cp = new ClientHandler(this);
	
	sl = new SocketListener(port, Socket::IP6);

	sl->start(*cp);

	std::thread dispatcher(&Receiver::receiverMessage, this);
	dispatcher.detach();

}

//---------------------------------------------------<Function to dequeue the message from the queue/dispatcher>----------------
void Receiver::receiverMessage()
{
	Sender *s = new Sender();
	do{
		//Verbose::show("MESSAGE TESTING");
		//Verbose::show(receiverQue.deQ().toString());
		MessageInterpreter incoming = receiverQue.deQ();
		std::map<std::string, std::string> m = incoming.getMessage();
		if (m["commandType"] == "File_Upload")
		{
			incoming.setFilePath("File Uploaded Successfully!!!");
			s->send(incoming);
		}
		else if (m["commandType"] == "File_Download")
		{
			//std::cout << "In server file download\n";
			//std::cout << m["filePath"];
			s->send(incoming);
		}
		else if (m["commandType"] == "File_Search")
		{
			std::cout << "In File Search-SERVER\n";
			incoming.setFilePath(fileSearch(m));
			s->send(incoming);
		}
		else if (m["commandType"] == "Text_Search")
		{
			std::cout << "In Text Search-SERVER\n";
			incoming.setFilePath(textSrc(m));
			s->send(incoming);
		}

	} while (1);
}

//-------------------------------------------------<Function to do a file search>------------------------------------------------
std::string Receiver::fileSearch(std::map<std::string, std::string> m)
{
	DataStore ds;
	size_t found = m["filePath"].find("#");
	std::string path = m["filePath"].substr(0, found);
	std::string pattern = m["filePath"].substr(found + 1);
	//std::cout << path << "pattern is" << pattern;
	FileManager fm(path, ds);
	fm.addPattern(pattern);
	fm.search(true);

	std::string answer = "";

	for (auto& temp : ds)
	{
		answer += "File:" + temp.first + "\t\tPaths:";
		for (auto it : temp.second)
		{
			answer += *it;
			answer += ',';
		}
		answer += '\v';
	}

	return answer;
}

//-------------------------------------------<Function to do a text search>-----------------------------------------------
std::string Receiver::textSrc(std::map<std::string, std::string> m)
{
	DataStore ds;
	size_t founded = m["filePath"].find("#");
	std::string pattern = m["filePath"].substr(0, founded);
	std::string searchText = m["filePath"].substr(founded + 1);
	//std::cout << path << "pattern is" << pattern;
	FileManager fm("../Server", ds);
	fm.addPattern(pattern);
	fm.search(true);

	std::string answer = "";

	answer += "File:\tPort:\t\tPaths:\v";
	bool found;
	for (auto fs : ds)
	{
		found = false;
		std::string file = fs.first;
		std::ostringstream out;
		out << file;
		out << "-" << m["receiverPort"] << "\t\t";
		//std::cout << file;
		for (auto iter : fs.second)
		{
			std::string path = *iter;
			//std::cout << path;
			std::string fileSpec = path + '/' + file;
			if (textSearch(fileSpec, searchText))
			{
				out << path << ",";
				found = true;

			}
		}
		if (found)
			answer += out.str() + "\v";
	}

	return answer;
}

//---------------------------------------<Function to search files for text>--------------------------------------------------
bool Receiver::textSearch(const std::string& filespec, const std::string& searchText)
{
	std::ifstream in(filespec);
	if (!in.good())
		return false;
	std::string fileText;
	while (in.good())
	{
		fileText += in.get();
	}
	in.close();
	size_t pos = fileText.find(searchText);
	return pos < fileText.size();
}

//--------------------------------------------<Function to enqueue into the receiver queue>----------------------------------
void Receiver::enqueue(MessageInterpreter msg)
{
	receiverQue.enQ(msg);
}

#ifdef TEST_RECEIVER
int main()
{
	Receiver r(9080);
	r->enqueue(Msg);
	std::string s=r->getmessage();
}


#endif