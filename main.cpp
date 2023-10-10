#include "lib/multithread.h"
#include "lib/FFmpegTool.h"
#include "lib/InputSimulator.h"


using namespace std;

int main() {

    InputSimulator click;
    click.rich_click(1500,500,0);

    return 0;
}
