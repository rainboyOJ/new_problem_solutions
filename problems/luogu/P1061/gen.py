import sys
import random
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)

# 生成合法的 s, t, w
# 保证 1 <= s < t <= 26, 2 <= w <= t - s
s = randint(1, 15)
t = randint(s + 3, min(26, s + 9)) # 控制在 10 个字符以内以保证全搜索暴力在 2s 内完成
w = randint(2, t - s)

io.input_writeln(f"{s} {t} {w}")

# 从可选字符集中随机抽取 w 个互不相同的字符并排序
available_chars = [chr(ord('a') + i - 1) for i in range(s, t + 1)]
chosen = sorted(random.sample(available_chars, w))
io.input_writeln("".join(chosen))
