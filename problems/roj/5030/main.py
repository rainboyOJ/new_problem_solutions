#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 19:45
# update_at: 2026-10-08 19:45

TOTAL = 100            # 百钱买百鸡：鸡共 100 只、钱共 100 文
ROOSTER_PRICE = 5      # 鸡翁一只值钱 5
HEN_PRICE = 3          # 鸡母一只值钱 3
CHICK_PER_COIN = 3     # 鸡雏 3 只值钱 1，所以鸡雏数必须是 3 的倍数


def solve() -> None:
    """枚举鸡翁、鸡母并推出鸡雏，校验钱数后按鸡翁升序输出全部解。"""
    for rooster in range(TOTAL // ROOSTER_PRICE + 1):
        for hen in range(TOTAL // HEN_PRICE + 1):
            chick = TOTAL - rooster - hen
            if chick < 0 or chick % CHICK_PER_COIN:
                continue  # 鸡雏按 3 只一组卖，数量不是 3 的倍数时钱数无意义
            cost = rooster * ROOSTER_PRICE + hen * HEN_PRICE + chick // CHICK_PER_COIN
            if cost == TOTAL:
                print(rooster, hen, chick)


if __name__ == "__main__":
    solve()
