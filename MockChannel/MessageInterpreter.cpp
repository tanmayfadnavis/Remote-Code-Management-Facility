///////////////////////////////////////////////////////////////////
// MessageInterpreter.cpp -Package for building and interpreting Messages//
// version 1.0													//
// Language:    Visual C++, Visual Studio 2013                   //
// Platform:    Lenovo V570, Core i5, Windows 7 SP2	              //
// Application: Object Oriented Design,Project-4 2015             //
// Author:      Tanmay Fadnavis, Syracuse University				//
//				315-560-3370, tfadnavi@syr.edu						//
/////////////////////////////////////////////////////////////////////////////  
///////////////////////////////////////////////////////////////////

#include"MessageInterpreter.h"
#include<string>
#include<map>
#include<iostream>

using namespace Client;

//-----------<Default Constructor>-------------------------------------------
MessageInterpreter::MessageInterpreter()
{

}

//-------------<Parameterized Constructor>------------------------------------
MessageInterpreter::MessageInterpreter(std::string cmd, std::string send, std::string rev, std::string path) :commandType_(cmd), senderPort_(send), receiverPort_(rev), path_(path), contentLength_(0)
{
	
}

//--------<Overloaded toString Method>----------------------------------------
std::string MessageInterpreter::toString()
{
	return commandType_ + senderPort_ + receiverPort_ + path_;
}

//-----------<Function to get the message in the form of a map, easy for sending it as a string>-------------
std::map<std::string, std::string> MessageInterpreter::getMessage()
{
	std::map<std::string, std::string> m;
	m["commandType"] = commandType_;
	m["senderPort"] = senderPort_;
	m["receiverPort"] = receiverPort_;
	m["filePath"] = path_;
	m["contentLength"] = std::to_string(contentLength_);
	return m;
}

//-----------<Function to parse the message on the receiver's side>--------------------------------------
void MessageInterpreter::buildMessage(std::vector<std::string> v)
{
	// The message received will be in the format command:file upload sender:9080 receiver:9081
	for (std::vector<std::string>::iterator it = v.begin(); it != v.end(); ++it)
	{
		std::size_t pos = it->find(":");
		pos += 1;

		if (it->find("commandType")!= std::string::npos)
		{
			this->commandType_ = it->substr(pos);
		}

		else if (it->find("senderPort") != std::string::npos)
		{
			this->senderPort_ = it->substr(pos);
		}
		else if (it->find("receiverPort") != std::string::npos)
		{
			this->receiverPort_ = it->substr(pos);
		}
		else if (it->find("filePath") != std::string::npos)
		{
			this->path_ = it->substr(pos);
		}
		else if (it->find("contentLength") != std::string::npos)
		{
			this->contentLength_ = std::stoi(it->substr(pos));
		}

	}

}

#ifdef TEST_MESSAGEINTERPRETER
int main()
{
	MessageInterpreter m("File_Upload","9080","9081","../ClientFiles/Testing.txt");
	std::map<std::string, std::string> map = m.getMessage();
	std::vector<std::string> vec;
	MessageInterpreter msg;
	msg.buildMessage(vec);

}

#endif
