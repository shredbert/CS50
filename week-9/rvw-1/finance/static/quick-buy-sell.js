(() => {
    document.addEventListener('click', async (e) => {
        if (e.target.classList.contains('buy-btn')) {
            const symbol = e.target.value;
            console.log('Buy!!!');
            console.log(symbol);
        } else if (e.target.classList.contains('sell-btn')) {
            const symbol = e.target.value;
            console.log('Sell!!!');
            console.log(symbol);
        }
    });
})();
