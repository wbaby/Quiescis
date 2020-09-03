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

# Features
- ⚙️ Autorun
- 📋 Information of system
- 🔭 Browse directories, delete files / folders
- ✔️ View all processes
- Ability to delete a process
- 🖋️ Real time keylogger
- 🔒 Encrypting files and directories
- 🔌 Shutting down the operating system
- 😄 Throw Error MessageBox

# Commands
|   command   |                                     description                                    |

| ----------- |:-----------------------------------------------------------------------------------|

|     pwd     |  find out current directory                                                        |

|     ls      |  look at some directory                                                            |

|     rm      |  delete a file                                                                     |

|    rmdir    |  delete a directory                                                                |

|    file     |  download file from victim up to 65 kb                                             |

|  ifconfig   |  network information                                                               |

|   upfile    |  upload file to victim up to to 65 kb                                              |

|   sysinfo   |  all system information                                                            |

|  keylogger  |  activate keylogger                                                                |

|   crypt     |  encryption using AES. you have two options for encryption: encryption of one file |

|             |  or directory, if you choose to encrypt a directory, all files in it will be       |

|             |  encrypted, but internal directories will not be decrypted                         |

|  shutdown   |  shutting down the 

#  Donate

    monero: 

    48TmwHGVsqSKgD7giTALoK7P2muKLTJn5R8s5XtKZL1jEr4MJFBAwczVtofuFGvzsT1CzTcFXotwZCDno1UsskqFFZe9wVC

***

    bitcoin:

    18LKUKWAUBAFKzLBdFFkt687vh8rMPhL1u

***

    ethereum:

    0x189a9436b2fbBd0b1C3927E8a398379DBb7105AA
