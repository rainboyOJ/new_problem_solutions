/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 18:45
 * update_at: 2026-07-11 18:49
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 300005;
const int INF = 1000000007;

int n, q;
ll limit_c;
int b_to[MAXN];          // B(i)：第一个比前 i 头牛最大值更大的位置
ll c[MAXN];              // 当前构造的分数
bool fixed_score[MAXN];  // 题面中已经给定的分数
int largest_free[MAXN];  // largest_free[i] 表示 <=i 的最大原始未知位置

struct MaxSegTree {
    int size;
    ll tree[MAXN * 4];

    void build(int p, int l, int r) {
        if (l == r) {
            tree[p] = c[l];
            return;
        }
        int mid = (l + r) / 2;
        build(p * 2, l, mid);
        build(p * 2 + 1, mid + 1, r);
        tree[p] = max(tree[p * 2], tree[p * 2 + 1]);
    }

    void update(int p, int l, int r, int pos, ll value) {
        if (l == r) {
            tree[p] = value;
            return;
        }
        int mid = (l + r) / 2;
        if (pos <= mid) {
            update(p * 2, l, mid, pos, value);
        } else {
            update(p * 2 + 1, mid + 1, r, pos, value);
        }
        tree[p] = max(tree[p * 2], tree[p * 2 + 1]);
    }

    ll query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) {
            return tree[p];
        }
        int mid = (l + r) / 2;
        ll ans = 0;
        if (ql <= mid) {
            ans = max(ans, query(p * 2, l, mid, ql, qr));
        }
        if (qr > mid) {
            ans = max(ans, query(p * 2 + 1, mid + 1, r, ql, qr));
        }
        return ans;
    }
} max_tree;

struct MinBSegTree {
    int tree[MAXN * 4];

    void build(int p, int l, int r) {
        if (l == r) {
            tree[p] = (b_to[l] == 0 ? INF : b_to[l]);
            return;
        }
        int mid = (l + r) / 2;
        build(p * 2, l, mid);
        build(p * 2 + 1, mid + 1, r);
        tree[p] = min(tree[p * 2], tree[p * 2 + 1]);
    }

    int find_rightmost(int p, int l, int r, int ql, int qr, int upper) {
        if (qr < l || r < ql || tree[p] >= upper) {
            return 0;
        }
        if (l == r) {
            return l;
        }
        int mid = (l + r) / 2;
        int right_ans = find_rightmost(p * 2 + 1, mid + 1, r, ql, qr, upper);
        if (right_ans != 0) {
            return right_ans;
        }
        return find_rightmost(p * 2, l, mid, ql, qr, upper);
    }
} b_tree;

bool fill_b_constraints(vector<pair<int, int> > memories) {
    for (int i = 1; i <= n; i++) {
        b_to[i] = 0;
    }

    for (int i = 0; i < (int)memories.size(); i++) {
        int a = memories[i].first;
        int h = memories[i].second;
        b_to[a] = h;
    }

    int cur = 1;
    while (cur <= n) {
        int start = cur;
        while (cur < b_to[start]) {
            if (b_to[cur] != 0 && b_to[cur] != b_to[start]) {
                return false;
            }
            b_to[cur] = b_to[start];
            cur++;
        }
        cur = max(cur, start + 1);
    }

    return true;
}

void print_answer_or_minus_one(bool ok) {
    if (!ok) {
        cout << -1 << '\n';
        return;
    }

    for (int i = 1; i <= n; i++) {
        if (c[i] > limit_c) {
            cout << -1 << '\n';
            return;
        }
    }

    for (int i = 1; i <= n; i++) {
        if (i > 1) {
            cout << ' ';
        }
        cout << c[i];
    }
    cout << '\n';
}

void solve_one_case() {
    cin >> n >> q >> limit_c;

    for (int i = 1; i <= n; i++) {
        cin >> c[i];
        fixed_score[i] = (c[i] != 0);
        if (c[i] == 0) {
            c[i] = 1;
        }
    }

    vector<pair<int, int> > memories;
    for (int i = 1; i <= q; i++) {
        int a, h;
        cin >> a >> h;
        memories.push_back(make_pair(a, h));
    }

    if (!fill_b_constraints(memories)) {
        cout << -1 << '\n';
        return;
    }

    largest_free[0] = 0;
    for (int i = 1; i <= n; i++) {
        if (!fixed_score[i]) {
            largest_free[i] = i;
        } else {
            largest_free[i] = largest_free[i - 1];
        }
    }

    max_tree.build(1, 1, n);
    b_tree.build(1, 1, n);

    bool ok = true;
    int i = 1;
    while (i <= n && ok) {
        if (b_to[i] == 0) {
            i++;
            continue;
        }

        int h = b_to[i];
        if (h <= i || h > n) {
            ok = false;
            break;
        }

        ll max_before = max_tree.query(1, 1, n, 1, i);
        ll max_until_before_h = max_tree.query(1, 1, n, 1, h - 1);

        if (max_until_before_h > max_before) {
            int bad = b_tree.find_rightmost(1, 1, n, 1, i, h);
            int pos = largest_free[i];
            if (pos <= bad) {
                ok = false;
                break;
            }
            c[pos] = max_until_before_h;
            max_tree.update(1, 1, n, pos, c[pos]);
            max_before = max_until_before_h;
        }

        if (!fixed_score[h]) {
            c[h] = max_before + 1;
            max_tree.update(1, 1, n, h, c[h]);
        }

        if (c[h] <= max_before) {
            ok = false;
            break;
        }

        i = h;
    }

    print_answer_or_minus_one(ok);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve_one_case();
    }

    return 0;
}
