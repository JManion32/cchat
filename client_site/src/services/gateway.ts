// services/gateway.ts
import GatewayWS from "./gatewayWS";

export const gateway = new GatewayWS(
    import.meta.env.VITE_GATEWAY_URL
);
