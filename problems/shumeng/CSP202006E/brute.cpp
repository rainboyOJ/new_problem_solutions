/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 20:46
 */
// brute.cpp：递归枚举每种商品的不买或所有合法购买数量。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 15;

struct Relation {
    int type, x, y;
};

int n, m, left_bound[MAXN], right_bound[MAXN], a[MAXN], b[MAXN], c[MAXN], amount[MAXN];
long long best_answer = 0;
vector<Relation> relation;

long long get_value(int i, int x) {
    return 1LL * a[i] * x * x + 1LL * b[i] * x + c[i];
}

void dfs(int position, long long value) {
    if (position > n) {
        for (int i = 0; i < (int)relation.size(); i++) {
            Relation now = relation[i];
            if (now.type == 1 && amount[now.y] > 0 && amount[now.x] == 0) return;
            if (now.type == 2 && (amount[now.y] == left_bound[now.y] || amount[now.y] == right_bound[now.y])
                    && amount[now.x] == 0) return;
        }
        best_answer = max(best_answer, value);
        return;
    }
    amount[position] = 0;
    dfs(position + 1, value);
    for (int x = left_bound[position]; x <= right_bound[position]; x++) {
        amount[position] = x;
        dfs(position + 1, value + get_value(position, x));
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> left_bound[i] >> right_bound[i] >> a[i] >> b[i] >> c[i];
    for (int i = 1; i <= m; i++) {
        Relation now;
        cin >> now.type >> now.x >> now.y;
        relation.push_back(now);
    }
    dfs(1, 0);
    cout << best_answer << '\n';

    return 0;
}
