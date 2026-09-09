/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-28 23:40
 * update_at: 2026-08-28 23:40
 */
// main.cpp：带走至多 m 本书，求最大总收益。
// 思路：基准转换——默认全部不带走（基准 = Σ b_i），
// 把第 i 本书改为带走只带来与其他书无关的变化 d_i = a_i - b_i，
// 所以只取 d_i > 0 的中最大的前 m 个累加。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500005;

int n, m;              // 书的数量、最多可带走数量
long long a[MAXN];     // a[i]：带走第 i 本书的收益
long long b[MAXN];     // b[i]：不带走第 i 本书的收益
long long diff[MAXN];  // diff[1..cnt]：正边际收益 d_i = a_i - b_i
int cnt;               // 正边际收益的个数

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];

    long long base = 0; // 基准收益：所有书都不带走
    for (int i = 1; i <= n; i++) {
        base += b[i];
        long long d = a[i] - b[i];
        if (d > 0) diff[++cnt] = d; // 只有 d > 0 的书才值得带走
    }

    // 正边际收益超过 m 个时，只保留最大的前 m 个
    if (cnt > m) {
        nth_element(diff + 1, diff + m + 1, diff + cnt + 1,
                    greater<long long>());
        cnt = m;
    }

    long long extra = 0; // 被带走的书贡献的边际收益之和
    for (int i = 1; i <= cnt; i++) extra += diff[i];

    cout << base + extra << '\n';
    return 0;
}
