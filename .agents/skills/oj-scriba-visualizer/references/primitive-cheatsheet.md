# Scriba 语法速查

只收录写题解配图会用到的那一档。全量语法在
`~/__git__/scriba/docs/SCRIBA-TEX-REFERENCE.md`；本文件是“背着就能写”的密度。

## 1. 两个环境

```latex
% 静态单帧：一个结论，一次呈现
\begin{diagram}[id="fig-1", label="图注写在这里"]

\end{diagram}

% 多帧：每个 \step 一帧，配一句 \narrate
\begin{animation}[id="anim-1", label="图注"]
\shape{a}{Array}{size=5, data=[3,1,4,1,5]}
\step
\narrate{初始状态。}
\end{animation}
```

- `id` 必须 `[a-z][a-z0-9-]*`，全局唯一；`label` 是图注，可写中文。
- `diagram` 里**禁止** `\step` / `\narrate` / `\cursor` / `\foreach` / `\compute`。
- 两个环境都不能嵌套，也不能放进 `$…$` 或 `lstlisting`。

## 2. 内部结构

```
prelude（第一个 \step 之前）
  \shape{…}{…}{…}     ← 只能在这里声明图形
  \compute{…}         ← Starlark，编译期求值，可用 ${name} 引用
  \apply / \recolor / \annotate   ← 初始状态
  \highlight 不允许出现在 prelude

每个 \step 之后
  \apply / \recolor / \reannotate / \annotate / \cursor
  \narrate{…}         ← 一帧一句，可含 $…$
```

状态**跨帧累积**：只写“这一帧变了什么”。

## 3. 状态色（用颜色承载结论）

| state | 视觉 | 用在 |
| --- | --- | --- |
| `idle` | 浅灰默认 | 无关元素 |
| `current` | 蓝底白字 | 正在处理的那一个 |
| `done` | 绿灰 | 已完成 |
| `good` | 绿框 | 命中、成功、合法 |
| `error` | 红框 | 违规、失败、越界 |
| `path` | 蓝框 | 属于答案路径 |
| `dim` | 淡化 | 不再相关（如“未定”的位） |
| `hidden` | 不渲染 | 预声明，后面帧再显示 |

`highlight`（黄底）只能通过 `\highlight{sel}` 命令，不能写进 `\recolor`。

```latex
\recolor{msk.cell[0]}{state=error}      % 禁用位
\recolor{msk.cell[1]}{state=good}       % 允许位
\recolor{pre.cell[3]}{state=dim}        % 尚未决定的位
```

## 4. 命令

| 命令 | 作用 |
| --- | --- |
| `\shape{名}{Type}{params}` | 声明图形（只在 prelude） |
| `\apply{sel}{value=…}` | 改数据值（`t{row=[…]}` 追加行、`M.cell[i]{value="0"}` 改字符） |
| `\recolor{sel}{state=…}` | 改状态（持久） |
| `\highlight{sel}` | 临时高亮（仅帧内） |
| `\annotate{sel}{label="…", color=error, position=above}` | 挂标签/箭头 |
| `\annotate{sel}{arrow_from="其他sel", label="+3"}` | 带箭头的注释 |
| `\reannotate{sel}{color=…}` | 改已有注释的颜色 |
| `\narrate{…}` | 本帧旁白（动画专用） |
| `\cursor{sel}{at=i}` | 指针/光标 |
| `\foreach{i}{0..4}…\endforeach` | 循环，内部必须用 `${i}` |
| `\compute{x = …}` | 编译期算量，`${x}` 引用 |
| `\invariant{…}` | 跨帧常驻的不变式面板（prelude） |
| `\group` / `\ungroup`、`\link`、`\note` | Graph 分组、跨图形桥、自由批注 |

`color=` 的可选值：`info` `warn` `good` `error` `muted` `path`，或
`color="state:current"`（**必须带引号**）把标签绑到某个状态色。

## 5. 选择器

`shape.family[index]`：`a.cell[3]`、`g.cell[1][2]`、`G.node[A]`、`G.edge[(A,B)]`、
`t.cell[2][1]`、`t.row[1]`、`h.bar[0]`。

| Primitive | 子元素 |
| --- | --- |
| Array / DPTable(1D) | `.cell[i]`、`.range[i:j]`、`.all` |
| Grid / Matrix / DPTable(2D) | `.cell[r][c]`、`.block[r0:r1][c0:c1]`、`.row[i]`、`.col[j]`、`.diag` |
| Graph | `.node[id]`、`.edge[(u,v)]` |
| Tree | `.node[id]`、`.edge[(p,c)]` |
| TraceTable | `.cell[k][j]`、`.row[k]`、`.col[j]`（表头**不可**寻址） |
| Hypercube | `.subset[十进制掩码]` |
| Stack / Queue / Deque | `.item[i]` / `.cell[i]`、`.top`、`.front`、`.back` |
| CodePanel | `.line[i]`，**1-based** |
| Forest | `.node[id]`、`.edge[(p,c)]` |
| Equation | `.term[id]`、`.line[i]` |
| 其他 | `.all` |

`\foreach` 里必须插值：`\recolor{a.cell[${i}]}{state=done}`。裸 `i` 会被当成字面
key，命令**静默丢弃**。

## 6. primitive 参数（以代码为准）

参数名写错是硬错误 E1114，报错会列出合法集合。**不要凭印象写**，直接问代码：

```bash
cd .agents/skills/oj-scriba-visualizer/scripts
python3 params.py            # 全部 21 个
python3 params.py Stack      # 单个
```

当前版本（Scriba 0.39.0）的可接受参数：

| Primitive | 参数 |
| --- | --- |
| `Array` | `size` / `n`、`data` / `values`、`labels`、`sentinels`、`label` |
| `Grid` | `rows`、`cols`、`data`、`label` |
| `DPTable` | `n` / `rows`+`cols`、`data`、`labels`、`label` |
| `Graph` | `nodes`、`edges`、`directed`、`show_weights`、`layout`、`positions`、`layout_seed`/`seed`、`orientation`、`auto_expand`、`split_labels`、`tint_by_edge`、`tint_by_source`、`global_optimize`、`label` |
| `Tree` | `root`、`nodes`、`edges`、`kind`、`links`、`data`、`range_lo`、`range_hi`、`show_sum`、`label` |
| `TraceTable` | `columns`、`label` |
| `Hypercube` | `bits`、`show_bits`、`label` |
| `Bar` | `data`、`max`、`show_values`、`bar_width`/`width`、`label` |
| `Stack` | `items`、`max_visible`、`orientation`、`label` |
| `Queue` / `Deque` | `capacity`、`data`、`label` |
| `VariableWatch` | `names`、`label` |
| `CodePanel` | `lines` / `source`、`label` |
| `Equation` | `tex` 或 `lines`（二选一）、`label` |
| `NumberLine` | `domain=[lo,hi]`、`ticks`、`labels`、`label` |
| `HashMap` | `capacity`、`label` |
| `LinkedList` | `data`、`label` |
| `Forest` | `nodes`、`edges`、`label` |
| `Matrix` / `Heatmap` | `rows`、`cols`、`data`、`row_labels`、`col_labels`、`show_values`、`vmin`、`vmax`、`colorscale`、`cell_size`、`label` |
| `MetricPlot` | `series`、`xrange`、`yrange`、`xlabel`、`ylabel`、`grid`、`width`、`height`、`show_legend`、`show_current_marker` |
| `Plane2D` | `points`、`segments`、`lines`、`circles`、`arcs`、`polygons`、`regions`、`wedges`、`axes`、`grid`、`xrange`、`yrange`、`aspect`、`show_coords`、`width`、`height`（**没有 `label`**） |

几个容易记错的地方：

- `Stack` 是 `items` + `max_visible`，**不是** `capacity`（`capacity` 属于 Queue/Deque/HashMap）。
- `CodePanel` 是 `lines`（行列表）或 `source`，**不是** `code`。
- `NumberLine` 是 `domain=[lo,hi]`，**不是** `lo=`/`hi=`。
- `Plane2D` 不接受 `label`，图注只能写在正文里。

## 7. 常用写法示例

```latex
% Array：位串 / 候选值
\shape{a}{Array}{size=5, data=["0","1","0","0","1"], labels="0..4", label="候选 $x_1$"}

% Grid：二维网格
\shape{g}{Grid}{rows=2, cols=3, data=[[1,0,0],[0,1,0]], label="网格"}

% DPTable：一维用 n；二维用 rows+cols，但 data 仍是**展平**的一维列表
\shape{dp}{DPTable}{n=6, data=[0,0,0,0,0,0], labels="0..5", label="dp 数组"}
\shape{d2}{DPTable}{rows=2, cols=3, data=[0,0,0,0,0,0], label="二维 dp"}

% Graph：有向图用 hierarchical/auto；stable 只适合小的无向图（对有向图会警告并
% 排出横躺/倒置的 DAG）；想完全固定摆放用 positions（坐标自动等比缩放）
\shape{G}{Graph}{nodes=["s","a","b","t"],
  edges=[("s","a",3),("a","t",2)], directed=true,
  show_weights=true, layout="hierarchical", label="样例图"}

% Tree
\shape{T}{Tree}{root=1, nodes=[1,2,3,4,5], edges=[(1,2),(1,3),(2,4),(2,5)], label="树"}

% TraceTable：干跑表（题解里性价比最高的一个）
\shape{t}{TraceTable}{columns=["k", "T", "ok", "M"], label="逐位干跑"}
\apply{t}{row=["2", "011", "yes", "011"]}   % 追加一行，自动成为当前行
\recolor{t.cell[1][2]}{state=good}

% Hypercube：位掩码子集格
\shape{L}{Hypercube}{bits=3, label="子集格"}
\recolor{L.subset[3]}{state=current}        % 下标是十进制掩码

% Bar：高度=数值
\shape{h}{Bar}{data=[3,1,4,1,5], show_values=true, label="柱高"}

% Stack / Queue
\shape{s}{Stack}{items=[], max_visible=6, label="栈"}
\apply{s}{push=3}
\apply{s}{pop=1}

% VariableWatch：变量面板
\shape{vars}{VariableWatch}{names=["lo","hi","mid"], label="变量"}
\apply{vars.var[mid]}{value=4}

% CodePanel：代码行高亮（行号 1-based）
\shape{code}{CodePanel}{lines=["while lo <= hi:", "  mid = (lo+hi)//2"], label="核心循环"}
\recolor{code.line[2]}{state=current}

% Equation：递推展开（\term 让子表达式可单独着色）
\shape{E}{Equation}{lines=["T(n) &= 2\term{rec}{T(n/2)} + cn", "&= cn\log_2 n"], label="展开"}
\recolor{E.term[rec]}{state=current}
```

## 8. 八个必踩的坑

1. **选择器索引要插值**：`${i}`，不是 `i`。裸变量静默丢弃命令。
2. **布尔值小写** `true` / `false`；`True` 会被当成字符串 `"True"`。
3. **CodePanel 行号 1-based**，其他 primitive 全部 0-based。
4. **数学只能 `$…$` / `$$…$$`**；`\(…\)`、`\[…\]` 会原样输出。
5. **中文字形缺失**：Scriba 的度量表只有 Inter 子集（拉丁 + 越南语），中文按
   1em/字估算 → 格子里放中文会溢出。**格子/列头用 ASCII，中文进 `label`。**
6. **`TraceTable` 按最大行数预留高度**（跨帧 `viewBox` 稳定），所以第 1 帧下方
   会留白，不是布局 bug。
7. **有向图别用 `layout="stable"`**：会警告“横躺/倒置的 DAG”，用 `hierarchical`
   或 `auto`。`force`（默认）结果随机感强，`layout_seed` 只保证可复现、不保证好看。
8. **`show_values` 的标签贴着柱顶**：柱高等于 `max` 时值标签会顶到画布上边界，和
   别的 primitive 堆叠时可能被切。给 `max` 留一点余量（如数据最大 5 时写 `max=7`）。

## 9. 排查手段

```bash
# 看得见的错误码：E1050 用了禁止的命令、E1102 未知 primitive、E1105 未知参数、
# E1107 类型不匹配、E1115 越界选择器（软丢弃）、E1159 foreach 变量当索引
cd ~/__git__/scriba
python3 render.py your.tex -o /tmp/x.html          # 报错会指出行号
python3 render.py your.tex --dump-frames | head    # 每帧状态 JSON，查“有没有生效”
python3 render.py your.tex --static -o /tmp/s.html # 胶片模式：所有帧一次看全
```

`--dump-frames` 是判断“命令到底生效了没有”的最快办法：状态没变就是选择器没匹配上。
