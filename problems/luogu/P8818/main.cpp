#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 100005;
const ll INF64 = (1LL << 60);

int n, m, q;
ll a[MAXN], b[MAXN];
int lg2_table[MAXN];
int zero_prefix[MAXN];

ll st_a_max[18][MAXN];
ll st_a_min[18][MAXN];
ll st_a_posmin[18][MAXN]; // 区间内最小正数，不存在时为 INF64
ll st_a_negmax[18][MAXN]; // 区间内最大的负数（最接近 0），不存在时为 -INF64

ll st_b_max[18][MAXN];
ll st_b_min[18][MAXN];

ll query_max(ll st[18][MAXN], int l, int r) {
    int k = lg2_table[r - l + 1];
    return max(st[k][l], st[k][r - (1 << k) + 1]);
}

ll query_min(ll st[18][MAXN], int l, int r) {
    int k = lg2_table[r - l + 1];
    return min(st[k][l], st[k][r - (1 << k) + 1]);
}

void build_logs(int limit) {
    lg2_table[1] = 0;
    for (int i = 2; i <= limit; i++) {
        lg2_table[i] = lg2_table[i >> 1] + 1;
    }
}

void build_st_a() {
    for (int i = 1; i <= n; i++) {
        st_a_max[0][i] = a[i];
        st_a_min[0][i] = a[i];
        st_a_posmin[0][i] = (a[i] > 0 ? a[i] : INF64);
        st_a_negmax[0][i] = (a[i] < 0 ? a[i] : -INF64);
        zero_prefix[i] = zero_prefix[i - 1] + (a[i] == 0);
    }

    for (int k = 1; (1 << k) <= n; k++) {
        int len = 1 << k;
        int half = len >> 1;
        for (int i = 1; i + len - 1 <= n; i++) {
            st_a_max[k][i] = max(st_a_max[k - 1][i], st_a_max[k - 1][i + half]);
            st_a_min[k][i] = min(st_a_min[k - 1][i], st_a_min[k - 1][i + half]);
            st_a_posmin[k][i] = min(st_a_posmin[k - 1][i], st_a_posmin[k - 1][i + half]);
            st_a_negmax[k][i] = max(st_a_negmax[k - 1][i], st_a_negmax[k - 1][i + half]);
        }
    }
}

void build_st_b() {
    for (int i = 1; i <= m; i++) {
        st_b_max[0][i] = b[i];
        st_b_min[0][i] = b[i];
    }

    for (int k = 1; (1 << k) <= m; k++) {
        int len = 1 << k;
        int half = len >> 1;
        for (int i = 1; i + len - 1 <= m; i++) {
            st_b_max[k][i] = max(st_b_max[k - 1][i], st_b_max[k - 1][i + half]);
            st_b_min[k][i] = min(st_b_min[k - 1][i], st_b_min[k - 1][i + half]);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> b[i];
    }

    build_logs(max(n, m));
    build_st_a();
    build_st_b();

    while (q--) {
        int l1, r1, l2, r2;
        cin >> l1 >> r1 >> l2 >> r2;

        ll b_min = query_min(st_b_min, l2, r2);
        ll b_max = query_max(st_b_max, l2, r2);

        ll a_max = query_max(st_a_max, l1, r1);
        ll a_min = query_min(st_a_min, l1, r1);
        ll a_posmin = query_min(st_a_posmin, l1, r1);
        ll a_negmax = query_max(st_a_negmax, l1, r1);
        bool has_zero = (zero_prefix[r1] - zero_prefix[l1 - 1] > 0);

        ll answer;

        if (b_min >= 0) {
            // B 区间全非负，小 Q 会取最小的 B。
            if (a_max < 0) {
                answer = a_negmax * b_max;
            }
            else {
                answer = a_max * b_min;
            }
        }
        else if (b_max <= 0) {
            // B 区间全非正，小 Q 会取最大的 B。
            if (a_min > 0) {
                answer = a_posmin * b_min;
            }
            else {
                answer = a_min * b_max;
            }
        }
        else {
            // B 区间同时有正有负。
            if (has_zero) {
                answer = 0;
            }
            else if (a_max < 0) {
                answer = a_negmax * b_max;
            }
            else if (a_min > 0) {
                answer = a_posmin * b_min;
            }
            else {
                ll cand1 = a_posmin * b_min;
                ll cand2 = a_negmax * b_max;
                answer = max(cand1, cand2);
            }
        }

        cout << answer << '\n';
    }

    return 0;
}
