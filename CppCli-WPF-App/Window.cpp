///////////////////////////////////////////////////////////////////
// Window.cpp - Package to create GUI using C++/CLI               //
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
*  To run as a Windows Application:
*  - Set Project Properties > Linker > System > Subsystem to Windows
*  - Comment out int main(...) at bottom
*  - Uncomment int _stdcall WinMain() at bottom
*  To run as a Console Application:
*  - Set Project Properties > Linker > System > Subsytem to Console
*  - Uncomment int main(...) at bottom
*  - Comment out int _stdcall WinMain() at bottom
*/
#include "Window.h"
using namespace CppCliWindows;


//--------------------------------------------------------<Default Constructor of WPF>---------------------------------------------
WPFCppCliDemo::WPFCppCliDemo()
{
  // set up channel
  ObjectFactory* pObjFact = new ObjectFactory;
  pSendr_ = pObjFact->createSendr();
  pRecvr_ = pObjFact->createRecvr(9080);
  pChann_ = pObjFact->createMockChannel(pSendr_, pRecvr_);
  pChann_->start();
  delete pObjFact;

  // client's receive thread
  recvThread = gcnew Thread(gcnew ThreadStart(this, &WPFCppCliDemo::getMessage));
  recvThread->Start();

  // set event handlers
  this->Loaded += 
    gcnew System::Windows::RoutedEventHandler(this, &WPFCppCliDemo::OnLoaded);
  this->Closing += 
    gcnew CancelEventHandler(this, &WPFCppCliDemo::Unloading);
  hFileSearch->Click += gcnew RoutedEventHandler(this, &WPFCppCliDemo::fileSearch);
  hClearButton->Click += gcnew RoutedEventHandler(this, &WPFCppCliDemo::clear);
  hFolderBrowseButton->Click += gcnew RoutedEventHandler(this, &WPFCppCliDemo::browseForFolder);
  hsendToServer1Button->Click += gcnew RoutedEventHandler(this, &WPFCppCliDemo::uploadFile);
  hTextSearch->Click += gcnew RoutedEventHandler(this, &WPFCppCliDemo::textSearch);
  hDownloadFile->Click += gcnew RoutedEventHandler(this, &WPFCppCliDemo::downloadFile);
  hClearButton2->Click += gcnew RoutedEventHandler(this, &WPFCppCliDemo::clear2);

  // set Window properties
  this->Title = "Remote Code Managment Facility";
  this->Width = 900;
  this->Height = 600;

  // attach dock panel to Window
  this->Content = hDockPanel;
  hDockPanel->Children->Add(hStatusBar);
  hDockPanel->SetDock(hStatusBar, Dock::Bottom);
  hDockPanel->Children->Add(hGrid);
  // setup Window controls and views
  setUpTabControl();
  setUpStatusBar();
  setUpSendMessageView();
  setUpFileListView();
  setUpConnectionView();
}

//----------------------------------------------------------<Destructor of WPF>----------------------------------------------------
WPFCppCliDemo::~WPFCppCliDemo()
{
  delete pChann_;
  delete pSendr_;
  delete pRecvr_;
}

//------------------------------------------------------<Function to set up the status bar of the window>-------------------------------
void WPFCppCliDemo::setUpStatusBar()
{
  hStatusBar->Items->Add(hStatusBarItem);
  hStatus->Text = "Remote Code Management Facility";
  //status->FontWeight = FontWeights::Bold;
  hStatusBarItem->Content = hStatus;
  hStatusBar->Padding = Thickness(10, 2, 10, 2);
}

//----------------------------------------------------<Function to set up the tab display of the window>---------------------------------
void WPFCppCliDemo::setUpTabControl()
{
  hGrid->Children->Add(hTabControl);
  hSendMessageTab->Header = "File Search";
  hFileListTab->Header = "File Upload and Download";
  hTextTab->Header = "Text Search";
  hTabControl->Items->Add(hSendMessageTab);
  hTabControl->Items->Add(hFileListTab);
  hTabControl->Items->Add(hTextTab);
}

//-----------------------------------------------------<Helper function for the Tab1- File search>------------------------------------------
void WPFCppCliDemo::setTextBlockProperties()
{
  RowDefinition^ hRow1Def = gcnew RowDefinition();
  hSendMessageGrid->RowDefinitions->Add(hRow1Def);
  Border^ hBorder1 = gcnew Border();
  hBorder1->BorderThickness = Thickness(1);
  hBorder1->BorderBrush = Brushes::Black;
  hBorder1->Child = hTextBlock1;
  hTextBlock1->Padding = Thickness(15);
  hTextBlock1->Text = "";
  hTextBlock1->FontFamily = gcnew Windows::Media::FontFamily("Tahoma");
  hTextBlock1->FontWeight = FontWeights::Bold;
  hTextBlock1->FontSize = 16;
  hScrollViewer1->VerticalScrollBarVisibility = ScrollBarVisibility::Auto;
  hScrollViewer1->Content = hBorder1;
  hSendMessageGrid->SetRow(hScrollViewer1, 0);
  hSendMessageGrid->Children->Add(hScrollViewer1);
}

//-----------------------------------------------------<Helper function for the Tab1- File search>------------------------------------------
void WPFCppCliDemo::setButtonsProperties()
{
	RowDefinition^ hRow2Def = gcnew RowDefinition();
	hRow2Def->Height = GridLength(75);
	hSendMessageGrid->RowDefinitions->Add(hRow2Def);
	hFileSearch->Content = "Search File";
	Border^ hBorder2 = gcnew Border();
	hBorder2->Width = 120;
	hBorder2->Height = 30;
	hBorder2->BorderThickness = Thickness(1);
	hBorder2->BorderBrush = Brushes::Black;
	hClearButton->Content = "Clear";
	hBorder2->Child = hFileSearch;
	Border^ hBorder3 = gcnew Border();
	hBorder3->Width = 120;
	hBorder3->Height = 30;
	hBorder3->BorderThickness = Thickness(1);
	hBorder3->BorderBrush = Brushes::Black;
	hBorder3->Child = hClearButton;
	hStackPanel1->Children->Add(hBorder2);
	TextBlock^ hSpacer = gcnew TextBlock();
	hSpacer->Width = 10;
	hStackPanel1->Children->Add(hSpacer);
	hStackPanel1->Children->Add(hBorder3);
	hStackPanel1->Orientation = Orientation::Horizontal;
	hStackPanel1->HorizontalAlignment = System::Windows::HorizontalAlignment::Center;
	hSendMessageGrid->SetRow(hStackPanel1, 1);
	hSendMessageGrid->Children->Add(hStackPanel1);
}

//-----------------------------------------------------<Helper function for the Tab1- File search>------------------------------------------
void WPFCppCliDemo::setButtonProperties2()
{
  //For text boxes and labels.
  RowDefinition^ hRow3 = gcnew RowDefinition();
  hRow3->Height = GridLength(75);
  hSendMessageGrid->RowDefinitions->Add(hRow3);
  hpath->IsEnabled = false;
  hpath->FontFamily = gcnew Windows::Media::FontFamily("Tahoma");
  hpath->FontSize = 18;
  hpath->FontWeight = FontWeights::Bold;
  hpath->Text = "Enter Path Here";
  hpath->Width = 160;
  hpath->Height = 25;
  hStackPanel3->Children->Add(hpath);
  TextBlock^ hSpacer2 = gcnew TextBlock();
  hSpacer2->Width = 10;
  hStackPanel3->Children->Add(hSpacer2);
  hfilePath->Width = 100;
  hfilePath->Height = 25;
  hStackPanel3->Children->Add(hfilePath);
  TextBlock^ hSpacer3 = gcnew TextBlock();
  hSpacer3->Width = 20;
  hStackPanel3->Children->Add(hSpacer3);
  hpattern->IsEnabled = false;
  hpattern->FontFamily = gcnew Windows::Media::FontFamily("Tahoma");
  hpattern->FontSize = 18;
  hpattern->FontWeight = FontWeights::Bold;
  hpattern->Text = "Enter Pattern Here";
  hpattern->Width = 180;
  hpattern->Height = 25;
  hStackPanel3->Children->Add(hpattern);
  TextBlock^ hSpacer4 = gcnew TextBlock();
  hSpacer4->Width = 20;
  hStackPanel3->Children->Add(hSpacer4);
  hfilePattern->Width = 100;
  hfilePattern->Height = 25;
  hStackPanel3->Children->Add(hfilePattern);
  hStackPanel3->Orientation = Orientation::Horizontal;
  hStackPanel3->HorizontalAlignment = System::Windows::HorizontalAlignment::Center;
  hSendMessageGrid->SetRow(hStackPanel3, 2);
  hSendMessageGrid->Children->Add(hStackPanel3);
}

//---------------------------------------------------------<Function to set up the Tab1 of the window>-----------------------------------
void WPFCppCliDemo::setUpSendMessageView()
{
  Console::Write("\n  setting up sendMessage view");
  hSendMessageGrid->Margin = Thickness(20);
  hSendMessageTab->Content = hSendMessageGrid;

  setTextBlockProperties();
  setButtonsProperties();
  setButtonProperties2();
}

//---------------------------------------------------------<Function to convert the system string to native string>------------------------
std::string WPFCppCliDemo::toStdString(String^ pStr)
{
  std::string dst;
  for (int i = 0; i < pStr->Length; ++i)
    dst += (char)pStr[i];
  return dst;
}

//----------------------------------------------------------<Function to send the file search request to the server>------------------------
void WPFCppCliDemo::fileSearch(Object^ obj, RoutedEventArgs^ args)
{
	std::cout << "Search for files button\n";
	String^ path = hfilePath->Text+"#"+hfilePattern->Text;
	std::cout << toStdString(path);
    pSendr_->postMessage("File_Search","9080","9081",toStdString(path));
    Console::Write("\n  sent message");
    hStatus->Text = "Sent message";

}

//----------------------------------------------------------<Function to send the text search request to the server>---------------------------
void WPFCppCliDemo::textSearch(Object^ obj, RoutedEventArgs^ args)
{
	std::cout << "Text search button\n";
	String^ path = hpattern2->Text + "#" + hsearchText->Text;
	pSendr_->postMessage("Text_Search", "9080", toStdString(hPortNo->Text), toStdString(path));

}

//-----------------------------------------------------------<Function to convert the native string to system string>--------------------------
String^ WPFCppCliDemo::toSystemString(std::string& str)
{
  StringBuilder^ pStr = gcnew StringBuilder();
  for (size_t i = 0; i < str.size(); ++i)
    pStr->Append((Char)str[i]);
  return pStr->ToString();
}

//-----------------------------------------------------------<Function to add the result to text block of Tab1>---------------------------------
void WPFCppCliDemo::addText(String^ msg)
{
  hTextBlock1->Text += msg + "\n\n";
}

//-----------------------------------------------------------<Function to add the result to the text block of Tab3>------------------------------
void WPFCppCliDemo::addText2(String^ msg)
{
	hTextBlock2->Text += msg + "\n\n";
}

//-----------------------------------------------------------<Function to display the file upload/download success msg>---------------------------
void WPFCppCliDemo::addUpload(String^ msg)
{
	uploadSuccess->Text = "";
	uploadSuccess->Text += msg;
}

//------------------------------------------------------<Function to get the message from the mock channel>---------------------------------
void WPFCppCliDemo::getMessage()
{
  // recvThread runs this function
  while (true)
  {
    std::cout << "\n  receive thread calling getMessage()";
    std::string msg = pRecvr_->getMessage();
	std::cout << msg;
    String^ sMsg = toSystemString(msg);
    array<String^>^ args = gcnew array<String^>(1);
    args[0] = sMsg;

    Action<String^>^ act = gcnew Action<String^>(this, &WPFCppCliDemo::addText);
	Action<String^>^ act2 = gcnew Action<String^>(this, &WPFCppCliDemo::addUpload);
	Action<String^>^ act3 = gcnew Action<String^>(this, &WPFCppCliDemo::addText2);

	if (sMsg->Contains("File Search"))
	{
		Dispatcher->Invoke(act, args);  // must call addText on main UI thread
	}
	else if (sMsg->Contains("File Uploaded"))
	{
		Dispatcher->Invoke(act2, args);
	}
	else if (sMsg->Contains("Text Search"))
	{
		Dispatcher->Invoke(act3, args);
	}
	else if (sMsg->Contains("File Downloaded"))
	{
		Dispatcher->Invoke(act2, args);
	} 
  }
}

//------------------------------------------------------------------<Function to clear the text block of Tab1>----------------------------------
void WPFCppCliDemo::clear(Object^ sender, RoutedEventArgs^ args)
{
  Console::Write("\n  cleared message text");
  hStatus->Text = "Cleared message";
  hTextBlock1->Text = "";
}

//-------------------------------------------------------------------<Function to clear the text block of Tab2>----------------------------------
void WPFCppCliDemo::clear2(Object^ sender, RoutedEventArgs^ args)
{
	Console::Write("\n  cleared message text");
	hStatus->Text = "Cleared message";
	hTextBlock2->Text = "";
}

//-----------------------------------------------------<Helper function for the Tab2- File upload/dwnld>------------------------------------------
void WPFCppCliDemo::setFile1()
{
	RowDefinition^ hRow1Def = gcnew RowDefinition();
	//hRow1Def->Height = GridLength(75);
	hFileListGrid->RowDefinitions->Add(hRow1Def);
	Border^ hBorder1 = gcnew Border();
	hBorder1->BorderThickness = Thickness(1);
	hBorder1->BorderBrush = Brushes::Black;
	hBorder1->Child = hListBox;
	hFileListGrid->SetRow(hBorder1, 0);
	hFileListGrid->Children->Add(hBorder1);
	RowDefinition^ hRow2Def = gcnew RowDefinition();
	hRow2Def->Height = GridLength(75);
	hFileListGrid->RowDefinitions->Add(hRow2Def);
	hFolderBrowseButton->Content = "Select Directory";
	Border^ hBorder2 = gcnew Border();
	hBorder2->Width = 120;
	hBorder2->Height = 30;
	hBorder2->BorderThickness = Thickness(1);
	hBorder2->BorderBrush = Brushes::Black;
	hsendToServer1Button->Content = "Upload to Server";
	hBorder2->Child = hFolderBrowseButton;
	Border^ hBorder3 = gcnew Border();
	hBorder3->Width = 120;
	hBorder3->Height = 30;
	hBorder3->BorderThickness = Thickness(1);
	hBorder3->BorderBrush = Brushes::Black;
	hBorder3->Child = hsendToServer1Button;
	hStackPanel2->Children->Add(hBorder2);
	TextBlock^ hSpacer = gcnew TextBlock();
	hSpacer->Width = 10;
	hStackPanel2->Children->Add(hSpacer);
	hStackPanel2->Children->Add(hBorder3);
	hStackPanel2->Orientation = Orientation::Horizontal;
	hStackPanel2->HorizontalAlignment = System::Windows::HorizontalAlignment::Center;
	hFileListGrid->SetRow(hStackPanel2, 1);
	hFileListGrid->Children->Add(hStackPanel2);
}

//-----------------------------------------------------<Helper function for the Tab2- File upload/dwnld>------------------------------------------
void WPFCppCliDemo::setFile2()
{
	RowDefinition^ hRow3Def = gcnew RowDefinition();
	hRow3Def->Height = GridLength(75);
	hFileListGrid->RowDefinitions->Add(hRow3Def);
	hDownloadFile->Content = "Download File";
	Border^ hBorder4 = gcnew Border();
	hBorder4->Width = 120;
	hBorder4->Height = 30;
	hBorder4->BorderThickness = Thickness(1);
	hBorder4->BorderBrush = Brushes::Black;
	hBorder4->Child = hDownloadFile;
	hStackPanel4->Children->Add(hBorder4);
	TextBlock^ hSpacer2 = gcnew TextBlock();
	hSpacer2->Width = 10;
	hStackPanel4->Children->Add(hSpacer2);
	downloadMsg->IsEnabled = false;
	downloadMsg->FontFamily = gcnew Windows::Media::FontFamily("Tahoma");
	downloadMsg->FontSize = 18;
	downloadMsg->FontWeight = FontWeights::Bold;
	downloadMsg->Text = "Enter Full File Path and File name:";
	downloadMsg->Width = 350;
	downloadMsg->Height = 35;
	hStackPanel4->Children->Add(downloadMsg);
	TextBlock^ hSpacer3 = gcnew TextBlock();
	hSpacer3->Width = 10;
	hStackPanel4->Children->Add(hSpacer3);
	download->Width = 200;
	download->Height = 25;
	hStackPanel4->Children->Add(download);
	hStackPanel4->Orientation = Orientation::Horizontal;
	hStackPanel4->HorizontalAlignment = System::Windows::HorizontalAlignment::Left;
	hFileListGrid->SetRow(hStackPanel4, 2);
	hFileListGrid->Children->Add(hStackPanel4);
	RowDefinition^ hRow4Def = gcnew RowDefinition();
	hRow4Def->Height = GridLength(75);
	hFileListGrid->RowDefinitions->Add(hRow4Def);
	uploadSuccess->IsEnabled = false;
	uploadSuccess->FontFamily = gcnew Windows::Media::FontFamily("Tahoma");
	uploadSuccess->FontSize = 20;
	uploadSuccess->FontWeight = FontWeights::Bold;
	uploadSuccess->Text = "";
	uploadSuccess->Width = 550;
	uploadSuccess->Height = 35;
	hFileListGrid->SetRow(uploadSuccess, 3);
	hFileListGrid->Children->Add(uploadSuccess);
	hFolderBrowserDialog->ShowNewFolderButton = false;
	hFolderBrowserDialog->SelectedPath = System::IO::Directory::GetCurrentDirectory();
}

//---------------------------------------------------------------<Function to set-up the Tab2 of the window>----------------------------------------
void WPFCppCliDemo::setUpFileListView()
{
  Console::Write("\n  setting up FileList view");
  hFileListGrid->Margin = Thickness(20);
  hFileListTab->Content = hFileListGrid;
  setFile1();
  setFile2();

}

//---------------------------------------------------------------<Function to browse for the folders>---------------------------------------------
void WPFCppCliDemo::browseForFolder(Object^ sender, RoutedEventArgs^ args)
{
  std::cout << "\n  Browsing for folder";
  hListBox->Items->Clear();
  System::Windows::Forms::DialogResult result;
  result = hFolderBrowserDialog->ShowDialog();
  if (result == System::Windows::Forms::DialogResult::OK)
  {
    String^ path = hFolderBrowserDialog->SelectedPath;
    std::cout << "\n  opening folder \"" << toStdString(path) << "\"";
    array<String^>^ files = System::IO::Directory::GetFiles(path, L"*.*");
    for (int i = 0; i < files->Length; ++i)
      hListBox->Items->Add(files[i]);
    array<String^>^ dirs = System::IO::Directory::GetDirectories(path);
    for (int i = 0; i < dirs->Length; ++i)
      hListBox->Items->Add(L"<> " + dirs[i]);
  }
}

//--------------------------------------------------------------------<Function to send the upload file request to the server>--------------------
void WPFCppCliDemo::uploadFile(Object^ sender, RoutedEventArgs^ args)
{

	std::cout << "\n IN UPLOAD BUTTON";
	String^ temp = hListBox->SelectedItem->ToString();
	std::cout << toStdString(temp);
	pSendr_->postMessage("File_Upload", "9080", "9081", toStdString(temp));
	Console::Write("\n  sent message");
	hStatus->Text = "Sent message";
}

//---------------------------------------------------------------------<Function to send the download file request to the server>------------------
void WPFCppCliDemo::downloadFile(Object^ sender, RoutedEventArgs^ args)
{
	std::cout << "\n IN DOWNLOAD BUTTON";
	String^ temp = download->Text;
	pSendr_->postMessage("File_Download", "9080", "9081", toStdString(temp));
	Console::WriteLine("\n Download Fie msg sent");
	hStatus->Text = "Sent Message";

}

//-----------------------------------------------------<Helper function for the Tab3- Text search>------------------------------------------
void WPFCppCliDemo::setConnect1()
{
	RowDefinition^ hRow1Def = gcnew RowDefinition();
	hTextSearchGrid->RowDefinitions->Add(hRow1Def);
	Border^ hBorder1 = gcnew Border();
	hBorder1->BorderThickness = Thickness(1);
	hBorder1->BorderBrush = Brushes::Black;
	hBorder1->Child = hTextBlock2;
	hTextBlock2->Padding = Thickness(15);
	hTextBlock2->Text = "";
	hTextBlock2->FontFamily = gcnew Windows::Media::FontFamily("Tahoma");
	hTextBlock2->FontWeight = FontWeights::Bold;
	hTextBlock2->FontSize = 16;
	hScrollViewerT1->VerticalScrollBarVisibility = ScrollBarVisibility::Auto;
	hScrollViewerT1->Content = hBorder1;
	hTextSearchGrid->SetRow(hScrollViewerT1, 0);
	hTextSearchGrid->Children->Add(hScrollViewerT1);
	//SET Button Properties.
	RowDefinition^ hRow2Def = gcnew RowDefinition();
	hRow2Def->Height = GridLength(75);
	hTextSearchGrid->RowDefinitions->Add(hRow2Def);
	hTextSearch->Content = "Search Text";
	Border^ hBorder2 = gcnew Border();
	hBorder2->Width = 120;
	hBorder2->Height = 30;
	hBorder2->BorderThickness = Thickness(1);
	hBorder2->BorderBrush = Brushes::Black;
	hClearButton2->Content = "Clear";
	hBorder2->Child = hTextSearch;
	Border^ hBorder3 = gcnew Border();
	hBorder3->Width = 120;
	hBorder3->Height = 30;
	hBorder3->BorderThickness = Thickness(1);
	hBorder3->BorderBrush = Brushes::Black;
	hBorder3->Child = hClearButton2;
	hStackPanelT1->Children->Add(hBorder2);
	TextBlock^ hSpacer = gcnew TextBlock();
	hSpacer->Width = 10;
	hStackPanelT1->Children->Add(hSpacer);
	hStackPanelT1->Children->Add(hBorder3);
	hStackPanelT1->Orientation = Orientation::Horizontal;
	hStackPanelT1->HorizontalAlignment = System::Windows::HorizontalAlignment::Center;
	hTextSearchGrid->SetRow(hStackPanelT1, 1);
	hTextSearchGrid->Children->Add(hStackPanelT1);
}

//-----------------------------------------------------<Helper function for the Tab3- Text search>------------------------------------------
void WPFCppCliDemo::setConnect2()
{	
	RowDefinition^ hRow3 = gcnew RowDefinition();
	hRow3->Height = GridLength(75);
	hTextSearchGrid->RowDefinitions->Add(hRow3);
	hPort->IsEnabled = false;
	hPort->FontFamily = gcnew Windows::Media::FontFamily("Tahoma");
	hPort->FontSize = 20;
	hPort->FontWeight = FontWeights::Bold;
	hPort->Text = "Port No-9081/9082";
	hPort->Width = 230;
	hPort->Height = 30;
	hStackPanelT3->Children->Add(hPort);
	TextBlock^ hSpacer2 = gcnew TextBlock();
	hSpacer2->Width = 10;
	hStackPanelT3->Children->Add(hSpacer2);
	hPortNo->Width = 50;
	hPortNo->Height = 25;
	hStackPanelT3->Children->Add(hPortNo);
	TextBlock^ hSpacer3 = gcnew TextBlock();
	hSpacer3->Width = 20;
	hStackPanelT3->Children->Add(hSpacer3);
	hPat->IsEnabled = false;
	hPat->FontFamily = gcnew Windows::Media::FontFamily("Tahoma");
	hPat->FontSize = 20;
	hPat->FontWeight = FontWeights::Bold;
	hPat->Text = "Pattern:";
	hPat->Width = 100;
	hPat->Height = 30;
	hStackPanelT3->Children->Add(hPat);
	TextBlock^ hSpacer4 = gcnew TextBlock();
	hSpacer4->Width = 20;
	hStackPanelT3->Children->Add(hSpacer4);
	hpattern2->Width = 50;
	hpattern2->Height = 25;
	hStackPanelT3->Children->Add(hpattern2);
	TextBlock^ hSpacer5 = gcnew TextBlock();
	hSpacer5->Width = 20;
	hStackPanelT3->Children->Add(hSpacer5);
	htext->IsEnabled = false;
	htext->FontFamily = gcnew Windows::Media::FontFamily("Tahoma");
	htext->FontSize = 20;
	htext->FontWeight = FontWeights::Bold;
	htext->Text = "Text:";
	htext->Width = 70;
	htext->Height = 30;
	hStackPanelT3->Children->Add(htext);
}

//-----------------------------------------------------<Helper function for the Tab3- Text search>------------------------------------------
void WPFCppCliDemo::setConnect3()
{
	TextBlock^ hSpacer6 = gcnew TextBlock();
	hSpacer6->Width = 20;
	hStackPanelT3->Children->Add(hSpacer6);
	hsearchText->Width = 200;
	hsearchText->Height = 25;
	hStackPanelT3->Children->Add(hsearchText);
	hStackPanelT3->Orientation = Orientation::Horizontal;
	hStackPanelT3->HorizontalAlignment = System::Windows::HorizontalAlignment::Left;
	hTextSearchGrid->SetRow(hStackPanelT3, 2);
	hTextSearchGrid->Children->Add(hStackPanelT3);
}

//------------------------------------------------------<Function to set up the Tab3 of the window>------------------------------------------
void WPFCppCliDemo::setUpConnectionView()
{
  Console::Write("\n  setting up Connection view");
  hTextSearchGrid->Margin = Thickness(20);
  hTextTab->Content = hTextSearchGrid;
  setConnect1();
  setConnect2();
  setConnect3();
}

//-------------------------------------------------------<Function which is called when the window is loaded>----------------------------------
void WPFCppCliDemo::OnLoaded(Object^ sender, RoutedEventArgs^ args)
{
  Console::Write("\n  Window loaded");
}

//--------------------------------------------------------<Function which is called when the window is closed>---------------------------------
void WPFCppCliDemo::Unloading(Object^ sender, System::ComponentModel::CancelEventArgs^ args)
{
  Console::Write("\n  Window closing");
}

[STAThread]
//int _stdcall WinMain()
int main(array<System::String^>^ args)
{
  Console::WriteLine(L"\n Starting WPFCppCliDemo");

  Application^ app = gcnew Application();
  app->Run(gcnew WPFCppCliDemo());
  //Console::WriteLine(L"\n\n");
  Console::ReadLine();
}