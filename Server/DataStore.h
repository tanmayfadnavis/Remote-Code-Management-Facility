#ifndef DATASTORE_H
#define DATASTORE_H


/////////////////////////////////////////////////////////////////////////////
// DataStore.h - Supports store of files and their paths information      //
// ver 1.0                                                                //
// ----------------------------------------------------------------------- // 
// ----------------------------------------------------------------------- //
// Language:    Visual C++, Visual Studio 2013                             //
// Platform:    Lenovo V570, Core i5, Windows 7 SP2	                       //
// Application: Object Oriented Design,Project-1 2015                      //
// Author:      Tanmay Fadnavis, Syracuse University					  //
//				315-560-3370, tfadnavi@syr.edu							//
/////////////////////////////////////////////////////////////////////////////
/*
* Module Operations:
* ==================
* This module provides DataStore class. The DataStore class is used to
* store the file information and their respective paths. File information
* is store in a stnd Map structure and Paths information is stored in the 
* Set structure. The DataStore class provides a public iterator for the Store.
*
* Public Interface:
* =================
*	using Path = std::string;
*	using Paths = std::set < Path > ;
*	using PathIter = Paths::iterator;
*	using PathIterPosition = std::pair < PathIter, bool > ;
*	using ListOfIters = std::list < PathIter > ;
*	using File = std::string;
*	using Store = std::map < File, ListOfIters > ;
*	using iterator = Store::iterator;
*	using StoreAvail = std::pair < iterator, bool > ;
*
*	void save(const std::string& filespec);
*	void save(std::string& filename,const std::string& path);
*	int getPathSize() { return paths.size(); }
*	int getFileSize() { return store.size(); }
*	iterator begin() { return store.begin(); }
*	iterator end() { return store.end(); }
*
* Required Files:
* ===============
* DataStore.h DataStore.cpp
*
* Build Command:
* ==============
* cl /EHa /TEST_DATASTORE DataStore.cpp
*
* Maintenance History:
* ====================
* ver 1.0, First Release
*/

#include <vector>
#include <set>
#include <list>
#include <map>
#include <string>

namespace Server
{
	class DataStore
	{
	public:
		using Path = std::string;
		using Paths = std::set < Path > ;
		using PathIter = Paths::iterator;
		using PathIterPosition = std::pair < PathIter, bool > ;
		using ListOfIters = std::list < PathIter > ;
		using File = std::string;
		using Store = std::map < File, ListOfIters > ;
		using iterator = Store::iterator;
		using StoreAvail = std::pair < iterator, bool > ;

		void save(const std::string& filespec);
		void save(std::string& filename, const std::string& path);
		int getPathSize() { return paths.size(); }
		int getFileSize() { return store.size(); }
		iterator begin() { return store.begin(); }
		iterator end() { return store.end(); }


	private:
		Store store;
		Paths paths;
	};
}
#endif