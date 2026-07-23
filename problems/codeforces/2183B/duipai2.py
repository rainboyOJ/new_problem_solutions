#!/usr/bin/env python3
# duipai2.py: 对拍 brute vs greedy2
import subprocess
import sys
import os

DIR = os.path.dirname(os.path.abspath(__file__))
BRUTE = os.path.join(DIR, "brute.py")
GREEDY2 = os.path.join(DIR, "greedy2.py")
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
        out_g, err_g = run(GREEDY2, inp)
        if out_b != out_g:
            print(f"=== MISMATCH at round {i} ===")
            print(f"Input:\n{inp}")
            print(f"Brute:   {out_b}")
            print(f"Greedy2: {out_g}")
            if err_b: print(f"Brute err: {err_b}")
            if err_g: print(f"Greedy2 err: {err_g}")
            return
        if i % 50 == 0:
            print(f"round {i} OK")
    print(f"All {rounds} rounds passed!")

if __name__ == "__main__":
    main()
