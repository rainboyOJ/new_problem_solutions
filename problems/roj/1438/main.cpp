/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 23:47
 * update_at: 2026-10-05 23:47
 */
// 灯泡影子问题：影子长度是人位置 x 的单峰函数，三分查找求最大值。
#include <cstdio>
#include <cmath>

typedef long long ll;

// 全局变量：H 灯高，h 人身高，D 灯到墙的水平距离
double H, h, D;

// 计算人站在距光源 x 处时的影子总长度（地面部分 + 墙面部分）
double shadow_len(double x) {
    // 光线过头顶，与地面交点距光源为 H*x/(H-h)
    if (H * x / (H - h) <= D) {
        // 影子全在地面：交点减去人所在位置
        return h * x / (H - h);
    }
    // 影子爬上墙：地面剩 D-x，墙上的高为 H - D(H-h)/x，加起来
    return D - x + H - D * (H - h) / x;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%lf%lf%lf", &H, &h, &D);
        // 三分：每次比较区间两个三等分点，向峰值一侧收缩
        double left = 0.0, right = D;
        for (int i = 0; i < 100; i++) {
            double m1 = left + (right - left) / 3;
            double m2 = right - (right - left) / 3;
            if (shadow_len(m1) < shadow_len(m2))
                left = m1;
            else
                right = m2;
        }
        printf("%.3f\n", shadow_len(left));
    }
    return 0;
}
