/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 01:24
 * update_at: 2026-10-06 01:24
 */

#include <cstdio>
#include <vector>
#include <string>
using namespace std;

typedef long long ll;

// 高精度整数：vector<int> 低位在前，支持构造、判零、输出、大数对大数取模
struct BigInt {
    vector<int> d; // d[0] 是个位

    BigInt() {}
    BigInt(const string &s) {
        for (int i = (int)s.size() - 1; i >= 0; --i) d.push_back(s[i] - '0');
    }

    bool isZero() const {
        return d.size() == 1 && d[0] == 0;
    }

    void fromInt(int x) {
        d.clear();
        if (x == 0) {
            d.push_back(0);
            return;
        }
        while (x > 0) {
            d.push_back(x % 10);
            x /= 10;
        }
    }

    void print() const {
        for (int i = (int)d.size() - 1; i >= 0; --i) printf("%d", d[i]);
    }
};

// 比较两个 BigInt 绝对值：a>b 返回 1，a==b 返回 0，a<b 返回 -1
int cmpBig(const BigInt &a, const BigInt &b) {
    if (a.d.size() != b.d.size())
        return a.d.size() > b.d.size() ? 1 : -1;
    for (int i = (int)a.d.size() - 1; i >= 0; --i)
        if (a.d[i] != b.d[i]) return a.d[i] > b.d[i] ? 1 : -1;
    return 0;
}

// 高精度大整数对高精度大整数取模，逐位试除法，返回余数
BigInt bigMod(BigInt a, BigInt b) {
    if (b.isZero()) return a;
    vector<int> aa(a.d.rbegin(), a.d.rend()); // 高位在前
    vector<int> bb(b.d.rbegin(), b.d.rend());
    vector<int> rr; // 余数，高位在前
    for (int i = 0; i < (int)aa.size(); ++i) {
        rr.push_back(aa[i]);
        while (rr.size() > 1 && rr[0] == 0) rr.erase(rr.begin());
        // 当 rr >= bb 时，rr -= bb
        while (true) {
            if (rr.size() < bb.size()) break;
            if (rr.size() == bb.size()) {
                bool less = false;
                for (int k = 0; k < (int)rr.size(); ++k) {
                    if (rr[k] < bb[k]) { less = true; break; }
                    if (rr[k] > bb[k]) break;
                }
                if (less) break;
            }
            int borrow = 0;
            int p1 = (int)rr.size() - 1;
            int p2 = (int)bb.size() - 1;
            for (; p2 >= 0; --p2, --p1) {
                int diff = rr[p1] - bb[p2] - borrow;
                if (diff < 0) {
                    diff += 10;
                    borrow = 1;
                } else {
                    borrow = 0;
                }
                rr[p1] = diff;
            }
            while (p1 >= 0 && borrow) {
                int diff = rr[p1] - borrow;
                if (diff < 0) {
                    diff += 10;
                    borrow = 1;
                } else {
                    borrow = 0;
                }
                rr[p1] = diff;
                --p1;
            }
            while (rr.size() > 1 && rr[0] == 0) rr.erase(rr.begin());
        }
    }
    BigInt r;
    r.d.assign(rr.rbegin(), rr.rend());
    if (r.d.empty()) r.fromInt(0);
    return r;
}

// 辗转相除法求 gcd，a、b 为非负整数且不同时为 0
BigInt gcdBig(BigInt a, BigInt b) {
    while (!b.isZero()) {
        BigInt r = bigMod(a, b);
        a = b;
        b = r;
    }
    return a;
}

char bufA[3010];
char bufB[3010];

int main() {
    scanf("%s", bufA);
    scanf("%s", bufB);
    BigInt A(bufA);
    BigInt B(bufB);
    BigInt ans = gcdBig(A, B);
    ans.print();
    printf("\n");
    return 0;
}
