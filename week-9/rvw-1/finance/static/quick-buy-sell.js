(() => {
    console.log('Loaded bitch!!!');
    document.addEventListener('click', (e) => {
        if (e.target.classList.contains('buy-btn')) {
            console.log('Buy!!!');
        } else if (e.target.classList.contains('sell-btn')) {
            console.log('Sell!!!');
        }
    });
})();
