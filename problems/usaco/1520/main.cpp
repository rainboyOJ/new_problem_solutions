/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 20:31
 * update_at: 2026-07-11 20:32
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 100005;
const int MAXC = 11;

int n, m;
int parent_node[MAXN];
int difficulty[MAXN];
ll enjoyment[MAXN];
ll sum_enjoy[MAXN];               // sum_enjoy[i] 表示从 i 滑到 1 的总乐趣
int top_diff[MAXN][MAXC];         // top_diff[i][k] 表示路径上第 k+1 大难度
pair<int, ll> info[MAXC][MAXN];   // 对每个 c 存 (第 c+1 大难度, 总乐趣)

void insert_difficulty(int node, int value) {
    for (int i = 0; i < MAXC; i++) {
        top_diff[node][i] = top_diff[parent_node[node]][i];
    }

    for (int i = 0; i < MAXC; i++) {
        if (value > top_diff[node][i]) {
            for (int j = MAXC - 1; j > i; j--) {
                top_diff[node][j] = top_diff[node][j - 1];
            }
            top_diff[node][i] = value;
            break;
        }
    }
}

void build_tables() {
    for (int c = 0; c < MAXC; c++) {
        for (int i = 1; i <= n; i++) {
            info[c][i] = make_pair(top_diff[i][c], sum_enjoy[i]);
        }

        sort(info[c] + 1, info[c] + n + 1);

        for (int i = 2; i <= n; i++) {
            if (info[c][i].second < info[c][i - 1].second) {
                info[c][i].second = info[c][i - 1].second;
            }
        }
    }
}

ll answer_query(int skill, int courage) {
    pair<int, ll> target = make_pair(skill + 1, -1LL);
    pair<int, ll> *it = lower_bound(info[courage] + 1, info[courage] + n + 1, target);
    int pos = (int)(it - info[courage]) - 1;
    return info[courage][pos].second;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    for (int i = 0; i < MAXC; i++) {
        top_diff[1][i] = -1;
    }
    sum_enjoy[1] = 0;

    for (int i = 2; i <= n; i++) {
        cin >> parent_node[i] >> difficulty[i] >> enjoyment[i];
        sum_enjoy[i] = sum_enjoy[parent_node[i]] + enjoyment[i];
        insert_difficulty(i, difficulty[i]);
    }

    build_tables();

    cin >> m;
    for (int i = 1; i <= m; i++) {
        int skill, courage;
        cin >> skill >> courage;
        cout << answer_query(skill, courage) << '\n';
    }

    return 0;
}
