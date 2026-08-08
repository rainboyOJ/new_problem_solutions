#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20005;

struct HashValue {
    unsigned long long h1, h2;
};

int n, k;
unsigned long long a[MAXN];
unsigned long long pow1_base[MAXN], pow2_base[MAXN];
unsigned long long pre1[MAXN], pre2[MAXN];
HashValue hashes[MAXN];

bool cmp_hash(const HashValue &a, const HashValue &b) {
    if (a.h1 != b.h1) {
        return a.h1 < b.h1;
    }
    return a.h2 < b.h2;
}

bool same_hash(const HashValue &a, const HashValue &b) {
    return a.h1 == b.h1 && a.h2 == b.h2;
}

void read_input() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i]++;
    }
}

void build_hash() {
    const unsigned long long base1 = 1000003;
    const unsigned long long base2 = 1000033;

    pow1_base[0] = 1;
    pow2_base[0] = 1;
    for (int i = 1; i <= n; i++) {
        pow1_base[i] = pow1_base[i - 1] * base1;
        pow2_base[i] = pow2_base[i - 1] * base2;
        pre1[i] = pre1[i - 1] * base1 + a[i];
        pre2[i] = pre2[i - 1] * base2 + a[i];
    }
}

HashValue get_hash(int left, int right) {
    HashValue res;
    int len = right - left + 1;
    res.h1 = pre1[right] - pre1[left - 1] * pow1_base[len];
    res.h2 = pre2[right] - pre2[left - 1] * pow2_base[len];
    return res;
}

bool check(int len) {
    if (len == 0) {
        return true;
    }

    int count_hash = 0;
    for (int i = 1; i + len - 1 <= n; i++) {
        count_hash++;
        hashes[count_hash] = get_hash(i, i + len - 1);
    }

    sort(hashes + 1, hashes + count_hash + 1, cmp_hash);

    int current = 1;
    for (int i = 2; i <= count_hash; i++) {
        if (same_hash(hashes[i], hashes[i - 1])) {
            current++;
        } else {
            current = 1;
        }
        if (current >= k) {
            return true;
        }
    }

    return k <= 1;
}

void solve() {
    build_hash();

    int left = 0;
    int right = n;
    int answer = 0;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (check(mid)) {
            answer = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
