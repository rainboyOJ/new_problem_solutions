/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-22 20:29
 * update_at: 2026-09-22 20:35
 */
// brute.cpp：小数据暴力解，使用 01 序列递归枚举每个申请"批准/拒绝"。
// 每一层只决定第 dep 个申请批准(1)还是不批准(0)，生成完整的 choose[] 后，
// 在叶子节点两两检查被批准的航道是否交叉，再统计批准数量取最大值。
// 两条航道 (s1,t1)、(s2,t2) 交叉 <=> (s1-s2)*(t1-t2) < 0。
// 只适合 N <= 15 左右的小数据。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20;

int n;
int s[MAXN];      // 每个申请的南岸坐标
int t[MAXN];      // 每个申请的北岸坐标
int choose[MAXN]; // choose[i]=1 表示批准第 i 个申请
int ans;

// 检查当前被批准的航道是否两两不交叉。
bool check(){
    for(int i = 1; i <= n; ++i){
        if(choose[i] == 0) continue;
        for(int j = i + 1; j <= n; ++j){
            if(choose[j] == 0) continue;
            // 南岸的大小顺序与北岸的大小顺序相反时, 两条航道必然交叉。
            long long cross = (long long)(s[i] - s[j]) * (t[i] - t[j]);
            if(cross < 0){
                return false; // 只要有一对交叉, 当前方案就不合法
            }
        }
    }
    return true;
}

// 统计当前被批准了多少条航道。
int calc_answer(){
    int cnt = 0;
    for(int i = 1; i <= n; ++i){
        if(choose[i] == 1) cnt++;
    }
    return cnt;
}

void dfs(int dep){
    if(dep == n + 1){
        // 一条完整的 01 选择序列生成完毕, 再统一检查合法性和统计答案。
        if(check()){
            int value = calc_answer();
            if(ans < value) ans = value;
        }
        return;
    }
    // 这一层决定第 dep 个申请批准还是不批准。
    for(int i = 0; i <= 1; ++i){
        choose[dep] = i;
        dfs(dep + 1);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for(int i = 1; i <= n; ++i){
        cin >> s[i] >> t[i];
    }

    ans = 0;
    dfs(1);

    cout << ans << "\n";
    return 0;
}
