// src/App.tsx
import { BrowserRouter, Route, Routes } from "react-router-dom";
import { useEffect, useState } from "react";

import Login from "./pages/Login";
import Chat from "./pages/Chat";
import { gateway } from "./services/gateway";

export default function App() {
    const [messages, setMessages] = useState<any[]>([]);
    const [success, setSuccess] = useState<boolean | null>(null);
    const [user, setUser] = useState<string>("");
    const [token, setToken] = useState<string>("");
    const [activeCount, setActiveCount] = useState(0);

    useEffect(() => {
        gateway.onMessage = (msg) => {
            switch (msg.type) {
                case "auth.response":
                    setSuccess(msg.payload.success);
                    setUser(msg.payload.name);
                    setToken(msg.payload.token);
                    break;

                case "chat.response":
                    if (typeof msg.payload.activeCount === "number") {
                        setActiveCount(msg.payload.activeCount);
                    }
                    setMessages(prev => [...prev, msg.payload]);
                    break;
            }
        };
    }, []);

    return (
        <BrowserRouter>
            <Routes>
                <Route
                    path="/"
                    element={
                        <Login
                            gateway={gateway}
                            success={success}
                            chosen_name={user}
                        />
                    }
                />
                <Route
                    path="/chat"
                    element={
                        <Chat
                            messages={messages}
                            gateway={gateway}
                            user={user}
                            token={token}
                            activeCount={activeCount}
                        />
                    }
                />
            </Routes>
        </BrowserRouter>
    );
}
