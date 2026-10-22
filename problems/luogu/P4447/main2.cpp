/**
 * Author by Rainboy blog: https://rainboylv.com github: https://rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-22 23:20
 * update_at: 2026-10-22 23:20
 */
// main2.cpp：第二层解法，排序后逐元素模拟接链，O(n^2)。
//
// 层 1 枚举了所有分法但数量爆炸；能不能直接构造？
//
// 关键观察：把每个组看成一条「链」，链上的实力值依次加 1。
// 按实力值从小到大处理每个队员时，他只能接到「以 a_i - 1 结尾」的链上，
// 接不上就只能新开一条长度为 1 的链 —— 决策顺序被值域唯一确定。
//
// 有多条链可接时接哪条？接最短的。短链才是最可能成为「最小组」的那条，
// 把增长机会给它，最小值不会下降（交换论证）。这一条规则就是全部贪心：
// 没人被接的链自然停在原地，冻结这件事自动发生了，不需要额外处理。
//
// 实现上没有堆，每次线性扫描所有链找最短的可接链，所以是 O(n^2)。
// 能过 n <= 1000 的 3~4 号测试点；再往上要靠第三层的桶/堆优化。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

int n;
int a[MAXN];

struct Chain {
    int end_value;  // 这条链的最后一个实力值
    int length;     // 这条链当前的组人数
};

Chain chains[MAXN];  // 最多 n 条链，每条至少 1 人
int chain_cnt = 0;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a + 1, a + n + 1);

    for (int i = 1; i <= n; i++) {
        int value = a[i];

        // 在所有链里找「能以 value-1 结尾接上」且长度最短的那一条
        int pick = -1;
        for (int c = 0; c < chain_cnt; c++) {
            if (chains[c].end_value != value - 1) continue;
            if (pick == -1 || chains[c].length < chains[pick].length) {
                pick = c;
            }
        }

        if (pick != -1) {
            // 接到最短的链后面，链长加 1
            chains[pick].end_value = value;
            chains[pick].length++;
        } else {
            // 接不上任何链，只能新开一条长度 1 的链
            chains[chain_cnt].end_value = value;
            chains[chain_cnt].length = 1;
            chain_cnt++;
        }
    }

    // 所有队员处理完后，每条链的长度已经定型，取最小的那个
    int answer = n;
    for (int c = 0; c < chain_cnt; c++) {
        answer = min(answer, chains[c].length);
    }
    cout << answer << '\n';
    return 0;
}
