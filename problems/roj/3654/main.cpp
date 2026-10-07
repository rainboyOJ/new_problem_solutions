/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 16:00
 * update_at: 2026-10-06 16:00
 */

#include <iostream>
#include <string>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    getline(cin, s);          // 读入整行（包含空格）
    int cnt = 0;
    for (size_t i = 0; i < s.size(); i++) {
        char ch = s[i];
        if (ch != ' ' && ch != '\n' && ch != '\r')
            cnt++;
    }
    // 注意：题目说输入只有一行，getline 读整行即可；
    // 若标题跨行，应改用循环读完整份输入再统一过滤。
    cout << cnt << '\n';
    return 0;
}
