# Quiescis 1.1

<b>Quescis</b> is a powerful Remote Access Trojan for windows computer on C++

## Update 1.1

     1. Сolored text
     (supported for Linux distributions and windows)
     2. Bug fix

![alt text](img/header.png)

# Installing
## Server

    - Clone this repository 
    - Get a static ip or purchase VDS
    - Server Questions cross platform
      you can run it on linux distributions
      and windows

   
### <b>Linux distributions</b>:<br/>
   - cd server/server
   - set Config.h, change PORT
   - g++ server.cpp -w
   - ./a.out
   
### <b>Windows</b>:<br/>
   - cd server
   - open server.sln in Visual Studio
   - change PORT in Config.h
   - compile Ctrl + F5
   - server.exe in Debug/
   
## Client
    - Open in Visual Studio client/client.sln
    - Change IP and PORT in Config.h
    - Compile Ctrl + F5

# Features
- ⚙️ Autorun
- 📋 Information of system
- 🔭 Browse directories, delete files / folders

![alt text](img/ls.png)

![alt text](img/rm.png)

- ✔️ View all processes

![alt text](img/ps.png)

- Ability to delete a process

![alt text](img/kill.png)

- 🖋️ Real time keylogger

![alt text](img/keylogger.png)

- 🔒 Encrypting files and directories

before:

![alt text](img/cryptfile_before.png)

after:

![alt text](img/cryptfile_after.png)

- 🔌 Shutting down the operating system
- 😄 Throw Error MessageBox

![alt text](img/error.png)

# Commands
|   command   |                   description               |
| ----------- |:--------------------------------------------|
|     pwd     |  find out current directory                 |
|     ls      |  list files and dirs                        |
|  rm, rmdir  |  delete file; delete directory              |
|   sysinfo   |  system information                         |
|     ps      |  process info                               |
|    kill     |  kill process                               |
|  keylogger  |  start  keylogger (real time)               |
|  cryptfile  |  encrypt file        with using XOR         |
|  cryptdir   |  encrypt directory   with using XOR         |
|  shutdown   |  shutting down                              |
|   error     |  throw error MessageBox                     |

#  Donate
    monero: 
    48TmwHGVsqSKgD7giTALoK7P2muKLTJn5R8s5XtKZL1jEr4MJFBAwczVtofuFGvzsT1CzTcFXotwZCDno1UsskqFFZe9wVC

***
    bitcoin:
    18LKUKWAUBAFKzLBdFFkt687vh8rMPhL1u
***
    ethereum:
    0x189a9436b2fbBd0b1C3927E8a398379DBb7105AA


