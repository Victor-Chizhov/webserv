function arrayBufferToBase64(buffer) {
    let binary = '';
    const bytes = new Uint8Array(buffer);
    const len = bytes.byteLength;

    for (let i = 0; i < len; i++) {
        binary += String.fromCharCode(bytes[i]);
    }

    return window.btoa(binary);
}

function fileUpload(input) {
    const file = input.files[0];
    console.log('Uploading file:', file);
    var reader = new FileReader();

	reader.onload = function(e) {
		
        fetch('/upload', {
            method: 'POST',
            body: btoa(e.target.result),

            headers: {
                'Content-Disposition': `attachment; filename="${file.name}"`
            }
        })
            .then(response => {
                if (!response.ok) {
                    window.location.href = 'errorPages/413.html';
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