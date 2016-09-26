#ifndef MOCKCHANNEL_H
#define MOCKCHANNEL_H
/////////////////////////////////////////////////////////////////////////////
// MockChannel.h - Demo for CSE687 Project #4, Spring 2015                 //
// - build as DLL to show how C++\CLI client can use native code channel   //
// - MockChannel reads from sendQ and writes to recvQ						//
// Language:    Visual C++, Visual Studio 2013								//
// Platform:    Lenovo V570, Core i5, Windows 7 SP2							//
// Application: Object Oriented Design,Project-3 2015						//
// Author:      Tanmay Fadnavis, Syracuse University						//
//				315-560-3370, tfadnavi@syr.edu								//
// Date: 25/04/2015															//
// Original Author: Jim Fawcett                                             //
/////////////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package is intended to build DLL for CLI to use native code.
*
* Required Files:
* ---------------
*   MockChannel.h MockChannel.cpp
*
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

#ifdef IN_DLL
#define DLL_DECL __declspec(dllexport)
#else
#define DLL_DECL __declspec(dllimport)
#endif

#include <string>

	struct ISendr
	{
		virtual void postMessage(std::string cmd, std::string sender, std::string receiver, std::string arg) = 0;

	};

	struct IRecvr
	{
		virtual std::string getMessage() = 0;
		
	};

	struct IMockChannel
	{
	public:
		virtual void start() = 0;
		virtual void stop() = 0;
	};

	extern "C" {
		struct ObjectFactory
		{
			DLL_DECL ISendr* createSendr();
			DLL_DECL IRecvr* createRecvr(int port);
			DLL_DECL IMockChannel* createMockChannel(ISendr* pISendr, IRecvr* pIRecvr);
		};
	}

#endif


