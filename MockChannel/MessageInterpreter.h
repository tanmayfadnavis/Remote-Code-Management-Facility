#ifndef MESSAGEINTERPRETER_H
#define MESSAGEINTERPRETER_H
///////////////////////////////////////////////////////////////////
// MessageInterpreter.h -Package for building and interpreting Messages //
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
* This package is intended to build messages for Sender for sending
* and parse messages received on the receiver side.
*
* Required Files:
* ---------------
*   MessageInterpreter.h MessageInterpreter.cpp
*
* Public Interfaces:
* -----------------
*	MessageInterpreter();
*	MessageInterpreter(std::string cmd, std::string sender, std::string rev, std::string path);
*	void buildMessage(std::vector<std::string>);
*	std::map<std::string,std::string> getMessage();
*	std::string toString();
*	void setContentLength(int length);
*	void setFilePath(std::string p);
*
* Build Process:
* --------------
*   devenv CppCli-WPF-App.sln /debug rebuild
*
* Maintenance History:
* --------------------
*
* Ver 1.0 : 13 April 15
* - first release
*/

#include<string>
#include<map>
#include<vector>

namespace Client
{
	class MessageInterpreter
	{
	public:

		MessageInterpreter();

		MessageInterpreter(std::string cmd, std::string sender, std::string rev, std::string path);

		void buildMessage(std::vector<std::string>);

		std::map<std::string, std::string> getMessage();

		std::string toString();

		void setContentLength(int length){ contentLength_ = length; }

		void setFilePath(std::string p){ path_ = p; }

	private:
		std::string commandType_;
		std::string senderPort_;
		std::string receiverPort_;
		std::string path_;
		int contentLength_;

	};
}
#endif

