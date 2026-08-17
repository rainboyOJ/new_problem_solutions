/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:39
 */
// brute.cpp：小数据暴力解，用映射保存第一个稀疏向量，再逐项查询第二个向量。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, a, b;
    cin >> n >> a >> b;
    map<int, int> first;           // 第一个稀疏向量：坐标 -> 非零值
    for (int i = 0; i < a; i++) {
        int index, value;
        cin >> index >> value;
        first[index] = value;
    }
    // 逐项读入第二个向量，在映射中查询同一坐标是否有非零值
    long long answer = 0;
    for (int i = 0; i < b; i++) {
        int index, value;
        cin >> index >> value;
        answer += 1LL * first[index] * value;   // 映射中不存在的坐标取 0
    }
    cout << answer << '\n';

    return 0;
}