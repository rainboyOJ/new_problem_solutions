#!/usr/bin/env python3
"""CF19D 数据生成器：无输入，stdout 就是一组数据。

小规模随机，坐标值域小以便大量 add/remove/find 互相命中；
add 只在未标记点中取，remove 只在已标记点中取，保证操作合法。
"""
import sys

from cyaron import IO, randint

op_count = randint(1, 12)
coord_max = randint(1, 6)

io = IO(input_file=sys.stdout, disable_output=True)
io.input_writeln(op_count)

marked = []  # 当前已标记的点，保证 remove 合法
all_points = [
    (x, y) for x in range(coord_max + 1) for y in range(coord_max + 1)
]

for _ in range(op_count):
    choice = randint(1, 100)
    if choice <= 40 and len(marked) < len(all_points):
        # add：从还没标记的点里挑
        rest = [p for p in all_points if p not in set(marked)]
        point = rest[randint(0, len(rest) - 1)]
        marked.append(point)
        io.input_writeln("add", point[0], point[1])
    elif choice <= 65 and marked:
        # remove：只能删已标记的点
        point = marked.pop(randint(0, len(marked) - 1))
        io.input_writeln("remove", point[0], point[1])
    else:
        # find：坐标在值域内随机，既会命中也会落空
        io.input_writeln("find", randint(0, coord_max), randint(0, coord_max))
