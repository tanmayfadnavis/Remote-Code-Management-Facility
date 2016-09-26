#ifndef WINDOW_H
#define WINDOW_H
///////////////////////////////////////////////////////////////////
// Window.h - Package to create GUI using C++/CLI               //
// Ver 3.0                                                      //
// Language:    Visual C++, Visual Studio 2013					//
// Platform:    Lenovo V570, Core i5, Windows 7 SP2	           //
// Application: Object Oriented Design,Project-4 2015          //
// Author:      Tanmay Fadnavis, Syracuse University		   //
//				315-560-3370, tfadnavi@syr.edu				  //
// Original Author:      Jim Fawcett, CST 4-187, 443-3948      //
//              jfawcett@twcny.rr.com						//
// Date: 04/28/2015											//
///////////////////////////////////////////////////////////////////
/*
*  Package Operations:
*  -------------------
*  This package demonstrates how to build a C++\CLI WPF application.  It 
*  provides one class, WPFCppCliDemo, derived from System::Windows::Window
*  that is compiled with the /clr option to run in the Common Language
*  Runtime, and another class MockChannel written in native C++ and compiled
*  as a DLL with no Common Language Runtime support.
*
*  The window class hosts, in its window, a tab control with three views, two
*  of which are provided with functionality that you may need for Project #4.
*  It loads the DLL holding MockChannel.  MockChannel hosts a send queue, a
*  receive queue, and a C++11 thread that reads from the send queue and writes
*  the deQ'd message to the receive queue.
*
*  The Client can post a message to the MockChannel's send queue.  It hosts
*  a receive thread that reads the receive queue and dispatches any message
*  read to a ListBox in the Client's FileList tab.  So this Demo simulates
*  operations you will need to execute for Project #4.
*
*  Required Files:
*  ---------------
*  Window.h, Window.cpp, MochChannel.h, MochChannel.cpp,
*  Cpp11-BlockingQueue.h, Cpp11-BlockingQueue.cpp
*  
*  Public Interfaces:
*  ------------------
*
*	WPFCppCliDemo();
*    ~WPFCppCliDemo();
*    void setUpStatusBar();
*    void setUpTabControl();
*    void setUpSendMessageView();
*    void setUpFileListView();
*    void setUpConnectionView();
*    void fileSearch(Object^ obj, RoutedEventArgs^ args);
*	void textSearch(Object^ obj, RoutedEventArgs^ args);
*    void addText(String^ msg);
*	void addText2(String^ msg);
*	void addUpload(String^ msg);
*    void getMessage();
*    void clear(Object^ sender, RoutedEventArgs^ args);
*	void clear2(Object^ sender, RoutedEventArgs^ args);
*    void browseForFolder(Object^ sender, RoutedEventArgs^ args);
*	void uploadFile(Object^ sender, RoutedEventArgs^ args);
*	void downloadFile(Object^ sender, RoutedEventArgs^ args);
*    void OnLoaded(Object^ sender, RoutedEventArgs^ args);
*    void Unloading(Object^ sender, System::ComponentModel::CancelEventArgs^ args);
*
*  Build Command:
*  --------------
*  devenv CppCli-WPF-App.sln
*  - this builds C++\CLI client application and native mock channel DLL
*
*  Maintenance History:
*  --------------------
*  ver 3.0 28 Apr 2015
*  ver 2.0 : 15 Apr 2015
*  - completed message passing demo with moch channel
*  - added FileBrowserDialog to show files in a selected directory
*  ver 1.0 : 13 Apr 2015
*  - incomplete demo with GUI but not connected to mock channel
*/
/*
* Create C++/CLI Console Application
* Right-click project > Properties > Common Language Runtime Support > /clr
* Right-click project > Add > References
*   add references to :
*     System
*     System.Windows.Presentation
*     WindowsBase
*     PresentatioCore
*     PresentationFramework
*/
using namespace System;
using namespace System::Text;
using namespace System::Windows;
using namespace System::Windows::Input;
using namespace System::Windows::Markup;
using namespace System::Windows::Media;                   // TextBlock formatting
using namespace System::Windows::Controls;                // TabControl
using namespace System::Windows::Controls::Primitives;    // StatusBar
using namespace System::Threading;
using namespace System::Threading::Tasks;
using namespace System::Windows::Threading;
using namespace System::ComponentModel;



#include "../MockChannel/MockChannel.h"
#include <iostream>

namespace CppCliWindows
{
  ref class WPFCppCliDemo : Window
  {
    // MockChannel references

    ISendr* pSendr_;
    IRecvr* pRecvr_;
    IMockChannel* pChann_;

    // Controls for Window

    DockPanel^ hDockPanel = gcnew DockPanel();      // support docking statusbar at bottom
    Grid^ hGrid = gcnew Grid();                    
    TabControl^ hTabControl = gcnew TabControl();
    TabItem^ hSendMessageTab = gcnew TabItem();
    TabItem^ hFileListTab = gcnew TabItem();
    TabItem^ hTextTab = gcnew TabItem();
    StatusBar^ hStatusBar = gcnew StatusBar();
    StatusBarItem^ hStatusBarItem = gcnew StatusBarItem();
    TextBlock^ hStatus = gcnew TextBlock();

    // Controls for SendMessage View

    Grid^ hSendMessageGrid = gcnew Grid();
    Button^ hFileSearch = gcnew Button();
    Button^ hClearButton = gcnew Button();
    TextBlock^ hTextBlock1 = gcnew TextBlock();
    ScrollViewer^ hScrollViewer1 = gcnew ScrollViewer();
    StackPanel^ hStackPanel1 = gcnew StackPanel();
	StackPanel^ hStackPanel3 = gcnew StackPanel();
	TextBox^ hfilePath = gcnew TextBox();
	TextBox^ hfilePattern = gcnew TextBox();
	TextBox^ hpath = gcnew TextBox();
	TextBox^ hpattern = gcnew TextBox();
	

    // Controls for FileListView View

    Grid^ hFileListGrid = gcnew Grid();
    Forms::FolderBrowserDialog^ hFolderBrowserDialog = gcnew Forms::FolderBrowserDialog();
    ListBox^ hListBox = gcnew ListBox();
    Button^ hFolderBrowseButton = gcnew Button();
	Button^ hsendToServer1Button = gcnew Button();
	StackPanel^ hStackPanel2 = gcnew StackPanel();
	StackPanel^ hStackPanel4 = gcnew StackPanel();
	TextBox^ uploadSuccess = gcnew TextBox();
    //Grid^ hGrid2 = gcnew Grid();
	Button^ hDownloadFile = gcnew Button();
	TextBox^ download = gcnew TextBox();
	TextBox^ downloadMsg = gcnew TextBox();

	//Controls for Text Search View

	Grid^ hTextSearchGrid = gcnew Grid();
	Button^ hTextSearch = gcnew Button();
	Button^ hClearButton2 = gcnew Button();
	TextBlock^ hTextBlock2 = gcnew TextBlock();
	ScrollViewer^ hScrollViewerT1 = gcnew ScrollViewer();
	StackPanel^ hStackPanelT1 = gcnew StackPanel();
	StackPanel^ hStackPanelT3 = gcnew StackPanel();
	TextBox^ hPort = gcnew TextBox();
	TextBox^ hPortNo = gcnew TextBox();
	TextBox^ hPat = gcnew TextBox();
	TextBox^ hpattern2 = gcnew TextBox();
	TextBox^ htext = gcnew TextBox();
	TextBox^ hsearchText = gcnew TextBox();


    // receive thread

    Thread^ recvThread;

  public:
    WPFCppCliDemo();
    ~WPFCppCliDemo();

    void setUpStatusBar();
    void setUpTabControl();
    void setUpSendMessageView();
    void setUpFileListView();
    void setUpConnectionView();

    void fileSearch(Object^ obj, RoutedEventArgs^ args);
	void textSearch(Object^ obj, RoutedEventArgs^ args);
    void addText(String^ msg);
	void addText2(String^ msg);
	void addUpload(String^ msg);
    void getMessage();
    void clear(Object^ sender, RoutedEventArgs^ args);
	void clear2(Object^ sender, RoutedEventArgs^ args);
    void browseForFolder(Object^ sender, RoutedEventArgs^ args);
	void uploadFile(Object^ sender, RoutedEventArgs^ args);
	void downloadFile(Object^ sender, RoutedEventArgs^ args);
    void OnLoaded(Object^ sender, RoutedEventArgs^ args);
    void Unloading(Object^ sender, System::ComponentModel::CancelEventArgs^ args);
  private:
    std::string toStdString(String^ pStr);
    String^ toSystemString(std::string& str);
    void setTextBlockProperties();
    void setButtonsProperties();
	void setButtonProperties2();
	void setFile1();
	void setFile2();
	void setConnect1();
	void setConnect2();
	void setConnect3();
  };
}


#endif
