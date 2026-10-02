---
name: python-oj-short
description: >-
  用 Python 3.15 写 OJ 题的「教学版短解法」：算法正确、复杂度与标准 C++ 解法同阶，
  但用 Python 的表达式能力（functools.cache、推导式、生成器、位运算）把代码压到最短，
  风格对齐 main3.py。允许 Python TLE/MLE，但不允许因此把算法换成暴力枚举。
  触发词：Python 短解法、Pythonic 精简写法、短变体、表达式优先、代码太长帮我压缩。
  不用于展开式教学代码（需要逐行讲清算法），也不用于明确要求 C++ 的场景。
---

# Python OJ 短解法（教学版）

用 Python 3.15 写一份 OJ 题的「教学版短解法」。风格对齐 main3.py：算法正确、
复杂度与标准 C++ 解法同阶，但用 Python 的表达式能力把代码压到最短。
允许 Python TLE/MLE，但绝不能因此把算法换成暴力枚举。

## 一、允许并鼓励

- 只用标准库；优先 `functools.cache`、`itertools`、`collections`，不引第三方依赖。
- 用列表/字典/集合推导替代 `for + append`；一个"家族"写一行，行尾注释标数量：

```python
LINES = (
    [((r, c), (r, c + 1), (r, c + 2)) for r in range(3) for c in range(3)]  # 横向 9 条
    + [((0, 2), (1, 2), (2, 2))]                                           # 纵向 1 条
    + [((0, c), (1, c + 1), (2, c + 2)) for c in range(3)]                  # 右下斜 3 条
    + [((0, c + 2), (1, c + 1), (2, c)) for c in range(3)]                  # 右上斜 3 条
)
```

- 用生成器 + `sum`/`max`/`any`/`all` 替代手写累加循环：

```python
return sum(
    (1 if get_color(window[2], r) else -1) * weight[r][col]  # X 红 +，O 蓝 -
    for r in range(3)
    if mask >> r & 1
)
```

- 用位运算表达"取某一位 / 置位"：`pattern >> row & 1`、`mask |= 1 << r`。
- 用集合推导做"全相等"判断：`len({get_color(window[c], r) for r, c in cells}) == 1`。
- 用条件表达式和 `dict.get` 收掉分支：`choices = range(8) if i < n else (None,)`、
  `nxt[k] = max(nxt.get(k, NEG), score + gain)`。
- 用 `@cache` 替代"手工生成全量预计算表"：装饰器 + 可哈希参数即可，不要写
  `TABLE = bytearray(9**5)` + `for code in range(9**5)` 这种建表循环。
- **读入优先用 `next()` 顺序消费**：
  `data = iter(map(int, sys.stdin.buffer.read().split()))` 之后一律
  `T = next(data)`、`n, k, q = next(data), next(data), next(data)`、
  `v = [next(data) for _ in range(n - 1)]`；位置量先命名再取（见第三节），
  不要写 `data[2 + n - 1 : 2 + n - 1 + n]` 这种人肉算偏移的切片。
  只有出现更好的方案才改用别的读法：整行文本要保留空格换行、
  同一份输入要回头重读或随机访问（先物化成 list 再切片）、
  按行处理的输入（`for line in sys.stdin`）。拿不准时先写 `next()`。
- 热路径之外的一切都尽量压成表达式：读入、分桶、输出用 `next(it)` / 推导式 / `map`，
  不要写"先建数组再 append 再输出"的三段式。

## 二、结构骨架（严格按此顺序）

1. `#!/usr/bin/env python3`
2. 文件头作者信息块（沿用 main.cpp 的写法，用 `#` 注释）：

```python
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47
```

不写模块 docstring（不写“一句话算法 + 关键观察 + 复杂度”那一段）。
3. 标准库 import
4. 模块级常量（哨兵如 `NEG = -10**100`）与类型别名（`type X = ...`），常量全大写
5. 小工具函数：函数名 = 算法概念，带一句话中文 docstring
6. 预处理数据表：推导式构建，一行一个家族，行尾注释标数量
7. `def solve()` 主流程
8. `if __name__ == "__main__": solve()`

## 三、硬性风格

- 参数与返回值必须有类型标注：`-> int`、`-> None`、`weight: list[list[int]]`。
- 复合类型（嵌套容器或含 `|`）在签名/注解里出现 2 次以上，用 `type X = ...`
  起模块级别名，含义一次注释在别名行；`list[int]`、`-> int` 这类简单类型不值得起名，
  直接内联：

```python
type PrevMap = dict[int, int]    # 上一轮/本轮的"值 -> 生产者编码"
type Seqs = list[list[int]]      # 每个人的序列
```
- 状态优先用 `tuple`（可含 `None` 哨兵）当 `dict` 键，靠可哈希性省掉手工进制编码。
- 哨兵值统一：棋盘外/不存在一律用 `None`，不要另造魔法数字（如 `NONE = 8`）。
- 不写 class，不写多文件，不用第三方库，不用 `sys.setrecursionlimit` 掩盖深递归
  （优先改写成迭代）。
- 注释只解释"为什么 / 是什么含义"，不复述代码；含糊的位运算/魔法数字必须给注释。
- 中文注释与中文标点，术语前后一致；用空行分组，不靠注释硬隔断。
- 格式里的量只要出现一次也要命名（`T = next(data)`、`length = next(data)`、
  `max_round = max(by_round)`），命名本身就是对题面格式的注解。
- 只被调用一次的"单行谓词"不抽函数、也不裸塞进 `if`：命名成局部变量再判断
  （`can_start = prev.get(value, person) != person` / `if can_start:`）。
  **概念名留在调用点，参数表消失**；单个动作同理内联，用紧贴注释说明意图。
- 只有当被两个以上调用点复用、或名字本身就是一层概念（如 `advance`）时才写函数。
  单调用点的判断与动作一律内联。
- 允许为了清晰而保留少量展开写法：只要一个表达式已经需要读者脑内模拟两层以上，
  就拆成显式的 `for` + 注释。

## 四、正例（照这个粒度写）

```python
def get_color(pattern: int, row: int) -> int:
    """取一列第 row 位的颜色：0 表示 O，1 表示 X。"""
    return pattern >> row & 1


@cache
def colored_mask(window) -> int:
    """窗口中间列哪几行位于某个三连中：第 row 位为 1 表示 (row, 2) 被染色。"""
    mask = 0
    for cells in LINES:
        if any(window[c] is None for _, c in cells):
            continue                                    # 有格子落在棋盘外
        if len({get_color(window[c], r) for r, c in cells}) == 1:  # 三格同色
            mask |= sum(1 << r for r, c in cells if c == 2)        # 只登记中间列
    return mask
```

## 五、样张（整篇结构照这个写）

冻结快照：2026-09-28，取自 `problems/luogu/P11230/main.py`（P11230 接龙），
类型标注已按第三节规则用 `type` 别名同步（2026-09-29）。
整篇的结构、分层粒度、命名、注释密度照它；局部细节（推导式、位运算、`@cache`）照第四节。

**只锚形式，不锚算法**：不要照搬 `deadline` 扫描、`ANY` 编码、询问分桶这些与本题结构
绑定的做法，遇到结构不同的题要重新过第七节的自检表。

```python
#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-28 16:40
# update_at: 2026-09-28 16:40

import sys
from collections import defaultdict
from collections.abc import Iterator

ANY = 0  # 生产者编码：0 = 至少两个人可以接（第 0 轮的值 1 也记成它）

# 类型别名（Python 3.12+ 的 type 语句），相当于 C++ 的 using / typedef
type PrevMap = dict[int, int]    # 上一轮/本轮的"值 -> 生产者编码"
type Seqs = list[list[int]]      # 每个人的序列


def reachable_values(seq: list[int], person: int, k: int, prev: PrevMap) -> Iterator[int]:
    """依次产出本轮这个人能收尾的值（同一个值的多次出现会重复产出）。

    合法起点 pos 覆盖结尾位置 [pos+1, pos+k-1]。起点从左往右扫，pos+k-1 单调递增，
    所以"覆盖到哪"只需一个 deadline，不必记录整段区间。
    """
    deadline = 0
    for pos, value in enumerate(seq, 1):
        covered = pos <= deadline                      # 更早的合法起点已经覆盖到 pos
        if covered:
            yield value
        can_start = prev.get(value, person) != person  # 上一轮到过 value，且不是只有自己
        if can_start:
            deadline = pos + k - 1                     # 从 pos 出发能延伸到的最右位置


def advance(prev: PrevMap, seqs: Seqs, k: int) -> PrevMap:
    """由第 r-1 轮可达状态推出第 r 轮状态：合并所有人的可达值。"""
    nxt: PrevMap = {}
    for person, seq in enumerate(seqs, 1):
        for value in reachable_values(seq, person, k, prev):
            # 登记生产者：本轮首次出现 value、或唯一生产者还是自己 → person，否则 ANY
            nxt[value] = person if nxt.setdefault(value, person) == person else ANY
    return nxt


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    T = next(data)

    for _ in range(T):
        n, k, q = next(data), next(data), next(data)

        seqs: Seqs = []
        for _ in range(n):
            length = next(data)  # 题面的 l_i
            seqs.append([next(data) for _ in range(length)])

        # 询问按轮数分桶，桶里存 (原始下标, 结尾值)，这样结果能按输入顺序输出。
        by_round = defaultdict(list)
        for i in range(q):
            r, c = next(data), next(data)
            by_round[r].append((i, c))

        ans = [0] * q
        prev: PrevMap = {1: ANY}  # 第 0 轮只有值 1，且没有上一轮的接龙人
        max_round = max(by_round)        # max(dict) 迭代的是 key，最大 key 就是最大轮数
        for rnd in range(1, max_round + 1):
            prev = advance(prev, seqs, k)
            for i, c in by_round[rnd]:
                ans[i] = 1 if c in prev else 0
            if not prev:  # 这一轮一个值都到不了，后面永远都到不了
                break

        out += map(str, ans)

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
```

## 六、反例（不要这样写）

- 写 `build_lines()` 里一堆 `lines = []` / `lines.append(...)`，能用推导式就展开成四行。
- 开 `NONE = 8` 哨兵 + `window_code()` / `decode_window()` 手工进制转换 + 全量建表循环。
- 嵌套三层以上、需要在脑子里展开的推导式（此时应拆成显式循环）。
- 用 `[[next(it) for _ in range(next(it))] for _ in range(n)]` 这类嵌套推导读入，
  逼读者去确认 `next(it)` 的求值顺序。
- 读入用手算偏移的切片（`v = data[2:2 + n - 1]`、`a = data[2 + n - 1:...]`），
  而不是第一节的 `next()` 顺序消费，且说不出比 `next()` 好在哪。
- 把全部逻辑写成 `solve()` 里的三层内联循环，没有函数边界。
- 写 `def can_start(prev, value, person) -> bool: return prev.get(value, person) != person`
  这类只有一个调用点的单行函数，让读者为了一个表达式跳去读参数表。
- 反过来，把带技巧的表达式裸塞进 `if`（如 `if nxt.setdefault(value, person) == person:`），
  让读者在条件里当场做脑内推导；应先用局部变量命名，或紧跟注释。
- 同一个复合类型（如 `dict[tuple[int | None, ...], int]`）在三处签名里原样手写三遍，
  不起 `type` 别名。

## 七、交付前自检表（逐条给行号证据，❌ 必须先改代码）

交付前对着自己的代码核对下表，并在回复里原样输出（✅/❌ + 行号 + 一句话依据）。
只有全部 ✅ 才算完成，不要“边交付边解释”。

| # | 检查项 | ❌ 的样子 |
| --- | --- | --- |
| 1 | 每个函数都能用一句话说清“它回答什么问题” | 有函数说不清职责，只能写“处理一下” |
| 2 | 状态编码的含义只在模块级常量处解释一次 | `ANY` / 哨兵的含义散落各处，靠读者拼 |
| 3 | 热循环里没有裸的复合表达式 | `if nxt.setdefault(v, p) == p:` 直接进 `if` |
| 4 | 只有一个调用点的单行函数数量 = 0 | 定义了 `add_producer(...) -> None` 却只调用一次 |
| 5 | “单人层 / 单轮层 / 主流程”各占一个函数 | 三层 `for` 全塞在 `solve` 里 |
| 6 | 输入里的每个位置量都有名字 | `for _ in range(next(data))`、`range(max(by_round) + 1)` |
| 7 | `solve` 只做读入、调用、输出 | `solve` 里出现算法判断 |
| 8 | 文件头是作者块，且没有模块 docstring | 开头十几行“算法 + 关键观察 + 复杂度” |
| 9 | 能用 dict / set / 生成器的地方不写定长数组或全量预计算 | 手写建表循环；`size=V` 的数组只为查一次 |
| 10 | 状态空了就停 | 明知后面全不可达还跑满 R 轮 |
| 11 | 复合类型出现 ≥2 次的都起了 `type` 别名，含义只写在别名行 | `dict[int, int]` 在签名里手写第 3 遍；含义注释散落 |
| 12 | 读入用 `next()` 顺序消费；改用切片/整行读入时能说出比 `next()` 好在哪 | `v = data[2:2 + n - 1]` 手算偏移，且没有更好的理由 |

## 八、验证与报告

1. 跑题目给出的每一个样例，贴出实际输出。
2. 若目录里有可信的 `main.cpp` / 其它正确实现，做固定种子的随机对拍（覆盖最小 n、
   边界、负数权值），并说明对拍组数与结果。用户明确说“不要对拍”时跳过，并如实说明。
3. 报告：文件路径、核心不变量、时间/空间复杂度、样例与对拍结果、Python 侧 TLE/MLE
   风险、以及“同样的算法在 C++ 里应该怎么落地”。
4. 报告必须附上第七节的自检表（逐条 ✅/❌ + 行号）。
5. 不要声称本地对拍通过等于官方 AC。
