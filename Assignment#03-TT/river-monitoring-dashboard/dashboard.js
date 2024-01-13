const timestamps = [];
const waterLevels = [];
myChart = null;

/**
 * Gets the status of the river monitoring system from the service and updates the dashboard.
 */
function getStatus() {
    fetch('http://127.0.0.1:5001/status')
        .then(response => response.json())
        .then(data => {
            document.getElementById('system-state').innerText = 'System State: ' + data.system_state;
            document.getElementById('valve-opening').innerText = 'Valve Opening Level: ' + data.valve_opening_level + '%';
            if (data.system_modality == 'automatic') {
                document.getElementById('automatic-button').classList.add('active');
                document.getElementById('manual-button').classList.remove('active');
            } else {
                document.getElementById('automatic-button').classList.remove('active');
                document.getElementById('manual-button').classList.add('active');
            }
            const timestamp = new Date().toLocaleTimeString();
            timestamps.push(timestamp);
            if (waterLevels.length >= 60) {
                timestamps.shift();
                waterLevels.shift();
            }
            waterLevels.push(data.water_level);
            updateChart();
        })
        .catch(error => console.error('Error fetching status:', error));
}

/**
 * Controls the valve based on the value of the valve level input.
 */
function controlValve() {
    const valveLevelInput = document.getElementById('valve-level-input');
    const valveLevel = valveLevelInput.value;
    fetch('http://127.0.0.1:5001/control', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/x-www-form-urlencoded',
            },
            body: new URLSearchParams({
                valve_level: valveLevel,
            })
        })
        .then(response => response.json())
        .then(data => {
            if (data.success) {
                getStatus();
            } else {
                console.error('Failed to control the valve:', data.message);
            }
        })
        .catch(error => console.error('Error controlling the valve:', error));
}

/**
 * Updates the chart with the latest water level data.
 */
function updateChart() {
    const ctx = document.getElementById('water-level-chart').getContext('2d');

    if (!myChart) {
        myChart = new Chart(ctx, {
            type: 'line',
            data: {
                labels: timestamps,
                datasets: [{
                    label: 'Water Level Over Time',
                    data: waterLevels,
                    borderColor: 'blue',
                    borderWidth: 1,
                    fill: false,
                }],
            },
            options: {
                scales: {
                    xAxes: [{
                        type: 'linear',
                        position: 'bottom',
                    }],
                    yAxes: [{
                        type: 'linear',
                        position: 'left',
                    }],
                },
            },
        });
    } else {
        myChart.data.labels = timestamps;
        myChart.data.datasets[0].data = waterLevels;
        myChart.update();
    }
}

// Get the initial status and start polling for updates.
getStatus();

setInterval(getStatus, 1000);