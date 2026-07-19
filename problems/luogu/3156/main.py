import sys
from array import array


data = sys.stdin.buffer.read().split()
n = int(data[0])
m = int(data[1])

# n 最大 2e6：用 array 存学号，避免 200 万个 Python int 对象拖慢
student_ids = array("i", map(int, data[2 : 2 + n]))

out = [str(student_ids[int(data[2 + n + i]) - 1]) for i in range(m)]
sys.stdout.write("\n".join(out))
