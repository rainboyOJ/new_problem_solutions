/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 05:11
 * update_at: 2026-10-05 05:11
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 题目数据：m, n 都是 int 范围内的正整数，且 m+n <= 20；用 ll 只是保险。
int m, n;

// 逐步累乘计算 C(N, k) = N*(N-1)*...*(N-k+1) / k*(k-1)*...*1。
// 顺序乘法再除以同阶分母，避免中间出现非整数。
ll comb(int N, int k) {
    if (k < 0 || k > N) return 0;
    if (k > N - k) k = N - k; // 利用 C(N,k) = C(N,N-k) 减少乘法次数
    ll num = 1;
    ll den = 1;
    for (int i = 0; i < k; i++) {
        num *= (N - i);
        den *= (i + 1);
    }
    return num / den;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> m >> n;

    // 每条路线恰含 m-1 步上、n-1 步右；路线数等价于从 m+n-2 步里选 m-1 步作为上步，
    // 答案 = C(m+n-2, m-1)。
    cout << comb(m + n - 2, m - 1) << endl;

    return 0;
}