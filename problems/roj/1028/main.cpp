/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 22:51
 * update_at: 2026-10-04 22:51
 */

#include <iostream>
#include <cstdlib>
using namespace std;

typedef long long ll;

const int SIZE = 5;          // 菱形共 5 行
const int MID = SIZE / 2;    // 最宽的中间行行号（0 起）

char ch;                     // 输入字符

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> ch;               // 输入只有一个字符

    // 第 r 行离中间行的距离 gap 就是前导空格数，字符数为 SIZE - 2*gap
    for (int r = 0; r < SIZE; r++) {
        int gap = abs(r - MID);
        for (int i = 0; i < gap; i++) cout << ' ';
        for (int i = 0; i < SIZE - 2 * gap; i++) cout << ch;
        cout << '\n';
    }

    return 0;
}
