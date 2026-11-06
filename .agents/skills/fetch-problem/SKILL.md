---
name: fetch-problem
description: >-
  用 scripts/problem-analysis-tools/fetch_problem.py 把在线 OJ 题目抓成本仓库的题目目录：
  建 problems/<oj>/<id>/ 骨架、写 problem.md 题面、in1/out1 样例、index.md frontmatter。
  需要抓题面、补题面、题目目录不存在、题面缺失、从题号或 URL 建题、拿中文题面、
  给 Codeforces / AtCoder 题找中文题面、VJudge 登录态失败要兜底时使用。
  只负责抓取与建档，不写题解、不做算法分析、不写代码。
---

# 抓取 OJ 题目

`fetch_problem.py` 把在线题目落成本仓库的题目目录。这个 skill 讲**怎么调用它**：选哪个入口、题号怎么写、参数怎么组合、失败怎么兜底。

不负责：写题解正文（`oj-problem-analysis-writer`）、写代码（`oj-cpp-style`）、判题对拍（`oj-judge-and-stress`）、维护 `pre`/`common`/`recommend`（`oj-problem-relation-writer`）。题面本身只是**归档**，不套题解格式、不含 `@include-code`。

完整参数与 VJudge 登录态细节见 [`docs/tools/fetch_problem.md`](../../../docs/tools/fetch_problem.md)。

## 调用方式

agent、脚本、CI 一律用底层脚本，不要用 `fetch_problem` shell 函数（那是给人类用的，会 `cd` 进题目目录，且需要先 `source ~/.zshrc`）：

```bash
python3 scripts/problem-analysis-tools/fetch_problem.py <oj> <problem_id>
python3 scripts/problem-analysis-tools/fetch_problem.py <url>
```

在仓库根目录执行。默认就会建目录、补骨架，不需要 `--init`。

产出结构：

```text
problems/<oj>/<problem_id>/
├── index.md          # frontmatter 骨架，description 留空
├── problem.md        # 原题面归档
├── main.cpp / brute.cpp / gen.py
├── in1 / out1 / in
├── problem-analysis-workspace/
└── talking_with_ai/
```

## 支持矩阵

| 入口 | 题号写法 | 题面语言 | 备注 |
| --- | --- | --- | --- |
| `luogu` | `P1001`、`1001`、`CF1A`、`AT_abc042_b`、`UVA1316` | 中文 | 纯洛谷题 + 收录的 CF/AT/UVA 题 |
| `codeforces` | `2183A`、`165E`、`1373D` | 中文（VJudge） | 需 VJudge 登录态；失败回退原站英文 |
| `atcoder` | `abc042_b`、`abs/practice_1`、`abc042/b` | 中文（VJudge） | 需 VJudge 登录态；**拿不到直接失败，不建骨架** |
| `shumeng` | `CSP201312A` | 中文 | 曙梦 OJ，仅单题 |
| `usaco` | `1515` | 中文 | |
| `kattis` | `hello` | 英文 | |
| `acwing` | 题号 | 中文 | 需 `ACWING_COOKIE` 或 `~/.acwing_cookie` |
| `leetcodecn` | 题号/slug | 中文 | |
| `vjudge` | `POJ-1000` | — | 只抓标题，不抓题面；建成 `problems/vjudge/POJ-1000/` |
| `poj` / `hdu` / `openj_bailian` | `1000` | 英文 | 旧入口只抓标题，不抓题面；建成 `problems/poj/1000/` |

URL 也可以直接用，脚本会自己识别 OJ：

```bash
python3 scripts/problem-analysis-tools/fetch_problem.py https://www.luogu.com.cn/problem/P1001
python3 scripts/problem-analysis-tools/fetch_problem.py https://codeforces.com/contest/2183/problem/A
python3 scripts/problem-analysis-tools/fetch_problem.py https://vjudge.net/problem/CodeForces-2183A
```

## 题号换算：仓库 id → 洛谷 id

洛谷入口的题号前缀是硬性的，写错会静默变成别的题或直接 404：

| 目标 | 洛谷入口写法 | 错误写法 |
| --- | --- | --- |
| Codeforces `1373D` | `luogu CF1373D` | `luogu 1373D` → 被当洛谷 P 题 → `P1373D` → 404 |
| AtCoder `abc042_b` | `luogu AT_abc042_b` | `luogu abc042_b` → 404 |
| 洛谷 `P1001` | `luogu P1001` 或 `luogu 1001` | — |

大小写不敏感：`cf1373D`、`CF1373d`、`at_abc042_b` 都会被归一。

两个已实测的坑：

- `AT_practice_1`（AtCoder 官方 ABS 练习题）**洛谷未收录**，走洛谷必然 404。
- `AT_arc065_a` 在洛谷的标题是 `[ABC049C] 白昼夢`——ABC/ARC 同题，标题会变，别拿标题反推题号。

## 中文题面怎么拿

**Codeforces / AtCoder 优先走 VJudge 入口**，它给的是社区中文翻译：

```bash
python3 scripts/problem-analysis-tools/fetch_problem.py codeforces 2183A
python3 scripts/problem-analysis-tools/fetch_problem.py atcoder abc042_b
```

成功后 `source` 是 `https://vjudge.net/problem/CodeForces-2183A#author=translator:...`，`#author=` 定位到实际选中的那个中文版本。

**VJudge 不可用时用洛谷兜底。** 洛谷对 CF/AT 收录题同时存了多语言版本，脚本按 `zh-CN` 优先取，所以 `luogu CF2183A` 也能拿到中文题面：

```bash
python3 scripts/problem-analysis-tools/fetch_problem.py luogu CF2183A
```

两边差别：

| | VJudge 入口 | 洛谷入口 |
| --- | --- | --- |
| 目录 | `problems/codeforces/2183A/` | `problems/luogu/CF2183A/`（`oj: "luogu"`） |
| `source` | vjudge 链接（带 `#author=`） | 洛谷链接 |
| `difficulty` | 空（脚本不解析 CF rating） | 洛谷难度（`入门`/`提高`） |
| 登录态 | 需要 | 不需要 |
| 翻译质量 | 社区翻译，可能有错 | 洛谷翻译组，通常更稳 |

**保持仓库分类一致**：CF/AT 题就该住在 `problems/codeforces/` 和 `problems/atcoder/`，不要让洛谷入口把它们建成 `problems/luogu/CF2183A/`。需要洛谷的中文题面又要有正确的目录时，见下一节。

## `--print-problem-content`：只要题面，不要副作用

纯只读：不建目录、不写任何文件、不输出 JSON，只把题面 markdown 打到 stdout。用于「已经有目录，只想补/换 `problem.md`」或「不想触发建档」：

```bash
python3 scripts/problem-analysis-tools/fetch_problem.py luogu CF2183A --print-problem-content \
  > problems/codeforces/2183A/problem.md
```

失败时退出码非 0、stdout 保持空、错误写 stderr——所以 `> problem.md` 不会写出空文件或错误页。**父目录必须已存在**，它不会替你 `mkdir`：

```bash
mkdir -p problems/codeforces/2183A
```

不能和 `--json`、`--dry-run` 同时用（脚本直接拒绝）。

典型兜底流程（VJudge 挂了，但要用洛谷中文题面 + codeforces 目录）：

```bash
python3 scripts/problem-analysis-tools/fetch_problem.py codeforces 2183A   # 建目录骨架（哪怕题面失败）
python3 scripts/problem-analysis-tools/fetch_problem.py luogu CF2183A --print-problem-content \
  > problems/codeforces/2183A/problem.md
# 然后手工把 index.md 的 source 改成原站或 vjudge 链接
```

## `source` 写什么

脚本默认值：洛谷题写洛谷链接；CF/AT 走 VJudge 时写 vjudge 链接（带 `#author=`）；CF 回退原站时写 `codeforces.com`。

要改成原站链接就手工编辑 `index.md` 的 frontmatter，`--force-index-meta` 会把 `source` 刷回脚本默认值，所以**先跑抓取再改**：

```yaml
source: https://codeforces.com/contest/2183/problem/A
source: https://atcoder.jp/contests/abc042/tasks/abc042_b
```

## 参数速查

| 参数 | 用途 |
| --- | --- |
| （无） | 建目录 + 写题面 + 样例 + `index.md` 骨架，不覆盖已有手写文件 |
| `--dry-run` | 只打印将创建/写入/跳过的路径，不落盘 |
| `--json` | 结构化输出，agent 用这个判断结果 |
| `--print-problem-content` | 只打题面到 stdout，纯只读 |
| `--force-statement` | 允许覆盖 `problem.md` |
| `--force-samples` | 允许覆盖 `in*` / `out*` |
| `--force-index-meta` | 只更新 frontmatter 的 `title`/`source`/`difficulty`，不碰正文 |
| `--vjudge-login` | 抓前先弹浏览器登录 VJudge 刷新 cookie |
| `--self-test` | 离线 fixture 自测，不碰网络和 `problems/` |

`--json` 的字段：`ok`、`fetched`、`oj`、`problem_id`、`problem_dir`、`title`、`source`、`difficulty`、`created`、`skipped`、`written`、`warnings`。

**agent 判断成功看 `fetched`，不要只看 `ok`。** `ok: true` 只表示没抛异常；`fetched: false` 意味着题面/样例没抓到、只建了空骨架（`warnings` 里会有原因）。

## 覆盖策略

默认不覆盖任何已有文件。手写文件（`index.md`、`main.cpp`、`brute.cpp`、`gen.py`、`problem-analysis-workspace/*.md`）永远不覆盖；抓取产物（`problem.md`、`in1`/`out1`、`in`）也只在不存时写。

要重抓就显式加 `--force-statement` / `--force-samples`，别为了「刷新一下」无脑加，会冲掉人工修过的题面。

## 失败诊断

| 现象 | 原因与处理 |
| --- | --- |
| `HTTP Error 404` + `luogu/AT_xxx` | 洛谷没收录该题，或题号前缀写错（缺 `AT_` / `CF`） |
| `codeforces` 抓成英文 + warnings 提到回退 | VJudge 登录态失效或未收录。跑 `--vjudge-login`，或改用 `luogu CF<id>` 兜底 |
| `atcoder` 直接报错不建目录 | AtCoder 是 `strict_fetch`，VJudge 拿不到就失败。先 `--vjudge-login`，仍失败用 `luogu AT_<task>` |
| `VJudge 登录态` 相关报错 | 凭据在 `~/.config/rbook/vjudge.json`；cookie 失效会自动试 Camoufox，没装就弹浏览器。细节见 `docs/tools/fetch_problem.md` |
| `--print-problem-content` 输出空、退出码非 0 | 看 stderr 的具体原因；这条命令**不会**降级建骨架，失败就是失败 |
| `无法识别 URL 对应的 OJ` | URL 形式不认识，改用 `<oj> <problem_id>` 两段式 |

抓不到题面但 OJ 和题号能确定时，脚本仍会建 skeleton（AtCoder 除外），`fetched: false`。这时可以继续建目录、写代码，但**题面必须先补齐再写题解**——不要拿 `index.md` 里的空 `description` 或猜测的题意往下做。

## 抓完之后

题面到手只是材料阶段。下一步：

- 题目要完整做完 → 进 [`oj-problem-workflow`](../oj-problem-workflow/SKILL.md)，它会按需加载规划、实现、验证、写作、审查各阶段。
- 只要题意/约束核对 → 直接读 `problem.md`，不要顺手改别的文件。
- `index.md` 的 `description` 留给写作阶段，抓取阶段不编造。

ROJ 题目不走这个脚本，用已安装的 `roj` skill。
