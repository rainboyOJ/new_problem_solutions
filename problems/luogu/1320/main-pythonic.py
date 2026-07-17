from itertools import groupby
import sys

text = "".join(line.strip() for line in sys.stdin if line.strip())
n = int(len(text) ** 0.5)
runs = [len(list(group)) for _, group in groupby(text)]
if text and text[0] == "1":
    runs = [0] + runs
print(n, *runs)
