

function fileUpload(input) {
    const file = input.files[0];
    console.log('Uploading file:', file);
    let reader = new FileReader();
	reader.onload = async function(e) {

        fetch('/upload', {
            method: 'POST',
            body: btoa(e.target.result),

            headers: {
                'Content-Disposition': `attachment; filename="${file.name}"`
            }
        })
            .then(response => {
                if (response.status == 413) {
                    window.location.href = 'errorPages/413.html';
                } else if (!response.ok) {
                    alert('Error uploading file');
                } else {
                    alert('File uploaded successfully')
                    window.location.href = 'index.html';
                }
                return response.text();
            })
            .then(data => {
                console.log('File uploaded successfully. Response from server:', data);
            })
            .catch(error => {
                console.error('Error uploading file:', error.message);
            });
	};
	reader.onerror = function(e) {
		// error occurred
		console.log('Error : ' + e.type);
	};
	reader.readAsBinaryString(file);
}
