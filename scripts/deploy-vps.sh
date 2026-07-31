#!/usr/bin/env bash
set -euo pipefail

APP_DIR="${APP_DIR:-/srv/rbook}"
SERVICE_NAME="${SERVICE_NAME:-problems-solution}"
BRANCH="${BRANCH:-master}"
NODE_ENV="${NODE_ENV:-production}"
COMPOSE_PROJECT_NAME="${COMPOSE_PROJECT_NAME:-problems-solution}"
IMAGE_REF="${IMAGE_REF:-ghcr.io/rainboyoj/new_problem_solutions:master}"
DEPLOY_IMAGE_REF="${DEPLOY_IMAGE_REF:-problems-solution:deploy}"
GHCR_USERNAME="${GHCR_USERNAME:-}"
GHCR_TOKEN_B64="${GHCR_TOKEN_B64:-}"
PULL_TIMEOUT="${PULL_TIMEOUT:-300}"
SKIP_IMAGE_PULL="${SKIP_IMAGE_PULL:-false}"

usage() {
  cat <<'EOF'
Usage: deploy-vps.sh [--help]

Deploy the app on a VPS using git and Docker Compose.

Environment variables:
  APP_DIR             App directory on the server. Default: /srv/rbook
  SERVICE_NAME        Docker Compose service name. Default: problems-solution
  BRANCH              Git branch to deploy. Default: master
  NODE_ENV            Node environment. Default: production
  COMPOSE_PROJECT_NAME Compose project name. Default: problems-solution
  IMAGE_REF           Image to pull. Default: ghcr.io/rainboyoj/new_problem_solutions:master
  DEPLOY_IMAGE_REF    Local image tag used by compose. Default: problems-solution:deploy
  GHCR_USERNAME       Optional GHCR username for docker login
  GHCR_TOKEN_B64      Optional base64 encoded GHCR token
  PULL_TIMEOUT        docker pull timeout seconds. Default: 300
  SKIP_IMAGE_PULL     Use existing local image when true. Default: false
EOF
}

if [[ "${1:-}" == "-h" || "${1:-}" == "--help" ]]; then
  usage
  exit 0
fi

cd "$APP_DIR"

echo "Deploying $(pwd) from branch $BRANCH"

git fetch origin "$BRANCH"
git reset --hard "origin/$BRANCH"

export SERVICE_NAME NODE_ENV COMPOSE_PROJECT_NAME

if docker compose version >/dev/null 2>&1; then
  compose=(docker compose)
elif command -v docker-compose >/dev/null 2>&1; then
  compose=(docker-compose)
else
  echo "Docker Compose is not installed. Install the Docker Compose plugin first." >&2
  exit 1
fi

if [[ "$SKIP_IMAGE_PULL" == "true" ]] && ! docker image inspect "$DEPLOY_IMAGE_REF" >/dev/null 2>&1; then
  echo "Local image $DEPLOY_IMAGE_REF does not exist; pulling image instead."
  SKIP_IMAGE_PULL="false"
fi

if [[ "$SKIP_IMAGE_PULL" != "true" && -n "$GHCR_USERNAME" && -n "$GHCR_TOKEN_B64" ]]; then
  printf '%s' "$GHCR_TOKEN_B64" | base64 -d | docker login ghcr.io -u "$GHCR_USERNAME" --password-stdin
fi

if [[ "$SKIP_IMAGE_PULL" == "true" ]]; then
  echo "Skipping image pull; restarting with the existing local image."
else
  pull_candidates=(
    "${IMAGE_REF/ghcr.io/ghcr.nju.edu.cn}"
    "gh-proxy.org/docker/$IMAGE_REF"
    "$IMAGE_REF"
  )

  pulled_image=""
  for candidate in "${pull_candidates[@]}"; do
    echo "Pulling image candidate: $candidate"
    if timeout "$PULL_TIMEOUT" docker pull "$candidate"; then
      pulled_image="$candidate"
      break
    fi
    echo "Failed to pull image candidate: $candidate" >&2
  done

  if [[ -z "$pulled_image" ]]; then
    echo "Failed to pull any image candidate for $IMAGE_REF" >&2
    exit 1
  fi

  docker tag "$pulled_image" "$DEPLOY_IMAGE_REF"
fi

export IMAGE_REF="$DEPLOY_IMAGE_REF"

existing_container_id="$(docker container inspect --format '{{.Id}}' "$SERVICE_NAME" 2>/dev/null || true)"
if [[ -n "$existing_container_id" ]]; then
  existing_project="$(docker container inspect --format '{{ index .Config.Labels "com.docker.compose.project" }}' "$existing_container_id")"
  existing_service="$(docker container inspect --format '{{ index .Config.Labels "com.docker.compose.service" }}' "$existing_container_id")"

  if [[ "$existing_project" != "$COMPOSE_PROJECT_NAME" || "$existing_service" != "problems-solution" ]]; then
    echo "Removing existing container $SERVICE_NAME from project ${existing_project:-none} before Compose takes ownership."
    docker container rm -f "$existing_container_id"
  fi
fi

"${compose[@]}" up -d --force-recreate --remove-orphans
"${compose[@]}" ps
