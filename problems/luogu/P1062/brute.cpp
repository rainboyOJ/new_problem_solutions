/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 00:16
 * update_at: 2026-11-11 00:16
 */
// brute.cpp：通过优先队列/有序集合逐步扩展生成前 N 项
#include <iostream>
#include <queue>
#include <set>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long k;
    int n;
    if (!(cin >> k >> n)) return 0;

    // 预处理 k 的前若干次幂
    vector<long long> p;
    long long cur = 1;
    for (int i = 0; i < 12; ++i) {
        p.push_back(cur);
        cur *= k;
    }

    // 暴力生成前 n 项：直接对 1 到 n 拆位计算
    long long res = 0;
    for (int num = 1; num <= n; ++num) {
        long long val = 0;
        for (int i = 0; i < 12; ++i) {
            if ((num >> i) & 1) {
                val += p[i];
            }
        }
        res = val;
    }

    cout << res << "\n";

    return 0;
}
