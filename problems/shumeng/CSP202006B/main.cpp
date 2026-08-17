/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:39
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXA = 500005;

int n, a, b;                       // n 为向量维数，a、b 为两个向量的非零项个数
int first_index[MAXA];             // 第一个稀疏向量的坐标
int first_value[MAXA];             // 第一个稀疏向量的非零值

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> a >> b;
    for (int i = 0; i < a; i++) cin >> first_index[i] >> first_value[i];

    // 双指针扫描：position 指向第一个向量当前项，顺序读入第二个向量的非零项
    long long answer = 0;
    int position = 0;
    for (int i = 0; i < b; i++) {
        int second_index, second_value;
        cin >> second_index >> second_value;
        // 跳过所有坐标比当前项小的第一向量项
        while (position < a && first_index[position] < second_index) position++;
        // 坐标相同说明两向量在该维度都不为 0，累加对应值的乘积
        if (position < a && first_index[position] == second_index) {
            answer += 1LL * first_value[position] * second_value;
        }
    }
    cout << answer << '\n';

    return 0;
}