//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#ifndef SCENES_BLACKBOARD_H
#define SCENES_BLACKBOARD_H

class Blackboard
{
public:
    int moveDirX = 0;
    int moveDirY = 0;
    int targetX = 0;
    int targetY = 0;
    int startX = 0;
    int startY = 0;
    int reachX = 0;
    int reachY = 0;

    void Reset()
    {
        moveDirX = 0;
        moveDirY = 0;
        targetX = 0;
        targetY = 0;
        startX = 0;
        startY = 0;
        reachX = 0;
        reachY = 0;
    }
};

#endif
