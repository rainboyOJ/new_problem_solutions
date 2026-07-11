/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 18:20
 * update_at: 2026-07-11 18:24
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 15;

int n;
int a[MAXN];

vector<int> get_best_lineup(vector<int> cur) {
    vector<int> res;
    int suffix_max = -1;

    for (int i = (int)cur.size() - 1; i >= 0; i--) {
        if (cur[i] >= suffix_max) {
            suffix_max = cur[i];
            res.push_back(cur[i]);
        }
    }

    reverse(res.begin(), res.end());
    return res;
}

bool lex_greater_vec(vector<int> x, vector<int> y) {
    int len = min((int)x.size(), (int)y.size());
    for (int i = 0; i < len; i++) {
        if (x[i] != y[i]) {
            return x[i] > y[i];
        }
    }
    return x.size() > y.size();
}

void solve_one_case() {
    cin >> n;
    vector<int> origin;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        origin.push_back(a[i]);
    }

    vector<int> best = get_best_lineup(origin);

    // 枚举把 old_pos 位置的牛移动到它之前的 insert_pos。
    for (int old_pos = 0; old_pos < n; old_pos++) {
        for (int insert_pos = 0; insert_pos <= old_pos; insert_pos++) {
            vector<int> cur = origin;
            int value = cur[old_pos];
            cur.erase(cur.begin() + old_pos);
            cur.insert(cur.begin() + insert_pos, value);

            vector<int> candidate = get_best_lineup(cur);
            if (lex_greater_vec(candidate, best)) {
                best = candidate;
            }
        }
    }

    for (int i = 0; i < (int)best.size(); i++) {
        if (i > 0) {
            cout << ' ';
        }
        cout << best[i];
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve_one_case();
    }

    return 0;
}
