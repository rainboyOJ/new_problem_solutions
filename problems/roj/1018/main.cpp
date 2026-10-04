/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 22:38
 * update_at: 2026-10-04 22:38
 */
#include <iostream>

using namespace std;

typedef long long ll;

int main() {
    // 用 sizeof 测量类型的存储宽度（单位：字节），不是对象大小
    ll bool_size = sizeof(bool); // bool 在常见编译器下占 1 字节
    ll char_size = sizeof(char); // char 按定义恰占 1 字节

    // 本题无输入，直接按先 bool 后 char 的顺序输出
    cout << bool_size << " " << char_size << endl;
    return 0;
}
