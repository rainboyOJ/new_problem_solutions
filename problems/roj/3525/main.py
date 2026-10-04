#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 22:00
# update_at: 2026-07-05 22:00

import sys

# 枚举量：罪犯 20 种 × 星期 7 种 = 140 个假设，逐一验证，复杂度 O(140·P)
MONDAY = ("Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday")
JUNK, OK = None, 0              # 证词语义：JUNK = 闲话不入推理，OK = 与当前假设一致


def sentence_opinion(sentence: str, suspect: str, speaker: str, day: str) -> int | None:
    """把一句证词翻译成它在当前假设下的立场：返回 1 表示与假设冲突，None 表示闲话。"""
    if sentence in ("I am guilty.", "I am GUILTY."):      # "I am GUILTY." 是原题的经典坑
        return OK if speaker == suspect else 1            # 说话者自认罪犯
    if sentence == "I am not guilty.":
        return OK if speaker != suspect else 1            # 说话者否认作案
    if sentence.endswith(" is guilty."):
        name = sentence[:-len(" is guilty.")]
        return OK if name == suspect else 1               # 指认他人是罪犯
    if sentence.endswith(" is not guilty."):
        name = sentence[:-len(" is not guilty.")]
        return OK if name != suspect else 1               # 替他人洗清嫌疑
    if sentence.startswith("Today is "):                  # 星期断言：同一天为真，否则为假
        return OK if sentence[9:-1] == day else 1
    return JUNK                                           # 其余闲话（含相似句式）不入推理


def solve() -> None:
    raw = sys.stdin.read().splitlines()          # 证词不能按词切，整个输入按行处理
    it = iter(raw[0].split())
    m, n, p = int(next(it)), int(next(it)), int(next(it))
    people = raw[1:1 + m]

    # 证词按行读：冒号前是说话者，冒号后是原句（闲话里可能有奇怪内容，不能按词切）
    statements = [(line.split(":", 1)[0], line.split(":", 1)[1].strip())
                  for line in raw[1 + m:1 + m + p]]

    suspects = []                          # 每个通过验证的假设对应的罪犯候选
    for suspect in people:
        for day in MONDAY:
            honest: set[str] = set()       # 当前假设下已确定说真话的人
            liars: set[str] = set()        # 当前假设下已确定说谎的人
            ok = True                      # 该假设是否自洽（无身份冲突且能凑满 N）
            for speaker, sentence in statements:
                opinion = sentence_opinion(sentence, suspect, speaker, day)
                if opinion is JUNK:        # 闲话谁说都一样，不约束任何人的身份
                    continue
                liar = opinion == 1        # 立场与假设冲突的人必须说谎，否则必须说真
                if (speaker in liars and not liar) or (speaker in honest and liar):
                    ok = False             # 同一个人被同时定为既真又假，假设作废
                    break
                (liars if liar else honest).add(speaker)
            # 空闲名额：只说闲话的人身份自由，补足"说谎者恰好 N 人"
            free = len({w for w, _ in statements}) - len(honest) - len(liars)
            if ok and len(liars) <= n <= len(liars) + free:
                suspects.append(suspect)
                break                      # 该人已有自洽假设，不必再试其余星期
    if not suspects:
        print("Impossible")                # 没有任何假设自洽
    elif len(set(suspects)) > 1:
        print("Cannot Determine")          # 多人可能是罪犯
    else:
        print(suspects[0])


if __name__ == "__main__":
    solve()
