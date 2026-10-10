/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-09 01:08
 * update_at: 2026-10-09 01:08
 */
// 一本通 5059《【例3.9】星期几》
// 题面三步判据（关键词 / 括号内算法名 / 标题）全空 ⇒ 未指定实现手段，
// 故用「一次区间判定 + 查表」：与题解的 switch / if 链语义等价，且把 7 个英文串
// 集中在一处，便于逐字核对大小写与拼写（题目的主要易错点）。
// 数据实测：p1..p7 = 1,7,2,3,4,5,6；p8 = 0、p9 = 8、p10 = 2147483647(INT_MAX)，
// 均输出 input error!。数据里不存在 INT_MIN，也没有超过 LLONG_MAX 的数。
// 输入用 ll 接收：判区间只做比较，无算术运算，超 32 位也不会截断或溢出。
#include <iostream>

using namespace std;

typedef long long ll;

// 下标 0 占位空串；下标 1..7 依次是 Monday..Sunday（首字母大写，拼写逐字对齐题面）
const char* WEEK_NAME[8] = {
    "", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"
};

ll n; // 输入的表示星期几的数字

// 合法输入集合是闭区间 [1, 7]，其余（0、8、负数、极值）一律输出错误提示。
void solve() {
    if (1 <= n && n <= 7) {
        cout << WEEK_NAME[n] << "\n";
    } else {
        cout << "input error!" << "\n"; // 题面要求的提示：全小写 + 感叹号，无行尾空格
    }
}

int main() {
    if (!(cin >> n)) return 0; // 无输入 / 非法 token：不输出，静默退出
    solve();
    return 0;
}
