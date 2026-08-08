// main.cpp：线性贪心。g[i] 表示处理到 i 时，最后一段从 g[i]+1 开始最优。
#include <bits/stdc++.h>
using namespace std;

const long long MOD_GEN = 1LL << 30;

int n, type_id_input;
vector<long long> prefix_sum;
vector<int> pre_pos, q;

void print_int128(__int128 x) {
    if (x == 0) {
        cout << 0;
        return;
    }
    if (x < 0) {
        cout << '-';
        x = -x;
    }
    string s;
    while (x > 0) {
        s.push_back((char)('0' + x % 10));
        x /= 10;
    }
    reverse(s.begin(), s.end());
    cout << s;
}

long long key_value(int idx) {
    return 2 * prefix_sum[idx] - prefix_sum[pre_pos[idx]];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> type_id_input;
    prefix_sum.assign(n + 1, 0);
    pre_pos.assign(n + 1, 0);
    q.assign(n + 2, 0);

    if (type_id_input == 0) {
        for (int i = 1; i <= n; i++) {
            long long a;
            cin >> a;
            prefix_sum[i] = prefix_sum[i - 1] + a;
        }
    } else {
        long long x, y, z, b1, b2;
        int m;
        cin >> x >> y >> z >> b1 >> b2 >> m;
        vector<long long> b(n + 1, 0);
        b[1] = b1;
        b[2] = b2;
        for (int i = 3; i <= n; i++) {
            b[i] = (x * b[i - 1] + y * b[i - 2] + z) % MOD_GEN;
        }

        int last_p = 0;
        for (int i = 1; i <= m; i++) {
            int p;
            long long l, r;
            cin >> p >> l >> r;
            for (int j = last_p + 1; j <= p; j++) {
                long long a = b[j] % (r - l + 1) + l;
                prefix_sum[j] = prefix_sum[j - 1] + a;
            }
            last_p = p;
        }
    }

    int head = 1;
    int tail = 1;
    q[1] = 0;

    for (int i = 1; i <= n; i++) {
        while (head < tail && key_value(q[head + 1]) <= prefix_sum[i]) {
            head++;
        }
        pre_pos[i] = q[head];
        while (head < tail && key_value(i) <= key_value(q[tail])) {
            tail--;
        }
        q[++tail] = i;
    }

    __int128 answer = 0;
    int pos = n;
    while (pos > 0) {
        __int128 sum = prefix_sum[pos] - prefix_sum[pre_pos[pos]];
        answer += sum * sum;
        pos = pre_pos[pos];
    }

    print_int128(answer);
    cout << '\n';
    return 0;
}
