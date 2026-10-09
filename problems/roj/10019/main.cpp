/*
 * Author: Antigravity
 * Date: 2026-10-10 05:00
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

typedef long long ll;

struct nod {
    short p[5];
    short tp;
    short f[5];
};

nod arr[100005];
int tot = 0;
vector<int> a[150005];

int hua(int x) { return (x - 1) % 4; }
int d(int x) { return (x - 1) / 4; }

void work(nod &now) {
    int p0 = now.p[0], p1 = now.p[1], p2 = now.p[2], p3 = now.p[3], p4 = now.p[4];
    int t0 = hua(p0), t1 = hua(p1), t2 = hua(p2), t3 = hua(p3), t4 = hua(p4);
    int d0 = d(p0), d1 = d(p1), d2 = d(p2), d3 = d(p3), d4 = d(p4);

    bool is_flush = (t0 == t1 && t1 == t2 && t2 == t3 && t3 == t4);
    bool is_straight = (d0 + 1 == d1 && d1 + 1 == d2 && d2 + 1 == d3 && d3 + 1 == d4);

    if (is_straight && is_flush) {
        now.tp = 2; now.f[0] = p0; now.f[1] = p1; now.f[2] = p2; now.f[3] = p3; now.f[4] = p4; return;
    }
    if (d0 == d1 && d1 == d2 && d2 == d3) {
        now.tp = 3; now.f[0] = p4; now.f[1] = p0; now.f[2] = p1; now.f[3] = p2; now.f[4] = p3; return;
    }
    if (d1 == d2 && d2 == d3 && d3 == d4) {
        now.tp = 3; now.f[0] = p0; now.f[1] = p1; now.f[2] = p2; now.f[3] = p3; now.f[4] = p4; return;
    }
    if (d0 == d1 && d1 == d2 && d3 == d4) {
        now.tp = 4; now.f[0] = p3; now.f[1] = p4; now.f[2] = p0; now.f[3] = p1; now.f[4] = p2; return;
    }
    if (d0 == d1 && d2 == d3 && d3 == d4) {
        now.tp = 4; now.f[0] = p0; now.f[1] = p1; now.f[2] = p2; now.f[3] = p3; now.f[4] = p4; return;
    }
    if (is_flush) {
        now.tp = 5; now.f[0] = p0; now.f[1] = p1; now.f[2] = p2; now.f[3] = p3; now.f[4] = p4; return;
    }
    if (is_straight) {
        now.tp = 6; now.f[0] = p0; now.f[1] = p1; now.f[2] = p2; now.f[3] = p3; now.f[4] = p4; return;
    }
    if (d0 == d1 && d1 == d2) {
        now.tp = 7; now.f[0] = p3; now.f[1] = p4; now.f[2] = p0; now.f[3] = p1; now.f[4] = p2; return;
    }
    if (d1 == d2 && d2 == d3) {
        now.tp = 7; now.f[0] = p0; now.f[1] = p4; now.f[2] = p1; now.f[3] = p2; now.f[4] = p3; return;
    }
    if (d2 == d3 && d3 == d4) {
        now.tp = 7; now.f[0] = p0; now.f[1] = p1; now.f[2] = p2; now.f[3] = p3; now.f[4] = p4; return;
    }
    now.tp = 0;
}

bool cmp(const nod &x, const nod &y) {
    if (x.tp != y.tp) return x.tp < y.tp;
    for (int i = 4; i >= 0; i--) {
        if (d(x.f[i]) != d(y.f[i])) return d(x.f[i]) > d(y.f[i]);
    }
    for (int i = 4; i >= 0; i--) {
        if (hua(x.f[i]) != hua(y.f[i])) return hua(x.f[i]) < hua(y.f[i]);
    }
    return false;
}

bool cmp2(const nod &x, const nod &y) {
    if (x.tp != y.tp) return x.tp < y.tp;
    for (int i = 4; i >= 0; i--) {
        if (d(x.f[i]) != d(y.f[i])) return d(x.f[i]) > d(y.f[i]);
    }
    return false;
}

char ch[15] = "23456789TJQKA";
char ch2[15] = "SHCD";

void out(const nod &x) {
    for (int i = 0; i < 5; i++) {
        cout << ch2[hua(x.p[i])] << ch[d(x.p[i])] << (i == 4 ? "" : " ");
    }
    cout << "\n";
}

int get_card() {
    string s;
    cin >> s;
    if (s.empty()) return 0;
    int tt = 0, qq = 0;
    if (s[0] == 'S') tt = 1;
    else if (s[0] == 'H') tt = 2;
    else if (s[0] == 'C') tt = 3;
    else if (s[0] == 'D') tt = 4;
    
    if (s[1] >= '2' && s[1] <= '9') qq = s[1] - '0';
    else if (s[1] == 'T') qq = 10;
    else if (s[1] == 'J') qq = 11;
    else if (s[1] == 'Q') qq = 12;
    else if (s[1] == 'K') qq = 13;
    else if (s[1] == 'A') qq = 14;
    return (qq - 2) * 4 + tt;
}

int get_hash(int x, int y, int z) {
    return x * 53 * 53 + y * 53 + z;
}

void solve() {
    for (int i = 1; i <= 52; i++) {
        for (int j = i + 1; j <= 52; j++) {
            for (int k = j + 1; k <= 52; k++) {
                for (int t = k + 1; t <= 52; t++) {
                    for (int q = t + 1; q <= 52; q++) {
                        tot++;
                        arr[tot].p[0] = i; arr[tot].p[1] = j; arr[tot].p[2] = k;
                        arr[tot].p[3] = t; arr[tot].p[4] = q;
                        work(arr[tot]);
                        if (arr[tot].tp == 0) {
                            tot--;
                        }
                    }
                }
            }
        }
    }
    sort(arr + 1, arr + tot + 1, cmp);

    for (int i = 1; i <= tot; i++) {
        a[get_hash(arr[i].p[0], arr[i].p[1], arr[i].p[2])].push_back(i);
        a[get_hash(arr[i].p[0], arr[i].p[1], arr[i].p[3])].push_back(i);
        a[get_hash(arr[i].p[0], arr[i].p[1], arr[i].p[4])].push_back(i);
        a[get_hash(arr[i].p[0], arr[i].p[2], arr[i].p[3])].push_back(i);
        a[get_hash(arr[i].p[0], arr[i].p[2], arr[i].p[4])].push_back(i);
        a[get_hash(arr[i].p[0], arr[i].p[3], arr[i].p[4])].push_back(i);
        a[get_hash(arr[i].p[1], arr[i].p[2], arr[i].p[3])].push_back(i);
        a[get_hash(arr[i].p[1], arr[i].p[2], arr[i].p[4])].push_back(i);
        a[get_hash(arr[i].p[1], arr[i].p[3], arr[i].p[4])].push_back(i);
        a[get_hash(arr[i].p[2], arr[i].p[3], arr[i].p[4])].push_back(i);
    }

    int q_val;
    if (!(cin >> q_val)) return;
    while (q_val--) {
        int X = get_card();
        X = X * 53 + get_card();
        X = X * 53 + get_card();

        int Y = get_card();
        Y = Y * 53 + get_card();
        Y = Y * 53 + get_card();

        if (a[Y].empty()) {
            cout << -1 << "\n";
            continue;
        }
        int y_best = a[Y][0];
        
        if (a[X].empty() || !cmp2(arr[a[X][0]], arr[y_best])) {
            cout << -1 << "\n";
            continue;
        }

        int now = 0;
        int siz = (int)a[X].size();
        for (int j = 1 << 12; j >= 1; j >>= 1) {
            if (now + j < siz && cmp2(arr[a[X][now + j]], arr[y_best])) {
                now += j;
            }
        }
        out(arr[a[X][now]]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
