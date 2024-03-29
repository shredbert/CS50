// Script for Sell Stocks page
(() => {
    // Display form group for shares owned -- populated with JS so hidden if JS
    // not enabled
    document.querySelector('#sharesOwnedGroup').removeAttribute('hidden');

    const refreshStockCount = () => {
        const stockSymbol = document.querySelector('#stockSelector').value;
        if (stockSymbol) {
            const sharesOwned = document
                .querySelector('#stockSelector')
                .querySelector(`option[value=${stockSymbol}]`)
                .dataset
                .totalShares;
            document.querySelector('#sharesOwned').value = sharesOwned;
        }
    }

    // Call immediately to take effect on back/forward
    refreshStockCount();

    // TODO: Figure out event to call refresh on when back button pressed so
    // fields auto-populated

    // Populate field when different stock symbols are selected
    document.querySelector('#stockSelector').addEventListener('change', () => {
        refreshStockCount();
    });
})();
