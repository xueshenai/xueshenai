//--------------------------------------------------------
 "use strict";
//--------------------------------------------------------





 function appProc ()
 {
 var par,grp,jo,pkt,obj;
 var int16Array;
 var float32Array,i;
 var sampleLength,sample;
 var pp;

 switch(aa.main_state.stage)
  {
  case 0:
  app.my_id=getOrCreateUUID();
  app.ei=aa.envInfoGet();
  loadSounds();
  guixInit(guixCallback);
  aa.mainStageSet(100);
  break;



  case 100:
  if(app.guix.is_ready!=true)      { break; }
  if(app.guix.group_ray.length==0) { break; }
  if(aa.main_state.initial_click!=true) { break; }
  aa.mainStageSet(200);
  break;




  case 200:
  for(jo=0;jo<30;jo++)
   {
   if(app.cli)
    {
    clientStatus(app.cli);
    if((pkt=clientRead(app.cli))==null) { break; }
    obj=JSON.parse(pkt);
    switch(obj.ev)
     {
     case "fis":
     achunks_got++;
     RECYCLABLE_INT16_VIEW=new Int16Array(obj.by);
     sampleLength=RECYCLABLE_INT16_VIEW.length;
     if(RECYCLABLE_FLOAT32_BUFFER.length<sampleLength)
      {
      RECYCLABLE_FLOAT32_BUFFER=new Float32Array(sampleLength);
      }
     for(i=0;i<sampleLength;i++)
      {
      sample=RECYCLABLE_INT16_VIEW[i];
      //csample<<=2;
      RECYCLABLE_FLOAT32_BUFFER[i]=sample<0?(sample/32768.0):(sample/32767.0);
      }
     playbackNode.port.postMessage(RECYCLABLE_FLOAT32_BUFFER.slice(0,sampleLength));
     RECYCLABLE_INT16_VIEW=null;
     break;



     case "fur":
     next_url=obj.url;
     console.log("url of uploaded pic "+next_url);
     next_url=null;
     break;
     }
    }
   }
  //if(jo>2) { console.log("jo="+jo); }


  if((grp=aa.guiGroupGetById("main_canvas"))==null) { aa.debugAlert("wedw"); }
  par=guixEqRead(app.guix.eq);
  //if(par!=null)   {   console.log(par.spot.sid+"  during chapter "+grp.vars.chapter);   }

  switch(grp.vars.chapter)
   {
   case 0:
   if(par!=null)
    {
    if(par.spot.sid==2024)
     {
     guixChapterSet("main_canvas",10);
     break;
     }
    }
   break;

   case 10:
   break;

   case 15:
   clientStatus(app.cli);
   if(app.cli.stage==666)
    {
    badSound();
    aa.envReload(true,1200);
    break;
    }
   if(par!=null)
    {
    if(par.spot.sid==2025)
     {
     badSound();
     aa.envReload(true,1200);
     break;
     }
    }
   if(app.cli.stage==1200)
    {
    guixChapterSet("main_canvas",20);
    break;
    }
   break;

   case 20:
   clientStatus(app.cli);
   if(app.cli.stage==666)
    {
    badSound();
    aa.envReload(true,1200);
    break;
    }

   if(par!=null)
    {
    if(par.spot.sid==2026)
     {
     badSound();
     aa.envReload(true,1200);
     break;
     }
    }
   break;


   }
  break;
  }
 profilerYield();
 }






