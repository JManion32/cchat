//import { useState } from 'react';
import '../css/message.css';

type Props = {
    name: string;
    content: string;
    date?: string;
    sent: boolean;
};

function Message({ name, content, sent }: Props) {
    return (
        <>
            <div className={`message-container ${sent ? 'sent-message' : 'received-message'}`}>
                <div className={`message-bubble ${sent ? 'sent-bubble' : 'received-bubble'}`}>
                    <p className="message-bubble-p">{content}</p>
                </div>
                <div className={`message-info ${sent ? 'sent-info' : 'received-info'}`}>
                    <span>{sent ? '' : name}</span>
                </div>
            </div>
        </>
    );
}

export default Message;