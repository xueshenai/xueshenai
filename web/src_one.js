//--------------------------------------------------------
 "use strict";
//--------------------------------------------------------
 var cfg_profiler_use=0;
 var cfg_profiler_hz=1.0;
//--------------------------------------------------------
 var cfg_app_version="3.1911";
 var cfg_app_speed=40;
//--------------------------------------------------------
 window.addEventListener("unhandledrejection",function(reason) { });
//--------------------------------------------------------
 var app=aa.main_vars.app;
//---------------------------------------------------------
 window.onload=function() {  aa.mainStart(cfg_app_version,cfg_app_speed,appProc); aa.mainRun(); };
//---------------------------------------------------------

 var RECYCLABLE_INT16_VIEW = null;
 var RECYCLABLE_FLOAT32_BUFFER = new Float32Array(4096); // Allocates a baseline reusable buffer once on boot

//---------------------------------------------------------


 function profilerYield ()
 {
 var sec,hit,lines,i,j;
 if(cfg_profiler_use&&aa_profiler.is_started==false)  {  aaProfilerStart();  }
 sec=aa.main_state.cycle/(1000/(1000/cfg_app_speed));
 hit=false;
 if(app.hz_sec==undefined) { app.hz_sec=0; }
 if(sec>(cfg_profiler_hz+app.hz_sec+1)) { hit=true;  app.hz_sec+=(cfg_profiler_hz+1); }
 if(cfg_profiler_use&&aa_profiler.is_started&&hit==true)
  {
  lines=aaProfilerDump(0,100,0,20000000,1,1,0);
  if(lines!=false&&lines.length>2)
   {
   console.log("---");
   for(i=0;i<lines.length;i++)
    {
    if(i==0||((i+1)==lines.length)) { continue; }
    j=15+i;
    console.log(lines[i]);
    }
   }
  }
 }


//---------------------------------------------------------

 function getOrCreateUUID              ()
 {
 const key='app_uuid';
 let uuid=localStorage.getItem(key);
 if (!uuid) {  uuid=crypto.randomUUID();   localStorage.setItem(key,uuid);  }
 return uuid;
 }

//---------------------------------------------------------




 function clientNew (address)
 {
 var obj={};
 obj.type="client";
 obj.show_bug=true;
 obj.stage=1000;
 obj.sock_handle=0;
 obj.sock_status=null;
 obj.sock_obj=null;
 obj.sock_xfwd="";
 obj.close_msg_shown=false;
 obj.error_msg_shown=false;
 obj.pkt_in_ray=[];

 // OPTIMIZATION: Track entries using a static read pointer instead of mutating the array memory envelope
 obj.read_index=0;

 obj.tot_pkts_sent=0;
 obj.tot_pkts_read=0;
 obj.address=address;
 obj.vars={};
 obj.sock_handle=aa.socketCreate(obj.address);
 if(obj.sock_handle==0) { aa.debugAlert("ff");  }
 ///aa.socketYield(obj.sock_handle);
 obj.sock_obj=aa.socketGet(obj.sock_handle);
 obj.sock_status=aa.socketStatus(obj.sock_handle);
 return obj;
 }





 function clientDelete (clientobj)
 {
 if(clientobj==null)          { return false; }
 if(clientobj.type!="client") { return false; }
 if(clientobj.sock_handle!=0) { aa.socketDestroy(clientobj.sock_handle); }
 clientobj.sock_handle=0;
 clientobj.sock_status=null;
 clientobj.sock_obj=null;
 clientobj.pkt_in_ray=[];
 clientobj.vars={};
 clientobj={};
 clientobj=null;
 return true;
 }




 function clientRead (clientobj)
 {
 var ret,pkt;
 if((ret=clientStatus(clientobj))!=true) { return null; }
 if(clientobj.read_index >= clientobj.pkt_in_ray.length)
  {
  if(clientobj.pkt_in_ray.length > 256)
   {
   clientobj.pkt_in_ray = [];
   clientobj.read_index = 0;
   }
  return null;
  }
 pkt=clientobj.pkt_in_ray[clientobj.read_index];
 clientobj.pkt_in_ray[clientobj.read_index] = null;
 clientobj.read_index++;
 return pkt;
 }





 function clientWrite (clientobj,sfy,pkt)
 {
 var ret,sai;
 if((ret=clientStatus(clientobj))!=true) {  return false; }
 if(sfy) { sai=JSON.stringify(pkt); aa.socketWrite(clientobj.sock_handle,sai);  }
 else    { aa.socketWrite(clientobj.sock_handle,pkt);  }
 clientobj.tot_pkts_sent++;
 return true;
 }






 function clientStatus (clientobj)
 {
 var pkt,go,jsp,grp,hihi,sai;

 if(clientobj==null)          { return false;  }
 if(clientobj.type!="client") { return false;  }
 if(clientobj.sock_handle==0) { return false;  }
 ///aa.socketYield(clientobj.sock_handle);
 clientobj.sock_obj=aa.socketGet(clientobj.sock_handle);
 clientobj.sock_status=aa.socketStatus(clientobj.sock_handle);

 if(clientobj.sock_status.is_closed==true&&clientobj.close_msg_shown==false)
  {
  badSound();
  console.log("cli closed");
  aa.envReload(true,300);
  clientobj.close_msg_shown=true;
  }

 if(clientobj.sock_status.is_error==true&&clientobj.error_msg_shown==false)
  {
  console.log("cli err");
  clientobj.stage=666;
  clientobj.error_msg_shown=true;
  }

 if(clientobj.sock_status.is_error==true||clientobj.sock_status.is_closed==true)
  {
  if(clientobj.error_msg_shown===false)
   {
   //guixChapterSet("main_canvas",666);
   }
  return aa.ret.FAILED;
  }

 switch(clientobj.stage)
  {
  case 666:
  break;

  case 1000:
  if(clientobj.sock_status.is_open!==true) { break; }
  ///console.log("opened");
    goodSound();
  hihi={};
  hihi.magic=1234;
  hihi.ev="hey";
  hihi.my_id=app.my_id;
  sai=JSON.stringify(hihi);
  aa.socketWrite(clientobj.sock_handle,sai);
  clientobj.tot_pkts_sent++;

  clientobj.stage=1200;
  break;


  case 1200:
  for(go=0;go<4;go++)
   {
   //aa.socketYield(clientobj.sock_handle);
   if((pkt=aa.socketRead(clientobj.sock_handle))==null) { break; }
   if(typeof pkt==="string")
    {
    jsp=JSON.parse(pkt);
    if(clientobj.sock_xfwd==="")  {  clientobj.sock_xfwd=jsp.val;   break;    }
    clientobj.tot_pkts_read++;
    clientobj.pkt_in_ray.push(pkt);
    }
   else
    {
    console.log("tot");
    console.log(pkt);
    }
   break;
   }
  return true;

  case 1500:
  break;
  }
 return false;
 }



//---------------------------------------------------------



