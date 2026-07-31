#!/usr/bin/env python3
"""Compare original main.cpp vs main-cout.cpp output on same sample input."""
import glob, re, os, subprocess

TMP = '/tmp/ojtest'

cout_dirs = sorted(set(os.path.dirname(f) for f in glob.glob('problems/noi_openjudge/**/main-cout.cpp', recursive=True)))

# Build original binaries (only for compare)
for d in cout_dirs:
    pid = os.path.basename(d)
    orig_exe = os.path.join(TMP, f'orig_{pid}')
    if os.path.exists(orig_exe):
        continue
    orig_cpp = os.path.join(d, 'main.cpp')
    if os.path.exists(orig_cpp):
        r = subprocess.run(['g++', '-std=c++17', '-O2', '-w', '-o', orig_exe, orig_cpp],
                           capture_output=True, text=True, timeout=30)

results = []
for d in cout_dirs:
    pid = os.path.basename(d)
    new_exe = os.path.join(TMP, pid)
    orig_exe = os.path.join(TMP, f'orig_{pid}')
    if not os.path.exists(new_exe) or not os.path.exists(orig_exe):
        continue
    pmd = os.path.join(d, 'problem.md')
    content = open(pmd).read()
    ins = re.findall(r'样例输入\n+```[a-z]*\n(.*?)\n```', content, re.DOTALL)
    if not ins:
        continue
    inp = ins[0].strip()
    try:
        ro = subprocess.run([orig_exe], input=inp, capture_output=True, text=True, timeout=15)
        rn = subprocess.run([new_exe], input=inp, capture_output=True, text=True, timeout=15)
    except Exception as e:
        results.append((pid, 'RUNTIME', str(e)))
        continue
    no = '\n'.join(l.rstrip() for l in ro.stdout.splitlines())
    nn = '\n'.join(l.rstrip() for l in rn.stdout.splitlines())
    if no == nn:
        results.append((pid, 'MATCH'))
    else:
        results.append((pid, 'DIFF', f'orig={ro.stdout[:60]!r} new={rn.stdout[:60]!r}'))

with open(os.path.join(TMP, 'compare.txt'), 'w') as f:
    for r in results:
        f.write('\t'.join(r) + '\n')

m = sum(1 for r in results if r[1] == 'MATCH')
d = sum(1 for r in results if r[1] == 'DIFF')
r = sum(1 for r in results if r[1] == 'RUNTIME')
print(f'MATCH: {m}  DIFF: {d}  RUNTIME: {r}  (total compared {len(results)})')
