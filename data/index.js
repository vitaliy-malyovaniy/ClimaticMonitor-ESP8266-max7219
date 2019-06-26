var xmlHttp=createXmlHttpObject();

function createXmlHttpObject() {
    if (window.XMLHttpRequest) {
        xmlHttp0 = new XMLHttpRequest();
    } else {
        xmlHttp0 = new ActiveXObject('Microsoft.XMLHTTP');
    }
    return xmlHttp0;
}

function timer() {
    if(xmlHttp.readyState==0 || xmlHttp.readyState==4){
        xmlHttp.open('GET', "/config.live.json", true);
        xmlHttp.send(null);
        xmlHttp.onload = function(e) {
            data3=JSON.parse(xmlHttp.responseText);
            document.getElementById("timer").innerText = data3.timerRun;
        }
    }
}

function termo() {
    if(xmlHttp.readyState==0 || xmlHttp.readyState==4){
        xmlHttp.open('GET', "/sensors.json", true);
        xmlHttp.send(null);
        xmlHttp.onload = function(e) {
           sensorsResponse=JSON.parse(xmlHttp.responseText);
            document.getElementById("termo").innerText = sensorsResponse.termo;
            document.getElementById("humin").innerText = sensorsResponse.humin;
            if (sensorsResponse.termo>27){
                document.getElementById('termo').style.color = 'red';
            }else if (sensorsResponse.termo<19){
                document.getElementById('termo').style.color = 'blue';
            }else {
                document.getElementById('termo').style.color = 'black';
        }
      }
    }
}


// http://localhost:3000/config.live.json
// http://localhost:3000/configs.json
function load(){
  console.log("Ready state xmlHttp in function load: " + xmlHttp.readyState);
 if(xmlHttp.readyState==0 || xmlHttp.readyState==4){
  xmlHttp.open('GET', "/configs.json", true);
  xmlHttp.send(null);
  xmlHttp.onload = function(e) {
   jsonResponse=JSON.parse(xmlHttp.responseText);
   loadBlock();
  }
 }
 return console.log("Function Load was down...");
}

function loadBlock() {
 data2 = JSON.parse(xmlHttp.responseText);
 data = document.getElementsByTagName('body')[0].innerHTML;
 var new_string;
for (var key in data2) {
 new_string = data.replace(new RegExp('{{'+key+'}}', 'g'), data2[key]);
 data = new_string;
}
 document.getElementsByTagName('body')[0].innerHTML = new_string;
//  handleServerResponse();
}

function val(id){
 var v = document.getElementById(id).value;
 return v;
}
function send_request(submit,server){
 request = new XMLHttpRequest();
 request.open("GET", server, true);
 request.send();
 save_status(submit,request);
}
function save_status(submit,request){
 old_submit = submit.value;
 request.onreadystatechange = function() {
  if (request.readyState != 4) return;
  submit.value = request.responseText;
  setTimeout(function(){
   submit.value=old_submit;
   submit_disabled(false);
  }, 1000);
 }
 submit.value = 'Подождите...';
 submit_disabled(true);
}
function submit_disabled(request){
 var inputs = document.getElementsByTagName("input");
 for (var i = 0; i < inputs.length; i++) {
  if (inputs[i].type === 'submit') {inputs[i].disabled = request;}
 }
}
function toggle(target) {
 var curVal = document.getElementById(target).className;
 document.getElementById(target).className = (curVal === 'hidden') ? 'show' : 'hidden';
}


setInterval(() => { termo()}, 2000);