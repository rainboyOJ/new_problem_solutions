# rbook-pi.sh

位置：

```text
scripts/navi/rbook-pi.sh
scripts/navi/rbook-pi-prompt/    # prompt 模板
```

作用：给写题用的 pi 启动器。它做的事只有三件——**预置参数**，**用 fzf 选一个 prompt 模板用 `@` 带进对话**，**把同一个模板目录注册成 `/` 命令**——然后进正常交互 TUI。

专注写题，所以脚本不问模型、不问 thinking：那些进 TUI 后随时改。

## 使用方式

`scripts/navi` 已在本仓库推荐的 `PATH` 里（见 [rbook-shell.md](rbook-shell.md)），所以两种写法都可以：

```bash
scripts/navi/rbook-pi.sh
rbook-pi.sh
```

脚本实际执行的是：

```bash
pi --append-system-prompt "你是一个有用的OJ题目解析辅助助手" \
   --prompt-template <模板目录> \
   @<选中的模板> [你的选项...] [你的消息...]
```

选项和消息原样接在末尾。`@file` 之后的选项照样生效（实测 `@模板 --mode json` 会真的输出 JSON），所以下面这些都不会失效：

```bash
rbook-pi.sh -c                                 # 接着上次会话
rbook-pi.sh -a                                 # 信任项目内文件
rbook-pi.sh --tools read,grep,find,ls          # 只读地审一遍
rbook-pi.sh -p "review problems/luogu/P1001"   # 想一次性跑完就自己传 -p
```

不写消息就直接开工，模板里「没给路径就用当前工作目录」的约定会接上：

```bash
cd problems/luogu/P1001 && rbook-pi.sh         # 选 review-code 模板就是审这道题
rbook-pi.sh "题面说 n 最大 1e5，但我的做法是 O(n^2)"   # 选模板 + 补一句上下文
```

进了 TUI 之后，同一批模板还是 `/` 命令，随时可以再触发一次，不用退出重开：

```text
/find-bug          # 打 / 会列出 /audit-problem、/review-code、/verify-solution 等
```

## 从 navi 打开

cheatsheet（`scripts/navi/problem-tools.cheat`）里有两条入口，见 [navi.md](navi.md)：

| 入口 | 实际命令 | 说明 |
| --- | --- | --- |
| `pi` | `rbook-pi.sh` | 在当前目录打开 |
| `pi-problem` | `cd <problem_dir> && rbook-pi.sh` | 先用 `ptool list-problems` 选题目目录再打开 |

```bash
rbook-navi
rbook-navi --query pi
```

`pi-problem` 靠 `rbook-navi` 在当前 shell 里 `eval` 才能把 `cd` 留在终端，所以不要用 navi 自己的执行方式，也不要把它配成 alias（原因见 [navi.md](navi.md)）。

## 预置的参数

| 参数 | 说明 |
| --- | --- |
| `--append-system-prompt "你是一个有用的OJ题目解析辅助助手"` | **追加**，不替换 pi 默认提示词 |
| `--prompt-template scripts/navi/rbook-pi-prompt` | 把模板目录注册成 `/` 命令，见下节 |

用追加而不是 `--system-prompt`：`--system-prompt` 是替换，会丢掉 pi 默认的行为约定（`Be concise in your responses`、`Show file paths clearly when working with files`、`Use bash for file operations` 等），且 pi 以后新增的约定也拿不到。实测替换成一句话后工具调用仍然可用，所以这不是「能不能用」的问题，而是白白丢掉已有的约定。

**脚本刻意不带的参数**：

| 不带的参数 | 原因 |
| --- | --- |
| `-p` | 要交互 TUI，不是一次性执行 |
| `--model` / `--thinking` | 进 TUI 后用 `ctrl+l` 选模型、`ctrl+p` 循环模型、`shift+tab` 循环 thinking，`ctrl+s` 存成默认，启动时再问一遍是重复劳动 |
| `-ne` | 交互模式下扩展才有意义，`pi-subagents`、`pi-web-access` 等全局包正常加载 |
| `-np` | 会把 `/` 命令一起关掉（虽然显式 `--prompt-template` 路径仍会加载，但没理由关） |

## 在 TUI 里用 `/` 命令

`--prompt-template` 让 `scripts/navi/rbook-pi-prompt/` 里的 10 个模板同时成为 slash 命令，命令名就是去掉 `.md` 的文件名：

```text
/audit-problem  /create-brute  /discover-solutions  /find-bug  /generate-data
/organize-ai-notes  /review-analysis  /review-code  /verify-solution  /write-solution
```

打 `/` 就能搜到，列表里的说明就是模板 frontmatter 的 `description`。

几点行为值得先知道：

- **不走 `.pi/prompts/`**。仓库里没有也不需要 `.pi/prompts`；`--prompt-template` 是显式路径，属于 CLI 参数，**不需要项目信任**（信任只管 `cwd/.pi/**` 的自动发现），所以 `rbook-pi.sh` 在任何目录下行为一致。
- **目录只扫一层**：直接子文件里的 `*.md`，不递归，`.txt` 不认。
- **`/名字` 后面的参数会被丢弃**。模板里没有 `$1` / `${@:-…}` 占位符时，pi 只替换正文、不追加参数——`/find-bug problems/luogu/P1001` 里的路径会被静默丢掉（不报错）。所以「带路径开工」用 fzf 那一遍（`@` 引入 + 把路径当消息），或者在 `/find-bug` 之后单独发一条路径消息。
- **不会和内置命令重名**：内置的是 `/model`、`/settings`、`/reload` 这类，和上表 10 个名字没有冲突。
- 改完模板要 `/reload` 才生效（模板在启动时读一次，所以正常用法——新开一次 `rbook-pi.sh`——不用管）。

验证方式（不花模型调用）：用 pi 自带的 `loadPromptTemplates` 直接加载目录，应当得到 10 个模板、`diagnostics: []`。

## prompt 模板

模板放在 `scripts/navi/rbook-pi-prompt/`：

| 文件 | 作用 |
| --- | --- |
| `audit-problem.md` | 发布前总验收：代码、验证证据、题解正文、仓库格式，**只读不修改** |
| `create-brute.md` | 创建或审查可信的 `brute.cpp`，作为对拍基准 |
| `discover-solutions.md` | 独立推导并检索真正不同的候选解法，**只报告不修改** |
| `find-bug.md` | 定位 WA/TLE/RE 根因，给出可复现反例，**不修改任何文件** |
| `generate-data.md` | 创建或审查 `gen.py`，覆盖小数据对拍与极限压力 |
| `organize-ai-notes.md` | 批量整理 `talking_with_ai/` 对话文档，补元数据 + 改名 |
| `review-analysis.md` | 独立审核 `index.md` 的正确性、完整性与教学质量，**只报告不修改** |
| `review-code.md` | 提交前审查正确性、边界、复杂度、IO 格式，**不修改任何文件** |
| `verify-solution.md` | 主动验证：样例、边界、随机对拍、极限压力，**只报告不修改文件** |
| `write-solution.md` | 按仓库规范写或补完 `index.md` |

选择界面是 fzf：

- 列表一行是 `文件名 — frontmatter 里的 description`，description 由 awk 从模板头部抽出。
- **输入行在顶部**（`--layout=reverse --header-first`），fzf 默认是从屏幕底部排，看起来会像输入框在下面。
- 带边框和标题：`--border --border-label ' 写题模板 '`，匹配计数用 `--info=inline` 跟在输入行后面。
- 右侧预览模板全文（`--preview 'cat {2}'`），选之前就能看清内容。
- 最后一项「（不用模板）」表示不加载任何模板，只带预置参数进 TUI。
- 按 Esc 取消会以 130 退出，不会启动 pi。

完整的 fzf 调用（改视觉参数看这里）：

```bash
fzf --delimiter=$'\t' --with-nth=1 --nth=1 --no-multi \
    --layout=reverse --header-first \
    --border --border-label ' 写题模板 ' --info=inline \
    --header '选 prompt 模板（右侧预览全文，Esc 取消）' \
    --preview 'cat {2}' --preview-window 'right:60%:wrap'
```

模板里只做「路由 + 硬约束」，细节规范全部指向仓库已有的 skill（`oj-problem-analysis-writer`、`oj-problem-format-spec`、`oj-cpp-competitive-style`），所以规范升级时模板不用改。

### 模板格式要求

- **必须是 `.md`**：目录发现只加载 `*.md`；`.txt` 不会被列出，也不会有预览。
- **`description` 是必需的**：它就是 fzf 列表里显示的说明。
- **`$1` / `$@` 只在 `/` 命令那一遍有意义，而模板里没有占位符**：脚本是用 `@` 原样读进消息的，参数替换不会发生；反过来 `/find-bug 某个路径` 里的参数也会被丢弃（见上节）。所以「参数」统一写成

  ```markdown
  题目目录：优先用用户消息里给出的路径；消息里没给就用当前工作目录。
  ```

  让用户把路径写在消息里，或者直接 `cd` 到题目目录再开工。这是刻意选的：模板只写「路由 + 硬约束」，不背 `argument-hint` 语法负担，`@` 与 `/` 两条路的行为因此完全一致。
- 模板内容会连同 YAML frontmatter 一起进入消息（4 行左右），frontmatter 本身也起到「这条消息要干什么」的提示作用，不必删除。

## 退出码

| 退出码 | 含义 |
| --- | --- |
| 0 | pi 正常结束 |
| 130 | 在 `fzf` 里取消（Esc / Ctrl-C），没有启动 pi |
| 1 | 找不到 `pi` 或 `fzf` |
| 其它 | pi 的退出码，会透传 |

## 依赖

- `pi`：必须。
- `fzf`：选模板需要，`--preview` 依赖它才有意义。
- `awk`：从 frontmatter 抽 description。

## 和直接跑 pi 的区别

| | `pi` | `rbook-pi.sh` |
| --- | --- | --- |
| 系统提示词 | pi 默认 | 追加「你是一个有用的OJ题目解析辅助助手」 |
| 写题模板 | 要自己 `@` 或手写 | fzf 选，带预览；10 个模板同时是 `/` 命令 |
| 模型 / thinking | 进 TUI 调 | 进 TUI 调（脚本不问） |
| 扩展 | 全部加载 | 全部加载 |
| 交互 | 交互 | 交互 |

要干写题以外的事、或者需要完全干净的默认环境，直接跑 `pi`。
