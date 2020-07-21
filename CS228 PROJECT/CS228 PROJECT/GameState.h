#pragma once
#include <vector>
#include <string>

class GameState
{
public:
    virtual void Load() = 0;
    virtual void Update(double dt) = 0;
    virtual void Unload() = 0;
    virtual void Draw() = 0;
    virtual std::string GetName() = 0;
private:
};