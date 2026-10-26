# AGENTS.md

rbook 题目库：Fastify + Pug + markdown-it 的 OJ 题解网站，数据源是 `problems/**/index.md`。附带 REST API、MCP 网关 `mcp/`、四套关系图前端 `relations{,2,3,4}-graph/`。

## 任务分流

**A. 题目或题解（`problems/**`）** — 走 `oj-problem-workflow`，它按需加载专项 skill，不要手动串一遍。阶段：核实题面 → `oj-solution-planner` → `oj-cpp-style`/`oj-python-style` → `oj-judge-and-stress` → `oj-problem-analysis-writer` + `oj-problem-format-spec` + `rbook-markdown` → `oj-problem-analysis-reviewer`。仅问思路、只写代码、只审稿就用单项 skill。交付前核对正文、代码、图片、样例、原题来源一致。

题目不存在时先拉题面：

```bash
python3 scripts/problem-analysis-tools/fetch_problem.py luogu P1001
python3 scripts/problem-analysis-tools/fetch_problem.py https://atcoder.jp/contests/abs/tasks/practice_1
```

支持 Luogu / AtCoder / Codeforces / 曙梦 / VJudge 系（poj、hdu、openj_bailian 仅标题）。脚本建好目录、`problem.md`（原题面归档，不写题解）、`in1`/`out1` 样例和 `index.md` 骨架；`--dry-run` 只看路径，`--force-statement`/`--force-samples` 才覆盖已有文件。ROJ 题目用 `roj` skill。

**B. 工程代码（`lib/` `routes/` `views/` `mcp/` `relations*-graph/` `scripts/`）** — 改完跑 `npm run verify:push`；API 变更同步 `views/api.pug` 与 `mcp/README.md`。

## 题目目录与 frontmatter

只用目录型结构，不写单文件题解。`index.md` 是唯一电子书内容，另可放 `main.cpp`/`main.py`（主解）、`brute.cpp`/`gen.py`（暴力与数据）、`talking_with_ai/`（公开讨论，图片放 `assets/`）、`problem-analysis-workspace/`（本地推导，git 忽略）。

`index.md` 必填：`oj` `problem_id` `title` `description` `difficulty` `date` `updated` `toc` `tags` `favorite` `favorite_reason` `categories` `showAtRbook` `pre` `common` `recommend` `source`。

- `description` 一句话写核心思路；`showAtRbook` 必须是字符串数组。
- `date` 只在新建时写；**`updated` 必须跟手刷成 `YYYY-MM-DD HH:MM`** —— 目录下任何受跟踪文件变动都要改，`pre-push` 会拦住。
- `talking_with_ai/*.md` 非草稿必须有 `title` `description` `date` `slug`；`slug` 只能小写字母数字连字符且题内唯一。

正文：`[[TOC]]` 目录、`[[oj/problem_id]]` 双链、`@include-code(./main.cpp, cpp)` 引代码。两种语言都有有效实现就都展示，同一算法分语言放同一 `### 代码`，不同算法各自成章；空壳文件不算实现。

Luogu 目录带 `P` 前缀（`problems/luogu/P1001/`），命令和 URL 仍兼容纯数字 `1001`。

## 命令

```bash
npm run preview        # 只渲染最新改的一道题并热刷新 —— 写题解用这个
npm start              # 全量扫描题库起站，127.0.0.1:3000
npm test               # build 四套关系图 + node --test + relations3/4
npm run verify:push    # 推送前完整检查，失败报阶段/命令/退出码
npm run check:content  # 只校验内容 frontmatter

python3 scripts/problem-analysis-tools/check_sample.py problems/luogu/P1001
python3 scripts/problem-analysis-tools/duipai.py --gen problems/luogu/P1001/gen.py \
  --user problems/luogu/P1001/main.cpp --brute problems/luogu/P1001/brute.cpp -n 200
```

MCP：`cd mcp && npm test && npm start`。部署：`./deploy.sh --dry-run` → `./deploy.sh`，要求干净 `master` 且构建机为 `linux-x64`；CI 只跑 PR 验证。

## 造数据与对拍

**造数据优先用 cyaron**（已安装，0.7.0），不要用 `random` 手搓边界，也不靠 `gen_random.py` 的通用模板。`duipai.py --gen` 的约定是「生成器无输入、stdout 就是这组数据」，所以 `gen.py` 这样写：

```python
import sys
from cyaron import IO, Vector, Graph, randint, String

io = IO(input_file=sys.stdout, disable_output=True)   # 数据直接写 stdout
n = randint(1, 1000)
io.input_writeln(n)
io.input_writeln(Vector.random(n, [1, 10**9]))
```

```bash
timeout 1500 python3 scripts/problem-analysis-tools/duipai.py \
  --gen problems/luogu/P1001/gen.py \
  --user problems/luogu/P1001/main.cpp --brute problems/luogu/P1001/brute.cpp \
  -n 200 --timeout 2 --deadline 1200
```

- **对拍主力是 `duipai.py`**：它直接给首个 WA 差异、失败用例落盘，单次运行由 `--timeout`（默认 2s，gen/user/brute 各一次）限定，整轮由 `--deadline` 限定。`roj-local-judge` **做不了随机对拍**（它要 `.in`/`.out` 期望答案），只在定版评测时用。
- cyaron 0.7.0 的 `Vector.random()` 返回 **list**，用 `io.input_writeln(...)` 写；`.println(io)` 是旧版写法，会报 `AttributeError`。
- 树用 `Graph.tree(n, chain=0.3, flower=0.2)`（位置参数是 chain/flower 比例，旧文档里的 `Graph.tree(n, "random")` 会报 `TypeError`），然后 `for e in t.iterate_edges(): io.input_writeln(e.start, e.end)`；链和连通图用 `Graph.chain` / `Graph.connected`，字符串用 `String.random`。
- 边界必须显式覆盖：最小规模、上限、退化结构（链、菊花、无解）。随机对拍不能只跑中等规模。
- 大数据/多组用例的情景用 `sys.argv` 或环境变量参数化，别每题复制一份脚本。

## 执行与资源限制

- **评测一律用 `roj-local-judge`**，不手写评测脚本（细节见 `oj-judge-and-stress` skill）。限制上限 **20s / 512MB**，题目自己的限制更紧就按题目的：

  ```bash
  roj-local-judge-lite problems/luogu/P1001/main.cpp --data-dir ./data \
    --time 20000 --memory 512 --output-format json
  ```

  `--time` 是 CPU 毫秒，`--memory` 是 MiB；栈默认与内存一样大，要单独放宽/收紧才加 `--stack <MiB>`（`0` 表示沿用继承的 rlimit）。
- **Python 按题目时限的 3 倍评测，内存沿用题目上限**。题目 3000ms → Python 用 `--time 9000 --memory 500`。不要拿 C++ 的原始时限判 Python；报告里要标明倍率口径。细节见 `oj-judge-and-stress` skill。
- **除评测外的命令前面都必须加 `timeout`**，禁止跑没有上限的长命令：

  ```bash
  timeout 300 npm run verify:push
  timeout 1500 python3 scripts/problem-analysis-tools/duipai.py ... -n 200 --deadline 1200
  ```

  不要用 `timeout` 包评测：`roj-local-judge` 自己计时，外包一层会把 TLE 变成假的 RE。
- **对拍必须同时给 `--deadline` 和 `--timeout`**，外层 `timeout` 再包一层作最后防线：

  | 参数 | 管什么 | 建议值 |
  | --- | --- | --- |
  | `--timeout` | 单次运行（一次 gen/user/brute） | 2s，题目限制紧就降到 1s |
  | `--deadline` | 整轮对拍总时间，用尽后停手并返回 3 | `n × 3 × --timeout` 量级，`-n 200` 给 600–1200 |
  | 外层 `timeout` | 最后防线 | `--deadline` + 120 |

  退出码：`0` 全过、`1` 发现差异、`2` 编译/参数错、`3` 总时限用尽（不是提交的问题，调小 `-n` 或加预算重跑）。

## Skill（`.agents/skills/`）

`oj-problem-workflow`（总入口）· `oj-problem-format-spec` · `oj-solution-planner` · `oj-cpp-style` `oj-python-style` · `oj-judge-and-stress` · `oj-problem-analysis-writer` `oj-problem-analysis-reviewer` · `oj-problem-relation-writer`（`pre`/`common`/`recommend`）· `oj-sample-visualizer` · `rbook-markdown` · `rbook-ai-note-organizer` · `rbook-problem-batch-launch` · `local-python-learn-oj` `oj-code-interactive-tutor` · `project-pre-push-check` · `agy-delegate`（把 agy 无头模式当外部第二模型做评审/思考，pi 自己复核结论）。

项目级 subagent 只有 `.pi/agents/oj-worker.md`；项目级 pi extension 只有 `.pi/extensions/agy-tab.ts`（`agy_tab` 工具：把 agy 无头调用放进 herdr tab 里跑，过程用户可见）。`tests/skill-contract.test.js` 校验 skill 引用齐全。

## 不要做

- 不格式化/重排整个 `problems/` 树，2 万文件 diff 会失控。
- 不提交 `problem-analysis-workspace/`、`problem-relation-workspace/`、`duipai-failed/`、编译产物。
- 不整体忽略 `*.out`：`data/*.out`、`<PID>_N.out` 是真答案。
- 不 `--no-verify` 强推。不在 skill 里重抄规则，改规则改这里或 `docs/` 原文。
