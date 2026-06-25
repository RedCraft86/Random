// ==UserScript==
// @name            Youtube Scroll Utils
// @namespace       https://www.youtube.com/
// @version         1.0
// @description     Saves/restores scroll position AND includes a kill-switch for the infinite scroll bug
// @author          RedCraft86
// @match           https://www.youtube.com/*
// @grant           none
// @license         MIT
// ==/UserScript==

(function() {
    'use strict';

    // --- CONFIGURATION ---
    const doAutoscroll = false;
    const saveDelay = 2000;
    const minScrollSave = 500;
    const loopJumpAmount = 3000; // How many pixels to jump up when hitting "Fix Loop"

    // --- STATE ---
    let isScrolling = false;
    let saveTimeout = null;
    let lastUrl = location.href;

    // --- NATIVE NOTIFICATIONS ---
    function notify(text, duration = 3000) {
        let toast = document.getElementById('yt-scroll-toast');
        if (!toast) {
            toast = document.createElement('div');
            toast.id = 'yt-scroll-toast';
            toast.style = `
                position: fixed !important; bottom: 20px !important; left: 20px !important; z-index: 999999 !important;
                background: rgba(0, 0, 0, 0.9) !important; color: white !important; padding: 12px 24px !important;
                border-radius: 8px !important; font-family: Roboto, Arial, sans-serif !important;
                font-size: 14px !important; pointer-events: none !important; opacity: 0;
                transition: opacity 0.3s ease !important; border: 1px solid #555 !important;
            `;
            document.body.appendChild(toast);
        }
        toast.innerText = text;
        toast.style.opacity = '1';

        clearTimeout(toast.timeoutId);
        toast.timeoutId = setTimeout(() => { toast.style.opacity = '0'; }, duration);
    }

    // --- CORE LOGIC ---
    function getChannelIdentifier() {
        const match = window.location.pathname.match(/(?:@|c\/|channel\/)([^/]+)/);
        return match ? match[1] : null;
    }

    function getCurrentScroll() {
        return window.scrollY || document.documentElement.scrollTop || document.body.scrollTop;
    }

    function saveScrollPosition() {
        if (!window.location.pathname.includes('/videos')) return;

        const channelId = getChannelIdentifier();
        if (!channelId) return;

        const scrollPosition = getCurrentScroll();
        if (scrollPosition > minScrollSave) {
            localStorage.setItem(`yt_scroll_${channelId}`, scrollPosition);
            notify(`💾 Saved scroll: ${Math.round(scrollPosition)}px`);
        }
    }

    function bumpBack() {
        if (!isScrolling) {
            const currentY = getCurrentScroll();
            const newY = Math.max(0, currentY - loopJumpAmount);

            window.scrollTo(0, newY);
            notify(`✅ Bumped up. Loop broken.`);
        }
    }

    function cancelScroll(waitTime = 1000, attempts = 2) {
        let offset = 500;
        for (let i = 0; i < attempts; i++) {
            setTimeout(() => {
                bumpBack();
            }, waitTime + (offset * i));
        }
    }

    function scrollToPos(pos) {
        isScrolling = true;
        let attempts = 0;
        const maxAttempts = 20;

        const uiContainer = document.getElementById('yt-scroll-ui-container');
        if (uiContainer) uiContainer.style.display = 'none';

        const scrollInterval = setInterval(() => {
            const current = getCurrentScroll();

            if (current >= pos - 100 || attempts >= maxAttempts) {
                clearInterval(scrollInterval);
                notify(`✅ Finished scrolling`);
                setTimeout(() => {
                    isScrolling = false;
                    cancelScroll();
                }, 100);
                return;
            }

            notify(`⏬ Scrolling...`);
            window.scrollTo(0, pos);
            attempts++;
        }, 300);
    }

    function injectUI(pos) {
        const existingContainer = document.getElementById('yt-scroll-ui-container');
        if (existingContainer) {
            existingContainer.style.display = 'flex';
        }

        const container = document.createElement('div');
        container.id = 'yt-scroll-ui-container';
        container.style = `
            position: fixed !important;
            top: 53px !important;
            right: 25px !important;
            z-index: 9999999 !important;
            display: flex !important;
            gap: 10px !important;
            pointer-events: none !important;
        `;

        const baseBtnStyle = `
            pointer-events: auto !important;
            background-color: #272727 !important;
            color: #ffffff !important;
            padding: 10px 16px 10px 12px !important;
            border-radius: 18px !important;
            font-weight: 500 !important;
            cursor: pointer !important;
            border: none !important;
            box-shadow: 0 1px 3px rgba(0,0,0,0.5) !important;
            font-family: "Roboto", "Arial", sans-serif !important;
            font-size: 13px !important;
            letter-spacing: 0.007em !important;
            transition: transform 0.1s ease !important;
        `;

        // The Updated "Fix Loop" Button
        if (pos && pos > minScrollSave) {
            const fixBtn = document.createElement("button");
            fixBtn.innerText = `⬆️ Fix Scroll Loop`;
            fixBtn.style = baseBtnStyle;
            fixBtn.onmouseover = () => { fixBtn.style.transform = 'scale(1.05)'; }
            fixBtn.onmouseout = () => { fixBtn.style.transform = 'scale(1)'; }
            fixBtn.addEventListener('click', (e) => {
                e.preventDefault();
                e.stopPropagation();
                if (!isScrolling) {
                    bumpBack();
                }
            });
            container.appendChild(fixBtn);

            const loadBtn = document.createElement("button");
            loadBtn.innerText = `🖲️ Load Scroll (${pos}px)`;
            loadBtn.style = baseBtnStyle;
            loadBtn.onmouseover = () => { loadBtn.style.transform = 'scale(1.05)'; }
            loadBtn.onmouseout = () => { loadBtn.style.transform = 'scale(1)'; }
            loadBtn.addEventListener('click', (e) => {
                e.preventDefault();
                e.stopPropagation();
                scrollToPos(pos);
            });
            container.appendChild(loadBtn);
        }

        document.body.appendChild(container);
    }

    function loadScrollPosition() {
        const channelId = getChannelIdentifier();
        let savedPosition = 0;

        if (channelId) {
            savedPosition = parseInt(localStorage.getItem(`yt_scroll_${channelId}`) || "0", 10);
            if (savedPosition > minScrollSave) {
                notify(`👀 Found saved position: ${savedPosition}px`);
                if (doAutoscroll) {
                    scrollToPos(savedPosition);
                }
            }
        }

        injectUI(savedPosition);
        setTimeout(() => injectUI(savedPosition), 1500);
        setTimeout(() => injectUI(savedPosition), 3000);
    }

    // --- EVENT LISTENERS ---
    window.addEventListener('scroll', () => {
        if (isScrolling) return;
        if (saveTimeout) clearTimeout(saveTimeout);
        saveTimeout = setTimeout(saveScrollPosition, saveDelay);
    }, { passive: true });

    const observer = new MutationObserver(() => {
        if (location.href !== lastUrl) {
            lastUrl = location.href;

            const oldContainer = document.getElementById('yt-scroll-ui-container');
            if (oldContainer) oldContainer.remove();

            if (window.location.pathname.includes('/videos')) {
                setTimeout(loadScrollPosition, 1500);
            }
        }
    });
    observer.observe(document.body, { childList: true, subtree: true });

    if (window.location.pathname.includes('/videos')) {
        setTimeout(loadScrollPosition, 1500);
    }

})();
