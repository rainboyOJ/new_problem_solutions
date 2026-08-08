#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005 + 10;
const int MAXL = 100000 + 5;
const int MAXS = 100000 + 5;

int n, m, k;
string dna[MAXN];

int total_len;
int a[MAXS * 2];         // 拼接后的整数串
int owner[MAXS * 2];     // owner[i] 表示位置 i 属于哪个物种
int valid_pos[MAXS * 2]; // valid_pos[i]=1 表示从这里开始至少还能取出一个长度 k 的子串

int sa[MAXS * 2], rk[MAXS * 2], old_rk[MAXS * 2], tmp_sa[MAXS * 2], cnt_sort[MAXS * 2];
int height_arr[MAXS * 2];

long long dp[10];        // n,m <= 5，这里只要很小的组合 dp
int occur[10];           // 当前长度 k 子串在每个物种里出现多少次

int trans(char ch) {
    if (ch == 'A') return 1;
    if (ch == 'C') return 2;
    if (ch == 'G') return 3;
    return 4;
}

void build_sequence() {
    total_len = 0;
    for (int i = 1; i <= n; i++) {
        int len = (int)dna[i].size();
        for (int j = 0; j < len; j++) {
            total_len++;
            a[total_len] = trans(dna[i][j]);
            owner[total_len] = i;
            valid_pos[total_len] = (j + k <= len);
        }
        total_len++;
        a[total_len] = 4 + i; // 每个物种后面加一个不同分隔符，防止跨串匹配
        owner[total_len] = 0;
        valid_pos[total_len] = 0;
    }
}

void build_sa() {
    int maxv = 4 + n;
    for (int i = 1; i <= total_len; i++) {
        rk[i] = a[i];
        sa[i] = i;
    }

    for (int w = 1;; w <<= 1) {
        for (int i = 1; i <= total_len; i++) {
            tmp_sa[i] = i;
        }
        auto cmp = [&](int x, int y) {
            if (rk[x] != rk[y]) return rk[x] < rk[y];
            int rx = (x + w <= total_len ? rk[x + w] : 0);
            int ry = (y + w <= total_len ? rk[y + w] : 0);
            return rx < ry;
        };
        sort(tmp_sa + 1, tmp_sa + total_len + 1, cmp);
        for (int i = 1; i <= total_len; i++) {
            sa[i] = tmp_sa[i];
        }

        old_rk[sa[1]] = 1;
        int classes = 1;
        for (int i = 2; i <= total_len; i++) {
            int x = sa[i - 1];
            int y = sa[i];
            int rx1 = rk[x], ry1 = rk[y];
            int rx2 = (x + w <= total_len ? rk[x + w] : 0);
            int ry2 = (y + w <= total_len ? rk[y + w] : 0);
            if (rx1 != ry1 || rx2 != ry2) {
                classes++;
            }
            old_rk[y] = classes;
        }
        for (int i = 1; i <= total_len; i++) {
            rk[i] = old_rk[i];
        }
        if (classes == total_len) {
            break;
        }
    }
}

void build_height() {
    int h = 0;
    for (int i = 1; i <= total_len; i++) {
        rk[sa[i]] = i;
    }
    for (int i = 1; i <= total_len; i++) {
        if (rk[i] == 1) {
            height_arr[1] = 0;
            continue;
        }
        int j = sa[rk[i] - 1];
        if (h > 0) {
            h--;
        }
        while (i + h <= total_len && j + h <= total_len && a[i + h] == a[j + h]) {
            h++;
        }
        height_arr[rk[i]] = h;
    }
}

long long count_group(int left, int right) {
    for (int i = 1; i <= n; i++) {
        occur[i] = 0;
    }
    for (int i = left; i <= right; i++) {
        int pos = sa[i];
        if (valid_pos[pos]) {
            occur[owner[pos]]++;
        }
    }

    for (int i = 0; i <= m; i++) {
        dp[i] = 0;
    }
    dp[0] = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = m; j >= 1; j--) {
            dp[j] += dp[j - 1] * occur[i];
        }
    }
    return dp[m];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
        cin >> dna[i];
    }

    build_sequence();
    build_sa();
    build_height();

    long long answer = 0;
    for (int i = 1; i <= total_len; ) {
        if (!valid_pos[sa[i]]) {
            i++;
            continue;
        }

        int j = i;
        while (j + 1 <= total_len && height_arr[j + 1] >= k) {
            j++;
        }
        answer += count_group(i, j);
        i = j + 1;
    }

    cout << answer << '\n';

    return 0;
}
