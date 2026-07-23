#!/usr/bin/env python3
# duipai.py: 对拍脚本，随机生成数据，比较 brute 和 greedy 的输出
import subprocess
import sys
import os

DIR = os.path.dirname(os.path.abspath(__file__))
BRUTE = os.path.join(DIR, "brute.py")
GREEDY = os.path.join(DIR, "greedy.py")
GEN = os.path.join(DIR, "gen.py")

def run(script, inp):
    r = subprocess.run(
        ["python3", script],
        input=inp, capture_output=True, text=True, timeout=10
    )
    return r.stdout.strip(), r.stderr.strip()

def main():
    rounds = int(sys.argv[1]) if len(sys.argv) > 1 else 500
    for i in range(1, rounds + 1):
        inp, _ = run(GEN, "")
        out_b, err_b = run(BRUTE, inp)
        out_g, err_g = run(GREEDY, inp)
        if out_b != out_g:
            print(f"=== MISMATCH at round {i} ===")
            print(f"Input:\n{inp}")
            print(f"Brute:  {out_b}")
            print(f"Greedy: {out_g}")
            if err_b: print(f"Brute err: {err_b}")
            if err_g: print(f"Greedy err: {err_g}")
            return
        if i % 50 == 0:
            print(f"round {i} OK")
    print(f"All {rounds} rounds passed!")

if __name__ == "__main__":
    main()
