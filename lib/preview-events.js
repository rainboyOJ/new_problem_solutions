function formatEvent(event) {
  return `event: ${event.type}\ndata: ${JSON.stringify(event)}\n\n`;
}

export class PreviewEventBroker {
  #active;
  #clients = new Map();
  #heartbeat = null;
  #unsubscribe;

  constructor(active, opts = {}) {
    this.#active = active;
    this.#unsubscribe = active.subscribe((update) => this.broadcast(update));

    const heartbeatMs = opts.heartbeatMs ?? 15_000;
    if (heartbeatMs > 0) {
      this.#heartbeat = setInterval(() => {
        for (const stream of this.#clients.keys()) stream.write(': heartbeat\n\n');
      }, heartbeatMs);
      this.#heartbeat.unref?.();
    }
  }

  get clientCount() {
    return this.#clients.size;
  }

  connect(stream, request) {
    const disconnect = () => this.#disconnect(stream);
    this.#clients.set(stream, { request, disconnect });
    request.once('close', disconnect);
    stream.write(formatEvent(this.#active.getClientState()));
  }

  broadcast(update) {
    const message = formatEvent(update);
    for (const stream of this.#clients.keys()) stream.write(message);
  }

  #disconnect(stream) {
    const client = this.#clients.get(stream);
    if (!client) return;
    client.request.removeListener('close', client.disconnect);
    this.#clients.delete(stream);
  }

  close() {
    if (this.#heartbeat) clearInterval(this.#heartbeat);
    this.#heartbeat = null;
    this.#unsubscribe?.();
    this.#unsubscribe = null;

    for (const [stream, client] of this.#clients) {
      client.request.removeListener('close', client.disconnect);
      stream.end();
    }
    this.#clients.clear();
  }
}
