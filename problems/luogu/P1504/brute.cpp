#include <bits/stdc++.h>
using namespace std;

// 暴力做法：把每座城堡能保留的高度全部枚举出来，再取交集。
// 这能直接对应题意，适合小数据验证。

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<int>> heights(n);
    for (int i = 0; i < n; i++) {
        int x, sum = 0;
        heights[i].push_back(0);
        while (cin >> x && x != -1) {
            sum += x;
            heights[i].push_back(sum);
        }
    }

    int answer = 0;
    for (int h : heights[0]) {
        bool ok = true;
        for (int i = 1; i < n && ok; i++) {
            if (!binary_search(heights[i].begin(), heights[i].end(), h)) {
                ok = false;
            }
        }
        if (ok) {
            answer = max(answer, h);
        }
    }

    cout << answer << '\n';

    return 0;
}
