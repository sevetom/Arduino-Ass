const timestamps = [];
const waterLevels = [];

function getStatus() {
    fetch('http://river-monitoring-service/status')
        .then(response => response.json())
        .then(data => {
            document.getElementById('water-level').innerText = 'Water Level: ' + data.water_level;
            document.getElementById('system-state').innerText = 'System State: ' + data.system_state;
            document.getElementById('valve-opening').innerText = 'Valve Opening Level: ' + data.valve_opening_level + '%';
            const timestamp = new Date().toLocaleTimeString();
            timestamps.push(timestamp);
            waterLevels.push(data.water_level);
            updateChart();
        })
        .catch(error => console.error('Error fetching status:', error));
}

function controlValve() {
    const valveLevelInput = document.getElementById('valve-level-input');
    const valveLevel = valveLevelInput.value;
    fetch('http://river-monitoring-service/control', {
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

function updateChart() {
    const ctx = document.getElementById('water-level-chart').getContext('2d');
    const myChart = new Chart(ctx, {
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
                x: [{
                    type: 'linear',
                    position: 'bottom',
                }],
                y: [{
                    type: 'linear',
                    position: 'left',
                }],
            },
        },
    });
}

getStatus();