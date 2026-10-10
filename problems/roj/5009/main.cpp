#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

static const int BUFSZ = 1 << 20;
static char ibuf[BUFSZ];
static int ipos = 0, ilen = 0;

static inline char getc() {
    if (ipos == ilen) {
        ilen = (int)fread(ibuf, 1, BUFSZ, stdin);
        ipos = 0;
        if (ilen == 0) return 0;
    }
    return ibuf[ipos++];
}

template <typename T>
static inline void readInt(T& x) {
    char c;
    do { c = getc(); } while (c != '-' && (c < '0' || c > '9'));
    int neg = 0;
    if (c == '-') { neg = 1; c = getc(); }
    x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = getc();
    }
    if (neg) x = -x;
}

struct Node {
    long long h;
    long long v;
};

struct Cmp {
    bool operator()(const Node& a, const Node& b) const {
        return a.v > b.v;
    }
};

int main() {
    long long n, m;
    readInt(n);
    readInt(m);
    ++m;

    long long ans = 0;
    long long sum = 0;
    long long cnt = 0;
    priority_queue<Node, vector<Node>, Cmp> pq;

    for (long long i = 1; i <= n; ++i) {
        long long h, v;
        readInt(h);
        readInt(v);

        if (i > m) break;

        sum += v;
        long long extra = h - 1;
        if (extra > 0) {
            sum += extra * v;
            cnt += extra;
            pq.push(Node{extra, v});
        }

        long long budget = m - i;
        while (!pq.empty() && cnt - pq.top().h >= budget) {
            cnt -= pq.top().h;
            sum -= pq.top().h * pq.top().v;
            pq.pop();
        }
        
        if (cnt > budget) {
            long long over = cnt - budget;
            ans = max(ans, sum - pq.top().v * over);
        } else {
            ans = max(ans, sum);
        }
    }

    printf("%lld\n", ans);
    return 0;
}
