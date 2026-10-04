/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 04:48
 * update_at: 2026-10-05 04:48
 */
#include <cstdio>
#include <iostream>

using namespace std;

typedef long long ll;

const int MOD = 32767;      // 题目要求的模数
const int MAXK = 1000000;   // k 的上界（严格小于 1e6，取 1e6 足够）

int pell[MAXK + 1];         // pell[k] 表示第 k 项对 MOD 取模的结果
int query[MAXK];            // 所有询问，最多 MAXK 个

// 预计算 Pell 数列到 limit，pell[k] 直接保存取模后的答案
void build_pell(int limit) {
    pell[1] = 1;
    pell[2] = 2;
    for (int i = 3; i <= limit; i++) {
        pell[i] = (2 * pell[i - 1] + pell[i - 2]) % MOD;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    int max_k = 0;
    for (int i = 0; i < n; i++) {
        cin >> query[i];
        if (query[i] > max_k) max_k = query[i];
    }

    build_pell(max_k);

    for (int i = 0; i < n; i++) {
        cout << pell[query[i]] << '\n';
    }

    return 0;
}
