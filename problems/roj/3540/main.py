#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 06:18
# update_at: 2026-10-02 06:18

import sys


def bonus(avg: int, cls: int, cadre: bool, western: bool, papers: int) -> int:
    """这份数据满足哪几项奖学金条件，返回奖金总数。"""
    # 每行一个家族：五项奖学金的条件与奖金，符合就累加
    return (
        (8000 if avg > 80 and papers >= 1 else 0)   # 院士奖学金
        + (4000 if avg > 85 and cls > 80 else 0)    # 五四奖学金
        + (2000 if avg > 90 else 0)                 # 成绩优秀奖
        + (1000 if avg > 85 and western else 0)     # 西部奖学金
        + (850 if cls > 80 and cadre else 0)        # 班级贡献奖
    )


def solve() -> None:
    """逐个学生统计奖金，在线维护「奖金最多且出现最早」的学生。"""
    tokens = iter(sys.stdin.buffer.read().split())
    n = int(next(tokens))

    best_bonus, best_name = -1, ""
    total = 0
    for _ in range(n):
        name = next(tokens).decode()
        avg, cls = int(next(tokens)), int(next(tokens))
        is_cadre = next(tokens) == b"Y"    # 是否学生干部
        is_western = next(tokens) == b"Y"  # 是否西部省份学生
        papers = int(next(tokens))
        b = bonus(avg, cls, is_cadre, is_western, papers)
        total += b
        # 严格大于：并列时保留先出现的那个
        if b > best_bonus:
            best_bonus, best_name = b, name

    print(best_name)
    print(best_bonus)
    print(total)


if __name__ == "__main__":
    solve()
