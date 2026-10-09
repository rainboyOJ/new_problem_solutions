#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-09 07:45
# update_at: 2026-10-09 08:12

# 一本通 2072《【例2.15】歌手大奖赛》（ROJ 5073）—— 无输入题，答案唯一。
# 由三个平均分反解最高分、最低分：T = 6a，H = T - 5b，L = T - 5c，ans = (T-H-L)/4。
# 本题 a=9.6, b=9.4, c=9.8，b + c = 2a，故 ans 恰等于 a —— 只是本题数字的巧合。

AVG_ALL = 9.6        # 6 名评委打分的平均分（题面给定的常量，不是答案）
AVG_DROP_HIGH = 9.4  # 去掉一个最高分后 5 人的平均分
AVG_DROP_LOW = 9.8   # 去掉一个最低分后 5 人的平均分
SCORE_CNT = 6        # 评委人数
REST_CNT = 4         # 去掉一高一低后剩下的人数


def solve() -> None:
    """无输入：直接由三个平均分算出剩余 4 人的平均分，按 %5.2f 的等价格式输出。"""
    total = SCORE_CNT * AVG_ALL                     # 6 人总分 57.6
    high = total - (SCORE_CNT - 1) * AVG_DROP_HIGH  # 最高分 10.6
    low = total - (SCORE_CNT - 1) * AVG_DROP_LOW    # 最低分 8.6
    ans = (total - high - low) / REST_CNT           # 38.4 / 4 = 9.6
    # f"{9.6:5.2f}" 对 "9.60" 左侧补 1 个空格，与 C++ 的 printf("%5.2f") 逐字节一致。
    print(f"{ans:5.2f}")


if __name__ == "__main__":
    solve()
