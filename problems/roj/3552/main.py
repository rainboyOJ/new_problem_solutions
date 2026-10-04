#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 07:06
# update_at: 2026-10-02 07:45

import sys


def money(avg: float, ev: float, cadre: str, west: str, papers: int) -> int:
    """五项奖学金全部命中的金额之和：bool 乘金额，命中加钱、未命中加 0。"""
    return (
        8000 * (avg > 80 and papers >= 1)  # 均分 >80 且有论文
        + 4000 * (avg > 85 and ev > 80)  # 均分 >85 且评议 >80
        + 2000 * (avg > 90)  # 均分 >90
        + 1000 * (avg > 85 and west == "Y")  # 均分 >85 的西部学生
        + 850 * (ev > 80 and cadre == "Y")  # 评议 >80 的学生干部
    )


def solve() -> None:
    lines = sys.stdin.read().splitlines()
    n = int(lines[0])  # 学生人数
    top_name, top_money, total = "", -1, 0

    for line in lines[1 : n + 1]:
        name, avg, ev, cadre, west, papers = line.split()
        amount = money(float(avg), float(ev), cadre, west, int(papers))
        total += amount
        if amount > top_money:  # 严格大于：并列时保留最先出现的学生
            top_name, top_money = name, amount

    print(f"{top_name}\n{top_money}\n{total}")


if __name__ == "__main__":
    solve()
