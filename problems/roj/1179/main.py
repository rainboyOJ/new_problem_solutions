#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 22:29
# update_at: 2026-09-29 22:29

import sys

TOP = 5      # 只有前 5 名拿奖学金
SUBJECTS = 3  # 每人语文、数学、英语三门成绩


def rank_key(stu: tuple[int, int, int]) -> tuple[int, int, int]:
    """奖学金排序键：总分高者在前，同分看语文，再同学号小者在前。"""
    idx, total, chinese = stu
    return (-total, -chinese, idx)


def solve() -> None:
    tokens = sys.stdin.buffer.read().split()
    count = int(tokens[0])  # 参评学生人数

    # (学号, 总分, 语文)，学号即输入行号，从 1 开始
    students = [
        (i + 1, sum(scores), scores[0])
        for i in range(count)
        if (scores := [int(t) for t in tokens[1 + SUBJECTS * i: 1 + SUBJECTS * (i + 1)]])
    ]

    # 排序键统一取负号，把"从大到小"折成"从小到大"，学号本身就是升序
    students.sort(key=rank_key)
    print('\n'.join(f"{idx} {total}" for idx, total, _ in students[:TOP]))


if __name__ == "__main__":
    solve()
