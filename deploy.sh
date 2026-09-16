#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
WORKFLOW_FILE=".github/workflows/deploy.yml"
DISCOVERY_TIMEOUT="${DEPLOY_DISCOVERY_TIMEOUT:-60}"
WAIT_TIMEOUT="${DEPLOY_WAIT_TIMEOUT:-1800}"
SAY_SCRIPT="${DEPLOY_SAY_SCRIPT:-$HOME/mybin/say.py}"

die() {
  echo "[deploy] $*" >&2
  exit 1
}

usage() {
  cat <<'EOF'
Usage: ./deploy.sh

Verify the clean master branch locally, push the new commit without running
the local pre-push hook a second time, then wait for its GitHub deployment run.

Environment variables:
  DEPLOY_DISCOVERY_TIMEOUT  Seconds to wait for the push workflow to appear (60)
  DEPLOY_WAIT_TIMEOUT       Seconds to wait for the workflow to finish (1800)
  DEPLOY_SAY_IP             LAN IP to test before announcing (defaults to SAY_WEBHOOK's host)
  DEPLOY_SAY_SCRIPT         Path to say.py ($HOME/mybin/say.py)
EOF
}

say_webhook_host() {
  local webhook host
  webhook="${SAY_WEBHOOK:-http://192.168.9.103:5678/webhook/say}"
  host="${webhook#*://}"
  host="${host%%/*}"
  host="${host##*@}"
  printf '%s\n' "${host%%:*}"
}

announce() {
  local message="$1"
  local say_ip
  say_ip="${DEPLOY_SAY_IP:-$(say_webhook_host)}"

  if ! command -v ping >/dev/null 2>&1; then
    echo "[deploy] 未找到 ping，跳过语音通知" >&2
    return
  fi
  if ! ping -c 1 -W 1 "$say_ip" >/dev/null 2>&1; then
    echo "[deploy] 局域网 IP ${say_ip} 在 1s 内不可达，跳过语音通知" >&2
    return
  fi
  if ! command -v python3 >/dev/null 2>&1 || [[ ! -f "$SAY_SCRIPT" ]]; then
    echo "[deploy] 无法使用 say.py（$SAY_SCRIPT），跳过语音通知" >&2
    return
  fi
  if ! python3 "$SAY_SCRIPT" "$message"; then
    echo "[deploy] 语音通知失败，但不影响部署结果" >&2
  fi
}

if [[ "${1:-}" == "-h" || "${1:-}" == "--help" ]]; then
  usage
  exit 0
fi

cd "$ROOT_DIR"

for command_name in git gh npm timeout; do
  command -v "$command_name" >/dev/null 2>&1 \
    || die "缺少命令: $command_name"
done

git rev-parse --show-toplevel >/dev/null 2>&1 \
  || die "当前目录不是 Git 仓库"

branch="$(git branch --show-current)"
[[ "$branch" == "master" ]] \
  || die "当前分支必须是 master，实际为: ${branch:-detached HEAD}"

assert_clean() {
  local status
  status="$(git status --porcelain=v1 --untracked-files=all --ignore-submodules=none)"
  if [[ -n "$status" ]]; then
    echo "$status" >&2
    die "Git 工作树不是干净状态"
  fi
}

assert_clean

gh auth status --hostname github.com >/dev/null 2>&1 \
  || die "gh 未登录 github.com，先执行 gh auth login"
gh repo view --json nameWithOwner --jq .nameWithOwner >/dev/null \
  || die "gh 无法访问当前 GitHub 仓库"
gh workflow view "$WORKFLOW_FILE" >/dev/null \
  || die "无法访问部署 workflow: $WORKFLOW_FILE"

git fetch --quiet origin master \
  || die "无法 fetch origin/master"
git rev-parse --verify refs/remotes/origin/master >/dev/null 2>&1 \
  || die "远端不存在 origin/master"

head_sha="$(git rev-parse HEAD)"
if ! git merge-base --is-ancestor refs/remotes/origin/master HEAD; then
  die "origin/master 已领先当前 HEAD；请先同步远端后重新部署"
fi
if [[ "$head_sha" == "$(git rev-parse refs/remotes/origin/master)" ]]; then
  message="当前已是最新版本，无需部署"
  echo "[deploy] $message"
  announce "$message"
  exit 0
fi

echo "[deploy] 本地验证 commit $head_sha"
npm run verify:push

assert_clean
[[ "$(git rev-parse HEAD)" == "$head_sha" ]] \
  || die "本地验证改变了 HEAD，部署已中止"

echo "[deploy] 推送 $head_sha 到 origin/master"
git push --no-verify origin HEAD:master

run_id=""
run_url=""
discovery_deadline=$((SECONDS + DISCOVERY_TIMEOUT))
while (( SECONDS < discovery_deadline )); do
  run_record="$(gh run list \
    --workflow "$WORKFLOW_FILE" \
    --commit "$head_sha" \
    --event push \
    --limit 1 \
    --json databaseId,url,status,conclusion \
    --jq 'if length == 0 then "" else .[0] | "\(.databaseId)\t\(.url)\t\(.status)\t\(.conclusion)" end' \
    2>/dev/null || true)"
  if [[ -n "$run_record" ]]; then
    IFS=$'\t' read -r run_id run_url run_status run_conclusion <<< "$run_record"
    break
  fi
  sleep 2
done

[[ -n "$run_id" ]] \
  || die "已推送 $head_sha，但在 ${DISCOVERY_TIMEOUT}s 内没有找到对应 workflow run"

echo "[deploy] 监控 workflow: $run_url"
set +e
timeout --foreground "$WAIT_TIMEOUT" gh run watch "$run_id" --exit-status
watch_status=$?
set -e

summary="$(gh run view "$run_id" \
  --json status,conclusion,url \
  --jq '"status=\(.status) conclusion=\(.conclusion) url=\(.url)"' \
  2>/dev/null || true)"
if [[ -n "$summary" ]]; then
  echo "[deploy] $summary"
fi

if [[ "$watch_status" == "124" ]]; then
  die "等待 workflow 超时（${WAIT_TIMEOUT}s），远端 workflow 未被取消"
fi
if (( watch_status != 0 )); then
  echo "[deploy] workflow 失败；请检查上面的 run URL，修复后提交新 commit 再部署" >&2
  exit "$watch_status"
fi

echo "[deploy] 部署成功: $head_sha"
announce "主人,题目解析系统 部署完成"
