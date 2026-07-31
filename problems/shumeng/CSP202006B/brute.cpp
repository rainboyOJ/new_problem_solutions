/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 20:34
 */
// brute.cpp：用映射保存第一个稀疏向量，逐项查询第二个向量。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, a, b;
    cin >> n >> a >> b;
    map<int, int> first;
    for (int i = 0; i < a; i++) {
        int index, value;
        cin >> index >> value;
        first[index] = value;
    }
    long long answer = 0;
    for (int i = 0; i < b; i++) {
        int index, value;
        cin >> index >> value;
        answer += 1LL * first[index] * value;
    }
    cout << answer << '\n';

    return 0;
}
