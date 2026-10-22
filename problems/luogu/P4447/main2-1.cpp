/**
 * Author by Rainboy blog: https://rainboylv.com github: https://rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-22 23:55
 * update_at: 2026-10-22 23:55
 */
// main2-1.cpp：第二层的「互不相同」特化解，套一层链长 DP，O(n^2)。
// 本层针对 3~4 号测试点：n <= 1000，且 a_i 互不相同。
//
// 与 main2.cpp 的区别：main2.cpp 无论如何都要处理「多条链可接时接哪条」，
// 因为同一个结尾值可能挂着好几条链。但 3~4 保证 a_i 互不相同，
// 每个实力值最多只有一个队员，于是「以某值结尾的链」最多只有一条 ——
// 争夺消失了，「接最短」这条选择规则也就消失了。
//
// 剩下的问题变成：每个队员只问「以我结尾的那条链有多长？」
//   若 a_i - 1 这个值不存在，我就是一条新链的起点，长度为 1；
//   若存在，我就接在它后面，长度是它的链长加 1。
// 这就是一层链长 DP：
//
//   len[i] = 1                      , 若不存在 j 使 a[j] == a[i] - 1
//   len[i] = len[j] + 1             , 否则（那个 j 唯一）
//
// 找前驱 j 直接线性扫描，所以是 O(n^2)。
//
// ⚠ 必须先把 a[] 排序。这一层 DP 的递推要求「前驱的链长已经算好」，
// 而 a_i - 1 只有排在 a_i 之前才能保证这一点。若按输入原序递推，
// 会出现「需要的前驱还没算」的情况（例如 4 5 2 3 -4 -3 -5 中，
// 4 的前驱 3 排在它后面，此时 len 还是初始值），答案就错了。
//
// ⚠ 答案只能在「链的终点」上收集。中间点的 len 只是前缀长度，
// 若把它也算进去会得到偏小的错误答案；只有没有后继（a_i + 1 不存在）的点
// 才携带完整组大小。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

int n;
int a[MAXN];

int len[MAXN];     // len[i] = 以 a[i] 结尾的链的长度（a[i] 是链的最后一个值）
bool has_next[MAXN];  // has_next[i] = 是否存在 a[j] == a[i] + 1，即 i 不是链的终点

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    // 排序：让 a_i - 1 一定排在 a_i 之前，DP 递推才有意义
    sort(a + 1, a + n + 1);

    // 互不相同是本层前提，检查一遍：本层若遇到重复值会给出错误答案
    // （同一个值出现两次时，「以某值结尾的链只有一条」不再成立）
    for (int i = 2; i <= n; i++) {
        if (a[i] == a[i - 1]) {
            cerr << "[main2-1] 本层只适用于 a_i 互不相同的 3~4 号测试点，"
                 << "但读到了重复的实力值 " << a[i]
                 << "；请改用 main.cpp（分块 + 双堆）\n";
            return 1;
        }
    }

    // 第一步：线性扫描求每个点的前驱，得到链长
    for (int i = 1; i <= n; i++) {
        len[i] = 1;  // 默认自己是链的起点
        for (int j = 1; j <= n; j++) {
            if (a[j] == a[i] - 1) {
                // 找到了唯一的前驱，接在它后面
                len[i] = len[j] + 1;
                break;
            }
        }
    }

    // 第二步：标记哪些点还有后继。没有后继的点才是链的终点，
    // 只有终点的 len 是完整组大小；中间点的 len 只是前缀长度。
    for (int i = 1; i <= n; i++) {
        has_next[i] = false;
        for (int j = 1; j <= n; j++) {
            if (a[j] == a[i] + 1) {
                has_next[i] = true;
                break;
            }
        }
    }

    // 答案 = 所有链终点上的 len 的最小值
    int answer = n;
    for (int i = 1; i <= n; i++) {
        if (!has_next[i]) {
            answer = min(answer, len[i]);
        }
    }

    cout << answer << '\n';
    return 0;
}
