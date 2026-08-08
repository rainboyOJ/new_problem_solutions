#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;

const int MAXN = 1000005;

int n;
int a_arr[MAXN];
int b_arr[MAXN];
int wait_arr[MAXN];

struct FastScanner {
    static const int BUFSIZE = 1 << 20;
    int idx, size;
    char buf[BUFSIZE];

    FastScanner() {
        idx = 0;
        size = 0;
    }

    inline char get_char() {
        if (idx >= size) {
            size = (int)fread(buf, 1, BUFSIZE, stdin);
            idx = 0;
            if (size == 0) {
                return 0;
            }
        }
        return buf[idx++];
    }

    template <typename T>
    bool read_int(T &x) {
        char ch = get_char();
        if (ch == 0) {
            return false;
        }

        while (ch != 0 && (ch < '0' || ch > '9')) {
            ch = get_char();
        }
        if (ch == 0) {
            return false;
        }

        x = 0;
        while (ch >= '0' && ch <= '9') {
            x = x * 10 + (ch - '0');
            ch = get_char();
        }
        return true;
    }
} fs;

int main() {
    fs.read_int(n);
    for (int i = 1; i <= n; i++) {
        fs.read_int(a_arr[i]);
    }
    for (int i = 1; i <= n; i++) {
        fs.read_int(b_arr[i]);
    }

    sort(a_arr + 1, a_arr + n + 1);
    sort(b_arr + 1, b_arr + n + 1);

    // 把问题看成“单位时间安排作业”：
    // 每个 a_i 表示这个数最早只能放到位置 a_i；
    // 若它最终放到时间 t，上移次数就是 t-a_i。
    //
    // 为了让后续能把最大的等待时间分给最小的 b，
    // 我们要让等待时间的 multiset 尽量优。
    // 经典贪心是：每个时刻都优先安排当前可选作业里 release time 最大的那个。
    priority_queue<int> pq;
    int i = 1;
    long long cur_time = a_arr[1];
    int tot = 0;

    while (i <= n || !pq.empty()) {
        if (pq.empty() && i <= n && cur_time < a_arr[i]) {
            cur_time = a_arr[i];
        }

        while (i <= n && a_arr[i] <= cur_time) {
            pq.push(a_arr[i]);
            i++;
        }

        int release_time = pq.top();
        pq.pop();
        wait_arr[++tot] = (int)(cur_time - release_time);
        cur_time++;
    }

    // 等待时间越大，越应该配更小的 b。
    sort(wait_arr + 1, wait_arr + n + 1, greater<int>());

    ull ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += (ull)wait_arr[i] * (ull)b_arr[i];
    }

    cout << ans << '\n';
    return 0;
}
