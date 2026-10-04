#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 22:15
# update_at: 2026-10-04 10:21

import sys


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    n, k = int(next(data)), int(next(data))  # n、k 转成 int；学号留在 data 里保持 bytes，避免丢前导零
    # 第 i 个学生是 (学号, 成绩)；成绩必须转成 float，字符串比较会把 "63.100" 排在 "63.2" 前面。
    students = [(sid, float(score)) for sid, score in zip(data, data)]
    # 成绩互不相同，故不存在并列，降序排序后第 k-1 个下标就是第 k 名。
    students.sort(key=lambda stu: stu[1], reverse=True)
    sid, score = students[k - 1]
    # 学号保持原始字节输出，保留测试数据里的前导零（如 092）；成绩按 %g 输出小数（68.4，而非 68.400000）。
    print(f"{sid.decode()} {score:g}")


if __name__ == "__main__":
    solve()
