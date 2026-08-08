#include <bits/stdc++.h>
using namespace std;

int n, m, k;
string s[10];
int choose_id[10];
int choose_pos[10];
long long answer;

void check_current() {
    string base = s[choose_id[1]].substr(choose_pos[1], k);
    for (int i = 2; i <= m; i++) {
        if (s[choose_id[i]].substr(choose_pos[i], k) != base) {
            return;
        }
    }
    answer++;
}

void dfs_pos(int dep) {
    if (dep > m) {
        check_current();
        return;
    }
    int id = choose_id[dep];
    int limit = (int)s[id].size() - k;
    for (int pos = 0; pos <= limit; pos++) {
        choose_pos[dep] = pos;
        dfs_pos(dep + 1);
    }
}

void dfs_species(int dep, int last) {
    if (dep > m) {
        dfs_pos(1);
        return;
    }
    for (int i = last + 1; i <= n; i++) {
        if ((int)s[i].size() < k) {
            continue;
        }
        choose_id[dep] = i;
        dfs_species(dep + 1, i);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
    }

    // brute.cpp：先枚举选哪些物种，再枚举每个物种里长度为 k 的子串起点，最后检查是否完全相同。
    // 复杂度非常高，只适合小数据对拍。
    answer = 0;
    dfs_species(1, 0);
    cout << answer << '\n';

    return 0;
}
