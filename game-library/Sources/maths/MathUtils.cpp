//    ____                        _     _ _                          
//   / ___| __ _ _ __ ___   ___  | |   (_) |__  _ __ __ _ _ __ _   _ 
//  | |  _ / _` | '_ ` _ \ / _ \ | |   | | '_ \| '__/ _` | '__| | | |
//  | |_| | (_| | | | | | |  __/ | |___| | |_) | | | (_| | |  | |_| |
//   \____|\__,_|_| |_| |_|\___| |_____|_|_.__/|_|  \__,_|_|   \__, |
//                                                             |___/ 
//  Retro Game Library
//  Copyright(C) 2024-2025 David St-Cyr

#include "Config.h"

const float MathUtils::PI = 4.0F * atanf(1.0F);
const float MathUtils::TwoPI = 2.0F * PI;
const float MathUtils::PIOverTwo = 0.5F * PI;
const float MathUtils::PIOverFour = 0.25F * PI;
const float MathUtils::TO_RADIANS = PI / 180.0F;
const float MathUtils::TO_DEGREES = 180.0F / PI;

bool MathUtils::NearEqual(float lhs, float rhs)
{
    float diff = std::abs(rhs - lhs);
    return diff <= 0.0001F;
}

float MathUtils::RandRange(float min, float max)
{
    return min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
}

int MathUtils::RandRange(int min, int max)
{
    int range = max - min + 1;
    return rand() % range + min;
}

float MathUtils::DistanceBetweenPoints(float p1x, float p1y, float p2x, float p2y)
{
    float diffX = p1x - p2x;
    float diffY = p1y - p2y;
    float tLen = diffX * diffX + diffY * diffY;
    return std::sqrtf(tLen);
}
