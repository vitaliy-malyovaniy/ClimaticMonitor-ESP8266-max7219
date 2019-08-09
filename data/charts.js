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

function chart(){
  if(xmlHttp.readyState==0 || xmlHttp.readyState==4){
      xmlHttp.open('GET', "/graf.json", true);
      xmlHttp.send(null);
      xmlHttp.onload = function(e) {
        const chartResponse=JSON.parse(xmlHttp.responseText);
          for (let i=0; i<dataShow.length; i++){
            dataShow[i][1] = +chartResponse.data[i];
          }
      }
  }
}

chart();

function drawChart() {
var data = new google.visualization.DataTable();
// data.addColumn('string', 'date');
data.addColumn('number', 'Day');
data.addColumn('number', 'CO2, ppm');
// data.addColumn('number', 'TOV, ppb');
// data.addColumn('number', 'Termo, C');
data.addRows(dataShow);

const options = {
    width: '100%',
    title: 'Climatic monitor: Level CO2',
    // curveType: 'function',
    legend: { position: 'bottom' },
    vAxis: {
      title: 'CO2',
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

  var chart = new google.visualization.LineChart(document.getElementById('curve_chart'));
  var formatter = new google.visualization.DateFormat({pattern: 'dd.MM.yyyy HH:mm'});
  formatter.format(data, 0);
  chart.draw(data, options);
}

setInterval(() => { chart(), drawChart() }, 5000);