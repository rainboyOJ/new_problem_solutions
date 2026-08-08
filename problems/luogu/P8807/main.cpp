#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

const i64 LIMIT = 1000000001LL;

vector<i64> lcm_prefix;

i64 gcd_i64(i64 a, i64 b) {
    while (b != 0) {
        i64 t = a % b;
        a = b;
        b = t;
    }
    return a;
}

void init_lcm() {
    lcm_prefix.push_back(1); // 占位，让下标从 1 开始更顺手

    i64 cur = 1;
    for (int i = 1; ; i++) {
        i64 g = gcd_i64(cur, i);
        i64 nxt = cur / g;
        if (nxt > LIMIT / i) {
            break;
        }
        nxt *= i;
        if (nxt > LIMIT) {
            break;
        }
        lcm_prefix.push_back(nxt);
        cur = nxt;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    init_lcm();

    int T;
    cin >> T;

    while (T--) {
        i64 n, m;
        cin >> n >> m;

        i64 need = n + 1;

        if (m >= (int) lcm_prefix.size()) {
            cout << "Yes\n";
            continue;
        }

        if (need % lcm_prefix[m] == 0) {
            cout << "No\n";
        }
        else {
            cout << "Yes\n";
        }
    }

    return 0;
}
