#include  <iostream>
#include "lib/database//MySQLDatabase.h"


using namespace std;


int main() {
    MySQLDatabase myDb;
    if(myDb.connect("yanzzp.xyz","YanSQL","123zpy","ToolsDB")){
        cout << "连接成功" << endl;
    }

    return 0;
}