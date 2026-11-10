/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 01:12
 * update_at: 2026-11-11 01:12
 */
#include <iostream>
#include <vector>
#include <deque>
#include <queue>
#include <algorithm>

using namespace std;

const int MAXN = 305;
const int MAXM = 2000005;

int n, m, k;
int a[MAXM];
int id[MAXM];              // id[x] 记录图案 x 当前放置的栈编号（0 表示不在任何栈中）
deque<int> st[MAXN];       // 每个栈维护当前存放的卡牌（front 为栈底，back 为栈顶）
queue<int> slot;           // 可用槽位队列（普通栈每个空位入队 1 次）
int spt;                   // 钦定的辅助空栈编号

const int OPN = 4000010;
int opty[OPN], opa[OPN], opb[OPN], opn = 0;

inline void op1(int s) {
    opty[opn] = 1;
    opa[opn] = s;
    opn++;
}

inline void op2(int s1, int s2) {
    // 规范化输出顺序：小的在前面，匹配样例输出习惯
    if (s1 > s2) swap(s1, s2);
    opty[opn] = 2;
    opa[opn] = s1;
    opb[opn] = s2;
    opn++;
}

// 模拟压栈：若栈顶连续两张相同则自动消去
inline void mpush(int s, int x) {
    st[s].push_back(x);
    int sz = st[s].size();
    if (sz >= 2 && st[s][sz - 1] == st[s][sz - 2]) {
        st[s].pop_back();
        st[s].pop_back();
    }
}

// 常规分支：处理卡牌 x
// 返回 false 表示槽位耗尽且 x 为全新卡牌，需进入特殊前瞻分支
bool simple(int x) {
    int s = id[x];
    if (s == 0) {
        // x 未在任何栈中：若有空闲槽位则领一个槽位放置
        if (slot.empty()) return false;
        s = slot.front();
        slot.pop();
        id[x] = s;
        op1(s);
        mpush(s, x);
    } else {
        // x 已在栈 s 中，说明本次为其配对消除牌
        id[x] = 0;
        slot.push(s); // 消除后释放出 1 个槽位
        if (st[s].back() == x) {
            // 在栈顶：直接压入该栈顶自动消除
            op1(s);
            mpush(s, x);
        } else {
            // 在栈底：压入辅助空栈，然后与栈 s 进行栈底消除
            op1(spt);
            mpush(spt, x);
            op2(s, spt);
            st[spt].pop_front();
            st[s].pop_front();
        }
    }
    return true;
}

void solve() {
    cin >> n >> m >> k;
    for (int i = 1; i <= m; ++i) {
        cin >> a[i];
    }

    // 初始化槽位队列：前 n-1 个栈各提供 2 个空槽位
    while (!slot.empty()) slot.pop();
    for (int i = 1; i < n; ++i) {
        slot.push(i);
        slot.push(i);
    }
    spt = n; // 第 n 个栈保留作为辅助空栈

    for (int i = 1; i <= n; ++i) st[i].clear();
    for (int x = 1; x <= k; ++x) id[x] = 0;

    opn = 0;

    for (int i = 1; i <= m; ++i) {
        if (simple(a[i])) continue;

        // 特殊分支：所有普通栈已满（每个栈各 2 张牌），且 a[i] 为无处存放的新图案 p
        int p = a[i], r = i + 1, x;
        for (; r <= m; ++r) {
            x = a[r];
            // 扫描直到遇到第一个不是栈顶的卡牌
            if (x == p || id[x] == 0 || st[id[x]].back() != x) {
                break;
            }
        }
        x = a[r];

        if (x == p) {
            // 情况 A：遇到的第一个非栈顶牌即为 p 自身
            // 将初始 p 垫入辅助栈底，中途所有栈顶牌直接自消，最后另一个 p 压入辅助栈顶对消
            op1(spt);
            mpush(spt, p);
            for (int j = i + 1; j < r; ++j) simple(a[j]);
            op1(spt);
            mpush(spt, p);
            st[spt].clear();
        } else {
            // 情况 B：x 是某个栈底元素，设所在栈为 s = id[x]，栈顶元素为 y
            int s = id[x], y = st[s].back();
            bool evn = true;
            for (int j = i + 1; j < r; ++j) {
                if (a[j] == y) evn = !evn;
            }

            if (evn) {
                // y 出现偶数次：将 p 放入栈 s 形成临时三元素
                op1(s);
                mpush(s, p);
                for (int j = i + 1; j < r; ++j) {
                    if (a[j] == y) {
                        op1(spt);
                        mpush(spt, y); // y 放入辅助栈成对自消
                    } else {
                        simple(a[j]);
                    }
                }
                op1(spt);
                mpush(spt, x);
                op2(s, spt); // 栈底消除 x
                st[spt].pop_front();
                st[s].pop_front();
                id[x] = 0;
                id[p] = s;
            } else {
                // y 出现奇数次：将 p 垫入辅助栈底
                op1(spt);
                mpush(spt, p);
                for (int j = i + 1; j < r; ++j) {
                    if (a[j] == y) {
                        op1(s);
                        mpush(s, y); // y 放回原栈消掉原栈顶
                    } else {
                        simple(a[j]);
                    }
                }
                op1(s);
                mpush(s, x); // 此时原栈只剩 x，压入直接消空
                st[s].clear();
                id[x] = 0;
                id[y] = 0;
                id[p] = spt;
                slot.push(spt); // 原辅助栈转正为普通栈
                spt = s;        // 栈 s 转为新辅助空栈
            }
        }
        i = r; // a[r] 已在分支逻辑中被完美消化
    }

    cout << opn << "\n";
    for (int t = 0; t < opn; ++t) {
        if (opty[t] == 1) {
            cout << "1 " << opa[t] << "\n";
        } else {
            cout << "2 " << opa[t] << " " << opb[t] << "\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        solve();
    }

    return 0;
}
