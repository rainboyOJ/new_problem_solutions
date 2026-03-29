import test from "node:test";
import assert from "node:assert/strict";

import { loadConfig } from "../src/config.js";

test("loadConfig uses defaults and required base url", () => {
  const config = loadConfig({ TARGET_API_BASE_URL: "http://127.0.0.1:3000" });

  assert.equal(config.mcpHost, "0.0.0.0");
  assert.equal(config.mcpPort, 3333);
  assert.equal(config.targetApiBaseUrl, "http://127.0.0.1:3000");
  assert.equal(config.upstreamTimeoutMs, 5000);
  assert.equal(config.mcpAuthToken, undefined);
});

test("loadConfig reads custom values", () => {
  const config = loadConfig({
    MCP_HOST: "127.0.0.1",
    MCP_PORT: "4567",
    TARGET_API_BASE_URL: "https://example.com",
    UPSTREAM_TIMEOUT_MS: "2500",
    MCP_AUTH_TOKEN: "token123"
  });

  assert.equal(config.mcpHost, "127.0.0.1");
  assert.equal(config.mcpPort, 4567);
  assert.equal(config.targetApiBaseUrl, "https://example.com");
  assert.equal(config.upstreamTimeoutMs, 2500);
  assert.equal(config.mcpAuthToken, "token123");
});

test("loadConfig throws when TARGET_API_BASE_URL is missing", () => {
  assert.throws(() => loadConfig({}), /TARGET_API_BASE_URL/);
});
