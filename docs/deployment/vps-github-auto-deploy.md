# VPS + GitHub + Docker 自动部署教程

目标：每次 push 到 GitHub 的 `master` 分支后，GitHub Actions 自动 SSH 到 VPS，拉取最新代码，用 Docker Compose 重新构建并启动 `problems-solution` 服务。

最终链路：

```text
git push origin master
  -> GitHub Actions
  -> SSH 到 VPS
  -> /srv/rbook/scripts/deploy-vps.sh
  -> git reset --hard origin/master
  -> docker compose up -d --build --remove-orphans
  -> ./problems 只读挂载到容器 /app/problems
  -> 容器 npm start
  -> 自动生成 problems.json
```

## 1. 准备本地项目

确认项目里有这些文件：

```text
Dockerfile
docker-compose.yml
.dockerignore
.github/workflows/deploy.yml
scripts/deploy-vps.sh
scripts/generate-problems-json.js
```

本地可以先检查：

```bash
npm test
npm run generate:problems
```

`problems.json` 是运行时生成文件，不提交到 Git。`npm start` 会先执行 `npm run generate:problems`，所以容器每次启动都会基于当前 `problems/` 重新生成。

Docker 镜像不包含 `problems/`，部署时由 `docker-compose.yml` 把 VPS 仓库里的 `./problems` 只读挂载到容器的 `/app/problems`。这样可以避免把较大的题目数据重复打进每个镜像层。

## 2. VPS 安装基础环境

SSH 登录 VPS：

```bash
ssh root@YOUR_VPS_IP
```

安装基础工具：

```bash
apt update
apt install -y git curl nginx ca-certificates
```

安装 Docker Engine 和 Compose 插件。推荐使用 Docker 官方源：

```bash
install -m 0755 -d /etc/apt/keyrings
curl -fsSL https://download.docker.com/linux/ubuntu/gpg -o /etc/apt/keyrings/docker.asc
chmod a+r /etc/apt/keyrings/docker.asc

echo \
  "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.asc] https://download.docker.com/linux/ubuntu \
  $(. /etc/os-release && echo "$VERSION_CODENAME") stable" \
  > /etc/apt/sources.list.d/docker.list

apt update
apt install -y docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin
docker --version
docker compose version
```

如果你的 VPS 不是 Ubuntu，请按 Docker 官方文档选择对应系统的安装方式。

## 3. 创建部署用户和项目目录

建议不要直接用 root 部署。

```bash
adduser --disabled-password --gecos "" rbook
usermod -aG docker rbook
mkdir -p /srv/rbook
chown -R rbook:rbook /srv/rbook
```

`rbook` 加入 `docker` 组后，需要重新登录该用户，组权限才会生效。

## 4. 在 VPS 上准备部署目录

切换到 `rbook` 用户：

```bash
su - rbook
```

确认目录权限：

```bash
mkdir -p /srv/rbook
cd /srv/rbook
```

## 5. Clone 项目到 VPS

仍然用 `rbook` 用户执行：

```bash
git clone https://gh-proxy.com/https://github.com/rainboyOJ/new_problem_solutions.git /srv/rbook
cd /srv/rbook
```

检查远端地址：

```bash
git remote -v
```

应该看到：

```text
origin  https://gh-proxy.com/https://github.com/rainboyOJ/new_problem_solutions.git (fetch)
origin  https://gh-proxy.com/https://github.com/rainboyOJ/new_problem_solutions.git (push)
```

后续 `scripts/deploy-vps.sh` 里的 `git fetch origin "$BRANCH"` 会继续使用这个 HTTPS 远端地址，不需要在 VPS 上额外配置 GitHub SSH deploy key。

注意：这个项目要独立部署，`problems/` 应该是仓库里的真实目录，而不是指向你本地电脑其它项目的软链接。Docker Compose 会把 `/srv/rbook/problems` 挂载到容器的 `/app/problems`。

检查：

```bash
ls -ld problems
test -L problems && echo "problems is symlink" || echo "problems is real directory"
```

如果输出 `problems is symlink`，请先把真实题目目录复制进仓库，再重新提交。

## 6. 首次启动 Docker 服务

在 VPS 上用 `rbook` 用户执行：

```bash
cd /srv/rbook
docker compose up -d --build
docker compose ps
```

检查本机访问：

```bash
curl -fsS http://127.0.0.1:3300/api/problems?limit=1
```

查看日志：

```bash
docker compose logs -f problems-solution
```

确认题目目录已挂载到容器：

```bash
docker compose exec problems-solution ls -ld /app/problems
```

如果你之前按旧教程创建过 systemd 服务，需要先用 root 停掉旧服务，避免它占用 `3000` 端口：

```bash
systemctl disable --now problems-solution
```

## 7. 配置 Nginx 反向代理

退出到 root：

```bash
exit
```

创建 Nginx 配置：

```bash
cat > /etc/nginx/sites-available/problems-solution <<'EOF'
server {
    listen 80;
    server_name YOUR_DOMAIN_OR_IP;

    location / {
        proxy_pass http://127.0.0.1:3300;
        proxy_http_version 1.1;
        proxy_set_header Host $host;
        proxy_set_header X-Real-IP $remote_addr;
        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
        proxy_set_header X-Forwarded-Proto $scheme;
    }
}
EOF

ln -sf /etc/nginx/sites-available/problems-solution /etc/nginx/sites-enabled/problems-solution
nginx -t
systemctl reload nginx
```

浏览器访问：

```text
http://YOUR_DOMAIN_OR_IP/
```

如果你有域名，后续可以用 certbot 配置 HTTPS。

## 8. 给 GitHub Actions 配置 SSH 登录 VPS

在你的本地电脑生成一把专门给 GitHub Actions 登录 VPS 的 key：

```bash
ssh-keygen -t ed25519 -C "github-actions-rbook" -f ./github_actions_rbook -N ""
```

把公钥复制到 VPS 的 `rbook` 用户：

```bash
ssh-copy-id -i ./github_actions_rbook.pub rbook@YOUR_VPS_IP
```

测试：

```bash
ssh -i ./github_actions_rbook rbook@YOUR_VPS_IP "cd /srv/rbook && docker compose ps"
```

然后打开 GitHub 仓库：

```text
Settings -> Secrets and variables -> Actions -> New repository secret
```

添加这些 secrets：

```text
VPS_HOST          = YOUR_VPS_IP
VPS_USER          = rbook
VPS_SSH_KEY       = github_actions_rbook 私钥全文
VPS_APP_DIR       = /srv/rbook
VPS_SERVICE_NAME  = problems-solution
```

`VPS_APP_DIR` 和 `VPS_SERVICE_NAME` 可以不填，workflow 默认使用 `/srv/rbook` 和 `problems-solution`。如果你的 SSH 端口不是 22，需要在 `.github/workflows/deploy.yml` 的 `ssh` 命令里加 `-p YOUR_PORT`，并在 `ssh-keyscan` 里加 `-p YOUR_PORT`。

`VPS_SSH_KEY` 填私钥内容：

```bash
cat ./github_actions_rbook
```

复制完整输出，包括：

```text
-----BEGIN OPENSSH PRIVATE KEY-----
...
-----END OPENSSH PRIVATE KEY-----
```

## 9. 首次手动测试部署脚本

在 VPS 上用 `rbook` 用户执行：

```bash
ssh rbook@YOUR_VPS_IP
cd /srv/rbook
bash scripts/deploy-vps.sh
```

成功后应该看到：

```text
problems-solution ... Up
```

如果这里失败，先修 VPS 本地问题，再测试 GitHub Actions。

## 10. Push 触发自动部署

本地提交并 push：

```bash
git add .
git commit -m "Configure Docker based VPS auto deploy"
git push origin master
```

打开 GitHub 仓库：

```text
Actions -> Deploy to VPS
```

查看 workflow 日志。如果成功，VPS 会自动拉取最新代码、重新构建镜像，并把仓库里的 `problems/` 挂载给新容器使用。宿主机暴露端口是 `127.0.0.1:3300`。

## 11. 日常使用

以后只需要：

```bash
git push origin master
```

VPS 会自动更新。

查看服务状态：

```bash
ssh rbook@YOUR_VPS_IP
cd /srv/rbook
docker compose ps
```

查看日志：

```bash
docker compose logs -f problems-solution
```

手动部署：

```bash
cd /srv/rbook
bash scripts/deploy-vps.sh
```

## 12. 常见问题

### GitHub Actions 报 Permission denied

检查：

- `VPS_SSH_KEY` 是否是私钥，不是 `.pub` 公钥。
- VPS 用户名是否正确。
- 公钥是否已经写入 VPS 用户的 `~/.ssh/authorized_keys`。

### docker compose 权限失败

检查 `rbook` 是否在 `docker` 组：

```bash
id rbook
```

如果没有 `docker`：

```bash
usermod -aG docker rbook
```

然后重新登录 `rbook` 用户。

### problems.json 没更新

`problems.json` 不提交到 Git，会在容器启动时根据挂载的 `/app/problems` 自动生成。检查容器日志：

```bash
cd /srv/rbook
docker compose logs --tail=100 problems-solution
```

也可以临时进入容器检查：

```bash
docker compose exec problems-solution ls -l problems.json
```

### 服务启动失败

查看日志：

```bash
docker compose logs --tail=100 problems-solution
```

常见原因：

- VPS 仓库里的 `problems/` 不存在，或不是一个真实目录。
- Docker build 时 `npm ci --omit=dev` 失败。
- `127.0.0.1:3300` 已被其它进程占用。
- Nginx 反向代理配置里的端口和 Compose 暴露端口不一致。

### 想部署非 master 分支

修改 `.github/workflows/deploy.yml`：

```yaml
on:
  push:
    branches:
      - main
```

或者把 `master` 换成你实际使用的分支名。
