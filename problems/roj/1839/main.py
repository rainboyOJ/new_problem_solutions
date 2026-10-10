#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 06:45
# update_at: 2026-10-08 06:45

import sys
from collections.abc import Iterator

# 五项奖学金的判定条件与金额：(期末成绩下界, 评议成绩下界, 需要干部, 需要西部, 论文下界)
# 成绩下界都按题面"高于"取严格大于，写成"最小成立值"；不需要的维度填 0 / 0 / False。
type Rule = tuple[int, int, bool, bool, int]  # avg_min, cls_min, leader, west, papers_min

RULES: tuple[tuple[Rule, int], ...] = (
    ((81, 0, False, False, 1), 8000),   # 院士奖学金：avg>80 且 papers>=1
    ((86, 81, False, False, 0), 4000),  # 五四奖学金：avg>85 且 cls>80
    ((91, 0, False, False, 0), 2000),   # 成绩优秀奖：avg>90
    ((86, 0, False, True, 0), 1000),    # 西部奖学金：avg>85 且西部省份学生
    ((0, 81, True, False, 0), 850),     # 班级贡献奖：cls>80 且学生干部
)


def students(data: Iterator[str]) -> Iterator[tuple[str, int]]:
    """依次产出每个学生的 (姓名, 奖金总额)。

    五项奖学金互相独立、可叠加，逐条判定后求和即可；
    学生属性读完即弃，不需要保存全量数据。
    """
    n = int(next(data))
    for _ in range(n):
        name = next(data)
        avg, cls = int(next(data)), int(next(data))
        leader, west = next(data) == 'Y', next(data) == 'Y'
        papers = int(next(data))
        yield name, sum(
            money
            for (avg_min, cls_min, need_leader, need_west, papers_min), money in RULES
            if avg >= avg_min and cls >= cls_min
            and (not need_leader or leader) and (not need_west or west)
            and papers >= papers_min
        )


def solve() -> None:
    data = iter(sys.stdin.buffer.read().decode().split())  # 姓名按字符串处理，整体解码

    total_sum = 0        # 全员奖学金总额
    best_val = -1        # 初值 -1：即使全员 0 元也能让第 1 个人完成初始化
    best_name = ''       # 最高奖金获得者（并列时保留最早出现的）

    for name, money in students(data):
        total_sum += money
        if money > best_val:  # 严格大于：并列时不覆盖，最早出现者胜出
            best_val, best_name = money, name

    print(f"{best_name}\n{best_val}\n{total_sum}")


if __name__ == "__main__":
    solve()
