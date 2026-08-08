// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;

int n;
int a[MAXN];
map<int, int> cnt;
int best_answer;

void dfs(map<int, int> current_cnt, int current_min_len, bool has_group) {
    bool empty = true;
    int start = 0;
    for (map<int, int>::iterator it = current_cnt.begin(); it != current_cnt.end(); ++it) {
        if (it->second > 0) {
            empty = false;
            start = it->first;
            break;
        }
    }

    if (empty) {
        if (has_group) {
            best_answer = max(best_answer, current_min_len);
        }
        return;
    }

    vector<int> group;
    int x = start;
    while (current_cnt[x] > 0) {
        current_cnt[x]--;
        group.push_back(x);
        int next_min = has_group ? min(current_min_len, (int)group.size()) : (int)group.size();
        dfs(current_cnt, next_min, true);
        x++;
    }
    for (int i = 0; i < (int)group.size(); i++) {
        current_cnt[group[i]]++;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        cnt[a[i]]++;
    }

    best_answer = 0;
    dfs(cnt, n, false);
    cout << best_answer << '\n';
    return 0;
}
