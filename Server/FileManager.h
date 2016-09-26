#ifndef FILEMANAGER_H
#define FILEMANAGER_H


/////////////////////////////////////////////////////////////////////////////
// FileManager.h - Support Operations on Files						  //
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
* This module provides FileManager class. The FileManager
* class interacts with the File System class provided by Dr. Fawcett.
* It gets the files and the corresponding paths information. It provides 
* this information to the Data Store for storing.
*
* Public Interface:
* =================
*	FileManager(const std::string& path, DataStore& ds);
*	void addPattern(const std::string& patt);
*	void search(bool recursive);
*	void find(const std::string& path,bool recursive);
*	void searchDirectories(const std::string& path);
*
* Required Files:
* ===============
* FileManager.cpp DataStore.h FileManager.h 
*
* Build Command:
* ==============
* cl /EHa /TEST_FILEMANAGER FileManager.cpp
*
* Maintenance History:
* ====================
* ver 1.0, First Release
*/

#include"FileSystem.h"
#include"DataStore.h"

namespace Server
{
	class FileManager
	{
	public:
		using patterns = std::vector < std::string > ;


		FileManager(const std::string& path, DataStore& ds);
		void addPattern(const std::string& patt);
		void search(bool recursive);
		void find(const std::string& path, bool recursive);
		void searchDirectories(const std::string& path);

	private:
		std::string path_;
		std::string options_;
		patterns patterns_;
		DataStore& store_;
	};
}

#endif