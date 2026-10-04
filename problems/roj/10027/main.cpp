/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 22:06
 * update_at: 2026-10-04 22:06
 */
#include <iostream>
#include <string>

using namespace std;

typedef long long ll;

string text;  // 第一行：待编码的字符串，只含大写字母和空格
string table; // 第二行：table[i] 表示字母 'A' + i 编码后变成的字母

int main() {
    getline(cin, text);
    getline(cin, table);

    ll len = text.size();
    for (ll i = 0; i < len; i++) {
        char c = text[i];
        if (c >= 'A' && c <= 'Z') {
            cout << table[c - 'A']; // 大写字母按下标 c-'A' 查表
        } else {
            cout << c; // 空格等非大写字母原样输出
        }
    }
    cout << "\n";
    return 0;
}
