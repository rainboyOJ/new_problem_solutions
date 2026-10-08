#include <iostream>
#include <vector>

using namespace std;

const int MAXV = 3000006;
int cnt[MAXV];
int bucket[MAXV + 8];

inline int readInt() {
    int c = getchar_unlocked();
    while (c != '-' && (c < '0' || c > '9')) {
        if (c == -1) return 0;
        c = getchar_unlocked();
    }
    int sgn = 1;
    if (c == '-') { sgn = -1; c = getchar_unlocked(); }
    int x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = getchar_unlocked();
    }
    return x * sgn;
}

int main() {
    int n = readInt();
    if (n == 0) return 0;
    int mxR = 0;
    for (int i = 0; i < n; ++i) {
        int r = readInt();
        ++cnt[r];
        if (r > mxR) mxR = r;
    }
    int lim = n > mxR ? n : mxR;
    int mx = 0;
    for (int r = 1; r <= lim; ++r) {
        if (cnt[r]) {
            ++bucket[cnt[r]];
            if (cnt[r] > mx) mx = cnt[r];
        }
    }
    
    int x = mx, y = mx, z = mx;
    long long ans = 0;
    while (x > 0 && y > 0 && z > 0) {
        while (x > 0 && bucket[x] == 0) --x;
        if (x == 0) break;
        --bucket[x];
        
        while (y > 0 && bucket[y] == 0) --y;
        if (y == 0) break;
        --bucket[y];
        
        while (z > 0 && bucket[z] == 0) --z;
        if (z == 0) break;
        --bucket[z];
        
        if (x > 1) ++bucket[x - 1];
        if (y > 1) ++bucket[y - 1];
        if (z > 1) ++bucket[z - 1];
        ++ans;
    }
    cout << ans << "\n";
    return 0;
}
