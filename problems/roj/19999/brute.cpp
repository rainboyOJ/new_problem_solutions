/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-28 18:45
 * update_at: 2026-08-28 18:45
 */
// brute.cpp：小数据暴力解，直接双重循环枚举所有 f(i,j) 排序取第 k 大。
// 这是本题最直观的朴素做法，复杂度 O(n^2 log n)，只适合 n 很小的数据，
// 用于帮助理解题意，并与 main.cpp 对拍验证。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n;
long long k;                     // 第 k 大，k 最大 n(n-1)/2，用 long long
long long x[MAXN], y[MAXN];      // 每个点的 x_i, y_i

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> y[i];
    }

    // 枚举所有无序对 (i,j)，计算 f(i,j) 并收集起来
    vector<double> all;
    all.reserve((long long)n * (n - 1) / 2);
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            double f = (double)(x[i] * y[i] + x[j] * y[j]) / (x[i] + x[j]);
            all.push_back(f);
        }
    }

    // 从高到低排序，取第 k 个（下标 k-1）
    sort(all.begin(), all.end(), greater<double>());
    printf("%.4f\n", all[k - 1]);
    return 0;
}