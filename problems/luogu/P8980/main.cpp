#include <bits/stdc++.h>
using namespace std;

const int HARD_N = 32465962;

struct FastScanner {
    static const int BUFSIZE = 1 << 20;
    int idx, size;
    char buf[BUFSIZE];

    FastScanner() {
        idx = 0;
        size = 0;
    }

    inline char getch() {
        if (idx >= size) {
            size = (int) fread(buf, 1, BUFSIZE, stdin);
            idx = 0;
            if (size == 0) {
                return 0;
            }
        }
        return buf[idx++];
    }

    template <class T>
    bool read_unsigned(T &x) {
        x = 0;
        char ch = getch();
        while (ch != 0 && (ch < '0' || ch > '9')) {
            ch = getch();
        }
        if (ch == 0) {
            return false;
        }
        while (ch >= '0' && ch <= '9') {
            x = x * 10 + (ch - '0');
            ch = getch();
        }
        return true;
    }
} scanner;

int spf[HARD_N + 1];
vector<int> primes;
int first_pos[HARD_N + 1];

void build_sieve() {
    primes.reserve(2100000);
    for (int i = 2; i <= HARD_N; i++) {
        if (spf[i] == 0) {
            spf[i] = i;
            primes.push_back(i);
        }
        for (int j = 0; j < (int) primes.size(); j++) {
            int p = primes[j];
            long long v = 1LL * i * p;
            if (v > HARD_N) {
                break;
            }
            spf[v] = p;
            if (p == spf[i]) {
                break;
            }
        }
    }
}

int need_exp_for_prime(int p, int n) {
    int exp = 1;
    long long cur = p;
    while (cur * p <= n) {
        cur *= p;
        exp++;
    }
    return exp;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    build_sieve();

    unsigned int T;
    scanner.read_unsigned(T);

    vector<int> touched;
    touched.reserve(100000);

    for (unsigned int tc = 0; tc < T; tc++) {
        unsigned long long n64;
        unsigned int Q;
        scanner.read_unsigned(n64);
        scanner.read_unsigned(Q);

        // n=1 时，小朋友第一轮后一定已经能唯一确定。
        if (n64 == 1) {
            unsigned long long tmp;
            for (unsigned int i = 0; i < Q; i++) {
                scanner.read_unsigned(tmp);
            }
            cout << 1 << '\n';
            continue;
        }

        bool impossible = false;

        // 对于 p > sqrt(n) 的质数，所需指数只能是 1。
        // 每个 a_i <= n 最多只能包含一个这样的质数。
        // 因此如果这类质数个数已经大于 Q，则不可能全部覆盖。
        if (n64 > HARD_N) {
            impossible = true;
        }

        int n = 0;
        if (!impossible) {
            n = (int) n64;
            int large_prime_count =
                (int) (upper_bound(primes.begin(), primes.end(), n) -
                       upper_bound(primes.begin(), primes.end(), (int) sqrt((long double) n)));
            if (large_prime_count > (int) Q) {
                impossible = true;
            }
        }

        for (unsigned int i = 1; i <= Q; i++) {
            unsigned long long a64;
            scanner.read_unsigned(a64);

            if (impossible) {
                continue;
            }

            int x = (int) a64;
            while (x > 1) {
                int p = spf[x];
                int cnt = 0;
                while (x % p == 0) {
                    x /= p;
                    cnt++;
                }

                int need = need_exp_for_prime(p, n);
                if (cnt >= need && first_pos[p] == 0) {
                    first_pos[p] = (int) i;
                    touched.push_back(p);
                }
            }
        }

        if (impossible) {
            cout << "game won't stop\n";
            continue;
        }

        int ans = 1;
        int limit = (int) (upper_bound(primes.begin(), primes.end(), n) - primes.begin());

        for (int i = 0; i < limit; i++) {
            int p = primes[i];
            if (first_pos[p] == 0) {
                impossible = true;
                break;
            }
            if (first_pos[p] > ans) {
                ans = first_pos[p];
            }
        }

        if (impossible) {
            cout << "game won't stop\n";
        } else {
            cout << ans << '\n';
        }

        for (int p : touched) {
            first_pos[p] = 0;
        }
        touched.clear();
    }

    return 0;
}
