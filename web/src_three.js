//--------------------------------------------------------
 "use strict";
//--------------------------------------------------------
 var vvideo;
 var playbackNode;
 var achunks_got=0;
 var currentStream=null;
 var useFrontCamera=false;
 var next_url=null;
//--------------------------------------------------------



 async function startBidirectionalPCMStreaming (sty)
 {
 var soso,i,s,val,k;
 var serializeArray;
 var float32Buffer;
 var bufferLength;
 var int16Buffer,ss;
 ///
 var textString,binaryData,textEncoder,textBytes;

 ss=Math.floor(Date.now()/100000);

 const audioContext=new AudioContext({sampleRate:16000});
 if(audioContext.state==='suspended') {  await audioContext.resume();  }
 await audioContext.audioWorklet.addModule('playback-processor.js?'+ss);
 playbackNode=new AudioWorkletNode(audioContext,'playback-processor');
 playbackNode.connect(audioContext.destination);

 const stream=await navigator.mediaDevices.getUserMedia({
 audio: { echoCancellation:true,noiseSuppression:true,autoGainControl:true,channelCount:1 },
 //audio: { echoCancellation:true,noiseSuppression:false,autoGainControl:true,channelCount:1 },
 video:false
 });

 const source=audioContext.createMediaStreamSource(stream);
 await audioContext.audioWorklet.addModule('pcm-processor.js?'+ss);
 const pcmWorkletNode=new AudioWorkletNode(audioContext,'pcm-processor');
 source.connect(pcmWorkletNode);

 pcmWorkletNode.port.onmessage=(event) =>
  {
  if(event.data.type==='AUDIO_DATA')
   {
   float32Buffer=event.data.buffer;
   bufferLength=float32Buffer.length;
   int16Buffer=new Int16Array(bufferLength);
   for(i=0;i<bufferLength;i++)
    {
    val=float32Buffer[i];
    s=val<-1.0?-1.0:(val>1.0?1.0:val);
    int16Buffer[i]=s<0?s*0x8000:s*0x7FFF;
    }
   if(app.cli!=undefined&&app.cli!=null)
    {
    if(app.cli.stage>1000)
     {
     soso={};
     soso.magic=1234;
     soso.ev="aud";
     //soso.pcm=int16Buffer;
     //clientWrite(app.cli,1,soso);
     serializeArray=new Array(bufferLength);
     for(k=0;k<bufferLength;k++)     {     serializeArray[k]=int16Buffer[k];     }
     soso.by=serializeArray;
     clientWrite(app.cli,1,soso);



    soso=null;
    }
   }
  }
 };
 }


//---------------------------------------------------------



 function loadSounds ()
 {
 app.soundEffect=new Audio("./sounds/nikon.mp3");
 app.soundEffect2=new Audio("./sounds/good.mp3");
 app.soundEffect3=new Audio("./sounds/bad.mp3");
 }



 function nikonSound ()
 {
 app.soundEffect.play()
  .then(() => { })//console.log("Audio playing successfully."); })
  .catch(error => {  console.error("Playback failed due to browser policies:", error);  });
 }


 function goodSound ()
 {
 app.soundEffect2.play()
  .then(() => { })//console.log("Audio playing successfully."); })
  .catch(error => {  console.error("Playback failed due to browser policies:", error);  });
 }




 function badSound ()
 {
 app.soundEffect3.play()
  .then(() => { })//console.log("Audio playing successfully."); })
  .catch(error => {  console.error("Playback failed due to browser policies:", error);  });
 }

