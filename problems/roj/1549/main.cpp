/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 07:39
 * update_at: 2026-10-05 07:39
 */
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXM = 200005; // m 的上限
const int MAXK = 20;     // 2^18 > 2*10^5，够放下所有层

// 在线 ST 表：st[k][j] 表示以下标 j + 2^k - 1 结尾、长度 2^k 的区间的最大值。
// 第 k 层只在序列够长后才存在，所以存下标 = 结尾位置 - 2^k + 1；
// len[k] 记录第 k 层当前已存了几个表项，新增表项就放在下标 len[k] 处。
ll st[MAXK][MAXM];
int len[MAXK];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll m, p;
    cin >> m >> p;

    ll size = 0;     // 当前序列长度
    ll last_ans = 0; // 上一次询问的答案 a，还没询问过时为 0

    for (ll i = 1; i <= m; i++) {
        char op;
        ll arg;
        cin >> op >> arg;

        if (op == 'A') {
            // 长度 1 的区间就是新元素本身
            st[0][len[0]] = (arg + last_ans) % p;
            len[0]++;

            ll pos = size; // 新元素的下标
            size++;

            // 增量补层：新元素只影响“以 pos 结尾”的块
            for (int k = 1; (1LL << k) <= size; k++) {
                ll half = 1LL << (k - 1); // 半段长度
                // 两段合成：以 pos-half 结尾的前半段 + 以 pos 结尾的后半段
                st[k][len[k]] = max(st[k - 1][pos - 2 * half + 1],
                                    st[k - 1][pos - half + 1]);
                len[k]++;
            }
        } else {
            // 询问最后 arg 个数：用两段长 2^k <= arg 的块夹住 [size-arg, size-1]
            int k = 0;
            while ((1LL << (k + 1)) <= arg) {
                k++;
            }
            ll span = 1LL << k;

            ll tail = st[k][size - span]; // 以末尾结尾的 2^k 段
            ll head = st[k][size - arg];  // 从询问左端起头的 2^k 段
            last_ans = max(tail, head);
            cout << last_ans << '\n';
        }
    }

    return 0;
}
