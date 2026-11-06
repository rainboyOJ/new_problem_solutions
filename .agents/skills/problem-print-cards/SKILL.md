---
name: problem-print-cards
description: 把已入库的 OJ 题目排成 A4「复习卡」PDF（typst 渲染，黑白省墨）。用于批量打印题单、生成纸质复习卡片、给题单出一份可存档的卡片册。只由 agent 调用：脚本负责抽题面结构与页面排版，agent 只补少量摘要字段。
---

# 题目复习卡 PDF（typst）

把 `problems/<oj>/<id>/` 里已有的题面与题解，排成每道题一张的纸质卡片，装订成 A4 卡片册。定位是**复习卡**：密排、含做法、不供当场做题。

## 边界

本 skill 负责：采集本地题目材料、按卡片契约排版、渲染 PDF、报告待补字段。

本 skill 不负责：写 `index.md` 题解（`oj-problem-analysis-writer`）、维护题目关系（`oj-problem-relation-writer`）、抓题（缺题面时先调用 `fetch_problem`）。也**不做题面改写之外的算法推导**：`solution.approach` 只允许来自 `index.md` 或 `main.*` 的既有内容。

## 卡片契约（冻结，勿自行更改）

每张卡自上而下四段：

1. **卡头**：题名（黑体，大字）；下一行小字 `难度 · tag · tag`；右侧 `●●○○○` 难度方块（由难度档位换算）＋ `oj#题号`。
2. **卡体**：题意。压缩规则是**结构化保留**——`输入格式`、`输出格式`、`样例`、`数据范围` 原文照搬，只压缩背景与冗长叙述；样例最多 3 组，超出部分印「另 N 组见索引表链接」。
3. **卡尾**：`做法`（1–2 句）、`复杂度`、`考察`（1–3 个考察点）、`典型坑`（1 句）。缺材料的字段印「待补」，不编造。
4. **卡底**：`☐ 未做 ☐ 会做 ☐ 需回看　用时 ___ 分　得分 ___　日期 ___`。

其他固定项：

- 前置：**封面页**（批次名/日期/题数/来源/待补统计）＋ **题目索引页**（题号、难度、完整 URL、待补数）。卡底只印 `roj#10001` 这类短标识，回连屏幕靠索引页。
- 版面：短题 **一面 2 张**（各 131 mm 高，剩余空间留白，不画任何横线或标签）；长题 **一面 1 张**，允许跨页。分档由脚本按估算行数自动决定，可用 `layout_locked` 人工钉死。
- 视觉：纯灰度 + 0.7 pt 细线框；不使用颜色，黑白/省墨打印不丢信息。

字段与取值来源见 `references/card-spec.md`。

## 工作流

### 1. 采集（脚本自动）

```bash
python3 .agents/skills/problem-print-cards/build.py collect \
  --batch prints/<批次名> \
  --name "CSP-J 400 分题单" \
  --source "problem-sets/csp-j-400.md" \
  roj/10000 roj/1000 luogu/b2002 https://www.luogu.com.cn/problem/P1001
```

- 目标可混写 `oj/id`、`oj id`、题目 URL。
- 默认**增量**：只更新本次传入的题，批次里其他卡原样保留（顺序按本次目标在前）；要重建整个批次就加 `--replace`。
- 脚本读 `problems/<oj>/<id>/problem.md`（结构化拆题面）和 `index.md`（frontmatter + `正解/思路/复杂度`）。
- 题面优先级：`problem.md` 正文 → `index.md` 的「题目描述」 → 题面截图（最多 2 张）。用了第二/第三档时卡体会印一行来源说明。
- 产物 `prints/<批次名>/cards.json`。

题号来自 `problem-sets/*.md` 时先读该文件取 `[[problem: oj,id]]` 列表；题目未入库则先 `fetch_problem`，仍失败就**跳过并在回话里列出**，不要生成空卡。

### 2. 补写摘要字段（agent 负责，逐题）

只改 `cards.json`，不要改 `cards.typ`（每次 render 重新生成）。

| 字段 | 要求 | 材料不足时 |
| --- | --- | --- |
| `body.summary` | 压缩后的题意：删背景与故事，保留全部约束语义；≤ 300 字 | 留空 → 脚本用原始描述截断 |
| `solution.approach` | 1–2 句「怎么想到 + 怎么做」 | 留空 → 卡上印「待补」 |
| `solution.approach_note` | 从 `main.cpp`/`main.py` 反推时填 `据参考代码反推` | 留空 |
| `solution.complexity` | `时间 O(n) / 空间 O(n)` | 留空则不印该行 |
| `solution.points` | 考察点 1–3 个，取自 `tags` 或题解 | 留空 → 卡上不印考察行 |
| `solution.pitfall` | 典型坑 1 句 | 留空 → 印「待补」 |

纪律：**宁可缺，不可错。** `tags` 非空率只有约 74%，`index.md` 有 `正解/思路` 的约 900/3700。没有材料就留空；读代码归纳做法时必须打 `据参考代码反推` 标记；绝不为了填满卡片而复述题面、编造复杂度或发明不存在的坑。

### 3. 渲染（脚本自动）

```bash
python3 .agents/skills/problem-print-cards/build.py render --batch prints/<批次名>
# 只生成 cards.typ 不编译：--no-compile
```

脚本生成 `cards.typ` → `layout.json`（每题 compact/full）→ `typst compile` 出 `<批次名>.pdf`。

### 4. 自检（交付前必做）

1. 看 render 回话里的待补清单：每一条要么补上，要么在回话里说明为什么留空。
2. 打开 `layout.json`：`full` 的题是否符合预期（题面长/样例多）；短题被排成 `full` 通常是估算误判。
3. 抽 1–2 页验证渲染，不要只看编译成功：

```bash
cd prints/<批次名> && typst compile --root ../.. --format png --ppi 95 cards.typ "pg{p}.png"
```

重点看：样例框里中文是否可见（等宽字体需 CJK 回退）、数学公式是否成了乱码标识符、图片题是否只剩一张缩略图、卡片是否有一整页空白。

4. 报路径与体积给用户；`prints/` 已在 `.gitignore` 中，不要提交 PDF。

## 常见故障

| 现象 | 原因与处理 |
| --- | --- |
| `unknown variable: xxx`（数学） | 题解里写了裸多字母标识符或罕见 LaTeX 命令；在 `build.py` 的 `MATH_MAP` / `MATH_IDENTS` 补条目 |
| `cannot access fields on user-defined functions` | 模板里自定义函数名撞了 typst 内置符号（曾有 `dots`，导致 `$a dots.h b$` 变成字段访问）。模板函数统一加前缀，如 `diff-mark` |
| `expected colon` 且指向行尾 | 正文行以字面反斜杠结尾；`fix_trailing_backslash()` 会改写，新增文本处理路径时别忘了套用 |
| 样例框里中文消失 | `conf.mono` 缺 CJK 回退字体（现为 `("Menlo", "DejaVu Sans Mono", "Songti SC", "PingFang SC")`） |
| 巨长样例把卡撑爆 | `SAMPLE_MAX_LINES` / `SAMPLE_MAX_CHARS` 截断生效但样例本身不规范（例如 Note 被当成样例）；优先让 agent 写 `body.summary` |
| 某题整页空白或跨页断裂 | 该题被误判为 `full` 且题面只有几行；人工在 `cards.json` 里设 `layout: compact` + `layout_locked: true` 后重渲染 |
| 题目目录不存在 | 未入库；先 `fetch_problem <oj> <id>`，或从目标列表移除并记录 |
| 版本 0.15 的 typst 语法变化 | 模板已适配：`set raw` 不再接受 `font`（改用 `show raw: set text(...)`）、`#show: f.with(...)` 不可用于整篇包装（改用闭包 `#show: it => doc(name, it)`） |

## 产物

```text
prints/<批次名>/
├── cards.json     # 唯一可编辑源（agent 字段 + 自动抽取字段）
├── cards.typ      # 生成物，勿手改
├── layout.json    # 每题 compact/full 判定结果
└── <批次名>.pdf   # 打印用
```

模板与脚本同目录：`template.typ`（版面）、`build.py`（采集/排版/编译）。
