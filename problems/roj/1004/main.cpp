/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 22:15
 * update_at: 2026-10-04 22:15
 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    char c;
    cin >> c;

    // 第 row 行（row = 0,1,2）输出 2-row 个空格 + 2*row+1 个字符 c，行尾不留空格。
    for (int row = 0; row < 3; row++) {
        for (int i = 0; i < 2 - row; i++) cout << ' ';
        for (int i = 0; i < 2 * row + 1; i++) cout << c;
        if (row != 2) cout << '\n';
    }

    return 0;
}