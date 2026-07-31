#!/usr/bin/env python3
"""Run sample tests for main-cout.cpp files. Results to /tmp/ojtest/results.txt"""
import glob, re, os, subprocess

TMP = '/tmp/ojtest'
os.makedirs(TMP, exist_ok=True)

cout_dirs = sorted(set(os.path.dirname(f) for f in glob.glob('problems/noi_openjudge/**/main-cout.cpp', recursive=True)))

lines = []
for d in cout_dirs:
    pid = os.path.basename(d)
    exe = os.path.join(TMP, pid)
    if not os.path.exists(exe):
        lines.append(f'{pid}\tSKIP\tcompile-failed')
        continue
    pmd = os.path.join(d, 'problem.md')
    if not os.path.exists(pmd):
        lines.append(f'{pid}\tSKIP\tno-problem.md')
        continue
    content = open(pmd).read()
    ins = re.findall(r'样例输入\n+```[a-z]*\n(.*?)\n```', content, re.DOTALL)
    outs = re.findall(r'样例输出\n+```[a-z]*\n(.*?)\n```', content, re.DOTALL)
    if not ins or not outs:
        lines.append(f'{pid}\tSKIP\tno-sample')
        continue
    if '不提供' in outs[0]:
        lines.append(f'{pid}\tSKIP\tno-real-sample')
        continue
    passed = True
    detail = ''
    for idx, (inp, exp) in enumerate(zip(ins, outs)):
        inp = inp.strip()
        exp = exp.strip()
        try:
            r = subprocess.run([exe], input=inp, capture_output=True, text=True, timeout=15)
            got = r.stdout.strip()
        except Exception as e:
            passed = False
            detail = f'RUNTIME:{type(e).__name__}'
            break
        norm_got = '\n'.join(l.rstrip() for l in got.splitlines())
        norm_exp = '\n'.join(l.rstrip() for l in exp.splitlines())
        if norm_got != norm_exp:
            passed = False
            detail = f'#{" vs ".join(map(str,[idx]))}: exp={exp[:60]!r} got={got[:60]!r}'
            break
    if passed:
        lines.append(f'{pid}\tPASS')
    else:
        lines.append(f'{pid}\tFAIL\t{detail}')

with open(os.path.join(TMP, 'results.txt'), 'w') as f:
    f.write('\n'.join(lines) + '\n')
