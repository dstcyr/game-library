//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#include "Config.h"
#include "utils/Stopwatch.h"

Stopwatch::Stopwatch() : start_time(std::chrono::high_resolution_clock::now())
{
}

void Stopwatch::Start()
{
    start_time = std::chrono::high_resolution_clock::now();
}

void Stopwatch::Stop()
{
    end_time = std::chrono::high_resolution_clock::now();
}

double Stopwatch::ElapsedMilliseconds()
{
    std::chrono::duration<double, std::milli> elapsed = end_time - start_time;
    return elapsed.count();
}