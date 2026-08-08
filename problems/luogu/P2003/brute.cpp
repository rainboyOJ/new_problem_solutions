#include <bits/stdc++.h>
using namespace std;

// brute.cpp：小数据暴力解。
// 对每个平板的左右支柱，分别枚举所有更低的平板，找离它最近的支撑高度。

const int MAXN = 105;

struct Platform {
    int h, l, r;
};

int n;
Platform a[MAXN];

bool cmp_platform(const Platform &A, const Platform &B) {
    return A.h < B.h;
}

int find_support_height(int idx, int cell) {
    int best = 0;
    for (int j = 1; j < idx; j++) {
        if (a[j].l <= cell && cell + 1 <= a[j].r) {
            best = max(best, a[j].h);
        }
    }
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].h >> a[i].l >> a[i].r;
    }

    sort(a + 1, a + n + 1, cmp_platform);

    long long answer = 0;
    for (int i = 1; i <= n; i++) {
        int left_support = find_support_height(i, a[i].l);
        int right_support = find_support_height(i, a[i].r - 1);
        answer += a[i].h - left_support;
        answer += a[i].h - right_support;
    }

    cout << answer << '\n';
    return 0;
}
