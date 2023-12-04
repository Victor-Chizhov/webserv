

function sendDelete() {
    console.log('sendDelete function called');

    let numberValue = document.getElementById('stringInput').value;
    if (numberValue === '') {
        alert('Please, enter the name of the file you want to delete');
        return;
    }
    document.getElementById('stringInput').value = '';

    fetch('deleter.html?Name=' + numberValue, {
        method: 'DELETE',
    })
        .then(response => {
            if (response.status === 405) {
                window.location.href = 'errorPages/405.html';
            } else if (response.status === 404) {
                alert('File not found');
            } else if (response.status === 200) {
                alert('File deleted successfully');
            }
            return response.text();
        })
        .then(response => {

            console.log(response);
        })
        .catch(error => {
            console.error('Error:', error);
        });
}
