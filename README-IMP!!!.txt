The project demonstrates "Remote Code Management Facility".

Below is the small note regarding the working of the application.

-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=

Screen:1- File Search

1.In the file search GUI, we enter the path and pattern. 

2.Please note that as we are runningthrough the run.bat file, the path taken
is that of the Debug folder. 

3.So if we needto search the server, the path to be enter is "../Server".

4.Hence the application will search all the files on this path.

5.Pattern could be input as any.

-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=

Screen:2- File Upload/File Download

1. Screen-2 has both the file upload and file download functionality.

2. File upload is just selecting the folder/ Then selecting the file and clicking
on File Upload.The uploaded file could be seen at "Server/DownloadedFiles" Folder.

3. Also plz note that, we are starting 2 servers at port 9081/9082. But we are uploading
the files on the server-9081.

4.Separate server functionality has been implement for text search as asked in the requirement.

5. For file download, we need to specify the entire path of the file and the name.
Again note that, the path is from Debug. So, for e.g. you need to enter the path,
"../Server/TestPath/Ana.cs" if you need to download this file. Or other path as per
the directory. 

6.The downloaded files on the client could be seen at "CppCli-WPF-App/DownloadedFiles".


-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=

Screen:3- Text Search

1. Screen-3 is for the text search requirement. Here, port no could be any 1 of the 2,
9081 and 9082, because we are starting servers only on these two ports.

2. Text search on server is done only relative to the server path. "../Server". Hence
all the files in the server would be searched, based on the pattern and the results
have been displayed as per the requirement.


-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-
Additional logging has been made on the server/client's console.


Thank you.
