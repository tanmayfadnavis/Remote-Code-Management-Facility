/////////////////////////////////////////////////////////////////////////////
// DataStore.cpp - Supports store of files and their paths information    //
// ver 1.0                                                                //
// ----------------------------------------------------------------------- // 
// ----------------------------------------------------------------------- //
// Language:    Visual C++, Visual Studio 2013                             //
// Platform:    Lenovo V570, Core i5, Windows 7 SP2	                       //
// Application: Object Oriented Design,Project-1 2015                      //
// Author:      Tanmay Fadnavis, Syracuse University					  //
//				315-560-3370, tfadnavi@syr.edu							//
/////////////////////////////////////////////////////////////////////////////


#include "DataStore.h"
#include<iostream>

using namespace Server;

//Implementation of Methods
//-----------------------------------<Function to create the Data Store>----------------------------
void DataStore::save(std::string& filename,const std::string& path)
{
	paths.insert(path);
	PathIterPosition pi = paths.insert(path);
	PathIter pi2 = pi.first;
	ListOfIters lt;
	lt.push_back(pi2);
	StoreAvail sa=  store.insert(std::map < File, ListOfIters >::value_type(filename, lt));
	//element already existed, then all the current iterator to the list
	if (sa.second == false)
	{
		ListOfIters temp = store[filename];
		temp.push_back(pi2);
		store.erase(filename);
		store.insert(std::map < File, ListOfIters >::value_type(filename, temp));
	}
}

#ifdef TEST_DATASTORE

int main()
{
	DataStore ds;
	std::string file="ObjectOrientedDesign.txt";
	std::string path = "../TestPath";
	ds.save(file, path);
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

