#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int MAXV = 1200005;

int n;
int a[MAXN];
int fa[MAXV]; // fa[x] : 从 x 开始往后，第一个还没被占用的位置

void init_dsu() {
    for (int i = 0; i < MAXV; i++) {
        fa[i] = i;
    }
}

int find_root(int x) {
    if (fa[x] == x) {
        return x;
    }
    fa[x] = find_root(fa[x]);
    return fa[x];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    init_dsu();

    for (int i = 1; i <= n; i++) {
        int x = find_root(a[i]);
        a[i] = x;

        // x 已经被占用，下一次如果还想用 x，就应该跳到 x+1 之后的可用位置。
        fa[x] = find_root(x + 1);
    }

    for (int i = 1; i <= n; i++) {
        if (i > 1) {
            cout << ' ';
        }
        cout << a[i];
    }
    cout << '\n';

    return 0;
}
