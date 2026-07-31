/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 20:54
 */
// brute.cpp：逐像素扫描，直接统计每种灰度的出现次数。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, levels;
    cin >> n >> m >> levels;
    int count[260] = {};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int value;
            cin >> value;
            count[value]++;
        }
    }
    for (int i = 0; i < levels; i++) cout << count[i] << (i + 1 == levels ? '\n' : ' ');
    return 0;
}
