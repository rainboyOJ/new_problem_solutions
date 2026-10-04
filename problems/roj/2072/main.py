#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 06:48
# update_at: 2026-10-01 06:48

import sys
from pathlib import Path

# 图上给出的字母分值，下标 = ord(字母) - ord('a')
SCORE = (2, 5, 4, 4, 1, 6, 5, 5, 1, 7, 6, 3, 5, 2, 3, 5, 7, 2, 1, 2, 4, 6, 6, 7, 5, 7)

DICT_NAME = "lgame.dict"  # 题面规定的字典文件


def letter_mask(word: str) -> int:
    """单词里出现过哪些字母：第 i 位为 1 表示 chr(ord('a') + i) 出现过。"""
    return sum(1 << (ord(ch) - 97) for ch in set(word))


def usage_vector(word: str) -> tuple[int, ...]:
    """单词在 26 个字母上各用了几个，用来精确判断手上的卡片够不够拼。"""
    counts = [0] * 26
    for ch in word:
        counts[ord(ch) - 97] += 1
    return tuple(counts)


def word_score(word: str) -> int:
    """单词得分 = 每个字母分值之和。"""
    return sum(SCORE[ord(ch) - 97] for ch in word)


def solve() -> None:
    # 卡片是第 1 个 token；字典长度不固定，以 "." 结束，只能用迭代器顺序消费到终止点。
    data = iter(sys.stdin.read().split())
    cards = next(data)                 # 第 1 个 token：手上的卡片
    words: list[str] = []
    for token in data:                 # 第 2..stop-1 个 token：字典单词
        if token == ".":
            break
        words.append(token)

    if not words:                      # 只给了卡片，字典按题面从 lgame.dict 读
        candidates = (Path(__file__).with_name(DICT_NAME), Path(DICT_NAME))
        words = next(p for p in candidates if p.is_file()).read_text().split()

    cards_mask, card_usage = letter_mask(cards), usage_vector(cards)

    # 用位与整批淘汰含卡片外字母的单词：掩码挡住字母种类，挡不住重复个数
    kept = [w for w in words if (letter_mask(w) & ~cards_mask) == 0]
    # 剩下的少量候选再逐字母比用量，抓出"卡片只有 1 个 a、单词却要 2 个 a"这类
    playing = [(w, word_score(w), usage_vector(w)) for w in kept]
    playing = [item for item in playing if all(x <= y for x, y in zip(item[2], card_usage))]

    best = max((score for _, score, _ in playing), default=0)
    winners = [word for word, score, _ in playing if score == best]

    # 词对枚举下标 i <= j：小者在前，同一对不会换个顺序再出现一次
    for i, (word_a, score_a, usage_a) in enumerate(playing):
        for word_b, score_b, usage_b in playing[i:]:
            if score_a + score_b < best:  # 追不平当前最高分，不必再算用量
                continue
            if any(x + y > z for x, y, z in zip(usage_a, usage_b, card_usage)):
                continue
            if score_a + score_b > best:
                best, winners = score_a + score_b, []
            winners.append(f"{word_a} {word_b}")

    sys.stdout.write("\n".join([str(best), *sorted(winners)]) + "\n")


if __name__ == "__main__":
    solve()
