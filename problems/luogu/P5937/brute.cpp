/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-16 17:48
 * update_at: 2026-07-21 09:53
 */
// brute.cpp：小数据暴力解，使用 01 序列递归枚举所有可能的原始序列。
#include <bits/stdc++.h>
using namespace std;

struct Query {
    int left;
    int right;
    int parity;
};

const int MAXN = 12;
const int MAXM = 20;

int n, m;
int choose_value[MAXN];
Query queries[MAXM];
int answer;

void check_sequence() {
    int prefix[MAXN + 1] = {};
    for (int i = 1; i <= n; i++) {
        prefix[i] = prefix[i - 1] ^ choose_value[i];
    }

    int satisfied = 0;
    for (int i = 0; i < m; i++) {
        int actual = prefix[queries[i].right] ^ prefix[queries[i].left - 1];
        if (actual != queries[i].parity) {
            break;
        }
        satisfied++;
    }
    answer = max(answer, satisfied);
}

void dfs(int position) {
    if (position == n + 1) {
        check_sequence();
        return;
    }

    choose_value[position] = 0;
    dfs(position + 1);
    choose_value[position] = 1;
    dfs(position + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        string word;
        cin >> queries[i].left >> queries[i].right >> word;
        queries[i].parity = (word == "odd");
    }

    answer = 0;
    dfs(1);
    cout << answer << '\n';
    return 0;
}
