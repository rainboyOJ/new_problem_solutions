#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-03-31 10:00
# update_at: 2026-03-31 10:00

import sys

BASE = 131
MOD = 1_000_000_000_000_000_003  # 64 位大质数防哈希冲突


def build_powers_and_prefixes(text: str, base: int, mod: int) -> tuple[list[int], list[int]]:
    """预处理字符串的前缀哈希值与进制幂次数组。"""
    n = len(text)
    powers = [1] * (n + 1)
    prefix_hashes = [0] * (n + 1)
    for i, ch in enumerate(text):
        powers[i + 1] = (powers[i] * base) % mod
        prefix_hashes[i + 1] = (prefix_hashes[i] * base + ord(ch)) % mod
    return powers, prefix_hashes


def segment_hash(prefix_hashes: list[int], powers: list[int], mod: int, left: int, right: int) -> int:
    """提取区间 [left, right) 的滚动哈希值。"""
    raw_hash = (prefix_hashes[right] - prefix_hashes[left] * powers[right - left]) % mod
    return raw_hash + mod if raw_hash < 0 else raw_hash


def hash_without_char(
    prefix_hashes: list[int],
    powers: list[int],
    mod: int,
    left: int,
    right: int,
    skip: int,
) -> int:
    """计算区间 [left, right) 剔除下标 skip 字符后的哈希值。"""
    left_part = segment_hash(prefix_hashes, powers, mod, left, skip)
    right_part = segment_hash(prefix_hashes, powers, mod, skip + 1, right)
    return (left_part * powers[right - skip - 1] + right_part) % mod


def find_unique_s(text: str, length: int) -> str:
    """遍历删除位置，枚举并判定是否存在唯一的原串 S。"""
    if length % 2 == 0:
        return "NOT POSSIBLE"

    half = length // 2
    powers, prefix_hashes = build_powers_and_prefixes(text, BASE, MOD)

    candidates: set[str] = set()

    for del_idx in range(length):
        if del_idx < half:
            left_hash = hash_without_char(prefix_hashes, powers, MOD, 0, half + 1, del_idx)
            right_hash = segment_hash(prefix_hashes, powers, MOD, half + 1, length)
            is_valid = left_hash == right_hash
            candidate_str = text[half + 1 :]
        elif del_idx == half:
            left_hash = segment_hash(prefix_hashes, powers, MOD, 0, half)
            right_hash = segment_hash(prefix_hashes, powers, MOD, half + 1, length)
            is_valid = left_hash == right_hash
            candidate_str = text[:half]
        else:
            left_hash = segment_hash(prefix_hashes, powers, MOD, 0, half)
            right_hash = hash_without_char(prefix_hashes, powers, MOD, half, length, del_idx)
            is_valid = left_hash == right_hash
            candidate_str = text[:half]

        if is_valid:
            candidates.add(candidate_str)
            if len(candidates) > 1:
                return "NOT UNIQUE"

    if not candidates:
        return "NOT POSSIBLE"
    return next(iter(candidates))


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    n_token = next(data, None)
    if n_token is None:
        return
    n = int(n_token)
    text = next(data).decode()
    result = find_unique_s(text, n)
    print(result)


if __name__ == "__main__":
    solve()
