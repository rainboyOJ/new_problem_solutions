/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 12:53
 * update_at: 2026-10-05 12:53
 */

#include <cstdio>
#include <string>
#include <vector>

typedef long long ll;

ll n;   // 病人总数
ll cnt;                   // 被初筛为甲流的人数
std::vector<std::string> ans; // 按输入顺序保存入选病人的姓名

int main() {
    scanf("%lld", &n);
    for (ll i = 1; i <= n; ++i) {
        char name[16]; // 姓名最多 8 个字符，留足余量
        double temp;
        ll cough;
        scanf("%s %lf %lld", name, &temp, &cough);

        // 初筛条件：体温 >= 37.5（含等于）且咳嗽，两个条件缺一不可
        if (temp >= 37.5 && cough == 1) {
            ans.push_back(name);
            ++cnt;
        }
    }

    // 先按输入顺序输出名单，最后一行输出人数
    for (size_t i = 0; i < ans.size(); ++i)
        printf("%s\n", ans[i].c_str());
    printf("%lld\n", cnt);
    return 0;
}
