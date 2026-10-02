/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-01 20:58
 * update_at: 2026-10-01 20:58
 */
// main.cpp：线性贪心。g[i] 表示处理到 i 时，最后一段从 g[i]+1 开始最优。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll MOD_GEN = 1LL << 30;

int n, type_id_input;
vector<ll> prefix_sum;   // prefix_sum[i] = a[1] + ... + a[i]
vector<int> pre_pos;     // pre_pos[i]：前缀 i 的最优划分中，上一段结尾位置
vector<int> mono_q;      // 单调队列，维护候选断点的下标

// 输出 __int128 类型的整数。
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

// 候选断点 idx 的关键值：key(idx) = 2*prefix_sum[idx] - prefix_sum[pre_pos[idx]]。
// 当 key(idx) <= prefix_sum[i] 时，idx 可以作为前缀 i 的上一段结尾。
ll key_value(int idx) {
    return 2 * prefix_sum[idx] - prefix_sum[pre_pos[idx]];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> type_id_input;
    prefix_sum.assign(n + 1, 0);
    pre_pos.assign(n + 1, 0);
    mono_q.assign(n + 2, 0);

    if (type_id_input == 0) {
        for (int i = 1; i <= n; i++) {
            ll a;
            cin >> a;
            prefix_sum[i] = prefix_sum[i - 1] + a;
        }
    } else {
        ll x, y, z, b1, b2;
        int m;
        cin >> x >> y >> z >> b1 >> b2 >> m;
        vector<ll> b(n + 1, 0);
        b[1] = b1;
        b[2] = b2;
        for (int i = 3; i <= n; i++) {
            b[i] = (x * b[i - 1] + y * b[i - 2] + z) % MOD_GEN;
        }

        int last_p = 0;
        for (int i = 1; i <= m; i++) {
            int p;
            ll l, r;
            cin >> p >> l >> r;
            for (int j = last_p + 1; j <= p; j++) {
                ll a = b[j] % (r - l + 1) + l;
                prefix_sum[j] = prefix_sum[j - 1] + a;
            }
            last_p = p;
        }
    }

    int head = 1;
    int tail = 1;
    mono_q[1] = 0;

    for (int i = 1; i <= n; i++) {
        // 队头：弹出 key 值已经 <= prefix_sum[i] 的候选，保留最后一个不满足的。
        while (head < tail && key_value(mono_q[head + 1]) <= prefix_sum[i]) {
            head++;
        }
        pre_pos[i] = mono_q[head];
        // 队尾：维护 key 值的单调递增性。
        while (head < tail && key_value(i) <= key_value(mono_q[tail])) {
            tail--;
        }
        mono_q[++tail] = i;
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
