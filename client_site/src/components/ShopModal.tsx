import { useState } from 'react';
import { createPortal } from 'react-dom';

import ShopPanel from './ShopPanel.tsx'
import '../css/modal.css';

function ShopModal() {
    const [isOpen, setIsOpen] = useState(false);
    const [isClosing, setIsClosing] = useState(false);

    const closeModal = () => {
        setIsClosing(true);
        setTimeout(() => {
            setIsClosing(false);
            setIsOpen(false);
        }, 300);
    };

    const handleOutsideClick = (e: React.MouseEvent<HTMLDivElement>) => {
        if ((e.target as HTMLElement).classList.contains('modal-container')) {
            closeModal();
        }
    };

    const modal = isOpen ? (
        <div className="modal-container" onClick={ handleOutsideClick }>
            <div
                className={`modal ${isClosing ? 'slide-down' : 'slide-up'}`}
            >
                <ShopPanel/>
            </div>
        </div>
    ) : null;

    return (
        <>
            {/* Trigger */}
            <button
                className="default-btn shop-btn"
                onClick={() => setIsOpen(true)}
            >
                Shop (50)
            </button>

            {modal && createPortal(modal, document.getElementById('modal-root')!)}
        </>
    );
}

export default ShopModal;
