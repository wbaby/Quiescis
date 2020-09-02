#include <iostream>
#include <ctime>
#include "Menu.h"

#ifndef  __linux__
	#pragma warning(disable: 4996)
#endif

void PrintGreeting() {
	std::cout << 
		   "      * ***                                                                               \n"
		<< "    *  ****                    *                                       *                  \n" 
		<< "   *  *  ***                  ***                                     ***                 \n" 
		<< "  *  **   ***                  *                                       *                  \n" 
		<< " *  ***    *** **   ****                          ****                          ****      \n" 
		<< "**   **     **  **    ***  * ***        ***      * **** *    ****    ***       * **** *   \n" 
		<< "**   **     **  **     ****   ***      * ***    **  ****    * ***  *  ***     **  ****    \n"
		<< "**   **     **  **      **     **     *   ***  ****        *   ****    **    ****         \n"
		<< "**   **     **  **      **     **    **    ***   ***      **           **      ***        \n"
		<< "**   **     **  **      **     **    ********      ***    **           **        ***      \n"
		<< " **  ** *** **  **      **     **    *******         ***  **           **          ***    \n"
		<< "  ** *   ****   **      **     **    **         ****  **  **           **     ****  **    \n"
		<< "   ***     ***   ******* **    **    ****    * * **** *   ***     *    **    * **** *     \n"
		<< "    ******* **    *****   **   *** *  *******     ****     *******     *** *    ****      \n"
		<< "      ***   **                  ***    *****                *****       ***               \n"
		<< "            **                                     -------------------------------------- \n"
		<< "            *                                      |  Quiescis Rat                      | \n"
		<< "           *                                       |  development by Nikait             | \n"
		<< "          *                                        |  github: https://github.com/Nikait | \n"
		<< "                                                   -------------------------------------- \n" << std::endl;
}

void HelpMenu() {
	std::cout <<  "\t\t     HELP [MENU]\n" << "\nbase:\n"
		<< "-----------------------------------------------------\n"
		<< "| [close]        - close connection                 |\n"
		<< "| [pwd]          - path                             |\n"
		<< "| [ls]           - list files and dirs              |\n"
		<< "| [rm] [rmdir]   - delete file; delete directory    |\n"
		<< "| [sysinfo]      - system information               |\n"
		<< "-----------------------------------------------------\n"
		<< "\nadvanced:\n"
		<< "-----------------------------------------------------\n"
		<< "| [ps]           - process info                     |\n"
		<< "| [kill]         - kill process                     |\n"
		<< "| [keylogger]    - start keylogger                  |\n"
		<< "| [cryptfile]    - encrypt file      with using XOR |\n"
		<< "| [cryptdir]     - encrypt directory with using XOR |\n"
		<< "-----------------------------------------------------\n"
		<< "\ntrolling:\n"
		<< "-----------------------------------------------------\n"
		<< "| [shutdown]     - shuting down                     |\n"
		<< "| [error]        - print error                      |\n"
		<< "-----------------------------------------------------\n" << std::endl;
}

void timenow() {
	char time_buf[80];
	time_t seconds = time(NULL);
	tm* timeinfo = localtime(&seconds);
	const char* format = "%H:%M:%S";
	strftime(time_buf, 80, format, timeinfo);

	std::cout << time_buf;
}

