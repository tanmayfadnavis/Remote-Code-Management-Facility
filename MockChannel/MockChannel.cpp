/////////////////////////////////////////////////////////////////////////////
// MockChannel.cpp - Demo for CSE687 Project #4, Spring 2015               //
// - build as DLL to show how C++\CLI client can use native code channel   //
// - MockChannel reads from sendQ and writes to recvQ                      //
//  Language:    Visual C++, Visual Studio 2013								//
// Platform:    Lenovo V570, Core i5, Windows 7 SP2							//
// Application: Object Oriented Design,Project-3 2015						//
// Author:      Tanmay Fadnavis, Syracuse University						//
//				315-560-3370, tfadnavi@syr.edu								//
// Date: 25/04/2015	                                                       //
// Original Author:Jim Fawcett												//
/////////////////////////////////////////////////////////////////////////////

#define IN_DLL
#include "MockChannel.h"
#include "AppHelpers.h"
#include "Sender.h"
#include "Receiver.h"
#include <string>
#include <thread>
#include <iostream>
#include <mutex>
#include<ostream>
#include<fstream>
#include<sstream>
#include<exception>


using namespace ApplicationHelpers;
using namespace Client;

	class MockChannel : public IMockChannel
	{
	public:
		MockChannel(ISendr* pSendr, IRecvr* pRecvr);
		void start();
		void stop();
	private:
		std::thread thread_;
		ISendr* pISendr_;
		IRecvr* pIRecvr_;
		bool stop_ = false;
	};

	//----< pass pointers to Sender and Receiver >-------------------------------

	MockChannel::MockChannel(ISendr* pSendr, IRecvr* pRecvr) : pISendr_(pSendr), pIRecvr_(pRecvr) {}

	//----< creates thread to read from sendQ and echo back to the recvQ >-------

	void MockChannel::start()
	{
		std::cout << "\n  MockChannel starting up";
		thread_ = std::thread(
			[this] {
			Sendr* pSendr = dynamic_cast<Sendr*>(pISendr_);
			Recvr* pRecvr = dynamic_cast<Recvr*>(pIRecvr_);
			if (pSendr == nullptr || pRecvr == nullptr)
			{
				std::cout << "\n  failed to start Mock Channel\n\n";
				return;
			}
			while (!stop_)
			{

			}
			/* BQueue& sendQ = pSendr->queue();
			 BQueue& recvQ = pRecvr->queue();
			 while (!stop_)
			 {
			 std::cout << "\n  channel deQing message";
			 Message msg = sendQ.deQ();  // will block here so send quit message when stopping
			 std::cout << "\n  channel enQing message";
			 recvQ.enQ(msg);
			 }*/
			std::cout << "\n  Server stopping\n\n";
		});
		//thread_.detach();
	}
	//----< signal server thread to stop >---------------------------------------

	void MockChannel::stop() { stop_ = true; }

	//----< factory functions >--------------------------------------------------

	ISendr* ObjectFactory::createSendr() { return new Sendr; }

	IRecvr* ObjectFactory::createRecvr(int port) { return new Recvr(port); }

	IMockChannel* ObjectFactory::createMockChannel(ISendr* pISendr, IRecvr* pIRecvr)
	{
		return new MockChannel(pISendr, pIRecvr);
	}


#ifdef TEST_MOCKCHANNEL

//----< test stub >----------------------------------------------------------

int main()
{
  ObjectFactory objFact;
  ISendr* pSendr = objFact.createSendr();
  IRecvr* pRecvr = objFact.createRecvr();
  IMockChannel* pMockChannel = objFact.createMockChannel(pSendr, pRecvr);
  pMockChannel->start();
  pSendr->postMessage("Hello World");
  pSendr->postMessage("CSE687 - Object Oriented Design");
  Message msg = pRecvr->getMessage();
  std::cout << "\n  received message = \"" << msg << "\"";
  msg = pRecvr->getMessage();
  std::cout << "\n  received message = \"" << msg << "\"";
  pSendr->postMessage("stopping");
  msg = pRecvr->getMessage();
  std::cout << "\n  received message = \"" << msg << "\"";
  pMockChannel->stop();
  pSendr->postMessage("quit");
  std::cin.get();
}
#endif
