/**
 * @author tommaso.ceredi@studio.unibo.it
 * @author tommaso.severi2@studio.unibo.it
 */

const timestamps = [];
const waterLevels = [];
myChart = null;

/**
 * Gets the status of the river monitoring system from the service and updates the dashboard.
 */
function getStatus() {
  fetch("http://127.0.0.1:5001/status")
    .then((response) => response.json())
    .then((data) => {
      document.getElementById("system-state").innerText =
        "System State: " + data.system_state;
      document.getElementById("valve-opening").innerText =
        "Valve Opening Level: " + data.valve_opening_level + "%";
      document.getElementById("system-modality").innerText =
        "System Modality: " + data.system_modality;
      console.log("System Modality: " + data.system_modality);
      switch (data.system_modality) {
        case "manual":
          document.getElementById("automatic-button").disabled = false;
          break;
        case "automatic":
          document.getElementById("automatic-button").disabled = true;
          break;
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
    .catch((error) => console.error("Error fetching status:", error));
}

/**
 * Controls the valve based on the value of the valve level input.
 * @param {string} modality - The modality of the system.
 */
function controlValve(modality) {
  switch (modality) {
    case "manual":
      console.log("Pressed manual button");
      const valveLevelInput = document.getElementById("valve-level-input");
      if (!valveLevelInput.value > 0) {
        valveLevelInput.value = 50;
      }
      const valveLevel = valveLevelInput.value;
      fetch("http://127.0.0.1:5001/control", {
        method: "POST",
        headers: {
          "Content-Type": "application/x-www-form-urlencoded",
        },
        body: new URLSearchParams({
          valve_level: valveLevel,
        }),
      })
        .then((response) => response.json())
        .then((data) => {
          if (data.success) {
            getStatus();
          } else {
            console.error("Failed to control the valve:", data.message);
          }
        })
        .catch((error) => console.error("Error controlling the valve:", error));
      break;
    case "automatic":
      console.log("Pressed automatic button");
      fetch("http://127.0.0.1:5001/control", {
        method: "POST",
        headers: {
          "Content-Type": "application/x-www-form-urlencoded",
        },
        body: new URLSearchParams({
          valve_level: -1,
        }),
      })
        .then((response) => response.json())
        .then((data) => {
          if (data.success) {
            getStatus();
          } else {
            console.error("Failed to change the modality:", data.message);
          }
        })
        .catch((error) => console.error("Error changing the modality:", error));
      break;
  }
}

/**
 * Updates the chart with the latest water level data.
 */
function updateChart() {
  const ctx = document.getElementById("water-level-chart").getContext("2d");

  if (!myChart) {
    myChart = new Chart(ctx, {
      type: "line",
      data: {
        labels: timestamps,
        datasets: [
          {
            label: "Water Level Over Time",
            data: waterLevels,
            borderColor: "blue",
            borderWidth: 1,
            fill: false,
          },
        ],
      },
      options: {
        scales: {
          xAxes: [
            {
              type: "linear",
              position: "bottom",
            },
          ],
          yAxes: [
            {
              type: "linear",
              position: "left",
            },
          ],
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

// updates the values displayed in the dashboard every 3 seconds
setInterval(getStatus, 3000);
