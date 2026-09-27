#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
BRANCH="master"
DEPLOY_HOST="${RBOOK_DEPLOY_HOST:-bohai}"
BASE_DIR="/opt/problems-solution"
PUBLIC_HEALTH_URL="${RBOOK_PUBLIC_HEALTH_URL:-https://rbook2.roj.ac.cn/api/health/content}"
DRY_RUN=false
SAY_SCRIPT="${DEPLOY_SAY_SCRIPT:-$HOME/mybin/say.py}"

die() {
  echo "[deploy] $*" >&2
  exit 1
}

usage() {
  cat <<'EOF'
Usage: ./deploy.sh [--dry-run]

Verify and build the clean master commit locally, push it, transfer an immutable
native release to the VPS over SSH, and activate it through systemd.

Options:
  --dry-run  Show the commit, changed files, and deployment mode only.

Environment variables:
  RBOOK_DEPLOY_HOST       SSH host or alias (default: bohai)
  RBOOK_PUBLIC_HEALTH_URL Public content-health endpoint
  DEPLOY_SAY_IP           LAN IP checked before voice notification
  DEPLOY_SAY_SCRIPT       Path to say.py
EOF
}

while (( $# > 0 )); do
  case "$1" in
    --dry-run)
      DRY_RUN=true
      shift
      ;;
    -h|--help)
      usage
      exit 0
      ;;
    *)
      die "unknown argument: $1"
      ;;
  esac
done

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

  command -v ping >/dev/null 2>&1 || return 0
  ping -c 1 -W 1 "$say_ip" >/dev/null 2>&1 || return 0
  command -v python3 >/dev/null 2>&1 || return 0
  [[ -f "$SAY_SCRIPT" ]] || return 0
  python3 "$SAY_SCRIPT" "$message" >/dev/null 2>&1 || true
}

for command_name in git npm node ssh rsync tar zstd sha256sum curl python3; do
  command -v "$command_name" >/dev/null 2>&1 || die "missing command: $command_name"
done

cd "$ROOT_DIR"
git rev-parse --show-toplevel >/dev/null 2>&1 || die "not a Git repository"
[[ "$(git branch --show-current)" == "$BRANCH" ]] || die "current branch must be $BRANCH"

assert_clean() {
  local status
  status="$(git status --porcelain=v1 --untracked-files=all --ignore-submodules=none)"
  if [[ -n "$status" ]]; then
    printf '%s\n' "$status" >&2
    die "working tree is not clean"
  fi
}

assert_clean
ssh -o BatchMode=yes -o ConnectTimeout=15 "$DEPLOY_HOST" true \
  || die "cannot connect to $DEPLOY_HOST"
git fetch --quiet origin "$BRANCH" || die "cannot fetch origin/$BRANCH"

head_sha="$(git rev-parse HEAD)"
remote_sha="$(git rev-parse "refs/remotes/origin/$BRANCH")"
if ! git merge-base --is-ancestor "$remote_sha" "$head_sha"; then
  die "origin/$BRANCH is ahead of or diverged from local HEAD"
fi

remote_release_sha="$(ssh "$DEPLOY_HOST" "readlink -f '$BASE_DIR/current' 2>/dev/null | sed 's#.*/##'" || true)"
if [[ "$remote_release_sha" == "$head_sha" ]]; then
  echo "[deploy] $head_sha is already deployed"
  exit 0
fi

if [[ "$remote_release_sha" =~ ^[0-9a-f]{40}$ ]] \
  && git cat-file -e "${remote_release_sha}^{commit}" 2>/dev/null \
  && git merge-base --is-ancestor "$remote_release_sha" "$head_sha"; then
  mapfile -t changed_files < <(git diff --name-only "$remote_release_sha...$head_sha")
elif [[ "$head_sha" != "$remote_sha" ]]; then
  mapfile -t changed_files < <(git diff --name-only "$remote_sha...$head_sha")
else
  mapfile -t changed_files < <(git diff-tree --no-commit-id --name-only -r "$head_sha")
fi

content_changed=false
application_changed=false
for file in "${changed_files[@]}"; do
  case "$file" in
    problems/*|problem-sets/*)
      content_changed=true
      ;;
    *)
      application_changed=true
      ;;
  esac
done

if [[ "$content_changed" != true && "$application_changed" != true ]]; then
  echo "[deploy] no deployable changes"
  exit 0
fi

if [[ "$application_changed" == true ]]; then
  deploy_mode=application
else
  deploy_mode=content
fi

echo "[deploy] commit=${head_sha:0:12} mode=$deploy_mode host=$DEPLOY_HOST"
printf '[deploy] changed files: %s\n' "${#changed_files[@]}"

if [[ "$DRY_RUN" == true ]]; then
  printf '%s\n' "${changed_files[@]}"
  echo "[deploy] dry run; no verification, build, push, transfer, or restart was performed"
  exit 0
fi

echo "[deploy] verify $head_sha"
npm run verify:push
assert_clean
[[ "$(git rev-parse HEAD)" == "$head_sha" ]] || die "HEAD changed during verification"

work_dir="$(mktemp -d "${TMPDIR:-/tmp}/problems-solution-native-deploy.XXXXXX")"
trap 'rm -rf "$work_dir"' EXIT

"$ROOT_DIR/scripts/build-native-release.sh" \
  --work-dir "$work_dir" \
  --commit "$head_sha" \
  --mode "$deploy_mode"

# shellcheck disable=SC1090
source "$work_dir/artifacts.env"

assert_clean
[[ "$(git rev-parse HEAD)" == "$head_sha" ]] || die "HEAD changed during build"

if [[ "$head_sha" != "$remote_sha" ]]; then
  echo "[deploy] push ${head_sha:0:12} to origin/$BRANCH"
  git push --no-verify origin "HEAD:$BRANCH"
fi

remote_stage_root="$(ssh "$DEPLOY_HOST" \
  'umask 077; mkdir -p "$HOME/.cache/problems-solution-deploy"; cd "$HOME/.cache/problems-solution-deploy"; pwd')"
[[ "$remote_stage_root" =~ ^/[[:alnum:]_./-]+$ ]] \
  || die "VPS returned an invalid staging path"
incoming_dir="$remote_stage_root/$head_sha"
ssh "$DEPLOY_HOST" "mkdir -p '$incoming_dir'"

dependency_needed=false
if ! ssh "$DEPLOY_HOST" "test -d '$BASE_DIR/dependencies/$LOCK_HASH/$PLATFORM_KEY/node_modules'"; then
  dependency_needed=true
fi

rsync_options=(-a --partial --info=progress2 -e ssh)
rsync "${rsync_options[@]}" \
  "$RELEASE_ARCHIVE" "$RELEASE_ARCHIVE.sha256" \
  "$DEPLOY_HOST:$incoming_dir/"

if [[ "$dependency_needed" == true ]]; then
  rsync "${rsync_options[@]}" \
    "$DEPENDENCY_ARCHIVE" "$DEPENDENCY_ARCHIVE.sha256" \
    "$DEPLOY_HOST:$incoming_dir/"
fi

rsync "${rsync_options[@]}" \
  "$ROOT_DIR/scripts/deploy-native.sh" \
  "$ROOT_DIR/deploy/problems-solution.service" \
  "$DEPLOY_HOST:$incoming_dir/"

deploy_actor="$(id -un | tr -cd '[:alnum:]_.-')"
deploy_source_host="$(hostname | tr -cd '[:alnum:]_.-')"

echo "[deploy] activate ${head_sha:0:12} on $DEPLOY_HOST"
printf -v remote_env \
  'RELEASE_SHA=%q LOCK_HASH=%q PLATFORM_KEY=%q DEPLOY_MODE=%q INCOMING_DIR=%q DEPLOY_ACTOR=%q DEPLOY_SOURCE_HOST=%q PUBLIC_HEALTH_URL=%q' \
  "$head_sha" "$LOCK_HASH" "$PLATFORM_KEY" "$deploy_mode" "$incoming_dir" \
  "$deploy_actor" "$deploy_source_host" "$PUBLIC_HEALTH_URL"
printf -v remote_script '%q' "$incoming_dir/deploy-native.sh"
ssh "$DEPLOY_HOST" \
  "if [ \"\$(id -u)\" -eq 0 ]; then env $remote_env bash $remote_script; else sudo -n env $remote_env bash $remote_script; fi"

echo "[deploy] deployed $head_sha"
announce "主人,题目解析系统 部署完成"
