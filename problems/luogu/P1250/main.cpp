#include <bits/stdc++.h>
using namespace std;

const int MAXN = 30005;
const int MAXH = 5005;

struct Request {
    int l;
    int r;
    int need;
};

int n, h;
Request req[MAXH];
int tree_bit[MAXN];
bool planted[MAXN];

bool cmp_request(const Request &a, const Request &b) {
    if (a.r != b.r) {
        return a.r < b.r;
    }
    return a.l > b.l;
}

void bit_add(int pos, int val) {
    while (pos <= n) {
        tree_bit[pos] += val;
        pos += pos & -pos;
    }
}

int bit_sum(int pos) {
    int res = 0;
    while (pos > 0) {
        res += tree_bit[pos];
        pos -= pos & -pos;
    }
    return res;
}

int range_sum(int l, int r) {
    return bit_sum(r) - bit_sum(l - 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    cin >> h;
    for (int i = 1; i <= h; i++) {
        cin >> req[i].l >> req[i].r >> req[i].need;
    }

    sort(req + 1, req + h + 1, cmp_request);

    int ans = 0;
    for (int i = 1; i <= h; i++) {
        int have = range_sum(req[i].l, req[i].r);
        int lack = req[i].need - have;
        for (int pos = req[i].r; lack > 0 && pos >= req[i].l; pos--) {
            if (!planted[pos]) {
                planted[pos] = true;
                bit_add(pos, 1);
                ans++;
                lack--;
            }
        }
    }

    cout << ans << '\n';
    return 0;
}
