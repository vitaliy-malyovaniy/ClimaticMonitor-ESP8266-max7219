google.charts.load('current', {'packages':['corechart']});
google.charts.setOnLoadCallback(drawChart);

var xmlHttp=createXmlHttpObject();

function createXmlHttpObject() {
  if (window.XMLHttpRequest) {
      xmlHttp0 = new XMLHttpRequest();
  } else {
      xmlHttp0 = new ActiveXObject('Microsoft.XMLHTTP');
  }
  return xmlHttp0;
}
var lengthArray = 30;
var dataShow = [
    [1], [2], [3], [4], [5], [6], [7], [8], [9], [10], [11], [12], [13], [14], [15], [16], [17], [18], [19], [20] , [21], [22], [23], [24], [25], [26], [27], [28], [29], [30]
  ];
var dataShow1 = [
    [1], [2], [3], [4], [5], [6], [7], [8], [9], [10], [11], [12], [13], [14], [15], [16], [17], [18], [19], [20] , [21], [22], [23], [24], [25], [26], [27], [28], [29], [30]
  ];

function chart(){
  if(xmlHttp.readyState==0 || xmlHttp.readyState==4){
      xmlHttp.open('GET', "/graf.json", true);
      xmlHttp.send(null);
      xmlHttp.onload = function(e) {
        const chartResponse=JSON.parse(xmlHttp.responseText);
          for (let i=0; i<dataShow.length; i++){
            dataShow[i][1] = +chartResponse.data0[i];
            dataShow1[i][1] = +chartResponse.data1[i];
          }
      }
  }
}

chart();

function drawChart() {
var data = new google.visualization.DataTable();
data.addColumn('number', 'Day');
data.addColumn('number');  // , 'CO2, ppm'
data.addRows(dataShow);

var data1 = new google.visualization.DataTable();
data1.addColumn('number', 'Day');
data1.addColumn('number');
data1.addRows(dataShow1);

const options = {
    width: '100%',
    title: 'Level CO2, ppm',
    // curveType: 'function',
    legend: { position: 'bottom' },
    vAxis: {
      // title: 'CO2',
      maxValue: 3500,
      minValue: 400,
      gridlines: { count: 30 },
      // ticks: [400, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000]  
    },
    hAxis: {
        format: '', // 'HH:mm',
        gridlines: { count: 20 }
    }
  };

const options1 = {
    width: '100%',
    title: 'Temperature, °C',
    // curveType: 'function',
    legend: { position: 'bottom' },
    vAxis: {
      // title: '°C',
      maxValue: 45,
      gridlines: { count: 30 }
    },
    hAxis: {
        format: '', // 'HH:mm',
        gridlines: { count: 20 }
    }
  };

  var chart = new google.visualization.LineChart(document.getElementById('curve_chart'));
  var formatter = new google.visualization.DateFormat({pattern: 'dd.MM.yyyy HH:mm'});
  formatter.format(data, 0);
  chart.draw(data, options);

  var chart1 = new google.visualization.LineChart(document.getElementById('curve_chart1'));
  var formatter1 = new google.visualization.DateFormat({pattern: 'dd.MM.yyyy HH:mm'});
  formatter1.format(data1, 0);
  chart1.draw(data1, options1);
}

setInterval(() => { chart(), drawChart() }, 5000);