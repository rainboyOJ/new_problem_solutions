// brute_01_style.cpp：01 序列风格暴力，按石头编号依次决定移走或保留。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;

long long L;
int N, M;
long long stone[MAXN];
int keep_stone[MAXN]; // keep_stone[i] 表示第 i 块中间石头是否保留。
long long answer;

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

void dfs_choose(int pos, int removed) {
    if (removed > M) {
        return;
    }
    if (pos == N + 1) {
        answer = max(answer, calc_min_jump());
        return;
    }

    // 选择 0：移走第 pos 块石头。
    keep_stone[pos] = 0;
    dfs_choose(pos + 1, removed + 1);

    // 选择 1：保留第 pos 块石头。
    keep_stone[pos] = 1;
    dfs_choose(pos + 1, removed);
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
    dfs_choose(1, 0);

    cout << answer << '\n';
    return 0;
}
