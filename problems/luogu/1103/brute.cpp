#include <bits/stdc++.h>
using namespace std;

// brute.cpp：小数据暴力解，使用 01 序列枚举每本书保留或删除。

const int MAXN = 25;
const int INF = 1000000000;

struct Book {
    int h, w;
};

int n, k;
Book a[MAXN];
int keep_cnt;
int keep_book[MAXN]; // keep_book[i] = 0/1，表示第 i 本书删除/保留
int ans;

bool cmp_book(const Book &lhs, const Book &rhs) {
    return lhs.h < rhs.h;
}

int calc_keep_count() {
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (keep_book[i] == 1) cnt++;
    }
    return cnt;
}

bool check() {
    return calc_keep_count() == keep_cnt;
}

int calc_answer() {
    int last = 0;
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        if (keep_book[i] == 0) continue;
        if (last != 0) {
            sum += abs(a[i].w - a[last].w);
        }
        last = i;
    }
    return sum;
}

void dfs_choose(int dep) {
    if (dep == n + 1) {
        if (check()) {
            int value = calc_answer();
            if (ans > value) ans = value;
        }
        return;
    }

    // 第 dep 本书的 01 选择：0 删除，1 保留。
    for (int i = 0; i <= 1; i++) {
        keep_book[dep] = i;
        dfs_choose(dep + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].h >> a[i].w;
    }

    sort(a + 1, a + n + 1, cmp_book);

    keep_cnt = n - k;
    ans = INF;
    dfs_choose(1);

    cout << ans << '\n';
    return 0;
}
