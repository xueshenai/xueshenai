//--------------------------------------------------------
 "use strict";
//--------------------------------------------------------



 function guixInit (cbfunc)
 {
 var s,i,face;
 app.guix={};
 app.guix.callBack=cbfunc;
 app.guix.is_ready=false;
 app.guix.group_ray=[];
 app.guix.font_ray=[];
 app.guix.fonts_ready=false;
 if(1)  {  app.guix.pointer={};   aa.pointerStart();   }
 if(1)  {  app.guix.keyboard={};  aa.keyboardStart();  }
 s=Math.floor(Date.now()/100000);
 app.guix.font_ray.push(aa.guiFontLoad("roboto","ttf","./fonts/roboto-regular.ttf?"+s));
 app.guix.font_ray.push(aa.guiFontLoad("lcd","woff","./fonts/lcd.woff?"+s));

/// app.guix.sprite=aa.spriteLoad("./gfx/allsprites.png?"+s);
 app.guix.sprite=aa.spriteLoad("./gfx/sprites.png?"+s);
 app.guix.logo=aa.imageLoaderNew("./gfx/xlogo192.png?"+s);
 //app.guix.logo=aa.imageLoaderNew("./gfx/56456.png?"+s);
 app.guix.eq=aa.queueCreate();
 //------
  app.guix.etc={}
  app.guix.etc.fnt=[];
  face="roboto";
  app.guix.etc.fnt[0]=guixFontSet(face,100,10);
  app.guix.etc.fnt[1]=guixFontSet(face,200,12);
  app.guix.etc.fnt[2]=guixFontSet(face,300,16);
  app.guix.etc.fnt[3]=guixFontSet(face,600,20);
  app.guix.etc.fnt[4]=guixFontSet(face,600,24);
  app.guix.etc.fnt[5]=guixFontSet(face,600,28);
  app.guix.etc.fnt[6]=guixFontSet(face,600,32);
  app.guix.etc.fnt[7]=guixFontSet(face,600,34);
  face="lcd";
  app.guix.etc.fnt[8]=guixFontSet(face,300,36);

  app.guix.etc.pen=[];
  app.guix.etc.pen[0]=aa.guiRgbaString(212,12,12,1.0);
  app.guix.etc.pen[1]=aa.guiRgbaString(234,34,34,1.0);
  app.guix.etc.pen[2]=aa.guiRgbaString(128,128,128,1.0);
  app.guix.etc.pen[3]=aa.guiRgbaString(212,212,212,1.0);
  app.guix.etc.pen[4]=aa.guiRgbaString(255,255,255,1.0);
  app.guix.etc.pen[5]=aa.guiRgbaString(190,50,50,1.0);
  app.guix.etc.pen[6]=aa.guiRgbaString(50,120,50,1.0);
  app.guix.etc.pen[7]=aa.guiRgbaString(50,50,190,1.0);
 //--

 aa.ifaceStart(guixIfaceProc);
 }




 function guixChapterSet (id,chap)
 {
 var grp;
 if((grp=aa.guiGroupGetById(id))==null) { alert("wedw"); }
 if(grp.vars.chapter==chap) { return true; }
 grp.vars.chapter=chap;
 guixNeeds(id,true,true);
 return true;
 }





 function guixWarmup (obj)
 {
 var c,f;

 if(app.guix.is_ready==true) { return true; }
 if(app.guix.fonts_ready!=true)
  {
  for(c=0,f=0;f<app.guix.font_ray.length;f++)
   {
   if(aa.guiFontStatus(app.guix.font_ray[f])==true) { c++; }
   }
  if(c==app.guix.font_ray.length)
   {
   app.guix.fonts_ready=true;
   }
  }

 if(app.guix.sprite.is_ready!=true)
  {
  aa.spriteStatus(app.guix.sprite);
  if(app.guix.sprite.is_ready)
   {
   //console.log(app.guix.sprite.sheet_map.length);
   }
  }
 if(app.guix.logo.is_success!=true)
  {
  if(app.guix.logo.is_failed==true) alert("assas");
  //console.log(app.guix.logo.is_failed);
  return false;
  }
 if(app.guix.sprite.is_ready!=true||app.guix.fonts_ready!=true) { return false;  }
 //if(app.guix.is_ready!=true) alert("damn");

 app.guix.is_ready=true;
 return false;
 }





 function guixIfaceProc (obj)
 {
 var z,c,grp;

 if(guixWarmup(obj)!=true) { return false; }
 if(app.guix.group_ray.length==0)
  {
  guixCreate("canvas","main_canvas",8000);
  guixCreate("video","main_video",8002);
  guixCreate("canvas","main_canst",8004);

  }
 app.is_focus=obj.is_focus;
 guixPtrYield(obj);
 c=app.guix.group_ray.length;
 for(z=0;z<c;z++)
  {
  grp=app.guix.group_ray[z];
  if(grp.obj.id)
   {
   if(grp.obj.id=="main_canvas")
    {
    app.guix.callBack(obj,grp);
    }
   }
  }
 return true;
 }





 function guixCreate (type,id,zi)
 {
 var han,grp,rgb,pal;

 if((han=aa.guiCreate(type,id,zi))==0)  { alert("jjr"); }
 if((grp=aa.guiGroupGetById(id))==null) { alert("wedw"); }
 guixNeeds(id,true,true);
 grp.vars.chapter=0;
 grp.vars.probe=null;
 app.guix.group_ray.push(grp);
 if(type=="video")
  {
  grp.dom.playsInline=true;
  grp.dom.setAttribute('playsinline','');
  grp.dom.setAttribute('webkit-playsinline','');
  }
 //console.log(grp.obj.id);
//  aa.guiCssOutlineSet(grp.han,3,-4,"dashed",aa.guiRgbaString(aa.numRandValue(120,230),aa.numRandValue(0,200),aa.numRandValue(0,200),1));
 return grp;
 }





 function guixNeeds (id,paintstate,drawstate)
 {
 var grp;
 if((grp=aa.guiGroupGetById(id))==null) { alert(id); return false;  }
 if(paintstate!=null) { grp.vars.needs_paint=paintstate; }
 if(drawstate!=null)  { grp.vars.needs_draw=drawstate;   }
 return true;
 }












/*
 function initHorizontalInertialScroll(scrollContainer)
 {
    let startX = 0;
    let startTime = 0;
    let lastX = 0;
    let lastTime = 0;
    let velocity = 0;
    let currentX = 0; // Tracks virtual position including out-of-bounds scroll
    let animationFrameId = null;

    // Physics Configuration
    const FRICTION = 0.95;          // Glide decay rate
    const VELOCITY_MULT = 1.5;      // Flick sensitivity multiplier
    const BOUNCE_ATTENUATION = 0.15; // How stiff the boundary wall feels (lower = stiffer)
    const SNAP_SPEED = 0.15;        // How fast it snaps back to 0 or max scroll

    // Helper to find the maximum allowed horizontal scroll
    function getMaxScroll()
    {
        return scrollContainer.scrollWidth - scrollContainer.clientWidth;
    }

    function handleStart(e)
    {
        cancelAnimationFrame(animationFrameId);
        velocity = 0;
        const pageX = e.touches ? e.touches.pageX : e.pageX;
        startX = pageX;
        lastX = pageX;
        currentX = scrollContainer.scrollLeft;
        startTime = Date.now();
        lastTime = startTime;
    }

    function handleMove(e)
    {
        if (!startTime) return;
        const pageX = e.touches ? e.touches.pageX : e.pageX;
        const currentTime = Date.now();
        let deltaX = pageX - lastX;
        const deltaTime = currentTime - lastTime;
        const maxScroll = getMaxScroll();
        // Apply resistance if the user is physically pulling out of bounds
        if (currentX < 0 || currentX > maxScroll) {            deltaX *= BOUNCE_ATTENUATION;        }
        currentX -= deltaX;
        // Update the physical DOM element position
        scrollContainer.scrollLeft = currentX;
        // Calculate velocity (pixels/ms)
        if (deltaTime > 0) {            velocity = (deltaX / deltaTime) * VELOCITY_MULT;        }
        lastX = pageX;
        lastTime = currentTime;
    }

    function handleEnd()
    {
        if (!startTime) return;
        startTime = 0;
        animatePhysics();
    }

    function animatePhysics()
    {
        const maxScroll = getMaxScroll();
        // CASE 1: Out of bounds on the LEFT (Over-scrolled past 0)
        if (currentX < 0)
        {
            velocity = 0; // Kill glide momentum
            currentX += (0 - currentX) * SNAP_SPEED; // Elastic pull back to 0
            scrollContainer.scrollLeft = currentX;
            if (Math.abs(currentX) > 0.5) {   animationFrameId = requestAnimationFrame(animatePhysics);     }
            else {                scrollContainer.scrollLeft = 0;  }  // Hard reset to exactly zero
        }
        // CASE 2: Out of bounds on the RIGHT (Over-scrolled past maximum)
        else
        if (currentX > maxScroll)
        {
            velocity = 0; // Kill glide momentum
            currentX += (maxScroll - currentX) * SNAP_SPEED; // Elastic pull back to max
            scrollContainer.scrollLeft = currentX;
            if (Math.abs(currentX - maxScroll) > 0.5) {   animationFrameId = requestAnimationFrame(animatePhysics);   }
            else {                scrollContainer.scrollLeft = maxScroll; } // Hard reset to max
        }
        // CASE 3: In bounds, carrying out normal friction glide
        else
        {
            velocity *= FRICTION;
            currentX -= velocity;
            scrollContainer.scrollLeft = currentX;
            // Keep animating if we are moving fast or if a massive flick pushed us out of bounds this frame
            if (Math.abs(velocity) > 0.1 || currentX < 0 || currentX > maxScroll) {  animationFrameId = requestAnimationFrame(animatePhysics);            }
        }
    }

    // Touch events
    scrollContainer.addEventListener('touchstart', handleStart, { passive: true });
    scrollContainer.addEventListener('touchmove', handleMove, { passive: true });
    scrollContainer.addEventListener('touchend', handleEnd, { passive: true });

    // Desktop Mouse events
    scrollContainer.addEventListener('mousedown', handleStart);
    window.addEventListener('mousemove', handleMove);
    window.addEventListener('mouseup', handleEnd);
}



// --- Usage ---
const track = document.getElementById('horizontalSlider');
initHorizontalInertialScroll(track);





*/




 function guixPtrYield (obj)
 {
 var rat,x0,y0,x1,y1,etc;
 var mzi,el,grp,area,spot,mod,div,han;
 aaProfilerHit("ptryield");
 while(1)
  {
  if((rat=aa.pointerRead())==null)  { break; }
  if(rat.event.type=="pointerdown"||rat.event.type=="pointerup"||rat.event.type=="pointerout")
   {
   //console.log(rat.event.type);
   }
  x0=rat.event.pageX;
  y0=rat.event.pageY;
  han=0;
  grp=null;
  area=null;
  el=aa.guiElementFromPoint(x0,y0,0,10000);
  if(el>0)
   {
   han=el;
   grp=aa.guiGroupGet(han);
   area=aa.guiCssAreaGet(han);
   }
  if(rat.event.type=="pointermove") { break;}
  if(rat.event.type=="pointerup")
   {
   if(grp==null) { break; }
   if(han==0) { break; }
   if(area!=null)
    {
    x1=x0-area.left;
    y1=y0-area.top;
    spot=aa.guiSpotMatch(el,x0,y0);
    if(spot!=null)
     {
     etc={};
     etc.event="spotclicked";
     etc.rat=rat;
     etc.mxy={x1,y1};
     etc.spot=spot;
     etc.area=area;
     aa.queueWrite(app.guix.eq,JSON.stringify(etc));
     }
    }
   }
  break;
  }
 }





 function guixEqRead (obj)
 {
 var msg,par,grp;
 aaProfilerHit("eqread");
 while(1)
  {
  if((msg=aa.queueRead(app.guix.eq))==null) { break; }
  par=JSON.parse(msg);
  //if(par.event!="spotclicked") { break; }
  //if(par.spot.id!="main_canvas") { break; }
  if((grp=aa.guiGroupGetById(par.spot.id))==null) { alert("4wwwwww"); }
  //console.log(par);
  return par;
  }
 return null;
 }




 function guixDisplaySet (id,disp)
 {
 var grp;
 //aaProfilerHit("displayset");
 if((grp=aa.guiGroupGetById(id))==null) { alert(); return null; }
 if(disp==0)  {  grp.obj.dom.style.display="none";  }
 else         {  grp.obj.dom.style.display="inline-block";  }
 return true;
 }





 function guixAssertion (grp,disp,retina,opa,x,y,w,h,dwid,dhit,wmul,hmul)
 {
 var req,chg,ps,ds;
 grp.vars.probe=aa.guiProbeGet(grp.han);

 //aaProfilerHit("assertion");
 ///console.log(grp.vars.probe);
 ps=false;
 ds=false;

 req={};
 req.type="guirequirments";
 req.disp=disp;
 req.retina=retina;
 req.opa=opa;
 req.x=x;//>>0;
 req.y=y;//>>0;
 req.w=w;//>>0;
 req.h=h;//>>0;
 req.domw=dwid;//>>0;
 req.domh=dhit;//>>0;
 req.wmul=wmul;//>>0;
 req.hmul=hmul;//>>0;

 chg=aa.guiProbeCompare(grp.vars.probe,req.disp,req.retina,req.opa,req.x,req.y,req.w,req.h,req.domw,req.domh,req.wmul,req.hmul);
 if(chg<=0)
  {
  if(chg<0) alert("chg="+chg);
  return chg;
  }

 aa.guiApply(grp.vars.probe.handle,req.disp,req.retina,req.opa,req.x,req.y,req.w,req.h,req.domw,req.domh,req.wmul,req.hmul);
 grp.vars.probe=aa.guiProbeGet(grp.vars.probe.handle);

 if(chg>=16) { ps=true; }
 if(chg>=1)  { ds=true; }
 if(chg==1) alert("1");

 guixNeeds(grp.obj.id,ps,ds);
 return chg;
 }




 function guixFontSet (fidx,weight,px)
 {
 var fnt;
 fnt=""+weight+" "+px+"px ";
 if(isNaN(fidx))    {  fnt+=""+fidx;  return fnt;  }
 if(fidx<0)                         { return null; }
 if(fidx>=app.guix.font_ray.length) { return null; }
 fnt+=""+app.guix.font_ray[fidx].name;
 return fnt;
 }




 function guixFontFit (id,fidx,weight,txt,minx)
 {
 var grp,fnt,mes,ffs;
 if((grp=aa.guiGroupGetById(id))==null) { alert("sswe"); return null; }
 ffs=10;
 while(1)
  {
  fnt=guixFontSet(fidx,weight,ffs);
  mes=aa.guiCanvasFontMeasure(grp.han,fnt,txt);
  if(mes.width<minx) { ffs++; continue; }
  if(mes.width>minx) { ffs--; }
  //console.log("ffs="+ffs);
  break;
  }
 return fnt;
 }



//--------------------------------------------------------
//---------------------------------------------------



 function guixBigButtonEx (obj,grp,x,y,w,h,spid,lw,bc,fc,txtfnt,txtlc,txtbpen,txtfpen,txt)
 {
 aa.guiCanvasRounded2(grp.han,x,y,w,h,h>>1,lw,bc,fc);
 aa.guiCanvasTextEx(grp.han,x,y+4,w,h,"c","c",txtlc,txtbpen,txtfpen,txtfnt,1,txt);
 if(spid!=0)  {  aa.guiSpotAdd(grp.han,spid,x,y,w,h,1,2,3);  }
 }



 function guixMainLogo (obj,grp,x,y,w,h,spid)
 {
 var iw,ih;
 iw=app.guix.logo.img.width;
 ih=app.guix.logo.img.height;
 //aa.spritePaintByIndex(app.guix.sprite,grp.obj.id,60,x,y,w+4,h+4,0,0,0);
 aa.guiCanvasImageDraw(grp.han,0,0,iw,ih,x+4,y+4,w-8,h-8,app.guix.logo.img)
 aa.guiSpotAdd(grp.han,spid,x,y,w,h,1,2,3);
 }




 function xywh (obj,x,y,w,h)
 {
 if(obj===undefined) {  obj={};  }
 obj.x=x;
 obj.y=y;
 obj.w=w;
 obj.h=h;
 return obj;
 }


 function guixGetUseful (obj,grp)
 {
 var usf;
 usf={};
 usf.ww=obj.this_disp.win_wid>>0;
 usf.wh=obj.this_disp.win_hit>>0;
 usf.cw=grp.obj.ctx.canvas.width>>0;
 usf.ch=grp.obj.ctx.canvas.height>>0;
 usf.dw=grp.dom.width>>0;
 usf.dh=grp.dom.height>>0;
 return usf;
 }





 function guixSexyButton (obj,grp,x,y,w,h,spid,txtfnt,txt)
 {
 var us,zz,x,y,w,h;
 us=guixGetUseful(obj,grp);
 grp.obj.ctx.save();
 grp.obj.ctx.globalAlpha=0.2;
 aa.spritePaintByIndex(app.guix.sprite,grp.obj.id,60,x+8,y+8,w+4,h+4,0,0,0);
 grp.obj.ctx.globalAlpha=0.3;
 aa.spritePaintByIndex(app.guix.sprite,grp.obj.id,60,x,y,w+4,h+4,0,0,0);
 grp.obj.ctx.globalAlpha=0.7;
 if(spid==2024)  {  guixBigButtonEx(obj,grp,x,y,w,h,spid,3,aa.guiRgbaString(10,24,22,1),null,txtfnt,1,aa.guiRgbaString(210,24,22,1),aa.guiRgbaString(220,24,2,1),txt);  }
 else            {  guixBigButtonEx(obj,grp,x,y,w,h,spid,3,aa.guiRgbaString(10,24,22,1),null,txtfnt,1,aa.guiRgbaString(210,24,22,1),aa.guiRgbaString(20,184,2,1),txt);  }
 grp.obj.ctx.restore();
 }




 function guixBigLogo  (obj,grp)
 {
 var us,zz,i;
 us=guixGetUseful(obj,grp);
 zz={};
 xywh(zz,20,30,60,60);
 guixMainLogo(obj,grp,zz.x,zz.y,zz.w,zz.h,0);
 xywh(zz,75,50,200,24);
 aa.guiCanvasTextEx(grp.han,zz.x,zz.y,zz.w,zz.h,"l","t",0,app.guix.etc.pen[1],app.guix.etc.pen[7],app.guix.etc.fnt[8],1,"ueshen");
 }





 function guixMiddleButtonAndLogo (obj,grp,spid,txt)
 {
 var us,zz;

 zz={};
 us=guixGetUseful(obj,grp);
 aa.guiCanvasFill(grp.han,0,0,us.ww,us.wh,aa.guiRgbaString(255,255,255,1.0));
 guixBigLogo(obj,grp);
 xywh(zz,(us.ww>>1)-100,us.wh>>1,200,60);
 guixSexyButton(obj,grp,zz.x,zz.y,zz.w,zz.h,spid,app.guix.etc.fnt[7],txt);
 }





 function guixCallback (obj,grp)
 {
 var chg,us;

 us=guixGetUseful(obj,grp);
 chg=guixAssertion(grp,"inline-block",true,1.0,0,0,us.ww,us.wh,us.ww,us.wh,1,1);
 if(chg==0)  {  }


 if((grp.vars.needs_paint==true||grp.vars.needs_draw==true)||chg>=1)
  {
  aa.guiSpotPurge(grp.han);
  grp.obj.ctx.globalAlpha=1.0;

  switch(grp.vars.chapter)
   {
   case 0:
   guixMiddleButtonAndLogo(obj,grp,2024,"Connect");
   break;


   case 10:
   guixMiddleButtonAndLogo(obj,grp,2025,"Cancel");
   app.cli=clientNew("wss://xueshen.online/wss/");
   startBidirectionalPCMStreaming(app.cli);
   grp.vars.chapter=15;
   break;

   case 15:
   guixMiddleButtonAndLogo(obj,grp,2025,"Cancel");
   break;


   case 20:
   clientStatus(app.cli);
   guixMiddleButtonAndLogo(obj,grp,2026,"Hangup");
   break;

   }
  }
 guixNeeds(grp.obj.id,false,false);
 }






