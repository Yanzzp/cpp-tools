//#include "mytools.h"
//#include "ffmpegTool.h"
#include "multithread.h"

void test1213(){
    std::cout<< "test123123123"<<std::endl;
}

int main() {

    complex_multithread_functions(true,true,
                                []() {
                                    std::cout << "Thread ID: " << std::this_thread::get_id() << "  " << 1 << std::endl;
                                },
                                []() {
                                    std::cout << "Thread ID: " << std::this_thread::get_id() << "  " << 2 << std::endl;
                                },
                                []() {
                                    std::cout << "Thread ID: " << std::this_thread::get_id() << "  " << 3 << std::endl;
                                },
                                []() {
                                    std::cout << "Thread ID: " << std::this_thread::get_id() << "  " << 4 << std::endl;
                                },
                                test1213

    );


//    eazy_multithread_functions(
//            std::cout << "Thread ID: " << std::this_thread::get_id() << "  " << 4 << std::endl;
//            std::cout << "Thread ID: " << std::this_thread::get_id() << "  " << 4 << std::endl;
//            ,true);
//
//    get_function_running_time(
//
//            for (int i;i<1000;++i) {
//                std::cout<< "test"<<std::endl;
//            }
//
//            )
    for(auto i:test){
        i();
    }
    get_function_running_time(
            multithread_functions(test,true);
            std::cout<< "test"<<std::endl;
            );
    return 0;
}

