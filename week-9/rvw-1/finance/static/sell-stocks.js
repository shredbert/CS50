// Script for Sell Stocks page
(() => {
    document.querySelector('#stockSelector').addEventListener('click', (e) => {
        let prevIdx = e.target.selectedIndex;
        if (e.target.selectedIndex > 0 || e.target.selectedIndex !== prevIdx) {
            console.log(e.target.selectedIndex);
            // // Dynamically render # of shares available after selecting stock to sell
            // const sharesOwnedTemplate = document.querySelector('#totalSharesOwnedTemplate');
            // const sharesOwnedNode = sharesOwnedTemplate.cloneNode();
            // console.log(sharesOwnedNode);
        }
    });
})();
