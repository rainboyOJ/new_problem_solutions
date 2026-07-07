// brute_01_style.cpp：01 序列风格暴力，按花的下标依次决定保留或删除。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 30;

int n;
int h[MAXN];
int keep_flower[MAXN]; // keep_flower[i] = 0/1，表示第 i 朵花删除/保留
int answer;

bool check() {
    int last_height = 0;
    int last_sign = 0;
    int count_chosen = 0;
    for (int i = 1; i <= n; i++) {
        if (keep_flower[i] == 0) continue;
        if (count_chosen > 0) {
            if (h[i] == last_height) return false;
            int cur_sign = (h[i] > last_height ? 1 : -1);
            if (last_sign != 0 && cur_sign == last_sign) return false;
            last_sign = cur_sign;
        }
        last_height = h[i];
        count_chosen++;
    }
    return true;
}

int calc_answer() {
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (keep_flower[i] == 1) cnt++;
    }
    return cnt;
}

void dfs_choose(int dep) {
    if (dep == n + 1) {
        if (check()) {
            int value = calc_answer();
            if (answer < value) answer = value;
        }
        return;
    }

    for (int i = 0; i <= 1; i++) {
        keep_flower[dep] = i;
        dfs_choose(dep + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
    }

    answer = 0;
    dfs_choose(1);

    cout << answer << '\n';
    return 0;
}
