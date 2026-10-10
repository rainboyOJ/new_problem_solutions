import sys, subprocess, pathlib
d = pathlib.Path('/Users/rainboymac/mycode/RBOOK_series/new_ROJ/problems/3077/data')
ok = True
for f in sorted(d.glob('alpha*.in')):
    txt = f.read_text().split()
    n = int(txt[0]); A, B, C = txt[1], txt[2], txt[3]
    out = subprocess.run(['/tmp/gen3077/sol'], input=f.read_text(), capture_output=True, text=True, timeout=30).stdout.strip()
    v = list(map(int, out.split()))
    # 独立校验：把字母换成数字，做 n 进制加法
    assert len(v) == n, f'{f.name}: 长度 {len(v)} != n={n}'
    def to_int(s):
        r = 0
        for ch in s: r = r * n + v[ord(ch) - 65]
        return r
    correct = (to_int(A) + to_int(B) == to_int(C))
    # 还要检查是否双射（0..n-1 各一次）
    bijective = (sorted(v) == list(range(n)))
    print(f'  {f.name:14s} n={n:2d}  {A}+{B}={C}  {"✅" if correct and bijective else "❌"}  双射={bijective}')
    if not (correct and bijective): ok = False
print()
print('✅ 全部 10 个解经【独立进制换算】验证通过' if ok else '❌ 有失败')
