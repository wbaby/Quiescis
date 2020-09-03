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
   - cd server/server<br/>
   - set Config.h, change PORT<br/>
   - g++ server.cpp -w<br/>
   - ./a.out<br/>
   
### <b>Windows</b>:<br/>
   - cd server<br/>
   - open server.sln in Visual Studio<br/>
   - change PORT in Config.h<br/>
   - compile Ctrl + F5<br/>
   - server.exe in Debug/<br/>
   
## Client
    - Open in Visual Studio client/client.sln

    - Change IP and PORT in Config.h
    - Compile Ctrl + F5
