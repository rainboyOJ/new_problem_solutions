# rbook-pi.sh

位置：

```text
scripts/navi/rbook-pi.sh
scripts/navi/rbook-pi-prompt/    # prompt 模板
.pi/settings.json                # 把上面的模板目录注册成每个会话的 / 命令
.pi/extensions/oj-prompt.ts      # /oj-prompt：会话内选模板，插入输入框
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

- **两条注册路径都生效**。`--prompt-template <目录>` 是 CLI 参数，显式路径，**不需要项目信任**（信任只管 `cwd/.pi/**` 的自动发现）；仓库根目录的 `.pi/settings.json` 里另有一份 `"prompts": ["../scripts/navi/rbook-pi-prompt"]`（项目设置里的相对路径从 `.pi/` 起算），让**直接跑 `pi` 的会话**也有这 10 个命令，前提是项目已信任（`/trust`）。两条路同时加载不会重复：模板按名字去重，CLI 优先。
- **目录只扫一层**：直接子文件里的 `*.md`，不递归，`.txt` 不认。
- **`/名字` 后面的参数会进模板**。每个模板第一行是 `题目目录：${@:-优先用用户消息里给出的路径；消息里没给就用当前工作目录。}`：给了参数就替换，没给就保留默认句子。所以 `/find-bug problems/luogu/P1001` 现在渲染成 `题目目录：problems/luogu/P1001`，不再是「路径被静默丢掉」；frontmatter 里的 `argument-hint: "[题目目录]"` 会显示在 `/` 补全列表里。
- **`@模板` 这条路不替换占位符**。`rbook-pi.sh` 的 fzf 那一遍是 `@<模板绝对路径>`，属于 CLI 的文件参数，pi 会把整份文件原样放进消息——包括 `${@:-…}` 那行和 frontmatter。默认句子就在 `${@:-…}` 里面，指令仍然完整，只是消息里会留一段 shell 味儿的字面量；想要干净的消息就用 `/名字` 或 `/oj-prompt`。
- **不会和内置命令重名**：内置的是 `/model`、`/settings`、`/reload` 这类，和上表 10 个名字没有冲突。
- 改完模板要 `/reload` 才生效（模板在启动时读一次，所以正常用法——新开一次 `rbook-pi.sh`——不用管）。

验证方式（不花模型调用）：用 pi 自带的 `loadPromptTemplates` 直接加载目录，应当得到 10 个模板、`diagnostics: []`。

## 仓库级配置与 `rpi`

上面一条是「用 `--prompt-template` 把模板带进这一次会话」。如果想让**仓库任意目录**里的 pi 都自带写题环境，用仓库级配置目录加一个 `rpi` 函数：

```bash
cd problems/luogu/P1001 && rpi    # 题目目录里直接开工，写题命令都在
```

它实际就是：

```bash
PI_CODING_AGENT_DIR="<repo>/.pi/agent" pi "$@"
```

（函数定义在 `scripts/navi/rbook-shell.zsh`，见 [rbook-shell.md](rbook-shell.md#rpi)。）

为什么会需要它：pi 的项目配置只认 `cwd/.pi/**`，**不向上查找**。所以在 `problems/<oj>/<id>/` 里跑普通 `pi` 时，`.pi/settings.json` 和 `.pi/extensions/` 都不生效——实测就是 `/oj-prompt` 和 `/find-bug` 都不存在，`/find-bug` 还会被当成普通消息发给模型。

`PI_CODING_AGENT_DIR` 是**整体替换** `~/.pi/agent`，不是合并，所以直接换会把认证、模型表、项目信任和已装的包全丢掉。仓库里因此有两样东西：

| 位置 | 作用 |
| --- | --- |
| `.pi/agent/settings.json` | 仓库级设置：模板目录、扩展、`sessionDir`，以及从全局同步的 `packages` / 模型 / 主题偏好 |
| `.pi/agent/APPEND_SYSTEM.md` | 仓库级追加系统提示词（OJ 助手身份，等价于 `rbook-pi.sh` 的 `--append-system-prompt`） |
| `.pi/agent/{auth.json,models.json,models-store.json,trust.json,npm}` | 指向 `~/.pi/agent` 同名项的符号链接，由 setup 脚本创建，已 gitignore |

`rpi-agent-setup.sh` 负责建这些链接（幂等）：

```bash
scripts/navi/rpi-agent-setup.sh          # 建符号链接
scripts/navi/rpi-agent-setup.sh --sync   # 另外把全局 settings 里的 packages / 模型 / 主题偏好同步进来
```

几个要点：

- **会话是共用的**：`.pi/agent/settings.json` 里 `sessionDir` 指回 `~/.pi/agent/sessions`，所以 `rpi -c` 能接着该目录上一次普通 `pi` 的会话（反之亦然）。
- **认证与模型是共享的**：`auth.json` / `models.json` 是符号链接，在 `rpi` 里 `/login`、改模型写入的仍是全局那一份。
- **全局扩展要显式列出来**：换了配置目录后 `~/.pi/agent/extensions/` 不再自动发现，所以 `.pi/agent/settings.json` 的 `extensions` 里写了它。
- **全局装了新包要同步**：`packages` 是列表，不会自动继承；跑一次 `rpi-agent-setup.sh --sync` 拉齐（装好的包本身在符号链接的 `npm` 里，不会重复下载）。
- **不会重复加载**：`rpi` 在仓库根目录跑时，项目配置 `.pi/settings.json` 也生效，但资源按路径去重，模板和扩展都只出现一次（实测启动头里 `oj-prompt.ts` 只列一次）。

## `/oj-prompt`：会话内选模板再插入

`.pi/extensions/oj-prompt.ts` 注册了一个命令，用来在**已经开着**的会话里挑模板：模糊筛选、右侧预览正文，选完只把内容放进输入框，改完再回车。

```text
/oj-prompt                                  # 打开选择器
/oj-prompt 对拍                              # 打开选择器并预填筛选词（中文描述也能搜）
/oj-prompt find-bug problems/luogu/P1001    # 名字精确匹配，跳过选择器，参数直接渲染进正文
```

选择器按键：

| 按键 | 作用 |
| --- | --- |
| `↑` `↓` | 移动选择（首尾循环） |
| `Enter` | 插入模板正文：去 frontmatter、按 `${@:-…}` 渲染。编辑器为空时整段放入，方便先看再改 |
| `Tab` | 插入 `@scripts/navi/rbook-pi-prompt/<名字>.md` 引用，不展开正文 |
| `PgUp` `PgDn` | 滚动正文预览，`Home` / `End` 跳到首尾 |
| `Esc` `Ctrl+C` | 取消 |

和内置 `/名字` 命令的分工：

| | `/名字`（prompt template） | `/oj-prompt`（本扩展） |
| --- | --- | --- |
| 回车后 | 立即作为消息发送 | 只放进输入框，等你改完再发 |
| 筛选 | 按名字模糊匹配，显示 description | 名字优先、描述兜底，中文描述也能搜（如「对拍」） |
| 正文预览 | 没有 | 右侧显示渲染后的正文 |
| 参数 | `$1` / `${@:-…}` 占位符 | 同一套占位符；`/oj-prompt <名字> <参数>` 直接渲染 |
| 模板来源 | 所有已加载的 prompt 模板（含 pi 包带来的） | 同左，不写死本仓库目录 |

实现要点，便于以后改：

- 模板列表来自 `pi.getCommands()` 里 `source === "prompt"` 的项，路径取 `sourceInfo.path`，所以和 cwd 无关，从 `problems/luogu/P1001` 里跑也能用。
- 插入走 `ctx.ui.setEditorText()`（编辑器为空）或 `ctx.ui.pasteToEditor()`（非空时追加；超过 10 行会折叠成 `[paste #n +N lines]`，发送时自动展开）。
- 占位符替换复刻了 pi 的 `substituteArgs`（该函数没有从包入口导出），语义与 `/名字` 那条路一致。
- 面板是 `ctx.ui.custom()` 的 overlay：自绘的列表 + `Markdown` 预览，颜色取自注入的 `theme`，不依赖 jiti 下的全局主题。
- 选择器需要交互 TUI；JSON / print 模式下只有 `/oj-prompt <名字> <参数>` 这种形式能用（会提示改用这种写法）。

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
- **第一行统一是参数槽**：`题目目录：${@:-优先用用户消息里给出的路径；消息里没给就用当前工作目录。}`。
  `${@:-默认}` 是 bash 风格写法，语义是「有参数就用参数，没有就用默认」，pi 原生支持。这样 `/find-bug problems/luogu/P1001`、`/oj-prompt find-bug problems/luogu/P1001` 都能把路径填进去，不给参数时仍然是原来那句「没给就用当前工作目录」。
  frontmatter 里配一行 `argument-hint: "[题目目录]"`，`/` 补全列表会显示成 `[题目目录] — 说明`。
  注意 `@模板`（CLI 文件参数）不替换占位符，会原样读入；默认句子在 `${@:-…}` 里面，指令仍然完整。
- **frontmatter 的两种去向**：`/名字` 和 `/oj-prompt` 展开时只取正文，frontmatter 不进消息；`@模板` 会把 frontmatter 一起带上（4 行左右）。不影响理解，但两条路行为不同，查问题时别混着推理。

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
| 写题模板 | 仓库里直接有 `/名字` 命令（`.pi/settings.json`），还有 `/oj-prompt` 选择器 | fzf 选，带预览；同样有 `/名字` 和 `/oj-prompt` |
| 模型 / thinking | 进 TUI 调 | 进 TUI 调（脚本不问） |
| 扩展 | 全部加载 | 全部加载 |
| 交互 | 交互 | 交互 |

要干写题以外的事、或者需要完全干净的默认环境，直接跑 `pi`。
