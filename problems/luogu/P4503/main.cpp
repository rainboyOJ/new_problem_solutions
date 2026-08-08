#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

const int MAXN = 30005;
const int MAXL = 205;
const ull BASE = 131;

int n, L, S;
string str[MAXN];

ull power_base[MAXL];
ull prefix_hash[MAXN][MAXL];
ull suffix_hash[MAXN][MAXL];
ull keys[MAXN];

// 把题目中的 64 种字符映射成 1..64。
int value_of(char ch) {
    if ('a' <= ch && ch <= 'z') return ch - 'a' + 1;
    if ('A' <= ch && ch <= 'Z') return ch - 'A' + 27;
    if ('0' <= ch && ch <= '9') return ch - '0' + 53;
    if (ch == '_') return 63;
    return 64; // '@'
}

void build_hash(int id) {
    prefix_hash[id][0] = 0;
    for (int i = 1; i <= L; i++) {
        prefix_hash[id][i] = prefix_hash[id][i - 1] * BASE + value_of(str[id][i - 1]);
    }

    suffix_hash[id][L + 1] = 0;
    for (int i = L; i >= 1; i--) {
        suffix_hash[id][i] = suffix_hash[id][i + 1] * BASE + value_of(str[id][i - 1]);
    }
}

// 返回删除第 pos 位后的哈希值，pos 使用 1-based。
ull erased_hash(int id, int pos) {
    ull left = prefix_hash[id][pos - 1];
    ull right = suffix_hash[id][pos + 1];
    int right_len = L - pos;
    return left * power_base[right_len] + right;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> L >> S;
    for (int i = 1; i <= n; i++) {
        cin >> str[i];
    }

    power_base[0] = 1;
    for (int i = 1; i <= L; i++) {
        power_base[i] = power_base[i - 1] * BASE;
    }

    for (int i = 1; i <= n; i++) {
        build_hash(i);
    }

    long long answer = 0;
    for (int pos = 1; pos <= L; pos++) {
        for (int i = 1; i <= n; i++) {
            keys[i] = erased_hash(i, pos);
        }
        sort(keys + 1, keys + n + 1);

        long long len = 1;
        for (int i = 2; i <= n; i++) {
            if (keys[i] == keys[i - 1]) {
                len++;
            }
            else {
                answer += len * (len - 1) / 2;
                len = 1;
            }
        }
        answer += len * (len - 1) / 2;
    }

    cout << answer << '\n';

    return 0;
}
