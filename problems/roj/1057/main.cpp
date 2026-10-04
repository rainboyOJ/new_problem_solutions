/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 23:43
 * update_at: 2026-10-04 23:43
 */
#include <iostream>
using namespace std;
typedef long long ll;

int main() {
    // 读入两个整数和一个操作符
    ll a, b;
    char op;
    if (!(cin >> a >> b >> op)) return 0;

    // 先判断操作符是否合法，非法优先于除零报错
    bool valid = (op == '+' || op == '-' || op == '*' || op == '/');
    if (!valid) {
        cout << "Invalid operator!" << endl;
        return 0;
    }

    // 合法操作符下，再判断除数为零（只对除法生效）
    if (op == '/' && b == 0) {
        cout << "Divided by zero!" << endl;
        return 0;
    }

    // 按操作符分支计算；C++ / 是向零取整
    if (op == '+') cout << a + b << endl;
    else if (op == '-') cout << a - b << endl;
    else if (op == '*') cout << a * b << endl;
    else cout << a / b << endl; // op == '/'

    return 0;
}