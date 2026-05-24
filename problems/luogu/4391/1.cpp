#include <iostream>
#include <algorithm>
using namespace std;

typedef unsigned long long ull;
const int MAXN = 1000005;
const int P = 131;

ull h[MAXN], p[MAXN];
char s[MAXN];
int n;

void init_hash() {
    p[0] = 1;
    for (int i = 1; i <= n; ++i) {
        h[i] = h[i - 1] * P + s[i];
        p[i] = p[i - 1] * P;
    }
}

ull get_hash(int l, int r) {
    return h[r] - h[l - 1] * p[r - l + 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> (s + 1);
    init_hash();

    // 暴力枚举循环节长度 len
    for (int len = 1; len <= n; ++len) {
        bool ok = true;
        int _len = n-len;
        ull pre = get_hash(1, _len);
        ull suf = get_hash(n-_len+1 ,n);
        if( pre == suf) {
            cout << len << endl;
            break;
        }
        
    }

    return 0;
}
