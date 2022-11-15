// Script for Sell Stocks page
(() => {
    // Display form group for shares owned -- populated with JS so hidden if JS
    // not enabled
    document.querySelector('#sharesOwnedGroup').removeAttribute('hidden');

    // Populate field when different stock symbols are selected
    document.querySelector('#stockSelector').addEventListener('change', (e) => {
        const stockSymbol = e.target.value;
        const sharesOwned = e.target
            .querySelector(`option[value=${stockSymbol}]`).dataset.totalShares;
        document.querySelector('#sharesOwned').value = sharesOwned;
    });
})();
