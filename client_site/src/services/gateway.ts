// services/gateway.ts
import GatewayWS from './gatewayWS';

const gatewayUrl = import.meta.env.VITE_GATEWAY_URL || 'ws://localhost:8080';
export const gateway = new GatewayWS(gatewayUrl);
