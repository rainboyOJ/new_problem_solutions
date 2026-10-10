/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 15:39
 * update_at: 2026-10-07 15:39
 */

// 装箱问题：6*6*h 的包裹里塞 1*1 ~ 6*6 的六种方形产品，求最小包裹数。
// 思路：每种产品都占满包裹的高度，问题退化成二维的 6*6 方格切割，
//       大件（4*4 及以上）必须单独占一个包裹，3*3 每四个一箱，剩下的空位才用 1*1、2*2 填。

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// left_for_two[k] = 一箱里放 k 个 3*3（k = 0..3）之后，还能塞下的 2*2 个数
int left_for_two[4] = {0, 5, 3, 1};

// 循环处理每个订单：读入六个型号的数量，输出最小包裹数
int main() {
    ll cnt1, cnt2, cnt3, cnt4, cnt5, cnt6;

    while (cin >> cnt1 >> cnt2 >> cnt3 >> cnt4 >> cnt5 >> cnt6) {
        if (cnt1 == 0 && cnt2 == 0 && cnt3 == 0 && cnt4 == 0 && cnt5 == 0 && cnt6 == 0) {
            break;  // 六个 0 是输入结束标志，不产生输出
        }

        // 第一步：6*6、5*5、4*4 各占一个包裹，3*3 每四个占一个
        ll boxes = cnt6 + cnt5 + cnt4 + (cnt3 + 3) / 4;

        // 第二步：统计当前所有包裹里被大件腾出来的"2*2 槽位"总数。
        // 5*5 旁边只能放 1*1；4*4 旁边能放 5 个 2*2；
        // 3*3 按每箱剩余个数 0/1/2/3 分别能放 0/5/3/1 个 2*2。
        ll slots_two = 5 * cnt4 + left_for_two[cnt3 % 4];

        // 2*2 槽位不够就再开新箱，每箱最多 9 个 2*2
        if (cnt2 > slots_two) {
            boxes += (cnt2 - slots_two + 8) / 9;
        }

        // 第三步：剩下的空间全归 1*1。
        // 总面积减去已被占用的面积（6*6 用 36、5*5 用 25、4*4 用 16、3*3 用 9、2*2 用 4），
        // 就是所有包裹加起来还能放下的 1*1 个数。
        ll slots_one = 36 * boxes - 36 * cnt6 - 25 * cnt5 - 16 * cnt4 - 9 * cnt3 - 4 * cnt2;

        // 放不下 1*1 就继续开新箱，每箱 36 个
        if (cnt1 > slots_one) {
            boxes += (cnt1 - slots_one + 35) / 36;
        }

        cout << boxes << "\n";
    }

    return 0;
}
