# ROJ 缺解析 283 道：批量补齐计划

状态：已批准，执行中。日期：2026-10-07。仓库：`pcs2-roj-py`（产出）＋ `new_ROJ`（素材源）。

## 零、已确认参数

| 参数 | 决定 |
| --- | --- |
| 并发数 | **6**（2026-10-07 先提到 10，后按用户要求降回 6；在飞数自然排空到 6 后再补派，不主动 retire） |
| provider 轮换 | `small-sheep` 4 / `heibai` 3 / `ezlook` 3；**qiluyun 已停用**（首轮 10 道挂 7 道） |
| 范围 | **跑完全部 283 道** |
| A / B / D 组模型（249 道） | `qiluyun/global:deepseek-v4.1-flash` → 已改：`small-sheep` / `heibai` / `ezlook` 轮换 |
| C1 / C2 组模型（34 道） | `ezlook/mimo-v2.6-pro` |
| qiluyun 不可用时的回退链 | `small-sheep/deepseek-v4.1-flash` → `ezlook/mimo-v2.6-pro` → `heibai/deepseek-v4.1-flash` |
| 提交 | 由父会话分批统一提交，子代理不 commit |

## 一、缺口判定口径

`new_ROJ/problems/` 是 ROJ 题库本体（1480 道）；`pcs2-roj-py/problems/roj/` 是题解仓库（1197 道）。
两侧对比结果：

| 集合 | 数量 |
| --- | --- |
| ROJ 题库（`new_ROJ/problems`） | 1480 |
| pcs2 已有解析（`problems/roj/*/index.md`） | 1197 |
| **ROJ 有、pcs2 无解析** | **283** |
| pcs2 有、ROJ 无 | 0 |

`problems/roj/` 是 `new_ROJ/problems/` 的严格子集，因此缺口就是下面这 283 个编号。
判定口径是「`pcs2-roj-py/problems/roj/<id>/index.md` 不存在」；283 个目录在 pcs2 侧**完全不存在**
（不是存在但内容空）。

## 二、清单（283 道，按素材完整度分层）

分层依据是「还缺什么才能写出题解」，不是难度：

| 组 | 数量 | 还缺什么 | 编号 |
| --- | --- | --- | --- |
| **A** | 235 | 什么都不缺，直出 | 1125 1222 1226 1353 1414 1418 1419 1420 1421 1529 1682–1819(138) 1839 1992 1993 1994 2009 2070 2110 2123–2128 2141 2142 5004–5074(71) 8012 |
| **B** | 5 | 缺测试数据（有 std） | 1374 1378 1384 1388 1392 |
| **C1** | 28 | 缺参考解 std.cpp | 1425 1452 1519 1565 3058 3064 3065 3066 3072 3077 3079 3120 3133 3161 3165 3166 3190 3212 3218 3519 3547 3622 3640 3641 3650 3662 3678 8008 |
| **C2** | 6 | 缺参考解 + 缺数据 | 3123 3194 8010 20028 20029 20030 |
| **D** | 9 | 题面只在 `content.pdf` | 10005 10012 10013 10014 10015 10016 10017 10018 10019 |

三样「额外工作」的覆盖量：需提取题面 9 道、需搜或自研参考解 35 道、需造测试数据 19 道。
**235 道（83%）无额外工作**，这是本批次能批量推进的前提。

来源分布：信息学奥赛一本通 227 道、牛客 OI 赛前集训营 9 道、其余 43 道来源字段为空
（多为 1682–1819 的自拟/改编题）。连续区间占主体：`1682–1819`（138 道）、`5004–5074`（71 道）。

## 三、每题产出契约

在 `pcs2-roj-py/problems/roj/<id>/` 下新建，**恰好 4 个文件**：

| 文件 | 来源 / 规范 |
| --- | --- |
| `problem.md` | 复制 `new_ROJ/problems/<id>/content.md`（已核实 1183 逐字节相同）；D 组用 pypdf 提取 PDF 后按同样的小节结构写 |
| `main.cpp` | 正式解，遵循 `oj-cpp-competitive-style`；可参考 `new_ROJ/problems/<id>/std.cpp` 但**必须重写**为仓库风格（作者头、全局数组、`typedef long long ll`、中文注释） |
| `main.py` | Python 短解法，遵循 `python-oj-short`（含第七节 12 条自检表） |
| `index.md` | 遵循 `oj-problem-analysis-writer` + `oj-problem-format-spec`；frontmatter 全字段；**代码段两种都展示**（见下） |

`index.md` 的代码段排版沿用本仓库今天刚统一的形式：

```markdown
Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
```

frontmatter 必填：`oj: "roj"`、`problem_id`、`title`、`description`（20–80 字核心解法摘要，非空）、
`difficulty`、`date`/`updated`（新建时相等）、`toc: true`、`tags`、`favorite`/`favorite_reason`、
`categories`、`showAtRbook`、`pre`、`common`、`recommend`、`source`。
`difficulty` 可用 `new_ROJ/problems/<id>/config.json` 的 `level` 字段换算（仅 20 道有），
其余按复杂度估计，不能判断就写 `未知`。

**不放测试数据**：`problems/roj/` 现有 1197 道里 `.in`/`.out` 文件数为 0，本批遵守同一约定。

## 四、素材映射

| 需要的东西 | 从哪来 | 覆盖 |
| --- | --- | --- |
| 题面 | `new_ROJ/problems/<id>/content.md` | 274/283 |
| 题面（PDF） | `new_ROJ/problems/<id>/content.pdf` → `pypdf` | 9/283 |
| 参考解 | `new_ROJ/problems/<id>/std.cpp` | 248/283 |
| 验证数据 | `new_ROJ/problems/<id>/data/problem{1..10}.{in,out}` | 264/283 |
| 标签参考 | `new_ROJ/problems/<id>/tag-report.md` | 部分 |
| 限制 | `new_ROJ/problems/<id>/config.json` 的 `time` / `memory` | 全部 |

PDF 提取已验证可用（`pypdf` 已装，10012 成功提取出题面、样例、数据范围）。

## 五、验证协议（三档，按可用素材递进）

1. **样例实跑**：从 `problem.md` 取出全部样例，实跑 `main.cpp` 与 `main.py`，贴实际输出对照。
   每题必做。
2. **真实数据**（264 道可做）：把 `new_ROJ/problems/<id>/data/` 与 `main.cpp` 复制到临时目录，
   跑 `check_sample.py`。已实测 1183 得到 `PASS=10, FAIL=0`。命令形态：

   ```bash
   rm -rf /tmp/verify-<id> && mkdir -p /tmp/verify-<id>/data
   cp new_ROJ/problems/<id>/data/* /tmp/verify-<id>/data/
   cp problems/roj/<id>/main.cpp /tmp/verify-<id>/
   python3 scripts/problem-analysis-tools/check_sample.py /tmp/verify-<id>
   ```

   `main.py` 用同样的 `.in` 逐点跑，与 `.out` 比对。
3. **对拍**（仅 C1/C2 自研参考解的题）：写 `brute.cpp` + `gen.py`，用 `duipai.py` 固定种子 ≥ 200 组。
   A/B/D 组有可信 std 时不需要。

`check_sample.py` 的目录约定已核实：它认 `data/*.in` + `data/*.out`，且要求 `main.cpp` 同目录，
所以必须走临时目录，不能直接在题解目录跑（题解目录按约定不含数据）。

## 六、派发方案（subagent + qiluyun）

用 `subagent` 工具（即 herdr 子代理机制）派发，**不使用 herdr CLI**：

```js
subagent({
  tasks: [ { agent: "roj-analysis-worker", model: "qiluyun/global:deepseek-v4.1-flash", worktree: false, task: "<单题任务卡>" }, ... ],
})
```

- **角色**：专用项目角色 `roj-analysis-worker`（`~/.pi/agent/agents/roj-analysis-worker.md`）。
  它把 `worktree: false`、`maxSubagentDepth: 0`、四个产出文件、编译/验证命令、回传格式和
  verdict 行全部固化，避免逐次手写任务卡时漏项。

  > **不要用 builtin `worker`。** 它的 `worktree: true` 是默认值，一旦漏传 `worktree: false`
  > 就会给子代理开独立分支，而 `worker` 的系统前言还要求它「push 分支并打开 MR/PR」——
  > 283 道题就是 283 个 MR。2026-10-07 已因此报废 4 个 worker（1419/1420/1421/1529 首派），
  > 已 retire 并清理了对应的 worktree 与 `pi-subagent/worker-*` 分支。

  > **`thinking` 必须用 `high`，不能用 `max`。** 2026-10-07 角色初版写了 `thinking: max`，
  > 子代理在 1682《最小字典序》上单轮推理写了 **101 422 字符**（在句子中间被切断），
  > 触发 `stopReason: "length"` → 插件报 `execution: truncated`，四个文件一个都没写出。
  > 插件侧对应逻辑：`pi-herdr-subagents/src/shared/session.ts:357`，
  > `stopReason === "length"` 就映射成 `status: "truncated"`。
  > 角色已改为 `high`，并加了「推理要收敛」一节（想清楚框架就动手写文件，
  > 不要用 thinking 当草稿纸穷举样例）。
- **模型**：A/B/D 组用 `qiluyun/global:deepseek-v4.1-flash`（`~/.pi/agent/models.json` 的 `qiluyun`
  provider，即 "2元无限日卡"）；C1/C2 组用 `ezlook/mimo-v2.6-pro`。
- **回退链**：`qiluyun` 报 401/403/503、限速、`Connection error.` 或连续超时时，按
  `small-sheep/deepseek-v4.1-flash` → `ezlook/mimo-v2.6-pro` → `heibai/deepseek-v4.1-flash`
  依次换模型重派同一道题。换模型不算 worker 的 `gen` 计数，`note` 里记 `model=...`。
  四个 provider 的可用性都不依赖对方，任一可用即可推进。
- **多 provider 负载均衡 + 各 provider 并发上限（2026-10-07 实测后定）**：

  qiluyun 有硬并发上限。实测 7 路并发时直接报
  `429: {"message":"too many concurrent requests","type":"rate_limit_error"}`；
  限速时它也可能返回连接层错误（`Connection error.`）而不是干净的 429，所以早期那 3 道
  （1353 / 1222 / 1420）实际上也是撞限速。

  每轮 6 道的分配（并发降回 6 之后）：

  | provider | 模型 | 并发配额 | 实测 |
  | --- | --- | --- | --- |
  | `small-sheep` | `deepseek-v4.1-flash` | 2 | 未报 429 |
  | `heibai` | `deepseek-v4.1-flash` | 2 | 压 5–6 路时报 `429 rate_limit_exceeded: Concurrent request limit exceeded` |
  | `ezlook` | `mimo-v2.6-pro` | 2 | 未报 429 |
  | ~~`qiluyun`~~ | ~~`global:deepseek-v4.1-flash`~~ | **0（已停用）** | 首轮 10 道挂了 7 道 |

  **qiluyun 已从轮换中移除。** 它虽然是你指定的首选，但并发上限太低：即使只放 5–7 路，
  仍然是挂多活少（worker-1 / 1222、worker-3 / 1353、worker-4 / 1414、worker-2 / 1421、
  roj-analysis-worker-0 / 1419、roj-analysis-worker-1 / 1420 全部死于 429 或
  `Connection error.`）。只在其它三个 provider 都不可用时才回头试它。

  三者都是同一量级的模型，纯做负载均衡，不影响产出质量。收到 429 就把该题换到下一个
  provider 重派，并把该 provider 的在飞配额降 1。

  > **已实证的三个 provider 限额**：qiluyun 7 路报 429、随后升级为 503 no_healthy_account；
  > heibai 5–6 路报 `429 rate_limit_exceeded: Concurrent request limit exceeded`。
  > 所以每轮派发前先数一下各 provider 的在飞数；并发 6 时每家 2 路，谁也压不到 5 路。
- **角色**：专用角色 `roj-analysis-worker`（见第六节）。绝不用 builtin `worker`。
- **隔离**：`worktree: false` 必须显式给。每题写各自独立的 `problems/roj/<id>/`，本就不冲突；
  若用 worktree 会变成 283 个分支/MR。
- **并发**：**6**。283 道 ÷ 6 ≈ 48 轮。每道预估 15–35 分钟，整批约 15–25 小时。
- **commit**：子代理一律不 commit；由父会话分批统一提交。

### 单题任务卡模板（A 组，235 道）

> **两条实战教训（2026-10-07 首批 10 道观测得到，后续 273 道必须带上）**
>
> 1. **必须显式指定参考布局文件，不要让子代理自己全库 grep。** 首批 worker 在
>    `grep -rl "## 正解" problems/roj/*/index.md` 这类探索上烧掉了 170–200KB 上下文，
>    还没开始写文件就先触发了一次 context 压缩；worker-3 随后以
>    `Connection error` 挂掉。任务卡里直接给两个现成范例（`problems/roj/1213/index.md`、
>    `problems/roj/3108/index.md`）能省掉整段探索。
> 2. **全部路径写绝对路径。** 子代理的 cwd 不一定是目标仓库。

```text
为 ROJ 题目 <id>《<title>》补写题解，产出到 pcs2-roj-py/problems/roj/<id>/。

仓库根：/Users/rainboymac/mycode/RBOOK_series/pcs2-roj-py
素材源（只读）：/Users/rainboymac/mycode/RBOOK_series/new_ROJ/problems/<id>/

先读：AGENTS.md、README 第 6 节、CONTEXT.md，再读这些 skill：
  .agents/skills/oj-problem-analysis-writer/SKILL.md
  .agents/skills/oj-problem-format-spec/SKILL.md
  .agents/skills/oj-cpp-competitive-style/SKILL.md
  .agents/skills/python-oj-short/SKILL.md
  .agents/skills/rbook-markdown/SKILL.md

产出恰好 4 个文件：
1. problem.md  ← 逐字节复制 new_ROJ/problems/<id>/content.md
2. main.cpp    ← 遵循 oj-cpp-competitive-style 重写正式解（参考 std.cpp，不要照抄）
3. main.py     ← 遵循 python-oj-short 写短解法
4. index.md    ← 遵循 oj-problem-analysis-writer + format-spec

index.md 硬性要求：
- frontmatter 全字段，description 非空（20–80 字核心解法摘要），difficulty 用入门/普及-/普及/
  普及+/提高-/提高/提高+/省选-/省选/NOI-/未知，date 与 updated 相等（格式 YYYY-MM-DD HH:MM）
- 含 [[TOC]]、## 形式化题目、解法小节、## 总结
- 代码段两种都展示：
    Python 版：
    @include-code(./main.py, python)
    C++ 版（同一算法）：
    @include-code(./main.cpp, cpp)
- 不要把测试数据复制进题目目录

验证（必做，贴实际输出）：
- 从 problem.md 取全部样例，实跑 main.cpp 与 main.py，逐组对照
- 真实数据：rm -rf /tmp/verify-<id> && mkdir -p /tmp/verify-<id>/data &&
  cp /Users/rainboymac/mycode/RBOOK_series/new_ROJ/problems/<id>/data/* /tmp/verify-<id>/data/ &&
  cp main.cpp /tmp/verify-<id>/ &&
  python3 scripts/problem-analysis-tools/check_sample.py /tmp/verify-<id>
  （main.py 用同样 .in 逐点跑比对）
- 编译必须用 /opt/homebrew/bin/g++-16 -O2（系统 g++ 是 Apple Clang，没有 bits/stdc++.h）

硬约束：不 git commit、不建 MR、不改本题目目录以外的文件、不派发子代理、不跑 herdr 命令。

只回传：文件路径 · 核心不变量 · 时间复杂度/空间复杂度 · 样例结果 · 真实数据结果(几点 PASS/FAIL)
· main.py 自检表(12 条 ✅/❌ + 行号) · 剩余风险

末尾一行 verdict：
{"ok": true, "id": "<id>", "samples": "3/3", "realdata": "10/10", "checks": "12/12"}
```

### C1/C2/D 组任务卡的增量

在 A 组任务卡基础上追加对应段落：

- **B 组（缺数据）**：追加「`new_ROJ/problems/<id>/data/` 为空，需按 `data.py`/`config.json` 的范围
  写 `gen.py` 造 10 组分层数据（边界/小/中/大），用 main.cpp 产 .out，再按第五节验证。」
- **C1 组（缺 std）**：追加「无 std.cpp。先按题面特征句网络搜索原题（博客园/CSDN/洛谷同源题），
  或自行推导参考解写入 `brute.cpp`，用 `duipai.py` 与 main.cpp 对拍 ≥ 200 组。
  参考解来源 URL 必须写进 `brute.cpp` 头注或 `index.md` 的验证记录。」
- **C2 组（缺 std + 缺数据）**：C1 + B 两段都追加。
- **D 组（PDF 题面）**：追加「题面只有 `content.pdf`，用 `python3 -c "from pypdf import PdfReader; ..."`
  提取全文，按 content.md 的小节结构（`### 【题目描述】`/`### 【输入】`/`### 【输出】`/
  `### 【输入样例】`/`### 【输出样例】`）写入 `problem.md`，并把 `config.json` 的 `source` 补成
  `### 【来源】` 段。提取后必须人工核对样例数字（PDF 里的全角冒号 `：` 在样例中应转成半角）。」

## 七、队列与状态机

复用现有 `scripts/problem-analysis-tools/pcs2_queue.py`（JSONL + flock + 原子写，
`pending --claim--> claimed --done--> done`，`claimed --review/fail--> review/failed`，
`reset` 回池）。它的 `init` 目前只扫已存在的 `problems/roj/*/index.md`，本批需要**新增
`init --manifest <file>` 分支**从 `/tmp/roj283-manifest.json` 建队（283 行，字段见下）。

```json
{"pid":"5064","path":"problems/roj/5064","title":"【例1.4】牛吃牧草","cohort":"A",
 "source":"信息学奥赛一本通 · C++编程语言·第一章、C++语言入门","level":"",
 "has_content":true,"has_pdf":false,"has_std":true,"n_data":1,"time_ms":1000,"mem_mb":64,
 "need_extract":false,"need_std":false,"need_data":false,
 "status":"pending","worker":null,"gen":0,"note":""}
```

队列文件用独立路径（`--queue .tmp/roj283-queue.jsonl`），不污染其它批次在用的
`.tmp/pcs2-queue.jsonl`。该改动是纯增量（新增可选参数），对现有调用向后兼容。

## 八、分组与模型分配

| 组 | 数量 | 模型 | 理由 |
| --- | --- | --- | --- |
| A | 235 | `qiluyun/global:deepseek-v4.1-flash` | 素材齐全、有真实数据兜底，机械度最高 |
| B | 5 | `qiluyun/global:deepseek-v4.1-flash` | 只需造数据 |
| D | 9 | `qiluyun/global:deepseek-v4.1-flash` | 只需 PDF 提取；10005 需推导贪心结论，失败则回退链接管 |
| C1 | 28 | `ezlook/mimo-v2.6-pro` | 缺参考解，含 NOIP 提高/CSP-S/省选级（3640 换教室、3650 逛公园、3678 CSP-S 2023 结构体、3190 天天爱跑步） |
| C2 | 6 | `ezlook/mimo-v2.6-pro` | 缺参考解 + 缺数据，双重风险 |

C1/C2 共 34 道是真正的风险集中区，统一交给 `ezlook/mimo-v2.6-pro`（ctx 1M / max 131K）。
执行顺序上放在最后一批，此时 A/B/D 已经跑出稳定的任务卡与验收经验，可以针对性加强。

回退链（任一环节不可用就往下走）：

```
qiluyun/global:deepseek-v4.1-flash      ← A/B/D 首选
  ↓ 401/403/503/限速/连续超时
small-sheep/deepseek-v4.1-flash         ← 与首选同型号，行为最接近
  ↓
ezlook/mimo-v2.6-pro                    ← 同时是 C1/C2 的首选
  ↓
heibai/deepseek-v4.1-flash              ← 黑百中转，ctx 1M / max 384K
```

## 九、执行顺序

1. **建队**：`pcs2_queue.py init --manifest /tmp/roj283-manifest.json --queue .tmp/roj283-queue.jsonl`
2. **先跑 A 组试点 6 道**（选 5064、1682、1683、5006、5021、1125 这类最简单的），
   父会话逐题验收产出契约（4 个文件、frontmatter 全、两种代码都在、真实数据 PASS）。
   判据：6/6 通过才放大；有系统性问题先改任务卡。
3. **A 组全量**：按 6 并发滚动，`claim --count 6 --cohort A` → 派发 → 等回投 → 验收 → `done`/`reset`。
4. **B + D 组**：16 道。
5. **C1 + C2 组**：34 道，换模型或加 `reviewer` 复核。
6. **收尾**：全部写手停止后父会话统一
   `npm run check:content` → 分批 `git add problems/roj/<id> && git commit`（conventional commit + 中文）。
   `updated` 按 frontmatter 规范在新建时就等于 `date`，本批不存在上一批「改了目录没刷时间」的问题。

## 十、已知坑与风险

| 风险 | 说明 | 对策 |
| --- | --- | --- |
| C1/C2 无参考解 | 34 道缺 std.cpp，含省选级难题 | 换更强模型；或要求先搜同源题；对拍兜底 |
| D 组 PDF 全角标点 | 提取出的样例里 `00：00` 是全角冒号，直接当输入会 WA | 任务卡已写明转半角；样例实跑会暴露 |
| 10005 无 std 无数据 | 只有 PDF 题面 + tag-report 的思路线索（贪心结论题） | 单独标注，人工优先处理 |
| **子代理上下文烧光** | 首批 worker 在仓库内全库 grep 找布局范例，170–240KB 上下文后触发压缩（与失败无因果关系，但白烧时间与 token） | 任务卡直接给 `problems/roj/1213/index.md` 与 `3108/index.md` 两个范例，禁止全库探索（新角色 + `make_task_card.py` 已内置） |
| **provider 短时中断** | 10 路并发全压 qiluyun，2026-10-07 一次 91 秒抖动挂掉 3 道（1353 / 1222 / 1420） | 每轮按第四节的分额表分到 4 个 provider；失败题按回退链换 provider 重派 |
| **provider 限速（确证）** | qiluyun 实测 7 路并发直接 `429 too many concurrent requests`；限速时也可能报 `Connection error.`；随后升级为 `503 no_healthy_account`（账号池全挂） | qiluyun 已从轮换移除；收到 429/503 就换 provider |
| **推理撞输出上限（确证，已复发）** | 子代理单轮推理可达 10 万字符，触发 `stopReason: "length"` → 插件报 `execution: truncated`，整轮作废、零产出。已发生两次：1682（101 422 字符）、1707（104 970 字符） | 角色 `thinking` 降为 `high`（**不够，仍会复发**）；角色新增「推理要收敛」小节，关键是**单轮自我中断**：发现同一子问题反复推翻就立即输出工具调用，把推导留到下一轮；任务卡要求第一个动作先复制 problem.md |
| **单轮推理无硬上限可设（已查证）** | 四家 provider 都是 `api: openai-completions`，`thinking` 只映射成 `reasoning_effort`；token 预算制（`thinkingBudgets`）只对 Anthropic / Bedrock / Google 生效，对本批次**无效**。且 `ezlook/mimo-v2.6-pro` 的 `thinkingLevelMap` 为 `None`、`supportsReasoningEffort: false`，**`thinking:` 对它完全无效**（1706 因此冲到 68K 字符） | 无法从配置层设硬上限，只能靠运行机制：看门狗在 45K 字符预警 → 人工 `steer` 拦下 → 万一仍被截断就用 `subagent(action="continue")` 恢复会话（上下文保留，比整道重派便宜得多，1690 已用此法救回） |
| **截断后 resume 并不可靠（已验证）** | 1690 首次 `stop=length`（单轮 99 338 字符），用 `subagent(action="continue")` 恢复会话后**又被截断**（仍 `stop=length`）—— 因为恢复出来的上下文里仍然带着那段接近上限的推理，模型会继续在同一模式里撞墙 | resume 只当低成本试探（试一次，几秒就知道），失败就 `reset` 回 pending、**换一个 provider 全新派发**。1690 已按要求改 heibai 重派 |
| **管道吞掉检查脚本退出码 ⇒ 假通过（已发生一次）** | 父会话验收写成 `check_new_analysis.py --realdata X \| tail -4 && pcs2_queue.py done X`，`&&` 取的是 `tail` 的退出码（恒 0）。1704 的 index.md 有真实错误（`difficulty: "省选-"` 非法、缺 `favorite`/`favorite_reason`）却被静默标成 done | 新增 `accept.py`：把验证与落账绑成原子操作，检查脚本一报错就拒绝落账；并且额外检查输出里必须出现「失败 0」。以后一律用 `python3 scripts/problem-analysis-tools/accept.py <pid...>`，不要再手写 `&&` 链 |
| **任务卡 difficulty 选项表歧义（已发生一次）** | 任务卡把合法档位写成 `入门/普及-/普及/普及+/提高-/提高/提高+/省选-/省选/NOI-/未知`，但合法值是**带斜杠的合并档位**（`"普及+/提高-"` 是一个档位）。子代理把 `"普及+/提高-"` 读成两个选项，于是写出了非法的 `省选-` | 任务卡改为逐个加引号列出，并显式警告「不要写 省选-/NOI-」；同时补上 `favorite: false` 与 `favorite_reason: ""` 必填要求 |
| **在飞子代理静默集体死亡（已发生一次，损失约 1 小时）** | 2026-10-07 16:10–16:14 全部 10 路在飞子代理同时断线：3 路落到 `stopReason: "error"`（`Connection error.`）后停住，7 路停在 `stopReason: "toolUse"` 上等一个永不返回的响应。台账里仍是 `state=working / execution=running`，**看起来完全正常、也不回投完成通知**，父会话空等到用户追问才发现 | 新增 `scripts/problem-analysis-tools/watch_inflight.py`：按**会话文件最后写入时间**判断活性（这是唯一可靠的信号，台账状态和 claimed 集合都查不出死子代理）。每收到一次通知、以及用户每次插话时都跑一遍。阈值 15 分钟，同时预警单轮推理接近 10 万字符的（即将被截断） |
| **provider 声明上限不可信** | 模型声明 maxTokens 131 072–384 000，但实际在 ~35K token（约 10 万字符）就截断 | 不要把 thinking 预算当成硬约束使用；宁可分多轮 |
| 真实数据不是官方评测数据 | `new_ROJ` 的 `data/` 是随仓库数据，可能不等于线上评测点 | 报告里不声称「官方 AC」，只声称「随仓数据一致」 |
| 子代理并发写 | 每题独立目录，无冲突；但 10 个 worker 同时跑 `check_sample.py` 会用 `/tmp` | 临时目录名带 `<id>` 已隔离 |
| **漏传 `worktree: false`** | builtin `worker` 默认开 worktree，其系统前言还要求 push 分支 + 开 MR | 改用 `roj-analysis-worker`（角色内已固化 `worktree: false`）；每次派发后确认 `.pi-subagents/runs/<run>/worktrees/` 不存在 |
| 283 道一次全量提交 | 会让 `updated` 排序失真、diff 巨大 | 分批提交，每批一个 cohort |

## 十二、监控与异常处理（执行中总结）

### 每轮巡检要看的三个信号

```bash
python3 scripts/problem-analysis-tools/reconcile_queue.py   # 非零退出 = 有漏投通知
python3 scripts/problem-analysis-tools/pcs2_queue.py stats --queue .tmp/roj283-queue.jsonl
```

- **漏投通知**：子代理已 `execution: success` 但队列还挂 `claimed` → 立刻验收落账
  （2026-10-07 已发生三次：1353、1685、1418）。
- **静默长尾**：子代理 state 仍是 `working` 但会话文件长时间不更新。阈值取
  **15 分钟无写入**；超过就先 `steer` 一次（要求立刻落文件、放弃额外验证），
  再等 5 分钟仍无响应就 `retire` + 换 provider 重派。
  （2026-10-07：1226 的 worker 在 `/tmp` 反复写暴力验证脚本，17 分钟卡死。）

### 要 steer 的情况

子代理把时间花在**看不见产出的地方**（在 `/tmp` 里反复写验证脚本、做 worst-case 计时、
全库 grep）时，早期 steer 比等它自己收敛便宜。话术就是「立刻落四个文件，真实数据够用即可，
直接给报告 + verdict」。

## 十三、`new_ROJ` 素材源的数据质量问题（执行中发现，需单独反馈）

这批题解过程中通到了素材源自身的缺陷。它们不影响产出（已逐题如实记录在 `index.md`），
但会让任何「按题面写干净解法」的人在这些点上 WA，建议单独修数据。

| 题号 | 问题 | 证据 |
| --- | --- | --- |
| 1421 | 题面写「保证没有负环」，但 `data/problem7.in`、`problem8.in`、`problem10.in` **含负环**；官方 `.out` 是 C++ `long long` 溢出回绕后的结果 | 自写 Bellman-Ford 第 n 轮仍可松弛；精确 Floyd 最小值达 $-8.6\times10^{387}$ |
| 1529 | `std.cpp` **与本题无关**：它输出 `YES`/`NO` + 具体欧拉回路，而题面要求输出 `1`/`0`（属于另一道「输出欧拉回路」的题） | 用 `std.cpp` 跑本题 38 个数据点：`PASS=0, FAIL=38` |
| 1353 | `std.cpp` **在 `stack3` 上算错**：它把栈空时的 `)` 当成左括号加回去，输出 `YES` 而期望 `NO` | 用 `std.cpp` 跑本题 5 个数据点：`PASS=4, FAIL=1`；`stack3.in` = `(1000+(100+(10+1))))*(a-(b-(c-d))))@` |
| 1420 | 题面是**从网络题解三来源重建的**（原站「建设中」），`data/` 由素材源 `data.py` + `std.cpp` 自造，不是官方评测数据 | 子代理报告中说明；`data.py` 自造已在素材源可见 |

已把「`std.cpp` 可能与题面不符，先用它跑一遍 `data/` 确认」写进后续任务卡，
并把这一点加入角色的验证纪律。

## 十四、执行清单

1. ✅ 建 manifest（`.tmp/roj283-manifest.json`，283 行）
2. ☐ 给 `pcs2_queue.py` 加 `init --manifest` 分支
3. ☐ `init --manifest` 建队到 `.tmp/roj283-queue.jsonl`
4. ☐ A 组试点（先 6 道，2026-10-07 按用户要求把在飞数提到 10，追加 4 道），验证 4 文件契约与真实数据 PASS
5. ☐ A 组 235 道全量（10 并发滚动）
6. ☐ B + D 组 14 道
7. ☐ C1 + C2 组 34 道（`ezlook/mimo-v2.6-pro`）
8. ☐ `npm run check:content` + 分批 commit

`updated` 在新建时就等于 `date`，本批不存在「改了目录没刷时间」的问题。
