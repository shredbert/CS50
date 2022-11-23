(() => {
    // TODO: Make progressively enhanced -- don't display buy/sell buttons if
    // dialogues not working
    document.addEventListener('click', async (e) => {

        if (e.target.classList.contains('buy-btn')) {

            // Populate dialogue with symbol
            const buyDlg = document.querySelector('#buy-dlg');
            const symbol = e.target.dataset.symbol;
            buyDlg.querySelector('#symbol').value = symbol;
            const shares = e.target.dataset.shares;
            buyDlg.querySelector('#current-shares').value = shares;

            // Dialogue behaviours
            buyDlg.showModal();
            buyDlg.querySelector('#cancelBuy')
                .addEventListener('click', () => {
                    buyDlg.close();
                });

        } else if (e.target.classList.contains('sell-btn')) {

            // Populate dialogue with symbol
            const sellDlg = document.querySelector('#sell-dlg');
            const symbol = e.target.dataset.symbol;
            sellDlg.querySelector('#symbol').value = symbol;
            const shares = e.target.dataset.shares;
            sellDlg.querySelector('#current-shares').value = shares;

            // Dialogue behaviours
            sellDlg.showModal();
            sellDlg.querySelector('#cancelSell')
                .addEventListener('click', () => {
                    sellDlg.close();
                });

        }

    });
})();
