#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 02:27
# update_at: 2026-10-01 02:27

import sys

# 九宫格键盘字符到数字的映射（不包含 Q 和 Z）
CHAR_TO_DIGIT = str.maketrans("ABCDEFGHIJKLMNOPRSTUVWXY", "222333444555666777888999")


def word_to_number(word: str) -> str:
    """将英文名字转换为九宫格按键数字串。"""
    return word.translate(CHAR_TO_DIGIT)


def find_matching_names(words: list[str], target: str) -> list[str]:
    """从字典单词列表中筛选出与目标数字匹配的所有名字。"""
    return [w for w in words if len(w) == len(target) and word_to_number(w) == target]


def solve() -> None:
    tokens = sys.stdin.read().split()
    if not tokens:
        return

    # 输入前部为字典名字列表，最后一个词为目标数字串
    words = tokens[:-1]
    target = tokens[-1]

    matches = find_matching_names(words, target)
    print("\n".join(matches) if matches else "NONE")


if __name__ == "__main__":
    solve()
