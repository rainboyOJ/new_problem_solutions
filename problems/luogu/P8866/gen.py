import sys
import random
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)

# 生成一组合法数据
# T=1，栈个数 n 从 2 到 5，k 从 2n-2 到 2n-1
T = 1
io.input_writeln(T)

for _ in range(T):
    n = randint(2, 5)
    # k 取 2n-2 或 2n-1
    k = 2 * n - 1 if random.random() < 0.7 else 2 * n - 2
    # 每种图案出现偶数次（如 2 或 4 次）
    cards = []
    for val in range(1, k + 1):
        cnt = random.choice([2, 4])
        cards.extend([val] * cnt)
    random.shuffle(cards)
    m = len(cards)
    io.input_writeln(f"{n} {m} {k}")
    io.input_writeln(" ".join(map(str, cards)))
