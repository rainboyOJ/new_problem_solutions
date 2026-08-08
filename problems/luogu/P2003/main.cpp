#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
const int MAXX = 10005;

struct Platform {
    int h, l, r;
};

int n;
Platform a[MAXN];
int top_height[MAXX]; // top_height[x] 表示单位小格 [x, x+1] 当前最高的已建平板高度

bool cmp_platform(const Platform &A, const Platform &B) {
    return A.h < B.h;
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
        int h = a[i].h;
        int l = a[i].l;
        int r = a[i].r;

        // 左右支柱分别立在 [l,l+1] 和 [r-1,r] 这两个单位小格上方。
        answer += h - top_height[l];
        answer += h - top_height[r - 1];

        // 当前平板搭好后，它会成为自己覆盖范围内最高的平板。
        for (int x = l; x <= r - 1; x++) {
            top_height[x] = h;
        }
    }

    cout << answer << '\n';
    return 0;
}
