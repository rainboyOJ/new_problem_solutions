import sys
from cyaron import IO, randint, String

io = IO(input_file=sys.stdout, disable_output=True)
# 生成随机长度为 len_s, len_t 的字符串
len_s = randint(1, 15)
# 80% 概率长度相等，20% 概率不等用于测试边界
len_t = len_s if randint(1, 5) > 1 else randint(1, 15)

s = "".join([chr(randint(ord("a"), ord("e"))) for _ in range(len_s)])
t = "".join([chr(randint(ord("a"), ord("e"))) for _ in range(len_t)])

io.input_writeln(s)
io.input_writeln(t)

n = randint(0, 20)
io.input_writeln(n)

for _ in range(n):
    u = chr(randint(ord("a"), ord("e")))
    v = chr(randint(ord("a"), ord("e")))
    w = randint(0, 50)
    io.input_writeln(f"{u} {v} {w}")
