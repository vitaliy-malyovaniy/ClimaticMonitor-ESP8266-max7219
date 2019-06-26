var set_real_time;
//    function handleServerResponse(){
//     clearTimeout(set_real_time);
//     var res = jsonResponse.time.split(":");
//     real_time(hours=res[0],min=res[1],sec=res[2]);
//     document.body.style.backgroundColor="rgb("+jsonResponse.rgb+")";
//    }
//    function real_time(hours,min,sec) {
//    sec=Number(sec)+1;
//     if (sec>=60){min=Number(min)+1;sec=0;}
//     if (min>=60){hours=Number(hours)+1;min=0;}
//     if (hours>=24){hours=0};
//     document.getElementById("time").innerHTML = hours+":"+min+":"+sec;
//     set_real_time = setTimeout("real_time("+hours+","+min+","+sec+");", 1000);
//    }
   function load_time(submit){
    server = "/Time";
    send_request(submit,server);
    load();
   }

function setTimerOffState(submit){
    // формируем POST запрос
    server = "/set_timmer?varTimer="+val('timerSet');
    send_request(submit,server); 
    console.log("varTimer= " + val('timerSet'));
    // console.log("val('timerSet'): "+val('timerSet'));
}

   function set_ssid(submit){
    server = "/ssid?ssid="+val('ssid')+"&password="+encodeURIComponent(val('password'));
    send_request(submit,server);
    alert("Изменения вступят в силу после перезагрузки. Пожалуйста перезагрузите устройство.");
   }
   function set_ssdp(submit){
    server = "/ssdp?ssdp="+val('ssdp');
    console.log(server);
    send_request(submit,server);
    document.getElementById('ssdp_t').innerHTML = val('ssdp');
   }
   function pc_on(submit){
       console.log("PC ON");
       console.log(submit);
    server = "/pc_on?pc_on="+val('pcOn');
    console.log(server);
    send_request(submit,server);
    }
   function restart(submit,texts){
    if (confirm(texts)) {
	 server = "/restart?device=ok";
     send_request(submit,server);
     return true;
    } else {
     return false;
    }
   }