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
    int n; // 第一行的数字个数
    cin >> n;
    int current = 1; // 当前要输出的数字
    // 每行宽度从 n 递减到 1
    for (int width = n; width >= 1; width--) {
        for (int j = 0; j < width; j++) {
            printf("%02d", current); // 两位数字，不足补前导 0
            current++;
        }
        cout << endl; // 每行结束换行
    }
    return 0;
}
