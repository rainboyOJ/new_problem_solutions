/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:39
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXL = 260;

int n, m, levels;
int count_value[MAXL];   // count_value[x] 记录灰度值为 x 的像素个数

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> levels;
    // 逐个读入像素，累加对应灰度值的频次
    for (int i = 0; i < n * m; i++) {
        int value;
        cin >> value;
        count_value[value]++;
    }
    // 按灰度值从小到大输出频次
    for (int i = 0; i < levels; i++) {
        if (i) cout << ' ';
        cout << count_value[i];
    }
    cout << '\n';
    return 0;
}