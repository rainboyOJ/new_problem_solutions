## 关系图默认入口迁移

2026-10-02 用户确认：`/relations` 默认使用 `relations3-graph/`，`relations-graph/` 与 `relations2-graph/` 不再编译，也不再提供服务。本次变更以 `83101812` 为基线，替代首次实现规划中的三版并存方案。

### 页面与资源

下表说明迁移后的地址行为。

| 地址 | 当前行为 |
| --- | --- |
| `/relations` | 渲染 `relations3.pug`，加载 `relations3-graph` 产物 |
| `/relations?oj=luogu&pid=P2774` | 3D 图直接聚焦指定题目，继续支持 `edges`、`isolated` 参数 |
| `/relations3` 及带参数地址 | HTTP 308 重定向到 `/relations`，原始查询参数完整保留 |
| `/relations2` | HTTP 404，不提供旧版页面 |
| `/relations-graph/*` | HTTP 404，不提供旧版产物 |
| `/relations2-graph/*` | HTTP 404，不提供旧版产物 |
| `/relations3-graph/*` | 正常提供新版 JS、CSS 及动态加载资源 |

全站导航与题目页只保留默认“关系图”入口。新版页面删除 Canvas 入口，WebGL 不可用时仍保留搜索、分组清单和重试按钮。

删除两个旧版宿主模板和 `public/` 下的旧版生成产物。静态服务还显式拒绝旧版目录：在部署目录残留旧文件，或者有人手动生成旧产物时，也不会重新提供旧版服务。对目录名经过 URL 编码的请求同样拒绝，其他静态资源及题目附件正常提供。

### 构建与验证

`npm run build` 仅调用 `build:relations3`，删除 `build:relations` 与 `build:relations2` 脚本。`verify:push` 的构建目标列表只包含 `relations3-graph`，保留新版类型检查、测试、内容索引及真实服务健康检查。

两个旧版源码目录保留供历史查阅，未在本次变更中删除算法源码或清理依赖。它们不参与生产 bundle 构建。旧版布局纯函数的已有测试仍保留，不会生成或提供旧版页面。

集成测试覆盖默认 3D root 和真实资源、题目页参数、旧 3D 地址重定向、旧版 404、内容 guard，以及在旧版目录实际写入文件后依然无法获取的回归场景。浏览器验收改从 `/relations` 进入，并实际从题目页“关系图”链接返回新版，取消对已下线 Canvas 页面的运行依赖。

复验命令如下，在仓库根目录执行；浏览器脚本自行启动临时服务。

```bash
npm run build
npm exec --yes --package=node@22 -- npm run verify:push
R3_HEADFUL=1 R3_SOFTWARE_GPU=0 \
  R3_BROWSER_OUTPUT=.tmp/relations-default-3d-browser \
  npm run check:relations3:browser
```

复验结果：`npm run build` 通过，实际只执行 `build:relations3`；Node `v22.23.3` 下 `verify:push` 六个阶段全部通过，205 项仓库测试与 17 项新版测试通过，共 222 项。内容索引及真实服务健康：2169 道题目、33 个题目单。

Chromium `153.0.8010.36` 有窗口模式、Intel UHD Graphics 620 硬件渲染下，20 个浏览器场景全部通过，无未捕获页面异常。桌面视口 1440 × 1000、DPR 1；手机触摸模拟 390 × 844、DPR 1。验证覆盖默认入口、题目页链接、坐标稳定、缓存恢复、关系筛选、主题、窗口调整、网络失败、WebGL 失败和手机手势。尚未验收实体手机。

原资源检查比较了渲染器已上传的几何体计数，该数字随相机取景变化，不能据此判定泄漏。此次改为对照场景实际分配的几何资源，前后均为 4539，节点对象均为 2169，画布均为 1；GPU 上传数保留为诊断信息。这不是长期进程内存压测。

测得默认网络旋转约 60.3 FPS，全目录约 46.4 FPS，100 邻居压力样例约 60.7 FPS。首入画布就绪约 3.35 秒，布局稳定约 6.20 秒，包含宿主页和外部资源加载；不同设备及网络条件下结果会变化。

原始结果见 [本次浏览器报告](./relations-default-3d-assets/report.json)，默认页面截图见 [桌面聚焦图](./relations-default-3d-assets/desktop-focus.png)和 [手机抽屉图](./relations-default-3d-assets/mobile-focus.png)。首次实现的旧版对照与截图保留在 [历史验收记录](./relations3-graph-validation.md)，用于说明迁移前的行为。本次迁移尚未提交或部署。
