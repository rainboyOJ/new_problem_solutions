/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:40
 */
// brute.cpp：小数据暴力解，枚举每个候选左下角并逐格比较完整藏宝图。
#include <bits/stdc++.h>
using namespace std;

int n;
long long limit;
int s;
vector<pair<long long, long long> > tree;
set<pair<long long, long long> > exists; // 用集合记录每棵树的位置
vector<vector<int> > map_value;
int answer;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> limit >> s;
    tree.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> tree[i].first >> tree[i].second;
        exists.insert(tree[i]);
    }
    map_value.assign(s + 1, vector<int>(s + 1, 0));
    for (int row = s; row >= 0; row--) {
        for (int col = 0; col <= s; col++) {
            cin >> map_value[row][col];
        }
    }

    // 对每个树作为左下角，展开整个 (S+1)*(S+1) 窗口逐格比较
    for (int i = 0; i < n; i++) {
        long long x = tree[i].first, y = tree[i].second;
        if (x + s > limit || y + s > limit) continue;
        bool valid = true;
        for (int dx = 0; dx <= s && valid; dx++) {
            for (int dy = 0; dy <= s; dy++) {
                bool has_tree = exists.count({x + dx, y + dy}) != 0;
                if (has_tree != (map_value[dx][dy] != 0)) {
                    valid = false;
                    break;
                }
            }
        }
        if (valid) answer++;
    }

    cout << answer << '\n';
    return 0;
}