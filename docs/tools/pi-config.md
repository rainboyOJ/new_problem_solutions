# rbook 的 pi 配置与插件

这个仓库把「用 pi 写题」需要的配置、扩展和插件固化在了 `.pi/` 下，再用一个 `rpi` 启动器让它们在**仓库任意目录**都生效。本文讲**怎么用**：每个文件管什么、装了哪些插件、配置去哪儿改、出问题先查什么。

| 想了解 | 看哪 |
| --- | --- |
| `.pi/` 配置与插件（本文） | `docs/tools/pi-config.md` |
| `rbook-pi.sh` 启动器、10 个写题模板、`/oj-prompt` 细节 | [`rbook-pi.md`](rbook-pi.md) |
| `rpi` 函数、`PATH`、shell 集成 | [`rbook-shell.md`](rbook-shell.md) |
| pi 自身的设置/扩展/包机制 | pi 自带文档：`docs/settings.md`、`docs/extensions.md`、`docs/packages.md` |

实测环境：pi `0.87.1`。

## 五分钟上手

```bash
# 1. 建符号链接（幂等），并从全局 settings 同步 packages / 模型 / 主题偏好
scripts/navi/rpi-agent-setup.sh --sync

# 2. 在仓库任意目录启动（含题目目录）
cd problems/luogu/P1001 && rpi
```

`rpi` 就是 `PI_CODING_AGENT_DIR=<repo>/.pi/agent pi "$@"`（定义在 `scripts/navi/rbook-shell.zsh`）。

启动后立刻可用的东西：

| 试一下 | 是什么 |
| --- | --- |
| `/oj-prompt` | 模糊搜索写题模板，右侧预览，插入输入框再发 |
| `/find-bug`、`/review-code`、`/write-solution` … | 10 个写题模板命令，详见 [rbook-pi.md](rbook-pi.md#在-tui-里用--命令) |
| `/subagents`、`/subagents-doctor` | 子代理面板与自检 |
| `/websearch`、`/curator` | 联网检索与结果策展 |
| `/grill` | 设计评审式追问 |
| `/tool-display` | 工具输出渲染设置 |
| `/copy-message`、`/copy-user` | 复制原始消息文本 |

模型自己会调用的工具：`ask_user`（向你要决策）、`subagent` / `bg_wait`（派子代理）、`web_search` / `fetch_content` / `source_check` / `get_search_content`（联网）、`grill_ask`（追问面板）。

## `.pi/` 目录一览

| 路径 | 入库 | 作用 |
| --- | --- | --- |
| `.pi/settings.json` | ✅ | 项目设置：把写题模板目录注册成 `/` 命令 |
| `.pi/extensions/oj-prompt.ts` | ✅ | `/oj-prompt` 扩展（本仓库自己写的） |
| `.pi/agent/settings.json` | ✅ | `rpi` 用的 agent 级设置：packages、模型、主题、`sessionDir`、`extensions` |
| `.pi/agent/APPEND_SYSTEM.md` | ✅ | 追加系统提示词（OJ 助手身份） |
| `.pi/agent/{auth,models,models-store,trust}.json`、`.pi/agent/npm/` | ❌ | 指向 `~/.pi/agent` 同名项的符号链接，由 setup 脚本创建 |
| `.pi/agent/open-tui.json` | ❌ | `pi-open-tui` 的外观配置（本机偏好） |
| `.pi/agent/extensions/<插件>/config.json` | ❌ | 插件自己写的配置：`pi-tool-display`、`pi-subagents` |
| `.pi/agent/git/github.com/luw2007/pi-grill/` | ❌ | git 型包 `pi-grill` 的检出目录 |

规则很简单：**`settings.json` 和 `APPEND_SYSTEM.md` 入库共享，其余一切都在 `.gitignore` 里**（`.pi/agent/*` 被排除，只放行这两个文件）。所以密钥、机器偏好、插件缓存都留在本机，也不会因为别人 clone 仓库而互相干扰。

## 三个配置目录怎么叠

pi 只会读 `cwd/.pi/**` 作为项目配置，**不向上查找**。所以：

| 配置目录 | 何时生效 | 路径解析起点 |
| --- | --- | --- |
| `<repo>/.pi/`（项目） | cwd 在仓库根目录时（需项目信任） | `.pi/` |
| `<repo>/.pi/agent/`（仓库级 agent） | 用 `rpi` 时（`PI_CODING_AGENT_DIR`） | `rpi` 下就是它自己 |
| `~/.pi/agent/`（全局 agent） | 普通 `pi` | 全局目录 |

在题目目录里 `cd problems/luogu/P1001 && pi`，上面两条仓库配置都不生效——`/oj-prompt`、`/find-bug` 都不存在。`rpi` 通过 `PI_CODING_AGENT_DIR` 把 agent 目录整体换掉来解决这个问题。四条相关行为：

- **是替换，不是合并**：认证、模型表、项目信任、已装的包原本都在 `~/.pi/agent` 里，所以 setup 脚本用符号链接把 `auth.json`、`models.json`、`models-store.json`、`trust.json`、`npm/` 共享进来。在 `rpi` 里 `/login`、切模型，写的仍是全局那一份。
- **全局扩展目录不再自动发现**：所以 `.pi/agent/settings.json` 的 `extensions` 里显式写了 `~/.pi/agent/extensions`。
- **`packages` 不会自动继承**：全局装了新包，要跑一次 `rpi-agent-setup.sh --sync` 才会出现在 `rpi` 里（包本体在符号链接的 `npm/` 里，不会重复下载）。
- **`.pi/agent/` 不是普通项目配置**：pi 的项目配置只认 `.pi/settings.json`、`.pi/extensions/` 这类固定路径，不看 `.pi/agent/`。所以在仓库根跑普通 `pi`：写题模板和 `/oj-prompt` 有（项目级，需信任），但 OJ 助手身份（`.pi/agent/APPEND_SYSTEM.md`）没有；插件走的是全局 `~/.pi/agent/settings.json` 那一份声明。

在仓库根目录用 `rpi` 时，项目配置 `.pi/settings.json` 与仓库级配置同时生效，资源按路径去重，不会重复加载。

## `.pi/settings.json`

只有一件事：把写题模板目录注册成每个会话的 `/` 命令。

```json
{
  "prompts": ["../scripts/navi/rbook-pi-prompt"]
}
```

项目设置里的相对路径**从 `.pi/` 起算**，所以 `../` 就到了仓库根。这条对普通 `pi`（在仓库根、且项目已信任）同样有效。

## `.pi/agent/settings.json`

`rpi` 真正加载的设置文件。

| 键 | 当前值 | 作用 | `--sync` 会覆盖 |
| --- | --- | --- | --- |
| `sessionDir` | `~/.pi/agent/sessions` | 会话历史指回全局，`rpi -c` 能接着普通 `pi` 的会话 | 否 |
| `prompts` | `../../scripts/navi/rbook-pi-prompt` | 写题模板目录（相对 agent 目录） | 否 |
| `extensions` | `../../.pi/extensions`、`~/.pi/agent/extensions` | 本仓库扩展 + 全局扩展 | 否 |
| `packages` | 见下 | 插件包列表，逐条列出，不继承 | ✅ |
| `defaultProvider` / `defaultModel` | `zzzxin` / `deepseek-v4.1-flash` | 默认模型（进 TUI 后随时可换） | ✅ |
| `modelThinkingLevels` | `{"workbuddy/deepseek-v4.1-flash": "off"}` | 按模型覆盖 thinking 档位 | ✅ |
| `theme` | `dark` | 主题名，`/settings` → Theme 改 | ✅ |
| `hideThinkingBlock` | `true` | 折叠思考块 | ✅ |
| `lastChangelogVersion` | `0.87.1` | pi 自己记录已读更新日志的版本 | 否 |

`packages` 里每条的形态有三种（下面只节选四条）：

```json
"packages": [
  "git:github.com/luw2007/pi-grill",
  "npm:@capdiem/pi-ask-user",
  { "source": "git:https://github.com/hasit/pi-community-themes",
    "themes": ["-themes/nord.json", "+themes/gruvbox-dark-hard.json"] },
  "npm:pi-subagents"
]
```

第三条演示了资源过滤：`-path` 精确排除、`+path` 精确包含、`!pattern` 按 glob 排除。所以主题包目前只把 `gruvbox-dark-hard` 放进可选列表，其余主题不加载；当前 `theme: "dark"` 仍是 pi 内置主题，想换成 gruvbox 就用 `/settings` 选。

改这个文件后 `/reload` 生效（`prompts` 这类在启动时读一次，重开 `rpi` 更省事）。

## `.pi/agent/APPEND_SYSTEM.md`

内容是一句话：`你是一个有用的 OJ 题目解析辅助助手。`

它**追加**到 pi 默认系统提示词后面，不替换，所以 `Be concise in your responses`、`Use bash for file operations` 这些默认约定都还在。等价于 `rbook-pi.sh` 的 `--append-system-prompt`，区别只是对 `rpi` 全程生效。注意它是 agent 级文件：普通 `pi` 在仓库根只会去找**项目级**的 `.pi/APPEND_SYSTEM.md`（本仓库没有这个文件），所以 OJ 助手身份只在 `rpi` / `rbook-pi.sh` 下生效。

## `.pi/extensions/oj-prompt.ts`

本仓库自己写的扩展，注册 `/oj-prompt`：模糊筛选模板、右侧预览正文，选完只把内容放进输入框，改完再回车。它从 `pi.getCommands()` 里取所有 `source === "prompt"` 的模板，所以**不写死本仓库目录**，pi 包带来的模板也能选到。

用法、按键、与内置 `/名字` 命令的分工、实现要点见 [rbook-pi.md](rbook-pi.md#oj-prompt会话内选模板再插入)。这里只强调一点：它需要交互 TUI，JSON / print 模式下只有 `/oj-prompt <模板名> <参数>` 这种形式可用。

## 装了哪些插件

`packages` 里的包各自带来命令、工具、skill 或主题：

| 包 | 提供什么 | 入口 |
| --- | --- | --- |
| `pi-subagents` | 子代理编排：`subagent` / `bg_wait` / `contact_supervisor` 工具，`council-mode`、`pi-subagents` skill，`/parallel-review`、`/review-loop`、`/council` 等 prompt | `/subagents`、`/subagents-fleet`、`/subagents-doctor`、`/subagents-guide` |
| `pi-web-access` | 联网：`web_search`、`fetch_content`、`get_search_content`、`source_check` 工具（网页、GitHub 仓库、PDF、YouTube、本地视频） | `/websearch`、`/curator`、`/search`、`/google-account` |
| `pi-grill`（git） | 设计评审式追问：`grill_ask` 工具 + 常驻面板 | `/grill <描述>`、`/grill-panel`，快捷键 `ctrl+alt+g` |
| `@capdiem/pi-ask-user` | `ask_user` 表单工具（grilling / 设计评审类 skill 会把问题渲染成可选项） | 模型调用，无需命令 |
| `pi-tool-display` | 紧凑渲染工具调用、diff 可视化、超长输出截断 | `/tool-display` |
| `pi-open-tui` | TUI 外观：动画头部、Starship 风格 footer、圆角输入框、模型信息 | 自动生效，配置在 `open-tui.json` |
| `pi-copy-message` | 复制原始会话消息（不带换行包裹和 TUI 装饰） | `/copy-message`、`/copy-user` |
| `pi-community-themes`（git） | 主题库 | `/settings` → Theme |

skill（包里的 `skills/` 目录）注册成 `/skill:<名字>`，例如 `/skill:council-mode`、`/skill:pi-subagents`；不写命令直接自然语言描述任务，模型也会自己读对应 skill。

### pi-subagents：派子代理

不需要先定义 agent，可以直接用自然语言：

```text
让 reviewer 审一下这个 diff。
用三个并行 reviewer 分别看正确性、测试和多余的复杂度。
把这件事放到后台跑。
```

命令与自检：

```text
/subagents              # 面板
/subagents-fleet        # 实时查看、接管、停止正在跑的子代理
/subagents-doctor       # 检查配置是否正确
/subagents-models       # 查可用模型
/subagents-guide        # 内置指南（overview / workflows / agents / missions / …）
```

写题时的常用配套 skill：`pi-subagents`（编排）、`council-mode`（多顾问评审）。第一次用建议先跑 `/subagents-doctor`。

### pi-web-access：联网

```text
/websearch react hooks, next.js caching   # 预填多个检索词
/curator                                  # 切换结果策展（summary-review / auto-summary / none）
```

不配任何文件也能用：走环境变量里的 API key，或已登录的 provider（如 Codex 订阅）。要改 provider、代理、超时或放行内网地址，才需要 `<agent dir>/web-search.json`。

一个常见坑：用了 Clash / Surge 这类 TUN + fake-IP 代理时，公网域名会解析到保留网段，被 SSRF 保护拦下，`fetch_content` 会失败。在 `web-search.json` 里放行**最窄**的那段：

```json
{ "ssrf": { "allowRanges": ["198.18.0.0/15"] } }
```

### pi-grill：设计评审式追问

```text
/grill 把 review 命令移植成 pi 扩展
```

会打开常驻面板（`ctrl+alt+g` 收放），模型用 `grill_ask` 批量提问，你再逐条回答，最后收敛成实施计划。追问状态放在系统临时目录（`<tmpdir>/grill/<project>-<cwd 摘要>/`），属于草稿，长期搁置可能要重开一次。

### pi-tool-display：工具输出渲染

```text
/tool-display                 # 打开设置面板
/tool-display show            # 看当前生效配置
/tool-display preset balanced # 预设：opencode / balanced / verbose
```

面板里能改 preset、read/grep 输出档位、diff 布局、bash 折叠行数等；更细的键在它的 `config.json` 里。

### pi-open-tui：外观

仓库里已经有一份 `.pi/agent/open-tui.json`（footer 显示 cwd / git 分支 / tokens / cost，编辑器圆角，思考预览 1 行等）。这是**本机偏好**，不入库；删掉就回到默认外观。

### pi-copy-message：复制消息

```text
/copy-user                    # 复制最近一条用户消息
/copy-message                 # 打开选择器，键盘挑一条
/copy-message 3 --with-meta   # 直接复制第 3 条，带元数据
```

## 插件配置文件速查

`<agent dir>` 指：普通 `pi` 下的 `~/.pi/agent`，`rpi` 下的 `<repo>/.pi/agent`。

| 插件 | 配置文件 | 跟着 `rpi` 换目录？ | 入库 |
| --- | --- | --- | --- |
| pi-subagents | `<agent dir>/extensions/subagent/config.json` | 是 | ❌ |
| pi-web-access | `<agent dir>/web-search.json` | 是 | ❌ |
| pi-open-tui | `<agent dir>/open-tui.json` | 是 | ❌ |
| pi-tool-display | `<agent dir>/extensions/pi-tool-display/config.json` | 是 | ❌ |
| pi-grill | `~/.pi/agent/grill.config.json` | **否**（写死全局路径） | ❌ |
| pi-copy-message / pi-ask-user | 无配置文件 | — | — |

文件都不存在时用内置默认值；大多数情况**先跑命令面板**（`/tool-display`、`/subagents`）就够了，只有改 provider、代理、模型回退这类才需要手写 JSON。密钥一律放在这些被 gitignore 的文件或 `auth.json` 里，**不要写进 `.pi/agent/settings.json`**（它入库）。

## 怎么改、怎么加

| 想做的事 | 做法 |
| --- | --- |
| 改插件行为 | 先试它的命令面板；再改上表的配置文件；改完 `/reload` |
| 装一个新插件 | `pi install npm:<包名>` 装到全局 → `rpi-agent-setup.sh --sync` 同步 `packages` → 重开 `rpi` |
| 加一个写题模板 | 往 `scripts/navi/rbook-pi-prompt/` 放 `.md`（需要 `description`）→ 重开 `rpi` 或 `/reload` |
| 写一个仓库内扩展 | 放 `.pi/extensions/`（随 `rpi` 生效、入库共享）；只给自己用就放 `~/.pi/agent/extensions/`，但要在 `extensions` 里列出 |
| 换主题 | `/settings` → Theme；想启用主题包里其它主题，把对应条目的 `-` 改成 `+` |
| 让子代理默认用别的模型 | `<agent dir>/extensions/subagent/config.json`，键位见 pi-subagents 的 `docs/configuration.md` |

扩展 API、设置项全表、包机制分别见 pi 自带的 `docs/extensions.md`、`docs/settings.md`、`docs/packages.md`（在 pi-coding-agent 安装目录下）。

## 排查清单

| 症状 | 原因 | 处理 |
| --- | --- | --- |
| `rpi` 里没有 `/oj-prompt`、`/find-bug` | `.pi/agent/settings.json` 不存在 | `scripts/navi/rpi-agent-setup.sh` |
| 在题目目录里 `pi` 没有写题命令 | 正常：项目配置不向上查找 | 用 `rpi` |
| 新装的插件在 `rpi` 里看不到 | `packages` 不继承全局 | `rpi-agent-setup.sh --sync`，重开 `rpi` |
| `rpi` 里要重新登录 / 模型表是空的 | 符号链接没了或被覆盖成实体文件 | 重跑 setup 脚本；别手写 `auth.json` |
| 改了 settings / 扩展 / 主题没生效 | 资源在启动时加载 | `/reload`，或重开 `rpi` |
| 插件被 `-ne` / `-np` 关掉了 | 非交互模式或禁用扩展 | 交互模式启动，别加这两个参数，见 [rbook-pi.md](rbook-pi.md#预置的参数) |
| `fetch_content` 报私网 / 保留地址被拦 | TUN + fake-IP 代理 | `web-search.json` 配 `ssrf.allowRanges` |
| `/grill` 提示没有会话 | 面板只在有活动会话时可开 | 先 `/grill <描述>` |
| 启动时有快捷键冲突提示 | 多个扩展抢同一个键 | `/tool-display` 或 pi-grill 配置里换键 |

想确认到底加载了哪些扩展和包：看启动头部的资源列表，或者用 `/reload` 触发一次重新加载并把注意力放在它的报错上。
