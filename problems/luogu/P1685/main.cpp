#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;
const int MAXM = 50005;
const int BASE = 100000000;
const int WIDTH = 8;

struct BigInteger {
    vector<int> d; // 小端存储，d[0] 是最低位

    BigInteger(long long x = 0) {
        *this = x;
    }

    void operator=(long long x) {
        d.clear();
        if (x == 0) {
            d.push_back(0);
            return;
        }
        while (x > 0) {
            d.push_back(x % BASE);
            x /= BASE;
        }
    }

    void trim() {
        while (d.size() > 1 && d.back() == 0) {
            d.pop_back();
        }
    }

    string to_string() const {
        stringstream ss;
        ss << d.back();
        for (int i = (int) d.size() - 2; i >= 0; i--) {
            ss << setw(WIDTH) << setfill('0') << d[i];
        }
        return ss.str();
    }
};

BigInteger operator+(const BigInteger &a, const BigInteger &b) {
    BigInteger c;
    c.d.clear();

    int n = max((int) a.d.size(), (int) b.d.size());
    long long carry = 0;
    for (int i = 0; i < n; i++) {
        long long sum = carry;
        if (i < (int) a.d.size()) {
            sum += a.d[i];
        }
        if (i < (int) b.d.size()) {
            sum += b.d[i];
        }
        c.d.push_back(sum % BASE);
        carry = sum / BASE;
    }
    if (carry) {
        c.d.push_back(carry);
    }
    c.trim();
    return c;
}

BigInteger operator*(const BigInteger &a, int b) {
    if (b == 0) {
        return BigInteger(0);
    }

    BigInteger c;
    c.d.clear();

    long long carry = 0;
    for (int x : a.d) {
        long long now = 1LL * x * b + carry;
        c.d.push_back(now % BASE);
        carry = now / BASE;
    }
    while (carry) {
        c.d.push_back(carry % BASE);
        carry /= BASE;
    }
    c.trim();
    return c;
}

BigInteger sub_int(BigInteger a, int b) {
    int i = 0;
    int borrow = b;
    while (borrow > 0) {
        int cur = borrow % BASE;
        borrow /= BASE;
        if (a.d[i] >= cur) {
            a.d[i] -= cur;
        } else {
            a.d[i] += BASE - cur;
            int j = i + 1;
            while (a.d[j] == 0) {
                a.d[j] = BASE - 1;
                j++;
            }
            a.d[j]--;
        }
        i++;
    }
    a.trim();
    return a;
}

int n, m, s, t, t0;
int head[MAXN], to[MAXM], nxt[MAXM], w[MAXM], indeg[MAXN], edge_cnt;
BigInteger cnt[MAXN]; // cnt[i] : 从 s 到 i 的路径条数
BigInteger sum[MAXN]; // sum[i] : 从 s 到 i 的所有路径长度总和

void add_edge(int u, int v, int val) {
    edge_cnt++;
    to[edge_cnt] = v;
    w[edge_cnt] = val;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
    indeg[v]++;
}

void read_input() {
    cin >> n >> m >> s >> t >> t0;

    edge_cnt = 0;
    for (int i = 1; i <= n; i++) {
        head[i] = 0;
        indeg[i] = 0;
        cnt[i] = BigInteger(0);
        sum[i] = BigInteger(0);
    }

    for (int i = 1; i <= m; i++) {
        int u, v, val;
        cin >> u >> v >> val;
        add_edge(u, v, val);
    }
}

void solve() {
    queue<int> q;
    int deg[MAXN];
    memcpy(deg, indeg, sizeof(indeg));

    cnt[s] = BigInteger(1);

    for (int i = 1; i <= n; i++) {
        if (deg[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int i = head[u]; i != 0; i = nxt[i]) {
            int v = to[i];

            cnt[v] = cnt[v] + cnt[u];
            sum[v] = sum[v] + sum[u] + cnt[u] * w[i];

            deg[v]--;
            if (deg[v] == 0) {
                q.push(v);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    BigInteger ans = sum[t] + sub_int(cnt[t] * t0, t0);
    cout << ans.to_string() << '\n';

    return 0;
}
