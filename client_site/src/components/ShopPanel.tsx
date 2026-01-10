import { useState } from 'react';

import '../css/shop.css';
import '../css/colors.css';
import '../css/index.css';

import AirHockey from '../assets/air_hockey_mode.png'
import Festive from '../assets/festive_mode.png'
import Forest from '../assets/forest_mode.png'
import Galaxy from '../assets/galaxy_mode.png'
import Halloween from '../assets/halloween_mode.png'
import Monochrome from '../assets/monochrome_mode.png'
import Neon from '../assets/neon_mode.png'
import Premium from '../assets/premium_mode.png'
import Retro from '../assets/retro_mode.png'
import Soccer from '../assets/soccer_mode.png'
import Voltage from '../assets/voltage_mode.png'
import Warm from '../assets/warm_mode.png'

function ShopPanel() {
    const [isTheme, setIsTheme] = useState(true);
    const [isBanner, setIsBanner] = useState(false);

    function setCategory(category: string) {
        if (category === "theme" && isBanner) {
            setIsTheme(true);
            setIsBanner(false);
        }
        else if (category === "banner" && isTheme) {
            setIsTheme(false);
            setIsBanner(true);
        }
    }

    return (
        <>
            <div className={`shop-container`}>
                <div className="shop-nav">
                    <div className="nav-category-container">
                        <a className={`nav-category ${isTheme ? 'nav-category-toggled' : ''}`} onClick={ () => setCategory("theme") }>Themes</a>
                        <span className="nav-category-divider">{' | '}</span>
                        <a className={`nav-category ${isBanner ? 'nav-category-toggled' : ''}`}  onClick={ () => setCategory("banner") }>Banners</a>
                    </div>
                    <button className="credit-count count">Credits: 50</button>
                </div>
                <hr className="nav-divider"/>
                <div className={`center-theme ${isTheme ? '' : 'hide'}`}>
                    <div className={`theme-container`}>
                        <img src={AirHockey}/>
                        <img src={Festive}/>
                        <img src={Forest}/>
                        <img src={Galaxy}/>
                        <img src={Halloween}/>
                        <img src={Monochrome}/>
                        <img src={Neon}/>
                        <img src={Premium}/>
                        <img src={Retro}/>
                        <img src={Soccer}/>
                        <img src={Voltage}/>
                        <img src={Warm}/>
                    </div>
                </div>
                <div className={`banner-container ${isBanner ? '' : 'hide'}`}>
                    <div className="coming-soon">
                        Coming Soon!
                    </div>
                </div>
            </div>
        </>
    );
}

export default ShopPanel;