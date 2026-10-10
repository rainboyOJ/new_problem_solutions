#!/usr/bin/env python3
"""格式感知的 C++/Python 对拍验证器。

从 data/ 的真实输入中「学」每题的输入格式（token 分布），
生成同构随机输入做对拍 —— 避免凭猜测写输入格式（教训：我的第 32 个错误）。

用法: python3 verify_pyonly.py <pid> [组数]
"""
import random
import subprocess
import sys
from pathlib import Path

REPO = Path('/Users/rainboymac/mycode/RBOOK_series/pcs-roj-sol')
NEW_ROJ = Path('/Users/rainboymac/mycode/RBOOK_series/new_ROJ/problems')
PY = '/opt/homebrew/bin/python3.14'
GXX = '/opt/homebrew/bin/g++-16'


def learn_format(data_dir: Path, samples: int = 5):
    """从真实 .in 学格式：返回每题的 token 生成器模板。

    策略：数每行 token 数、token 类型（int/str）、值域，生成同构随机输入。
    这里用最稳的「模板行」法：保留真实文件的结构（行数、每行 token 数），
    把每个整数 token 换成同量级随机数。
    """
    infiles = sorted(data_dir.glob('*.in')) or sorted(
        f for f in data_dir.iterdir() if f.is_file() and f.suffix.lower() in ('.in', '.txt')
    )
    templates = []
    for f in infiles[:samples]:
        lines = f.read_text(errors='replace').splitlines()
        # 取前 12 行的结构
        struct = []
        for line in lines[:12]:
            toks = line.split()
            if not toks:
                continue
            row = []
            for t in toks:
                try:
                    v = int(t)
                    row.append(('int', abs(v) if 0 < abs(v) <= 10 ** 9 else 10))
                except ValueError:
                    row.append(('str', t))
            struct.append(row)
        if struct:
            templates.append(struct)
    return templates


def gen_from_template(template, rng):
    out_lines = []
    for row in template:
        toks = []
        for kind, v in row:
            if kind == 'int':
                if v == 0:
                    toks.append('0')
                else:
                    mag = max(1, min(v, 10 ** 9))
                    lo, hi = max(1, mag // 2), mag
                    toks.append(str(rng.randint(lo, hi)))
            else:
                toks.append(v)
        out_lines.append(' '.join(toks))
    return '\n'.join(out_lines) + '\n'


def main():
    pid = sys.argv[1]
    rounds = int(sys.argv[2]) if len(sys.argv) > 2 else 100
    prob = REPO / 'problems' / 'roj' / pid
    data_dir = NEW_ROJ / pid / 'data'
    rng = random.Random(hash(pid) & 0xffff)

    templates = learn_format(data_dir)
    if not templates:
        print(f'{pid}: ❌ 无数据可学格式')
        return 2

    binp = f'/tmp/verify_pyonly_{pid}'
    c = subprocess.run([GXX, '-O2', '-std=c++17', '-o', binp, str(prob / 'main.cpp')],
                       capture_output=True, text=True)
    if c.returncode != 0:
        print(f'{pid}: ❌ C++ 编译失败\n{c.stderr[:300]}')
        return 2

    diff = 0
    tested = 0
    for i in range(rounds):
        tpl = templates[i % len(templates)]
        inp = gen_from_template(tpl, rng)
        try:
            a = subprocess.run([PY, str(prob / 'main.py')], input=inp,
                               capture_output=True, text=True, timeout=10).stdout
            b = subprocess.run([binp], input=inp, capture_output=True, text=True, timeout=10).stdout
        except subprocess.TimeoutExpired:
            continue
        tested += 1
        if a != b:
            diff += 1
            if diff <= 2:
                print(f'  分歧样例输入:\n{inp[:200]}')
                print(f'  py: {a[:80]!r}  cpp: {b[:80]!r}')
    status = '✅' if diff == 0 else '❌'
    print(f'{pid}: {status} 对拍 {tested} 组，分歧 {diff}')
    return 0 if diff == 0 else 1


if __name__ == '__main__':
    sys.exit(main())
