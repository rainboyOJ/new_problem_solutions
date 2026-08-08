/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 115;

int n;

// 成员结构体
struct Member {
    char name[20];    // 姓名
    char role[20];    // 职位
    int  contribution; // 帮贡
    int  level;        // 等级
    int  idx;          // 输入顺序
};

Member members[MAXN];

// 职位对应的排名值（越小职位越高）
int role_rank(char *role) {
    if (strcmp(role, "BangZhu")    == 0) return 0;
    if (strcmp(role, "FuBangZhu")  == 0) return 1;
    if (strcmp(role, "HuFa")       == 0) return 2;
    if (strcmp(role, "ZhangLao")   == 0) return 3;
    if (strcmp(role, "TangZhu")    == 0) return 4;
    if (strcmp(role, "JingYing")   == 0) return 5;
    return 6; // BangZhong
}

// 阶段 1 排序：按帮贡降序，帮贡相同按输入顺序升序
bool cmp1(const Member &a, const Member &b) {
    if (a.contribution != b.contribution)
        return a.contribution > b.contribution;
    return a.idx < b.idx;
}

// 阶段 2 排序：按职位排名升序->等级降序->输入顺序升序
bool cmp2(const Member &a, const Member &b) {
    int ra = role_rank((char*)a.role);
    int rb = role_rank((char*)b.role);
    if (ra != rb) return ra < rb;
    if (a.level != b.level) return a.level > b.level;
    return a.idx < b.idx;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> members[i].name >> members[i].role
            >> members[i].contribution >> members[i].level;
        members[i].idx = i;
    }

    // 新职位分配表
    char new_roles[50][20] = {
        "HuFa", "HuFa",
        "ZhangLao", "ZhangLao", "ZhangLao", "ZhangLao",
        "TangZhu", "TangZhu", "TangZhu", "TangZhu",
        "TangZhu", "TangZhu", "TangZhu",
        "JingYing", "JingYing", "JingYing", "JingYing",
        "JingYing", "JingYing", "JingYing", "JingYing",
        "JingYing", "JingYing", "JingYing", "JingYing",
        "JingYing", "JingYing", "JingYing", "JingYing",
        "JingYing", "JingYing", "JingYing", "JingYing",
        "JingYing", "JingYing", "JingYing", "JingYing",
        "JingYing", "JingYing"
    };
    int new_role_cnt = 38; // 2+4+7+25

    // 筛选出可调整的成员（不是帮主和副帮主）
    Member adj[MAXN];
    int adj_cnt = 0;
    for (int i = 0; i < n; i++) {
        if (strcmp(members[i].role, "BangZhu") != 0 &&
            strcmp(members[i].role, "FuBangZhu") != 0) {
            adj[adj_cnt++] = members[i];
        }
    }

    // 按帮贡排序
    sort(adj, adj + adj_cnt, cmp1);

    // 重新分配职位
    for (int i = 0; i < adj_cnt; i++) {
        if (i < new_role_cnt)
            strcpy(adj[i].role, new_roles[i]);
        else
            strcpy(adj[i].role, "BangZhong");
    }

    // 把调整后的成员合并回原数组
    int p = 0;
    for (int i = 0; i < n; i++) {
        if (strcmp(members[i].role, "BangZhu") == 0 ||
            strcmp(members[i].role, "FuBangZhu") == 0) {
            continue;
        }
        members[i] = adj[p++];
    }

    // 最终排序并输出
    sort(members, members + n, cmp2);

    for (int i = 0; i < n; i++) {
        cout << members[i].name << " "
             << members[i].role << " "
             << members[i].level << "\n";
    }

    return 0;
}
