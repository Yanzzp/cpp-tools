//#include "mytools.h"
//#include "Python.h"
//
//using namespace std;
//
//
//int main() {
////    mytools tools;
//
////    tools.create_txt_file("C:\\Users\\Administrator\\Desktop\\test\\test.txt");
//
//    Py_Initialize();
//    if(!Py_IsInitialized()){
//        cout << "python init fail" << endl;
//        return 0;
//    }
//    // 2、初始化python系统文件路径，保证可以访问到 .py文件
//    PyRun_SimpleString("import sys");
//    PyRun_SimpleString("sys.path.append('./script')");
//
//    // 3、调用python文件名，不用写后缀
//    PyObject* pModule = PyImport_ImportModule("sayhello");
//    if( pModule == NULL ){
//        cout <<"module not found" << endl;
//        return 1;
//    }
//    // 4、调用函数
//    PyObject* pFunc = PyObject_GetAttrString(pModule, "say");
//    if( !pFunc || !PyCallable_Check(pFunc)){
//        cout <<"not found function add_num" << endl;
//        return 0;
//    }
//    //
//    PyObject_CallObject(pFunc, NULL);
//    // 5、结束python接口初始化
//    Py_Finalize();
//    return 0;
//}



#include<Python.h>

int main() {
    Py_Initialize();

    PyRun_SimpleString("print ('hello')");

    PyRun_SimpleString("import numpy as np");

    Py_Finalize();

    system("pause");
    return 0;
}