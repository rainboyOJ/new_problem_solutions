#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 20:09
# update_at: 2026-10-08 20:09

import sys
from collections.abc import Iterator

type Parents = dict[str, str]  # 人名 -> 父亲，根节点指向自己；名字是字符串，故用 dict 充当并查集底数组

FATHER_MARK = '#'   # 声明「当前父亲」：其后连续的 '+' 都挂在他名下
SON_MARK = '+'      # 认领一个儿子
QUERY_MARK = '?'    # 查询某人的最早祖先
END_MARK = '$'      # 输入结束


def find_root(parents: Parents, name: str) -> str:
    """返回 name 的最早祖先，并压缩路径：把沿途节点直接挂到祖先下。

    用迭代而非递归：数据里的家谱链可长达上万代（GEN8/GEN9），递归会爆栈。
    """
    path: list[str] = []
    while parents.get(name, name) != name:  # 沿父亲方向上溯，记下待压缩的节点
        path.append(name)
        name = parents[name]
    for node in path:                       # 回填：途经节点全部直连根，缩短后续查询
        parents[node] = name
    return name


def run_instructions(tokens: Iterator[str]) -> list[str]:
    """顺序执行指令流，返回每个 '?' 的「本人 最早祖先」答案。"""
    parents: Parents = {}
    current_father = ''
    answers: list[str] = []

    for token in tokens:
        if token == END_MARK:
            break
        op, name = token[0], token[1:]
        if op == FATHER_MARK:
            current_father = name
            parents.setdefault(name, name)          # 新名字先自立为根
        elif op == SON_MARK:
            child_root = find_root(parents, name)
            father_root = find_root(parents, current_father)
            parents[child_root] = father_root       # 整棵子树接到父亲家族的根下
        elif op == QUERY_MARK:
            answers.append(f'{name} {find_root(parents, name)}')

    return answers


def solve() -> None:
    # 按 token 读、不按行读：数据文件是 CRLF 行尾，split() 一并吃掉 '\r' 与空行
    tokens = iter(sys.stdin.read().split())
    answers = run_instructions(tokens)
    sys.stdout.write('\n'.join(answers) + ('\n' if answers else ''))


if __name__ == '__main__':
    solve()
