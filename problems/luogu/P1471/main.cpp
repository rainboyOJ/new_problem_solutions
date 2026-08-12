/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:10
 * update_at: 2026-08-12 22:10
 */
// main.cpp：P1471 正式解，线段树懒标记同时维护区间和与平方和，
// 支持区间加实数、查询区间平均值与方差，单次操作 O(log n)。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n, m;
double a[MAXN];          // 初始数列，下标从 1 开始
double sum[MAXN * 4];    // sum[p] 表示节点 p 覆盖区间的元素和 Σa[i]
double sum2[MAXN * 4];   // sum2[p] 表示节点 p 覆盖区间的平方和 Σa[i]^2
double lazy[MAXN * 4];   // lazy[p] 表示节点 p 上整段尚未下传的加法值

// 把节点 p 覆盖的整段区间（长度 len）的每个元素都加上 val，
// 并同步更新区间和、平方和与懒标记。
void apply(int p, int len, double val) {
    // 平方和公式：Σ(a[i]+val)^2 = Σa[i]^2 + 2*val*Σa[i] + len*val^2，
    // 注意这里必须先使用旧的 sum[p]，再更新 sum[p]。
    sum2[p] += 2 * val * sum[p] + val * val * len;
    sum[p] += val * len;
    lazy[p] += val;
}

// 把节点 p 的懒标记下传给两个孩子。
void push(int p, int l, int r) {
    if (lazy[p] == 0 || l == r) {
        return;
    }
    int mid = (l + r) / 2;
    apply(p * 2, mid - l + 1, lazy[p]);       // 左孩子长度 mid - l + 1
    apply(p * 2 + 1, r - mid, lazy[p]);       // 右孩子长度 r - mid
    lazy[p] = 0;
}

// 建树：叶子存单点值与平方，父亲合并两个孩子的和。
void build(int p, int l, int r) {
    if (l == r) {
        sum[p] = a[l];
        sum2[p] = a[l] * a[l];
        return;
    }
    int mid = (l + r) / 2;
    build(p * 2, l, mid);
    build(p * 2 + 1, mid + 1, r);
    sum[p] = sum[p * 2] + sum[p * 2 + 1];
    sum2[p] = sum2[p * 2] + sum2[p * 2 + 1];
}

// 区间加：把 [ql, qr] 内每个元素加上 val。
void update(int p, int l, int r, int ql, int qr, double val) {
    if (ql <= l && r <= qr) {
        // 完全覆盖，整段加 val 并打懒标记，不再下钻。
        apply(p, r - l + 1, val);
        return;
    }
    push(p, l, r);
    int mid = (l + r) / 2;
    if (ql <= mid) {
        update(p * 2, l, mid, ql, qr, val);
    }
    if (mid < qr) {
        update(p * 2 + 1, mid + 1, r, ql, qr, val);
    }
    sum[p] = sum[p * 2] + sum[p * 2 + 1];
    sum2[p] = sum2[p * 2] + sum2[p * 2 + 1];
}

// 区间查询：把 [ql, qr] 的和与平方和分别累加进 res_sum / res_sum2。
void query(int p, int l, int r, int ql, int qr, double &res_sum, double &res_sum2) {
    if (ql <= l && r <= qr) {
        res_sum += sum[p];
        res_sum2 += sum2[p];
        return;
    }
    push(p, l, r);
    int mid = (l + r) / 2;
    if (ql <= mid) {
        query(p * 2, l, mid, ql, qr, res_sum, res_sum2);
    }
    if (mid < qr) {
        query(p * 2 + 1, mid + 1, r, ql, qr, res_sum, res_sum2);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    build(1, 1, n);

    cout << fixed << setprecision(4); // 输出统一保留 4 位小数

    while (m--) {
        int opt, l, r;
        cin >> opt >> l >> r;
        if (opt == 1) {
            double k;
            cin >> k;
            update(1, 1, n, l, r, k);
        } else {
            double res_sum = 0, res_sum2 = 0;
            query(1, 1, n, l, r, res_sum, res_sum2);
            double len = r - l + 1;
            double avg = res_sum / len; // 平均值 = Σa / n
            if (opt == 2) {
                cout << avg << '\n';
            } else {
                // 方差 = E(x^2) - E(x)^2
                cout << res_sum2 / len - avg * avg << '\n';
            }
        }
    }

    return 0;
}
