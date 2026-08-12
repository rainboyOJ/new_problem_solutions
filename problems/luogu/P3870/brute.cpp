/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 21:48
 * update_at: 2026-08-12 21:48
 */
// brute.cpp：小数据暴力解，直接维护每盏灯的状态，用来理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

int n, m;
bool lamp[MAXN]; // lamp[i] = true 表示第 i 盏灯是亮的

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int c, a, b;
        cin >> c >> a >> b;
        if (c == 0) {
            // 区间取反：暴力逐盏翻转。
            for (int j = a; j <= b; j++)
                lamp[j] = !lamp[j];
        } else {
            // 区间查询：暴力数亮灯数量。
            int cnt = 0;
            for (int j = a; j <= b; j++)
                if (lamp[j])
                    cnt++;
            cout << cnt << '\n';
        }
    }
    return 0;
}
