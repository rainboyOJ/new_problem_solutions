/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 11:59
 * update_at: 2026-10-06 12:00
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 5005;
const ll MOD = (1LL << 61) - 1; // 梅森素数 2^61-1，作为滚动哈希模数
const ll BASE = 2003;           // 滚动哈希进制基数

ll n;
ll note[MAXN];     // note[i] 表示第 i 个音符，取值 1..88
ll diff_arr[MAXN]; // diff_arr[i] = note[i+1] - note[i] + 100，转调后只需比较差分
ll m;              // 差分数组长度，等于 n - 1

// 计算 (a * b) mod (2^61-1)，用 __int128 承载中间乘积防止溢出。
ll mul_mod(ll a, ll b) {
    __int128 prod = (__int128)a * b;
    ll hi = prod >> 61;
    ll lo = prod & MOD;
    ll res = hi + lo;
    if (res >= MOD) {
        res -= MOD;
    }
    return res;
}

map<ll, ll> first_pos; // first_pos[h] = 哈希值 h 第一次出现的差分串起点

// 判定差分数组中是否存在两段长度 k 的相同子串，且起点差 >= k+1（原音符子串不重叠）。
bool check(ll k) {
    if (k <= 0 || 2 * k + 1 > m) {
        return false;
    }

    // power = BASE^k，用于滑窗时消去最高位。
    ll power = 1;
    for (ll i = 0; i < k; i++) {
        power = mul_mod(power, BASE);
    }

    ll cur = 0;
    for (ll i = 0; i < k; i++) {
        cur = (mul_mod(cur, BASE) + diff_arr[i]) % MOD;
    }

    first_pos.clear();
    first_pos[cur] = 0;
    for (ll i = 1; i + k - 1 < m; i++) {
        // 滑窗更新：整体左移一位，去掉最高位 diff_arr[i-1]，再在末尾加入 diff_arr[i+k-1]。
        cur = mul_mod(cur, BASE);
        cur = (cur - mul_mod(diff_arr[i - 1], power) + MOD) % MOD;
        cur = (cur + diff_arr[i + k - 1]) % MOD;

        map<ll, ll>::iterator it = first_pos.find(cur);
        if (it != first_pos.end()) {
            // 保留最早出现的起点，当前下标与其之差最大，最容易满足不重叠。
            if (i - it->second >= k + 1) {
                return true;
            }
        } else {
            first_pos[cur] = i;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (ll i = 1; i <= n; i++) {
        cin >> note[i];
    }
    m = n - 1;
    for (ll i = 1; i <= m; i++) {
        diff_arr[i - 1] = note[i + 1] - note[i] + 100;
    }

    // 二分差分串长度 k，原题要求原主题长度 L = k + 1 >= 5，故 k >= 4。
    ll low = 4;
    ll high = n / 2;
    ll ans_k = -1;
    while (low <= high) {
        ll mid = (low + high) / 2;
        if (check(mid)) {
            ans_k = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    if (ans_k >= 4) {
        cout << ans_k + 1 << "\n";
    } else {
        cout << 0 << "\n";
    }

    return 0;
}
