import sys


data = list(map(int, sys.stdin.buffer.read().split()))
n, m = data[:2]
student_ids = data[2:2 + n]
queries = data[2 + n:2 + n + m]

print("\n".join(str(student_ids[position - 1]) for position in queries))
