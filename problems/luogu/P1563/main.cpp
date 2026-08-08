#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n, m;
int dir[MAXN];       // 0 表示朝内，1 表示朝外
string name_[MAXN];

void solve() {
    int cur = 0; // 从第 1 个玩具小人开始

    for (int i = 1; i <= m; i++) {
        int op, step;
        cin >> op >> step;
        step %= n;

        // 输入顺序按逆时针给出：
        // 若当前朝向与指令方向相同，则实际沿顺时针走；否则沿逆时针走。
        if (dir[cur] == op) {
            cur = (cur - step + n) % n;
        }
        else {
            cur = (cur + step) % n;
        }
    }

    cout << name_[cur] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> dir[i] >> name_[i];
    }

    solve();

    return 0;
}
