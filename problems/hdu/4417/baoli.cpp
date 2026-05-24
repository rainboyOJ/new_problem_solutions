#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

void solve(int caseNum) {
    int n, m;
    // 读取 n (道路长度) 和 m (查询次数)
    if (!(cin >> n >> m)) return;

    vector<int> h(n);
    // 读取每个砖块的高度
    for (int i = 0; i < n; ++i) {
        cin >> h[i];
    }

    printf("Case %d:\n", caseNum);

    // 处理 m 次查询
    for (int i = 0; i < m; ++i) {
        int L, R, H;
        cin >> L >> R >> H;

        int count = 0;
        // 暴力核心：直接遍历 L 到 R 区间
        // 题目保证 0 <= L <= R < n，所以不需要做边界检查
        for (int j = L; j <= R; ++j) {
            if (h[j] <= H) {
                count++;
            }
        }
        printf("%d\n", count);
    }
}

int main() {
    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        solve(i);
    }
    return 0;
}
