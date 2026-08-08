import sys
from array import array

data = sys.stdin.buffer.read().split()
n, m = map(int, data[:2])
ids = array("i", map(int, data[2 : 2 + n]))
sys.stdout.write("\n".join(str(ids[int(data[2 + n + i]) - 1]) for i in range(m)))
