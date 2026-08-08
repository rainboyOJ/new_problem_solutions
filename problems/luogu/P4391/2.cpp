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

    // 你的思路：暴力枚举循环节长度 len
    for (int len = 1; len <= n; ++len) {
        bool ok = true;
        
        // 验证后面的每一段
        // j 是每一段的起点：1, 1+len, 1+2len...
        for (int j = 1; j <= n; j += len) {
            // 计算当前这一段的长度
            // 通常是 len，但最后一段可能不足 len
            int cur_len = min(len, n - j + 1);
            
            // 核心验证：
            // 当前段的 Hash vs 第一段对应长度的前缀 Hash
            if (get_hash(j, j + cur_len - 1) != get_hash(1, cur_len)) {
                ok = false;
                break; // 这一段对不上，说明 len 不行，直接跳出内层循环
            }
        }

        if (ok) {
            cout << len << endl;
            return 0; // 因为是从小到大枚举，找到的第一个就是最短长度
        }
    }

    return 0;
}
