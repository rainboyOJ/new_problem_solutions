#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
BRANCH="master"
DEPLOY_HOST="${RBOOK_DEPLOY_HOST:-bohai}"
BASE_DIR="/opt/problems-solution"
# The release is built natively for the VPS, so the build host has to be the same
# platform: scripts/build-native-release.sh derives PLATFORM_KEY/NODE_ABI from the
# local node, and scripts/deploy-native.sh on the VPS refuses to install artifacts
# whose platform differs from its own. Keep this equal to the VPS platform.
REQUIRED_PLATFORM="linux-x64"
PUBLIC_HEALTH_URL="${RBOOK_PUBLIC_HEALTH_URL:-https://pcs2.roj.ac.cn/api/health/content}"
DRY_RUN=false
SAY_SCRIPT="${DEPLOY_SAY_SCRIPT:-$HOME/mybin/say.py}"

# Inside Herdr, mark the workspace and the tab this deploy runs in:
#   workspace -> a metadata token (rendered in the sidebar by $deploy in config.toml)
#   tab       -> a prefix on the tab label (Herdr has no per-tab styling or status render)
# Cleared on a successful finish; deliberately left behind on failure, so the 🚀 on the tab
# stays as the clue that this deploy went wrong. Set RBOOK_DEPLOY_EMOJI= to disable it all.
DEPLOY_EMOJI="${RBOOK_DEPLOY_EMOJI-🚀}"
DEPLOY_TOKEN_NAME="deploy"
DEPLOY_TOKEN_SOURCE="rbook-deploy"
DEPLOY_TAB_LABEL_ORIGINAL=""

die() {
  echo "[deploy] $*" >&2
  if [[ -n "$DEPLOY_TAB_LABEL_ORIGINAL" ]]; then
    echo "[deploy] $DEPLOY_EMOJI kept on $HERDR_TAB_ID / $HERDR_WORKSPACE_ID: the deploy did not finish" >&2
  fi
  exit 1
}

usage() {
  cat <<'EOF'
Usage: ./deploy.sh [--dry-run]

Verify the clean master commit locally, incrementally sync content, upload the
app release only when source changes, and activate the deployment with systemd.
The native release is built for the VPS platform, so a real deploy must run on a
linux-x64 host; --dry-run only prints the deploy scope and runs anywhere.
Inside Herdr the current workspace and tab are marked while this runs.

Options:
  --dry-run  Show the commit, changed files, and upload decisions only.

Environment variables:
  RBOOK_DEPLOY_HOST       SSH host or alias (default: bohai)
  RBOOK_PUBLIC_HEALTH_URL Public content-health endpoint
  DEPLOY_SAY_IP           LAN IP checked before voice notification
  DEPLOY_SAY_SCRIPT       Path to say.py
  RBOOK_DEPLOY_EMOJI      Emoji marked on the Herdr workspace/tab while deploying
                          (default: 🚀; set to an empty value to disable)
EOF
}

while (( $# > 0 )); do
  case "$1" in
    --dry-run) DRY_RUN=true; shift ;;
    -h|--help) usage; exit 0 ;;
    *) die "unknown argument: $1" ;;
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

herdr_cli() {
  local bin="${HERDR_BIN_PATH:-herdr}"
  [[ -x "$bin" ]] || command -v "$bin" >/dev/null 2>&1 || return 1
  "$bin" "$@"
}

# Only when this shell really runs inside Herdr and the CLI answers.
herdr_available() {
  [[ -n "${HERDR_ENV:-}" && -n "${HERDR_WORKSPACE_ID:-}" && -n "${HERDR_TAB_ID:-}" ]] || return 1
  [[ -n "$DEPLOY_EMOJI" ]] || return 1
  herdr_cli tab list >/dev/null 2>&1 || return 1
}

# Every Herdr call is best effort: a UI marker must never fail a deployment.
herdr_mark_on() {
  herdr_available || return 0
  local label
  label="$(herdr_cli tab get "$HERDR_TAB_ID" 2>/dev/null \
    | python3 -c 'import json,sys; print(json.load(sys.stdin)["result"]["tab"]["label"])' 2>/dev/null || true)"
  if [[ -n "$label" ]]; then
    DEPLOY_TAB_LABEL_ORIGINAL="$label"
    herdr_cli tab rename "$HERDR_TAB_ID" "$DEPLOY_EMOJI $label" >/dev/null 2>&1 || true
  fi
  herdr_cli workspace report-metadata "$HERDR_WORKSPACE_ID" \
    --source "$DEPLOY_TOKEN_SOURCE" \
    --token "$DEPLOY_TOKEN_NAME=$DEPLOY_EMOJI" >/dev/null 2>&1 || true
  echo "[deploy] marked $HERDR_WORKSPACE_ID / $HERDR_TAB_ID with $DEPLOY_EMOJI"
}

# Called only on the success path: a failure keeps the marker on purpose.
herdr_mark_off() {
  herdr_available || return 0
  if [[ -n "$DEPLOY_TAB_LABEL_ORIGINAL" ]]; then
    herdr_cli tab rename "$HERDR_TAB_ID" "$DEPLOY_TAB_LABEL_ORIGINAL" >/dev/null 2>&1 || true
    DEPLOY_TAB_LABEL_ORIGINAL=""
  fi
  herdr_cli workspace report-metadata "$HERDR_WORKSPACE_ID" \
    --source "$DEPLOY_TOKEN_SOURCE" --clear-token "$DEPLOY_TOKEN_NAME" >/dev/null 2>&1 || true
}

for command_name in git npm node ssh rsync tar zstd sha256sum curl python3; do
  command -v "$command_name" >/dev/null 2>&1 || die "missing command: $command_name"
done

# Stop a wrong-platform run on the build host. Without this it would upload the
# content delta first and only then die inside deploy-native.sh with "dependency
# platform mismatch", leaving the VPS untouched and the deploy half-applied.
# --dry-run is exempt: it prints the commit, changed files and upload decisions
# without verifying, building, pushing, transferring, or restarting anything.
if [[ "$DRY_RUN" != true ]]; then
  deploy_platform="$(node -p "[process.platform, process.arch].join('-')")"
  [[ "$deploy_platform" == "$REQUIRED_PLATFORM" ]] \
    || die "deploy from a $REQUIRED_PLATFORM host: this host is $deploy_platform, and the native release must match the VPS platform"
fi

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

remote_value() {
  local name="$1"
  ssh "$DEPLOY_HOST" \
    "sed -n 's/^${name}=//p' '$BASE_DIR/current/deployment.env' 2>/dev/null | head -1" \
    || true
}

assert_clean
ssh -o BatchMode=yes -o ConnectTimeout=15 "$DEPLOY_HOST" true \
  || die "cannot connect to $DEPLOY_HOST"
git fetch --quiet origin "$BRANCH" || die "cannot fetch origin/$BRANCH"

head_sha="$(git rev-parse HEAD)"
remote_sha="$(git rev-parse "refs/remotes/origin/$BRANCH")"
git merge-base --is-ancestor "$remote_sha" "$head_sha" \
  || die "origin/$BRANCH is ahead of or diverged from local HEAD"

remote_deployment_sha="$(remote_value PROBLEMS_SOLUTION_DEPLOYMENT_SHA)"
remote_app_sha="$(remote_value PROBLEMS_SOLUTION_APP_SHA)"
remote_content_sha="$(remote_value PROBLEMS_SOLUTION_CONTENT_SHA)"
remote_node_abi="$(remote_value PROBLEMS_SOLUTION_NODE_ABI)"

# Before the first split deployment, current still points to the old monolithic
# release. Its directory name remains a valid deployed revision for diffing.
if [[ ! "$remote_deployment_sha" =~ ^[0-9a-f]{40}$ ]]; then
  remote_deployment_sha="$(ssh "$DEPLOY_HOST" \
    "readlink -f '$BASE_DIR/current' 2>/dev/null | sed 's#.*/##'" || true)"
fi

if [[ "$remote_deployment_sha" == "$head_sha" \
  && "$remote_app_sha" =~ ^[0-9a-f]{40}$ \
  && "$remote_content_sha" =~ ^[0-9a-f]{40}$ ]]; then
  echo "[deploy] $head_sha is already deployed"
  exit 0
fi

if [[ "$remote_deployment_sha" =~ ^[0-9a-f]{40}$ ]] \
  && git cat-file -e "${remote_deployment_sha}^{commit}" 2>/dev/null \
  && git merge-base --is-ancestor "$remote_deployment_sha" "$head_sha"; then
  mapfile -t changed_files < <(git diff --name-only "$remote_deployment_sha...$head_sha")
elif [[ "$head_sha" != "$remote_sha" ]]; then
  mapfile -t changed_files < <(git diff --name-only "$remote_sha...$head_sha")
else
  mapfile -t changed_files < <(git diff-tree --no-commit-id --name-only -r "$head_sha")
fi

content_changed=false
application_changed=false
for file in "${changed_files[@]}"; do
  case "$file" in
    problems/*|problem-sets/*) content_changed=true ;;
    *) application_changed=true ;;
  esac
done

# The first deployment of the split layout seeds both stores even if this
# commit changed only deployment code.
if [[ ! "$remote_app_sha" =~ ^[0-9a-f]{40}$ ]] \
  || ! ssh "$DEPLOY_HOST" "test -d '$BASE_DIR/apps/$remote_app_sha'"; then
  application_changed=true
fi
if [[ ! "$remote_content_sha" =~ ^[0-9a-f]{40}$ ]] \
  || ! ssh "$DEPLOY_HOST" "test -d '$BASE_DIR/contents/$remote_content_sha'"; then
  content_changed=true
fi

if [[ "$content_changed" != true && "$application_changed" != true ]]; then
  echo "[deploy] no deployable changes"
  exit 0
fi

if [[ "$application_changed" == true ]]; then
  deploy_mode=application
  app_sha="$head_sha"
  deployment_node_abi=""
else
  deploy_mode=content
  app_sha="$remote_app_sha"
  deployment_node_abi="$remote_node_abi"
fi
if [[ "$content_changed" == true ]]; then
  content_sha="$head_sha"
  if [[ "$remote_content_sha" =~ ^[0-9a-f]{40}$ ]] \
    && git cat-file -e "${remote_content_sha}^{commit}" 2>/dev/null \
    && git merge-base --is-ancestor "$remote_content_sha" "$head_sha" \
    && ssh "$DEPLOY_HOST" "test -d '$BASE_DIR/contents/$remote_content_sha/problems' && test -d '$BASE_DIR/contents/$remote_content_sha/problem-sets'"; then
    content_sync_mode=delta
  else
    content_sync_mode=full
  fi
else
  content_sha="$remote_content_sha"
  content_sync_mode=reuse
fi

echo "[deploy] commit=${head_sha:0:12} mode=$deploy_mode host=$DEPLOY_HOST"
echo "[deploy] app=${app_sha:0:12} upload=$application_changed content=${content_sha:0:12} sync=$content_sync_mode"
printf '[deploy] changed files: %s\n' "${#changed_files[@]}"

if [[ "$DRY_RUN" == true ]]; then
  printf '%s\n' "${changed_files[@]}"
  echo "[deploy] dry run; no verification, build, push, transfer, or restart was performed"
  exit 0
fi

herdr_mark_on
echo "[deploy] verify $head_sha"
npm run verify:push
assert_clean
[[ "$(git rev-parse HEAD)" == "$head_sha" ]] || die "HEAD changed during verification"

work_dir="$(mktemp -d "${TMPDIR:-/tmp}/problems-solution-native-deploy.XXXXXX")"
trap 'rm -rf "$work_dir"' EXIT
"$ROOT_DIR/scripts/build-native-release.sh" \
  --work-dir "$work_dir" --commit "$head_sha" --content-sha "$content_sha" --mode "$deploy_mode"
# shellcheck disable=SC1090
source "$work_dir/artifacts.env"
if [[ "$application_changed" == true ]]; then
  deployment_node_abi="$NODE_ABI"
fi

[[ "$deployment_node_abi" =~ ^[0-9]+$ ]] || die "invalid app Node ABI"

if [[ "$content_sync_mode" == delta ]]; then
  content_delta_archive="$work_dir/problems-solution-content-delta-${content_sha:0:12}.tar.zst"
  content_changed_list="$work_dir/content-changed-${content_sha:0:12}.nul"
  content_deleted_list="$work_dir/content-deleted-${content_sha:0:12}.nul"
  content_delta_checksums="$work_dir/content-delta-${content_sha:0:12}.sha256"

  git diff --no-renames --name-only -z --diff-filter=ACMRTUXB \
    "$remote_content_sha" "$head_sha" -- problems problem-sets > "$content_changed_list"
  printf 'content.env\0' >> "$content_changed_list"
  git diff --no-renames --name-only -z --diff-filter=D \
    "$remote_content_sha" "$head_sha" -- problems problem-sets > "$content_deleted_list"

  tar -C "$CONTENT_DIR" --null --no-recursion -T "$content_changed_list" -cf - \
    | zstd -T0 -3 -q -o "$content_delta_archive"
  (
    cd "$work_dir"
    sha256sum \
      "$(basename "$content_delta_archive")" \
      "$(basename "$content_changed_list")" \
      "$(basename "$content_deleted_list")" \
      > "$(basename "$content_delta_checksums")"
  )
fi

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

rsync_options=(-a --partial --info=progress2 -e ssh)
if [[ "$application_changed" == true ]]; then
  echo "[deploy] upload app release ${app_sha:0:12}"
  rsync "${rsync_options[@]}" \
    "$APP_ARCHIVE" "$APP_ARCHIVE.sha256" \
    "$DEPLOY_HOST:$incoming_dir/"

  if ! ssh "$DEPLOY_HOST" \
    "test -d '$BASE_DIR/dependencies/$LOCK_HASH/$PLATFORM_KEY-node$deployment_node_abi/node_modules'"; then
    rsync "${rsync_options[@]}" \
      "$DEPENDENCY_ARCHIVE" "$DEPENDENCY_ARCHIVE.sha256" \
      "$DEPLOY_HOST:$incoming_dir/"
  fi
fi

upload_content_index=false
if [[ "$content_changed" == true ]] \
  || ! ssh "$DEPLOY_HOST" "test -f '$BASE_DIR/contents/$content_sha/content-index-v1.json'"; then
  upload_content_index=true
  echo "[deploy] upload content index ${content_sha:0:12} schema=v1"
  rsync "${rsync_options[@]}" \
    "$CONTENT_INDEX_ARCHIVE" "$CONTENT_INDEX_ARCHIVE.sha256" \
    "$DEPLOY_HOST:$incoming_dir/"
fi

if [[ "$content_changed" == true ]]; then
  if [[ "$content_sync_mode" == delta ]]; then
    changed_count="$(git diff --no-renames --name-only --diff-filter=ACMRTUXB \
      "$remote_content_sha" "$head_sha" -- problems problem-sets | wc -l)"
    deleted_count="$(git diff --no-renames --name-only --diff-filter=D \
      "$remote_content_sha" "$head_sha" -- problems problem-sets | wc -l)"
    echo "[deploy] upload content delta ${content_sha:0:12} changed=$changed_count deleted=$deleted_count"
    rsync "${rsync_options[@]}" \
      "$content_delta_archive" "$content_changed_list" "$content_deleted_list" \
      "$content_delta_checksums" "$DEPLOY_HOST:$incoming_dir/"
  else
    echo "[deploy] seed full content ${content_sha:0:12}"
    ssh "$DEPLOY_HOST" "mkdir -p '$incoming_dir/content'"
    content_rsync_options=(-rlp --delete --checksum --partial --info=progress2 -e ssh)
    if ssh "$DEPLOY_HOST" "test -d '$BASE_DIR/current/problems'"; then
      content_rsync_options+=("--copy-dest=$BASE_DIR/current")
    elif [[ "$remote_deployment_sha" =~ ^[0-9a-f]{40}$ ]] \
      && ssh "$DEPLOY_HOST" "test -d '$BASE_DIR/releases/$remote_deployment_sha/problems'"; then
      content_rsync_options+=("--copy-dest=$BASE_DIR/releases/$remote_deployment_sha")
    elif ssh "$DEPLOY_HOST" "test -d '$BASE_DIR/releases/$remote_sha/problems'"; then
      content_rsync_options+=("--copy-dest=$BASE_DIR/releases/$remote_sha")
    elif ssh "$DEPLOY_HOST" "test -d '/srv/rbook/problems' && test -d '/srv/rbook/problem-sets'"; then
      content_rsync_options+=("--copy-dest=/srv/rbook")
    fi
    rsync "${content_rsync_options[@]}" \
      "$CONTENT_DIR/" "$DEPLOY_HOST:$incoming_dir/content/"
  fi
fi

rsync "${rsync_options[@]}" \
  "$ROOT_DIR/scripts/deploy-native.sh" \
  "$ROOT_DIR/scripts/apply-content-delta.sh" \
  "$ROOT_DIR/deploy/problems-solution.service" \
  "$DEPLOY_HOST:$incoming_dir/"

deploy_actor="$(id -un | tr -cd '[:alnum:]_.-')"
deploy_source_host="$(hostname | tr -cd '[:alnum:]_.-')"
printf -v remote_env \
  'RELEASE_SHA=%q APP_SHA=%q CONTENT_SHA=%q CONTENT_BASE_SHA=%q CONTENT_SYNC_MODE=%q LOCK_HASH=%q PLATFORM_KEY=%q NODE_ABI=%q DEPLOY_MODE=%q UPLOAD_APP=%q UPLOAD_CONTENT=%q UPLOAD_CONTENT_INDEX=%q INCOMING_DIR=%q DEPLOY_ACTOR=%q DEPLOY_SOURCE_HOST=%q PUBLIC_HEALTH_URL=%q' \
  "$head_sha" "$app_sha" "$content_sha" "$remote_content_sha" "$content_sync_mode" "$LOCK_HASH" "$PLATFORM_KEY" "$deployment_node_abi" "$deploy_mode" \
  "$application_changed" "$content_changed" "$upload_content_index" "$incoming_dir" "$deploy_actor" \
  "$deploy_source_host" "$PUBLIC_HEALTH_URL"
printf -v remote_script '%q' "$incoming_dir/deploy-native.sh"

echo "[deploy] activate ${head_sha:0:12} on $DEPLOY_HOST"
ssh "$DEPLOY_HOST" \
  "if [ \"\$(id -u)\" -eq 0 ]; then env $remote_env bash $remote_script; else sudo -n env $remote_env bash $remote_script; fi"

echo "[deploy] deployed $head_sha"
herdr_mark_off
announce "主人,题目解析系统 部署完成"
