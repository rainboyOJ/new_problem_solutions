/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-27 17:04
 * update_at: 2026-10-27 19:52
 */
// main2.cpp：中间层对照解。线段树求区间最大值，再在位置上二分答案，每次询问 O(log^2 n)。
// 正确性没问题，但每次询问要多付一个 log，大数据下明显更慢。
// 这里故意用 cin/cout，不写快读：这一层本来就要 TLE，读者该看的是二分逻辑本身。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 2000000 + 5;
const int MAXNODE = MAXN * 4;

int n, m;
int a[MAXN];    // a[i] 只有 2e6 以内且只做大小比较，用 int 省内存
int mx[MAXNODE]; // mx[p]：结点 p 覆盖区间里的最大值

void push_up(int p) {
    mx[p] = max(mx[p << 1], mx[p << 1 | 1]);
}

void build(int p, int l, int r) {
    if (l == r) {
        mx[p] = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    push_up(p);
}

// 区间最大值查询：[ql, qr] 内最大的 a[i]，区间封闭在 [1, n] 内
int query_max(int p, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return mx[p];
    int mid = (l + r) >> 1;
    int answer = 0; // a[i] >= 1，用 0 当"还没有值"
    if (ql <= mid) answer = max(answer, query_max(p << 1, l, mid, ql, qr));
    if (qr > mid) answer = max(answer, query_max(p << 1 | 1, mid + 1, r, ql, qr));
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    build(1, 1, n);

    for (int i = 1; i <= m; i++) {
        int l, r, k;
        cin >> l >> r >> k;
        // prefix_max(t) = max(a[l..t]) 随 t 增大单调不降，
        // 所以"prefix_max(t) > k"在位置上单调，可以二分第一个成立的位置
        int lo = l;
        int hi = r;
        int answer = -1;
        while (lo <= hi) {
            int mid = (lo + hi) >> 1;
            if (query_max(1, 1, n, l, mid) > k) {
                answer = mid;
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        cout << answer << '\n';
    }

    return 0;
}
