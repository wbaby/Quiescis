#include <stdio.h>
#include "Menu.h"

void PrintGreeting() {
	printf("%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s", 
			"      * ***                                                                               \n",
			"    *  ****                    *                                       *                  \n", 
			"   *  *  ***                  ***                                     ***                 \n", 
			"  *  **   ***                  *                                       *                  \n", 
			" *  ***    *** **   ****                          ****                          ****      \n", 
			"**   **     **  **    ***  * ***        ***      * **** *    ****    ***       * **** *   \n", 
			"**   **     **  **     ****   ***      * ***    **  ****    * ***  *  ***     **  ****    \n",
			"**   **     **  **      **     **     *   ***  ****        *   ****    **    ****         \n", 
			"**   **     **  **      **     **    **    ***   ***      **           **      ***        \n", 
			"**   **     **  **      **     **    ********      ***    **           **        ***      \n", 
			" **  ** *** **  **      **     **    *******         ***  **           **          ***    \n", 
			"  ** *   ****   **      **     **    **         ****  **  **           **     ****  **    \n", 
			"   ***     ***   ******* **    **    ****    * * **** *   ***     *    **    * **** *     \n", 
			"    ******* **    *****   **   *** *  *******     ****     *******     *** *    ****      \n", 
			"      ***   **                  ***    *****                *****       ***               \n", 
			"            **                                                                            \n", 
			"            *                                                                             \n", 
			"           *                                                                              \n", 
			"          *                                                                                 ");
	printf("\t\t\t\t\t\t\tQuiescis Rat\n\t\t\t\t\t\t\tdevelopment by Nikait\n\t\t\t\t\t\t\tgithub: https://github.com/Nikait\n\t\t\t\t\t\t\t\t\t\t     2020\n\n");
}

void HelpMenu() {
	printf("%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s",  "\t\t     HELP [MENU]\n", "\nbase:\n",
			"-----------------------------------------------------\n",
			"| [close]        - close connection                 |\n",
			"| [pwd]          - path                             |\n",
			"| [ls]           - list files and dirs              |\n",
			"| [rm] [rmdir]   - delete file; delete directory    |\n",
			"| [sysinfo]      - system information               |\n",
			"-----------------------------------------------------\n",
			"\nadvanced:\n",
			"-----------------------------------------------------\n",
			"| [ps]           - process info                     |\n",
			"| [kill]         - kill process                     |\n",
			"| [keylogger]    - start keylogger                  |\n",
			"| [cryptfile]    - encrypt file      with using XOR |\n",
			"| [cryptdir]     - encrypt directory with using XOR |\n",
			"-----------------------------------------------------\n",
			"\ntrolling:\n",
			"-----------------------------------------------------\n",
			"| [shutdown]     - shuting down                     |\n",
			"| [error]        - print error                      |\n",
			"-----------------------------------------------------\n");
}

