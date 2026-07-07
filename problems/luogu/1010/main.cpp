#include <iostream>
using namespace std;
int n;


void dfs(int n) {
    if( n == 1) {
        cout << "2(0)";
        return;
    }
    if( n == 2) {
        cout << "2";
        return;
    }
    //找到最后一个为 1 的位置
    int last = -1;
    for(int i =31;i>=0;i--) {
        if( ((1LL<<i)& n )!= 0)
            last = i;
    }

    for(int i =31;i>=0;i--){
        if( ((1LL<<i)& n )!= 0)
        {
            //得到 2^i,需要分解
            if( i == 0)
                cout <<"2(0)";
            else if( i == 1)
                cout << 2;
            else{
                cout << "2(";
                dfs(i);
                cout << ")";
            }

            if( i !=last)
                cout << "+";
        }
    }
}
int main() {
    cin >> n;
    dfs(n);

    return 0;
}
