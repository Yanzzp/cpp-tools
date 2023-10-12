#include "lib/multithread.h"
#include "lib/FFmpegTool.h"
#include "lib/MyTools.h"
#include "lib/InputSimulator.h"

using namespace std;



int main() {
    MyTools myTools;

//    eazy_multithread_functions(
//            cout<< "Hello world"<<endl;
//            get_function_running_time(
//                    myTools.multithread_get_folder_size("D:\\zpplibrary\\tencentcloud-sdk-cpp-master",true);
//                    );
//            get_function_running_time(
//                    myTools.get_folder_size("D:\\zpplibrary\\tencentcloud-sdk-cpp-master");
//                    );
//            ,true);
    myTools.delete_files("E:\\分类","开发");

    return 0;
}
