/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 22:28
 */
// brute.cpp：枚举每个候选左下角，逐格比较完整藏宝图。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, limit, size;
    cin >> n >> limit >> size;
    vector<pair<int, int> > tree(n);
    set<pair<int, int> > exists;
    for (int i = 0; i < n; i++) {
        cin >> tree[i].first >> tree[i].second;
        exists.insert(tree[i]);
    }
    vector<vector<int> > map(size + 1, vector<int>(size + 1));
    int tree_count = 0;
    for (int row = size; row >= 0; row--) {
        for (int col = 0; col <= size; col++) {
            cin >> map[row][col];
            tree_count += map[row][col];
        }
    }
    int answer = 0;
    for (int i = 0; i < n; i++) {
        int x = tree[i].first, y = tree[i].second;
        if (x + size > limit || y + size > limit) continue;
        bool valid = true;
        for (int dx = 0; dx <= size && valid; dx++) {
            for (int dy = 0; dy <= size; dy++) {
                bool found = exists.count({x + dx, y + dy}) != 0;
                if (found != (map[dx][dy] != 0)) valid = false;
            }
        }
        if (valid) answer++;
    }
    cout << answer << '\n';
    return 0;
}
