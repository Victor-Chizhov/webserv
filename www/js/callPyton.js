
function callPyton() {
    fetch('/callPyton', {
        method: 'GET'
    })
        .then(response => response.json())
        .then(data => {
            console.log('Python is called successfully:', data);
        })
        .catch(error => {
            console.error('Python is not called:', error);
        })
}