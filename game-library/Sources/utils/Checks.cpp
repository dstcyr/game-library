//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#include "Config.h"

#if defined(_DEBUG)

bool DoAssert(const bool aValue, const char* aFile, const int aLn, const char* aMsg)
{
    if (!aValue) 
    {
        char tBuffer[4096];
        char tPrgName[260];
        HWND hWndParent = GetActiveWindow();
        GetModuleFileName(nullptr, tPrgName, sizeof(tPrgName));
        char* tPrg = (strrchr(tPrgName, '\\')) + 1;
        const char* tSrcFile = (strrchr(aFile, '\\'));

        if (nullptr == tSrcFile) 
        {
            tSrcFile = aFile;
        }
        else 
        {
            tSrcFile += 1;
        }

        wsprintf(tBuffer, "%s\n\nProgram: %s\nFile: %s\nLine: %d", aMsg, tPrg, tSrcFile, aLn);

        int tResult = MessageBox(hWndParent, tBuffer, "Debug Assertion Failed",
            MB_TASKMODAL | MB_SETFOREGROUND |
            MB_ABORTRETRYIGNORE | MB_ICONEXCLAMATION);

        if (tResult == IDABORT) 
        {
            exit(0);
        }

        return (tResult == IDRETRY);
    }

    return false;
}

#endif