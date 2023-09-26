#include "mytools.h"
#include "ffmpegTool.h"


using namespace std;



int main() {

//    mytools mytools;
//    ffmpegTool ffmpeg;

    get_function_run_time(
        cout << "1"<<endl;
                              cout << "Hello World!" << endl;
                              cout << "Hello World!" << endl;
                          );

    cout << "1231h2kj3hkjahskdjhaskdjhasd";

    get_function_run_time(
                              cout << "2"<<endl;
                              cout << "Hello World!" << endl;
                              cout << "Hello World!" << endl;
                          );
    get_function_run_time(
                              cout << "3"<<endl;
                              cout << "Hello World!" << endl;
                              cout << "Hello World!" << endl;
                          );

    get_function_running_time([]() {
        cout << "4"<<endl;
        cout << "Hello World!" << endl;
        cout << "Hello World!" << endl;
    });

    return 0;
}

