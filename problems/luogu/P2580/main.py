import sys

# 一次性读入全部输入，用迭代器依次取数
data = iter(sys.stdin.buffer.read().split())

# 读入 n 个姓名作为名单
n = int(next(data))
valid = {next(data) for _ in range(n)}  # 名单集合，O(1) 查询

# 处理 m 次点名
m = int(next(data))
called = set()    # 已点到过的姓名
answers = []      # 收集每次结果

for _ in range(m):
    name = next(data)
    if name not in valid:
        answers.append("WRONG")   # 不在名单中
    elif name in called:
        answers.append("REPEAT")  # 已经点过了
    else:
        called.add(name)
        answers.append("OK")      # 第一次点到

print("\n".join(answers))
