/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-01 17:32:02
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll; 

const int MAX_N = 100005;
const int MAX_M = 7000005;


// --- 全局变量定义 ---
// Q1 存放初始蚯蚓，大小只需 N
// Q2, Q3 存放切出来的蚯蚓，最坏情况每次操作产生一个，大小需 M
int q1[MAX_N], h1 = 0, t1 = 0; 
int q2[MAX_M], h2 = 0, t2 = 0; 
int q3[MAX_M], h3 = 0, t3 = 0; 

bool compare(int a, int b) {
    return a > b;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, q, u, v, t;
    cin >> n >> m >> q >> u >> v >> t;

    // --- 【修正 1】 Vector 大小和循环边界 ---
    vector<int> a(n);
    // 必须是 i < n，不能等于 n
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }


    // 1. 初始处理：排序并放入 Q1
    sort(a.begin(), a.end(), compare);
    for(int i = 0; i < n; i++) {
        q1[t1++] = a[i];
    }

    // --- 核心模拟循环 ---
    // i 代表当前是第几秒（从1开始计数，对应题目的第1秒到第m秒）
    // 此时全场已经累积增长了 i * q 的长度
    for(int i = 1; i <= m; i++) {
        
        int source = -1; 
        long long max_val = -2e18; 


        // --- [A] 寻找最大值 ---
        // 比较三个队列的队头，找出真实长度最大的
        // 我们存的是 "相对值"，所以比较的时候可以直接比，不需要加 delta
        if(h1 < t1 && q1[h1] > max_val) { max_val = q1[h1]; source = 1; }
        if(h2 < t2 && q2[h2] > max_val) { max_val = q2[h2]; source = 2; }
        if(h3 < t3 && q3[h3] > max_val) { max_val = q3[h3]; source = 3; }


        // 弹出队头
        if(source == 1) h1++;
        else if(source == 2) h2++;
        else if(source == 3) h3++;

        // --- [B] 还原真实长度 (此处体现 "其余蚯蚓增加 q") ---
        // 第 1 秒时，之前长了 0 秒 -> (1-1)*q = 0. 正确
        // 第 2 秒时，之前长了 1 秒 -> (2-1)*q = q. 正确
        long long real_len = max_val + (long long)(i - 1) * q;


        // 输出逻辑
        if(i % t == 0) {
            cout << real_len << " ";
        }

        // --- [C] 切割 ---
        long long len_left = real_len * u / v;
        long long len_right = real_len - len_left;

        // --- [D] 存入新蚯蚓 (此处体现 "新蚯蚓不增加，且需要匹配未来的增加") ---
        // 这一秒切出来的，下一秒(i+1)开始才算长了 q
        // 下一秒还原时会加上 i*q (因为下一秒是 i+1, 还原公式是 (i+1-1)*q = i*q)
        // 所以这里减去 i*q。
        // 原值 - i*q + i*q = 原值。 正确。
        q2[t2++] = len_left - (long long)i * q;
        q3[t3++] = len_right - (long long)i * q;
    }
    
    cout << "\n";

    // --- 收尾：输出剩余蚯蚓 ---
    // 现在时间走到了第 m 秒，所有还在队列里的蚯蚓，都要加上 m * q
    // 我们做一个简单的三路归并输出
    int total_left = (t1 - h1) + (t2 - h2) + (t3 - h3);
    for(int i = 1; i <= total_left; i++) {
        long long max_val = -2e18;
        int source = -1;

        if(h1 < t1 && q1[h1] > max_val) { max_val = q1[h1]; source = 1; }
        if(h2 < t2 && q2[h2] > max_val) { max_val = q2[h2]; source = 2; }
        if(h3 < t3 && q3[h3] > max_val) { max_val = q3[h3]; source = 3; }

        if(source == 1) h1++;
        else if(source == 2) h2++;
        else if(source == 3) h3++;

        // 这里的公式也不需要变，因为 m 就是总时长
        if(i % t == 0) {
            cout << (max_val + (long long)m * q) << " ";
        }
    }
    
    cout << "\n";
    return 0;
}
