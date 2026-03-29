import { ConfigError } from "./errors.js";

function parseInteger(name, rawValue, fallback) {
  const value = rawValue === undefined || rawValue === "" ? fallback : Number(rawValue);
  if (!Number.isInteger(value) || value <= 0) {
    throw new ConfigError(`${name} must be a positive integer`);
  }
  return value;
}

function normalizeBaseUrl(rawValue) {
  if (!rawValue) {
    throw new ConfigError("TARGET_API_BASE_URL is required");
  }

  let parsed;
  try {
    parsed = new URL(rawValue);
  } catch {
    throw new ConfigError("TARGET_API_BASE_URL must be a valid URL");
  }

  return parsed.origin;
}

export function loadConfig(env = process.env) {
  const mcpHost = env.MCP_HOST || "0.0.0.0";
  const mcpPort = parseInteger("MCP_PORT", env.MCP_PORT, 3333);
  const targetApiBaseUrl = normalizeBaseUrl(env.TARGET_API_BASE_URL);
  const upstreamTimeoutMs = parseInteger("UPSTREAM_TIMEOUT_MS", env.UPSTREAM_TIMEOUT_MS, 5000);
  const mcpAuthToken = env.MCP_AUTH_TOKEN || undefined;

  return {
    mcpHost,
    mcpPort,
    targetApiBaseUrl,
    upstreamTimeoutMs,
    mcpAuthToken
  };
}
