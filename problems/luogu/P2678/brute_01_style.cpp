// brute_01_style.cpp：01 序列风格暴力，按石头编号依次决定移走或保留。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;

long long L;
int N, M;
long long stone[MAXN];
int keep_stone[MAXN]; // keep_stone[i] 表示第 i 块中间石头是否保留。
long long answer;

bool check() {
    int removed = 0;
    for (int i = 1; i <= N; i++) {
        if (keep_stone[i] == 0) removed++;
    }
    return removed <= M;
}

long long calc_min_jump() {
    long long last = 0;
    long long best = L;
    for (int i = 1; i <= N; i++) {
        if (keep_stone[i]) {
            best = min(best, stone[i] - last);
            last = stone[i];
        }
    }
    best = min(best, L - last);
    return best;
}

void dfs_choose(int dep) {
    if (dep == N + 1) {
        if (check()) {
            answer = max(answer, calc_min_jump());
        }
        return;
    }

    // 第 dep 块石头的 01 选择：0 移走，1 保留。
    for (int i = 0; i <= 1; i++) {
        keep_stone[dep] = i;
        dfs_choose(dep + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> L >> N >> M;
    for (int i = 1; i <= N; i++) {
        cin >> stone[i];
    }
    sort(stone + 1, stone + N + 1);

    answer = 0;
    dfs_choose(1);

    cout << answer << '\n';
    return 0;
}
