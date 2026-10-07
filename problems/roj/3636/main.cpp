/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 15:52
 * update_at: 2026-10-06 15:52
 */
#include <cstdio>

typedef long long ll;

const int MAXN = 100005;   // 船的数量上限
const int MAXP = 300005;   // 乘客总数上限（sum k <= 3*10^5）
const int MAXC = 100005;   // 国籍的值域上限

ll tim[MAXN];    // tim[i]：第 i 艘船的到达时间（秒）
int pcnt[MAXN];  // pcnt[i]：第 i 艘船的乘客数
int pst[MAXN];   // pst[i]：第 i 艘船的乘客在 nat[] 中的起始下标
int nat[MAXP];   // nat[]：按船的顺序展开存放的所有乘客国籍
int cnt[MAXC];   // cnt[c]：当前 24 小时窗口内国籍为 c 的乘客人数

int n;            // 船的数量
int tot = 0;      // nat[] 已存放的乘客总数
int left_id = 1;  // 窗口最左端还没过期的船的编号
int distinct = 0; // 当前窗口内不同国籍的数量

// 把第 i 艘船整船放进窗口：船上每个乘客的国籍计数 +1
// 船 i 的乘客存放在 nat[pst[i]+1 .. pst[i]+pcnt[i]]（nat 从 1 开始存放）
void add_ship(int i) {
    for (int p = pst[i] + 1; p <= pst[i] + pcnt[i]; p++) {
        int c = nat[p];
        if (cnt[c] == 0) distinct++; // 这个国籍第一次进入窗口
        cnt[c]++;
    }
}

// 把第 i 艘船整船移出窗口：船上每个乘客的国籍计数 -1
void remove_ship(int i) {
    for (int p = pst[i] + 1; p <= pst[i] + pcnt[i]; p++) {
        int c = nat[p];
        cnt[c]--;
        if (cnt[c] == 0) distinct--; // 这个国籍完全离开了窗口
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld %d", &tim[i], &pcnt[i]);
        pst[i] = tot; // 船 i 的乘客从 nat[tot+1] 开始存放
        for (int j = 1; j <= pcnt[i]; j++) {
            tot++; // 先确定本乘客的下标，再读入
            scanf("%d", &nat[tot]);
        }
    }
    for (int i = 1; i <= n; i++) {
        add_ship(i); // 右端：第 i 艘船进窗
        // 左端：t_i 递增保证过期船都在队首，整船弹出；
        // 窗口是开左闭右区间 (t_i-86400, t_i]，取等即出
        while (left_id <= i && tim[left_id] <= tim[i] - 86400) {
            remove_ship(left_id);
            left_id++;
        }
        printf("%d\n", distinct);
    }
    return 0;
}
