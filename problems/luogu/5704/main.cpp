/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    char ch; // 小写字母
    cin >> ch;
    // 小写字母的 ASCII 码比大写字母大 32，减 32 得到大写
    cout << (char)(ch - 32) << endl;
    return 0;
}
