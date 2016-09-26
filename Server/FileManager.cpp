/////////////////////////////////////////////////////////////////////////////
// FileManager.cpp - Supports operations on file                          //
// ver 1.0                                                                //
// ----------------------------------------------------------------------- // 
// ----------------------------------------------------------------------- //
// Language:    Visual C++, Visual Studio 2013                             //
// Platform:    Lenovo V570, Core i5, Windows 7 SP2	                       //
// Application: Object Oriented Design,Project-1 2015                      //
// Author:      Tanmay Fadnavis, Syracuse University					  //
//				315-560-3370, tfadnavi@syr.edu							//
/////////////////////////////////////////////////////////////////////////////

#include "FileManager.h"
#include "FileSystem.h"
#include <iostream>
#include <vector>

//Implementation of Methods.
using namespace Server;

//------------------------------------------------<Function to add patterns>--------------------------------------------------
void FileManager::addPattern(const std::string& patt)
{
	if (patterns_.size() == 1 && patterns_[0] == "*.*")
		patterns_.pop_back();

	patterns_.push_back(patt);
}

//-------------------------------------------------<Function to search for files>------------------------------------------
void FileManager::search(bool recursive)
{
	find(path_,recursive);
	//searchDirectories(path_);
}

//--------------------------------------------------<Parameterized Constructor>--------------------------------------------
FileManager::FileManager(const std::string& path, DataStore& ds) : path_(path), store_(ds)
{
	patterns_.push_back("*.*");
}

//----------------------------------------------------<Function to find files>---------------------------------------
void FileManager::find(const std::string& path,bool recursive)
{
	for (auto patt : patterns_)
	{
		std::vector <std::string> files = FileSystem::Directory::getFiles(path, patt); 
		for (auto f : files)
		{
			store_.save(f,path);
		}
	}

	if (recursive)
	{
		//Adding recursion for directories
		std::vector<std::string> dirs = FileSystem::Directory::getDirectories(path);
		for (auto d : dirs)
		{
			if (!(d == "." || d == ".."))
			{
				std::string tempStr = path;
				find(FileSystem::Path::fileSpec(path,d),recursive);
			}
		}
	}
	
}

/*void FileManager::searchDirectories(const std::string& path)
{
	std::vector<std::string> dirs = FileSystem::Directory::getDirectories(path);
	for (auto d : dirs)
	{
		if (!(d == "." || d == ".."))
		{
			std::string tempStr = path;
			find(tempStr+"/"+d);
		}
	}
}*/

#ifdef TEST_FILEMANAGER

int main()
{
	DataStore ds;

	FileManager fm("../TestPath", ds);
	fm.addPattern("*.*");
	fm.search(true);
	for (auto& temp : ds)
	{
		std::cout << "\n " << temp.first;
		for (auto it : temp.second)
		{
			std::string path = *it;
			std::cout << "path is" << path;
			
		}
	}

}

#endif