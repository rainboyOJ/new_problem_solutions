/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 05:37
 * update_at: 2026-10-05 05:38
 */
// main.cpp：判断 x 是否属于以 k 为种子的集合 M。
// 生成规则 y -> 2y+1 与 y -> 3y+1 都严格递增，反过来就是 x 的父亲只能是
// (x-1)/2 或 (x-1)/3。从 x 反向递归收缩，配上记忆化，每个中间值只算一次。

#include <iostream>
#include <string>
#include <cctype>
#include <cstring>
using namespace std;

typedef long long ll;

const int MAXX = 100000 + 5;          // x <= 100000，中间值不会超过 x
int k, x;

// memo[v] = -1 未算；0 不可达；1 可达。仅按 x 的值域开数组。
int memo[MAXX];

// 判断以 k 为种子时，cur 是否在集合 M 中：沿 (cur-1)/2、(cur-1)/3 反向收缩。
int dfs(int cur) {
    if (cur < k) return 0;            // 越缩越小，再也回不到种子 k
    if (cur == k) return 1;
    if (cur < MAXX && memo[cur] != -1) return memo[cur]; // 记忆化：同一中间值只算一次

    int reach = 0;
    for (int d = 2; d <= 3; ++d) {    // 候选父亲：要求 (cur-1) 能被 d 整除
        if ((cur - 1) % d == 0) {
            reach = reach || dfs((cur - 1) / d);
            if (reach) break;         // 任一分支可达即为可达
        }
    }

    if (cur < MAXX) memo[cur] = reach;
    return reach;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 题面写“逗号间隔”，实际测试数据可能是空格，统一按整数抓取。
    // 不依赖正则，用顺序扫描把“逗号/空格/换行”等分隔符之间的整数字段逐一取出。
    string buf;
    if (!getline(cin, buf)) return 0;
    // 用 isspace/isdigit 字符级判断 + 手写状态机：避免 range-for / lambda。
    int nums[2];
    int cnt = 0;
    int n = (int)buf.size();
    int i = 0;
    while (i < n && cnt < 2) {
        while (i < n && !isdigit(static_cast<unsigned char>(buf[i]))) ++i;
        if (i >= n) break;
        int v = 0;
        while (i < n && isdigit(static_cast<unsigned char>(buf[i]))) {
            v = v * 10 + (buf[i] - '0');
            ++i;
        }
        nums[cnt++] = v;
    }
    if (cnt < 2) return 0;
    k = nums[0];
    x = nums[1];
    if (x >= MAXX) x = MAXX - 1;       // 防御：x 越界裁到合法区间

    fill(memo, memo + MAXX, -1);
    cout << (dfs(x) ? "YES" : "NO") << "\n";
    return 0;
}