/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 13:35
 * update_at: 2026-10-06 13:35
 */
#include <iostream>
#include <cstring>
using namespace std;

typedef long long ll;

const int MAXN = 100005; // n 最大约 1e5
const int OP_AND = 0;    // 门运算的编号
const int OP_OR = 1;
const int OP_XOR = 2;

int n;        // 防御门数量
ll m;         // 初始攻击力的上限
int door_op[MAXN]; // door_op[i]：第 i 扇门的运算编号
ll door_t[MAXN];   // door_t[i]：第 i 扇门的参数 t

// 把攻击力 x 依次送过所有 n 扇门，返回最终伤害。
ll apply_doors(ll x) {
    for (int i = 0; i < n; i++) {
        if (door_op[i] == OP_AND) {
            x = x & door_t[i];
        } else if (door_op[i] == OP_OR) {
            x = x | door_t[i];
        } else {
            x = x ^ door_t[i];
        }
    }
    return x;
}

void read_input() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        char op[8];
        cin >> op >> door_t[i];
        if (strcmp(op, "AND") == 0) {
            door_op[i] = OP_AND;
        } else if (strcmp(op, "OR") == 0) {
            door_op[i] = OP_OR;
        } else {
            door_op[i] = OP_XOR;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    read_input();

    // 每扇门都是逐位运算，某一位的输出只取决于输入的同一位。把所有需要决定的位一起摆 1，
    // 一次穿越就同时得到「每位输入 1 的结果」hi；输入 0 的 lo 同理，两次穿越即可。
    ll max_val = m;
    for (int i = 0; i < n; i++) {
        if (door_t[i] > max_val) {
            max_val = door_t[i];
        }
    }
    int top = 0; // 需要决定的位数
    while ((1LL << top) <= max_val) {
        top++;
    }

    ll lo = apply_doors(0);                       // 第 b 位 = 该位输入 0 时的输出
    ll hi = apply_doors((1LL << top) - 1);        // 第 b 位 = 该位输入 1 时的输出

    // 从高位到低位贪心：输入 0 就是 1 的位白拿；否则预算够且花钱能买到 1 才买。
    ll ans = 0;  // 最终最大伤害
    ll used = 0; // 已花掉的预算（即构造中的初始攻击力）
    for (int b = top - 1; b >= 0; b--) {
        ll w = 1LL << b;
        int lo_bit = (lo >> b) & 1;
        int hi_bit = (hi >> b) & 1;
        if (lo_bit == 1) {
            ans |= w;
        } else if (hi_bit == 1 && used + w <= m) {
            ans |= w;
            used += w;
        }
    }

    cout << ans << "\n";
    return 0;
}
