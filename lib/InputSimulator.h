#ifndef CPP_TOOLS_INPUTSIMULATOR_H
#define CPP_TOOLS_INPUTSIMULATOR_H
#include <iostream>
#include <utility>
#include <vector>

class InputSimulator {
private:

public:
    void set_position(int x, int y);

    void mouse_single_click();

    void rich_click(int x,int y,int times,bool isSmooth = false);

    void smooth_movement(int OriginX,int OriginY,int TargetX,int TargetY);
};


#endif //CPP_TOOLS_INPUTSIMULATOR_H
