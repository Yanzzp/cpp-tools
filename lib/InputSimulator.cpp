#include "InputSimulator.h"

void InputSimulator::set_position(int x, int y) {
    SetCursorPos(x, y);
}

void InputSimulator::mouse_single_click() {
    INPUT input[2];
    memset(input, 0, sizeof(input));
    // 设置第一个输入事件为鼠标左键按下
    input[0].type = INPUT_MOUSE;
    input[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    // 设置第二个输入事件为鼠标左键释放
    input[1].type = INPUT_MOUSE;
    input[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
    // 模拟鼠标点击操作
    SendInput(2, input, sizeof(INPUT));
}

void InputSimulator::rich_click(int x, int y, int times, bool isSmooth) {
    POINT cursorPos;
    GetCursorPos(&cursorPos);
    if(isSmooth){
        smooth_movement(cursorPos.x, cursorPos.y, x, y);
    }else{
        set_position(x, y);
    }
    for (int i = 0; i < times; ++i) {
        mouse_single_click();
    }
}

void InputSimulator::smooth_movement(int OriginX, int OriginY, int TargetX, int TargetY) {
    POINT cursorPos;
    GetCursorPos(&cursorPos);
    std::pair<int, int> originPosition = std::make_pair(cursorPos.x, cursorPos.y);
    std::pair<int, int> targetPosition = std::make_pair(TargetX, TargetY);
    set_position(OriginX, OriginY);
    int x = OriginX;
    int y = OriginY;
    int dx = (TargetX - OriginX) / 100;
    int dy = (TargetY - OriginY) / 100;
    for (int i = 0; i < 100; ++i) {
        x += dx;
        y += dy;
        set_position(x, y);
        Sleep(1);
    }
    set_position(TargetX, TargetY);
}
