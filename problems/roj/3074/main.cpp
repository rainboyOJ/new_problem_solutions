/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 17:42
 * update_at: 2026-10-06 17:42
 */
#include <cstdio>
#include <map>
#include <algorithm>
using namespace std;

typedef long long ll;

// 8 条笔画：首尾相接的 7 个格子编号，按箭头方向滚动一格（末格移到首位）
const int LINE[8][7] = {
    {0, 2, 6, 11, 15, 20, 22},     // A 最左列自上而下
    {1, 3, 8, 12, 17, 21, 23},     // B 第二列自上而下
    {10, 9, 8, 7, 6, 5, 4},        // C 最下行自右向左
    {19, 18, 17, 16, 15, 14, 13},  // D 最右列自下而上
    {23, 21, 17, 12, 8, 3, 1},     // E 是 B 的反向
    {22, 20, 15, 11, 6, 2, 0},     // F 是 A 的反向
    {13, 14, 15, 16, 17, 18, 19},  // G 是 D 的反向
    {4, 5, 6, 7, 8, 9, 10},        // H 是 C 的反向
};
const int CENTER[8] = {6, 7, 8, 11, 12, 15, 16, 17};  // 中央 8 格
const int BACK[8] = {5, 4, 7, 6, 1, 0, 3, 2};         // BACK[k] 是操作 k 的逆操作

int a[24];            // 棋盘 24 个格子的数字（1/2/3），按题面从上到下、同行从左到右编号
int path[32];         // 搜索路径，path[g] = 第 g 步走的操作编号
int bound;            // 当前迭代加深的步数上限
map<ll, int> proved;  // 本轮已证下界缓存：棋盘打包键 -> 从该状态至少还需几步（每轮 bound 重建）

// 把整个棋盘打包成 48 位整数键：每个格子占 2 位，取值只有 1/2/3
ll pack_state() {
    ll key = 0;
    for (int i = 0; i < 24; i++) key |= (ll)a[i] << (2 * i);
    return key;
}

// 可采纳估价 h = 中央 8 格里“非众数格”的个数。
// 每条笔画与中央 8 格的交恰是该笔画里下标 2、3、4 的三格，滚动一格只换掉 1 个中央格，
// 所以众数个数每步至多 +1，h 每步至多 -1，h 就是最少剩余步数的下界。
int h_value() {
    int c1 = 0, c2 = 0, c3 = 0;
    for (int i = 0; i < 8; i++) {
        if (a[CENTER[i]] == 1) c1++;
        else if (a[CENTER[i]] == 2) c2++;
        else c3++;
    }
    return 8 - max(c1, max(c2, c3));
}

// 沿笔画 k 顺箭头滚动一格：环上第 j 格改取第 j+1 格的数字，末格改取原首格
void do_op(int k) {
    int first = a[LINE[k][0]];
    for (int j = 0; j < 6; j++) a[LINE[k][j]] = a[LINE[k][j + 1]];
    a[LINE[k][6]] = first;
}

// 撤销操作 k：逆着滚动方向把数字移回去
void undo_op(int k) {
    int last = a[LINE[k][6]];
    for (int j = 6; j > 0; j--) a[LINE[k][j]] = a[LINE[k][j - 1]];
    a[LINE[k][0]] = last;
}

// 在步数上限 bound 内深搜：找到解返回 true（路径存在 path[0..bound-1]），否则返回 false
bool dfs(int g, int bad) {
    int real = h_value();
    ll key = pack_state();
    int known = 0;
    map<ll, int>::iterator it = proved.find(key);
    if (it != proved.end()) known = it->second;
    // 取真实估价与已证下界的较大者：剪枝更强，但都来自本轮已穷尽的搜索，仍可采纳
    int h = real > known ? real : known;
    if (g + h > bound) return false;  // 本分支在上限内不可能有解
    if (real == 0) return true;       // 中央 8 格已同色
    for (int k = 0; k < 8; k++) {     // 按 A~H 字典序尝试，命中即得最短且字典序最小的解
        if (k == bad) continue;       // 走上一步的逆操作等于原路返回，最短解里不会出现
        path[g] = k;
        do_op(k);
        if (dfs(g + 1, BACK[k])) return true;
        undo_op(k);
    }
    // 本状态在剩余步数内走不到目标：它至少还差 bound - g + 1 步，记下来供同轮其它分支复用
    int need = bound - g + 1;
    if (need > known) proved[key] = need;
    return false;
}

int main() {
    int first;
    while (scanf("%d", &first) == 1 && first != 0) {
        a[0] = first;
        for (int i = 1; i < 24; i++) scanf("%d", &a[i]);
        bound = h_value();  // 步数上限从估价下界开始逐次 +1
        while (!dfs(0, -1)) {
            bound++;
            proved.clear();  // 已证下界相对当前 bound 才有效，每轮重建
        }
        if (bound == 0) printf("No moves needed\n");
        else {
            for (int i = 0; i < bound; i++) putchar('A' + path[i]);
            putchar('\n');
        }
        printf("%d\n", a[CENTER[0]]);  // dfs 命中时棋盘已是解状态，中央同色
    }
    return 0;
}
