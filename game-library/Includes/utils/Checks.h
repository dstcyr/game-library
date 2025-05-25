//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef UTILS_CHECKS_H
#define UTILS_CHECKS_H

#if defined(_DEBUG)

bool DoAssert(bool aValue, const char* aFile, int aLn, const char* aMsg);
#define BX_CHECKS(condition, message) if (DoAssert(condition, __FILE__, __LINE__, message)) { DebugBreak(); }
#define BX_FAIL(message)if(DoAssert(false, __FILE__, __LINE__, message)) { DebugBreak(); }

#else
#define BX_CHECKS(condition, message)
#define BX_FAIL(message)
#endif

#endif
