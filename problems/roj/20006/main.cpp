/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 02:18
 * update_at: 2026-10-06 02:18
 */

#include <iostream>
#include <cstdio>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    char ch;
    bool is_open = true; // 下一个双引号是开引号（左）还是闭引号（右）
    while (cin.get(ch)) {
        if (ch == '"') {
            // 第奇数个双引号输出左引号，第偶数个输出右引号
            if (is_open) cout << "``";
            else cout << "''";
            is_open = !is_open; // 翻转奇偶状态
        } else {
            cout << ch;
        }
    }
    return 0;
}
