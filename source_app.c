/*-----------------------------------------------------------------------*/
 #include "source_hdr.h"
/*-----------------------------------------------------------------------*/
 _app app={.magic=0};
/*-----------------------------------------------------------------------*/




 V aaMain                              (V)
 {
 B ret;
 H i;

 appStart();
 while(appYield()==YES)
  {
  if(app.do_restart)
   {
   aaRestart();
   if(app.do_restart==2) { appStop();  }
   else                  { appStop(); }
   aaQuit();
   return;
   }
  switch(aa_stage)
   {
   case 0:
   for(i=0;i<aaElementCount(app.voxlev_timeline[0]);i++)
    {
    voxlevPush(0,12.0);
    voxlevPush(1,12.0);
    }
   aaStageSet(10);
   break;


   case 10:
   if(aaMathRand32(0,100)==0)    {    appLabel(0,"%s",app.c_time);    }
   //if(aaMathRand32(0,40)==0)    {   appLog("%I64d",aaMsRunning());    }
   ret=appCpuViz();

   ///if(app.the_aisesh==NULL) { break; }
   if(ret!=RET_YES) { break; }

   voxlevPaint(0,140,10);
   voxlevPaint(1,500,10);
   break;
   }
  }
 appStop();
 }



//===================================================
//===================================================
//===================================================




 B appKonfig                           (VP filename)
 {
 B ret;
 _fileunit fun;
 H li,fi,sl,jj;
 B tkey[_1K];
 B tval[_32K];
 D tdub;
 H have;

 app.kfg.magic=1234;
 appLog("loading kfg %s",filename);
 if((ret=aaFileUnitLoad(&fun,filename))!=YES) { oops; return ret; }
 fun.mem[fun.bytes]=NULL_CHAR;
 aaStringRemoveChars(fun.mem,0,CR_CHAR);
 aaStringRemoveChars(fun.mem,0,LF_CHAR);
 aaStringLen(fun.mem,&sl);
 fun.bytes=sl;
 appProfiler(0,1,1);
 if((ret=aaJsonToTextReader((H)fun.bytes,(VP)fun.mem,&app.kfg.tre))!=YES) { oops; }
 appLog("took %.5f",appProfiler(0,0,1));
 aaFileUnitRelease(&fun);
 if(ret!=RET_YES) { oops;  return ret; }
 for(li=0;li<app.kfg.tre.line_count;li++)
  {
  if((ret=appKonfigGet(li,tkey,tval,&tdub))!=YES) { oops; break;  }
  if(0) { appLog("%lu [%s] [%s]",li,tkey,tval); }
  }
 li=0;
 have=0;
 while(1)
  {
  //tdud=modf(tdub,&tdui);
  if(appKonfigFind(li,&fi,tkey,tval,&tdub,0,"app.speed")==RET_YES)   { have++;
   app.kfg.app_speed=(H)tdub;
   }
  if(appKonfigFind(li,&fi,tkey,tval,&tdub,0,"app.version")==RET_YES)   { have++;
   app.kfg.app_version=tdub;
   }
  if(appKonfigFind(li,&fi,tkey,tval,&tdub,0,"stun.host")==RET_YES)   { have++;
   aaStringUnQuote(tval,0,0);
   aaStringCopy(app.kfg.stun_host,tval);
   }
  if(appKonfigFind(li,&fi,tkey,tval,&tdub,0,"stun.match")==RET_YES)   { have++;
   aaStringUnQuote(tval,0,0);
   aaStringCopy(app.kfg.stun_match,tval);
   }
  if(appKonfigFind(li,&fi,tkey,tval,&tdub,0,"stun.pause")==RET_YES)   { have++;
   app.kfg.stun_pause=(H)tdub;
   }
  if(appKonfigFind(li,&fi,tkey,tval,&tdub,0,"twilio.sip.host")==RET_YES)   { have++;
   aaStringUnQuote(tval,0,0);
   aaStringCopy(app.kfg.twilio_sip_host,tval);
   }
  if(appKonfigFind(li,&fi,tkey,tval,&tdub,0,"twilio.sip.domain")==RET_YES)   { have++;
   aaStringUnQuote(tval,0,0);
   aaStringCopy(app.kfg.twilio_sip_domain,tval);
   }
  if(appKonfigFind(li,&fi,tkey,tval,&tdub,0,"twilio.sip.user")==RET_YES)   { have++;
   aaStringUnQuote(tval,0,0);
   aaStringCopy(app.kfg.twilio_sip_user,tval);
   }
  if(appKonfigFind(li,&fi,tkey,tval,&tdub,0,"twilio.sip.pass")==RET_YES)   { have++;
   aaStringUnQuote(tval,0,0);
   aaStringCopy(app.kfg.twilio_sip_pass,tval);
   }
  if(appKonfigFind(li,&fi,tkey,tval,&tdub,0,"twilio.sip.agent")==RET_YES)   { have++;
   aaStringUnQuote(tval,0,0);
   aaStringCopy(app.kfg.twilio_sip_agent,tval);
   }
  if(appKonfigFind(li,&fi,tkey,tval,&tdub,0,"translate.host")==RET_YES)   { have++;
   aaStringUnQuote(tval,0,0);
   aaStringCopy(app.kfg.translate_host,tval);
   }
  if(appKonfigFind(li,&fi,tkey,tval,&tdub,0,"deepgram.key")==RET_YES)   { have++;
   aaStringUnQuote(tval,0,0);
   aaStringCopy(app.kfg.deepgram_key,tval);
   }
  if(appKonfigFind(li,&fi,tkey,tval,&tdub,0,"deepgram.endpoint")==RET_YES)   { have++;
   aaStringUnQuote(tval,0,0);
   aaStringCopy(app.kfg.deepgram_endpoint,tval);
   }
  if(appKonfigFind(li,&fi,tkey,tval,&tdub,0,"deepgram.keepalive")==RET_YES)   { have++;
   app.kfg.deepgram_keepalive=(H)tdub;
   }
  if(appKonfigFind(li,&fi,tkey,tval,&tdub,0,"deepgram.defaults.model")==RET_YES)   { have++;
   aaStringUnQuote(tval,0,0);
   aaStringCopy(app.kfg.deepgram_defaults_model,tval);
   }
  if(appKonfigFind(li,&fi,tkey,tval,&tdub,0,"inworld.key")==RET_YES)   { have++;
   aaStringUnQuote(tval,0,0);
   aaStringCopy(app.kfg.inworld_key,tval);
   }

  if(appKonfigFind(li,&fi,tkey,tval,&tdub,0,"fish.key")==RET_YES)   { have++;
   aaStringUnQuote(tval,0,0);
   aaStringCopy(app.kfg.fish_key,tval);
   }
  if(appKonfigFind(li,&fi,tkey,tval,&tdub,0,"fish.endpoint")==RET_YES)   { have++;
   aaStringUnQuote(tval,0,0);
   aaStringCopy(app.kfg.fish_endpoint,tval);
   }
  if(appKonfigFind(li,&fi,tkey,tval,&tdub,0,"fish.defaults.model")==RET_YES)   { have++;
   aaStringUnQuote(tval,0,0);
   aaStringCopy(app.kfg.fish_defaults_model,tval);
   }
  if(appKonfigFind(li,&fi,tkey,tval,&tdub,0,"fish.defaults.temperature")==RET_YES)   { have++;
   app.kfg.fish_defaults_temperature=tdub;
   }
  if(appKonfigFind(li,&fi,tkey,tval,&tdub,0,"fish.defaults.voiceid")==RET_YES)   { have++;
   aaStringUnQuote(tval,0,0);
   aaStringCopy(app.kfg.fish_defaults_voiceid,tval);
   }
  if(appKonfigFind(li,&fi,tkey,tval,&tdub,0,"claude.key")==RET_YES)   { have++;
   aaStringUnQuote(tval,0,0);
   aaStringCopy(app.kfg.claude_key,tval);
   }
  if(appKonfigFind(li,&fi,tkey,tval,&tdub,0,"claude.endpoint")==RET_YES)   { have++;
   aaStringUnQuote(tval,0,0);
   aaStringCopy(app.kfg.claude_endpoint,tval);
   }
  if(appKonfigFind(li,&fi,tkey,tval,&tdub,0,"claude.defaults.model")==RET_YES)   { have++;
   aaStringUnQuote(tval,0,0);
   aaStringCopy(app.kfg.claude_defaults_model,tval);
   }
  if(appKonfigFind(li,&fi,tkey,tval,&tdub,0,"claude.defaults.temperature")==RET_YES)   { have++;
   app.kfg.claude_defaults_temperature=tdub;
   }
  if(appKonfigFind(li,&fi,tkey,tval,&tdub,0,"claude.defaults.max_tokens")==RET_YES)   { have++;
   app.kfg.claude_defaults_max_tokens=(H)tdub;
   }
  if(appKonfigFind(li,&fi,tkey,tval,&tdub,0,"claude.defaults.system_prompt")==RET_YES)   { have++;
   aaStringUnQuote(tval,0,0);
   aaStringCopy(app.kfg.claude_defaults_system_prompt,tval);
   }
  if(appKonfigFind(li,&fi,tkey,tval,&tdub,0,"server.max_calls")==RET_YES)   { have++;
   app.kfg.server_max_calls=(H)tdub;
   }
  if(appKonfigFind(li,&fi,tkey,tval,&tdub,0,"server.port")==RET_YES)   { have++;
   app.kfg.server_port=(W)tdub;
   }
  if(appKonfigFind(li,&fi,tkey,tval,&tdub,0,"voip.delay")==RET_YES)   { have++;
   app.kfg.voip_delay=(H)tdub;
   }
  if(appKonfigFind(li,&fi,tkey,tval,&tdub,0,"voip.frame_size")==RET_YES)   { have++;
   app.kfg.voip_frame_size=(H)tdub;
   }
  if(appKonfigFind(li,&fi,tkey,tval,&tdub,0,"voip.codec")==RET_YES)   { have++;
   aaStringUnQuote(tval,0,0);
   aaStringCopy(app.kfg.voip_codec,tval);
   }
  for(jj=0;jj<7;jj++)
   {
   if(appKonfigFind(li,&fi,tkey,tval,&tdub,0,"crank.c%i",jj)==RET_YES)   { have++;
    app.kfg.cx[jj]=(H)tdub;
    }
   }
  break;
  }
 if(have!=app.kfg.tre.line_count)
  {
  appLog("kfg have/count mismatch (%i,%i)",have,app.kfg.tre.line_count);
  return RET_FAILED;
  }

 //aaTextReaderDump(&app.kfg.tre,aaTextReaderProc);
 ///appLog("sizeof(_textpair)=%i  sizeof(fepe)=%i  elements=%i",sizeof(_textpair),sizeof(app.fepe),sizeof(app.fepe)/sizeof(_textpair));
 return RET_YES;
 }




 B appKonfigGet                        (H index,VP key,VP val,DP dub)
 {
 B ret;
 H chars,pos;
 B txt[_64K];
 D dv;
 BP bp;
 if(key) { aaStringNull(key); }
 if(val) { aaStringNull(val); }
 if(dub) { *dub=0.0; }
 if(index>=app.kfg.tre.line_count) { return RET_BOUNDS; }
 if((ret=aaTextReaderLineGet(&app.kfg.tre,index,&chars,txt))!=YES) { oops; return ret; }
 if(aaStringFindChar(txt,0,&pos,':',YES,0,YES)!=YES) { oof; return RET_FAILED; }
 bp=(BP)txt;
 if(key) { aaStringNCopy(key,bp,pos,YES); }
 if(val) { aaStringCopy(val,&bp[pos+1]);  }
 if(dub) { if(aaStringToDouble(&bp[pos+1],0,&dv)==YES) { *dub=dv; }  }
 return RET_YES;
 }



 B appKonfigFind                       (H index,HP found,VP key,VP val,DP dub,B partial,VP fmt,...)
 {
 B ret;
 H li;
 B tkey[_4K];
 B tval[_64K];

 aaVargsf32K(fmt);
 if(key) { aaStringNull(key); }
 if(val) { aaStringNull(val); }
 if(dub) { *dub=0.0; }
 if(index>=app.kfg.tre.line_count) { return RET_BOUNDS; }
 for(li=index;li<app.kfg.tre.line_count;li++)
  {
  if((ret=appKonfigGet(li,tkey,tval,dub))!=YES) { oops; return ret; }
  if(partial) {  if(aaStringNICompare(tkey,str32k.buf,F32,0)!=YES) { continue; }  }
  else        {  if(aaStringNICompare(tkey,str32k.buf,0,0)!=YES) { continue; }   }
  if(key) { aaStringCopy(key,tkey); }
  if(val) { aaStringCopy(val,tval); }
  if(found) { *found=li; }
  return RET_YES;
  }
 return RET_NOTFOUND;
 }



//===================================
//===================================




 B odeoAmplify                         (H samples,IP pcm,D gain)
 {
 D factor,scaled;
 H i;
 if(pcm==NULL||samples==0) { oof; }
 factor=pow(10.0,gain/20.0);
 for(i=0;i<samples;i++)
  {
  scaled=(D)pcm[i]*factor;
  if(scaled>+32767.0) { scaled=+32767.0; }
  else
  if(scaled<-32768.0) { scaled=-32768.0; }
  pcm[i]=(I)scaled;
  }
 return RET_YES;
 }




 D odeoMinDbForSamples                 (Z samples)
 {
 D res_min;
 if(samples<=0)  {  return -130.0;    }
 res_min=-10.0*log10((D)samples)-20.0*log10(32768.0);
 if(res_min<-130.0) { res_min=-130.0; }
 return res_min;
 }





 B odeoLevelDerive                     (Z samples,IP pcm,DP lev,DP nor,DP bias)
 {
 D sum,s,rms,full,res,vel,mdb,bas;
 Z i;

 if(samples!=128) oof;
 mdb=odeoMinDbForSamples(samples);//min_db_for_samples(samples);
 bas=fabs(mdb);
 if(bias) { *bias=bas; }
 //appLog("mdb=%.4f",mdb);
 sum=0.0;
 for(i=0;i<samples;i++)
  {
  s=(D)pcm[i];
  sum+=(s*s);
  }
 if(samples<=0)
  {
  ////vel=(-130.0);
  vel=mdb;
  if(lev) { *lev=vel; }
  ///if(nor) { *nor=vel+130.0; }
  if(nor) { *nor=vel+bas; }
  return RET_YES;
  }
 rms=sqrt(sum/(D)samples);
 full=32768.0;
 if(rms<=1e-9)
  {
  vel=(+0.0);
  if(lev) { *lev=vel; } //(+0.0); }
  //if(nor) { *nor=vel+130.0; }
  if(nor) { *nor=vel+bas; }
  return RET_YES;
  }
 res=20.0*log10(rms/full);
 ///if(res<(-130.0)) { res=(-130.0); }
 if(res<mdb)     { res=mdb; }
 if(res>(+0.0))  { res=(+0.0);   }
 vel=res;
 if(lev) { *lev=vel; }
 //if(nor) { *nor=vel+130.0; }
 if(nor) { *nor=vel+bas; }
 return RET_YES;
 }






 B odeoLevelGet                        (H samples,IP pcm,DP lev)
 {
 D sum,s,rms,full,res,mdb;
 H i;
 mdb=odeoMinDbForSamples(samples);//min_db_for_samples(samples);
 *lev=fabs(mdb);//12345.0;
 if(pcm==NULL||samples==0) { return RET_FAILED; }
 sum=0.0;
 for(i=0;i<samples;i++)
  {
  s=(D)pcm[i];
  sum+=s*s;
  }
 rms=sqrt(sum/(D)samples);
 if(rms<=0.0)
  {
  *lev=mdb;//-12345.0;
  return RET_YES;
  //return RET_FAILED;
  }
 full=32768.0;
 res=20.0*log10(rms/full);
 *lev=res;
 return RET_YES;
 }






 B odeoComfort                         (IP out,H num_samples,D target_rms,D smoothing,DP state)
 {
 H i;
 D prev,r,sample;
 prev=state?*state:0.0;
 for(i=0;i<num_samples;i++)
  {
  r=((D)rand()/RAND_MAX)*2.0-1.0;
  sample=r*target_rms*1.732050808; /* sqrt(3) */
  sample=smoothing*prev+(1.0-smoothing)*sample;
  prev=sample;
  if(sample>+32767.0) { sample=+32767.0; }
  if(sample<-32768.0) { sample=-32768.0; }
  out[i]=(I)sample;
  }
 if(state) { *state=prev; }
 return RET_YES;
 }



//===================================
//===================================





 B stunnerNew                          (_stunner*stunner,VP thishost)
 {
 if(stunner==NULL)  { return RET_MISSINGPARM; }
 if(thishost==NULL) { return RET_MISSINGPARM; }
 aaMemoryFill(stunner,sizeof(_stunner),0);
 stunner->magic=aaHPP(stunnerNew);
 stunner->stage=100;
 aaStringCopy(stunner->this_host,thishost);
 return RET_YES;
 }




 B stunnerDelete                       (_stunner*stunner)
 {
 if(stunner==NULL) { return RET_MISSINGPARM; }
 if(stunner->magic!=aaHPP(stunnerNew)) { return RET_NOTINITIALIZED; }
 if(stunner->dns.handle)     {  aaNetDnsDestroy(stunner->dns.handle);  stunner->dns.handle=0;  }
 if(stunner->stun.handle)    {  aaNetStunClientDestroy(stunner->stun.handle);  stunner->stun.handle=0;  }
 if(stunner->udp[0].handle)  {  aaNetUdpDestroy(stunner->udp[0].handle);  stunner->udp[0].handle=0;  }
 aaMemoryFill(stunner,sizeof(_stunner),0);
 return RET_YES;
 }




 B stunnerYield                        (_stunner*stunner,H ita)
 {
 B ret;
 H i,pos;
 B txt[_1K];
 B etc[8][_1K];
 Q el;

 if(stunner==NULL) { return RET_MISSINGPARM; }
 if(stunner->magic!=aaHPP(stunnerNew)) { return RET_NOTINITIALIZED; }
 if(ita==0) { ita=1; }
 ita=1;
 while(ita--)
  {
  switch(stunner->stage)
   {
   case 100:
   stunner->stage=110;
   break;

   case 110:
   if((ret=aaNetDnsCreate(&stunner->dns.handle,stunner->this_host,aa_DNS_MODE_A,1))!=YES) { oops; }
   aaNetDnsStatus(stunner->dns.handle,&stunner->dns.status);
   stunner->stage=120;
   break;

   case 120:
   aaNetDnsStatus(stunner->dns.handle,&stunner->dns.status);
   if(stunner->dns.status.is_inprogress==YES) { break; }
   if(stunner->dns.status.is_notfound)   { appLog("STUNNER: %s not found",stunner->dns.status.query);     stunner->stage=230; break; }
   if(stunner->dns.status.is_failed)     { appLog("STUNNER: %s lookup failed",stunner->dns.status.query); stunner->stage=230; break; }
   if(stunner->dns.status.is_found!=YES) {  break; }
   for(i=0;i<32;i++)    {    if(stunner->dns.status.type[i]==0) { continue; }    }
   stunner->dns_index=0;
   stunner->stage=130;
   break;

   case 130:
   if((i=stunner->dns_index)>=32) { oof; break; }
   if(stunner->dns.status.type[i]!=aa_DNS_MODE_A) { stunner->dns_index++; break; }
   aaNetIpToString(stunner->dns.status.ip[i],stunner->wanting_dot);
   aaNetDnsDestroy(stunner->dns.handle);
   stunner->dns.handle=0;
   stunner->is_finished=YES;
   stunner->stage=150;
   break;


   case 150:
   if((ret=aaNetDnsCreate(&stunner->dns.handle,app.kfg.stun_host,aa_DNS_MODE_A,1))!=YES) { oops; }
   aaNetDnsStatus(stunner->dns.handle,&stunner->dns.status);
   stunner->stage=200;
   break;

   case 200:
   aaNetDnsStatus(stunner->dns.handle,&stunner->dns.status);
   if(stunner->dns.status.is_inprogress==YES) { break; }
   if(stunner->dns.status.is_notfound)   { appLog("STUNNER: %s not found",stunner->dns.status.query);     stunner->stage=230; break; }
   if(stunner->dns.status.is_failed)     { appLog("STUNNER: %s lookup failed",stunner->dns.status.query); stunner->stage=230; break; }
   if(stunner->dns.status.is_found!=YES) { break; }
   for(i=0;i<32;i++)    {    if(stunner->dns.status.type[i]==0) { continue; }    }
   stunner->dns_index=0;
   stunner->stage=210;
   break;

   case 210:
   i=stunner->dns_index;
   if(i>=32) { appLog("STUNNER: all dns_index's tested"); stunner->stage=330; break; }
   if(stunner->dns.status.type[i]!=aa_DNS_MODE_A) { stunner->dns_index++; break; }
   aaNetIpToString(stunner->dns.status.ip[i],txt);
   if((ret=aaNetUdpCreateAny(&stunner->udp[0].handle,0,1024,38192))!=YES) { oops; }
   aaNetUdpStatus(stunner->udp[0].handle,&stunner->udp[0].status);
   aaNetAdrToString(&stunner->udp[0].status.local_adr,txt);
   if((ret=aaNetStunClientCreate(&stunner->stun.handle,stunner->udp[0].handle,stunner->dns.status.ip[i],19302))!=YES)
    {
    oops;
    appQuit();
    }
   stunner->stage=220;
   break;


   case 220:
   aaNetUdpStatus(stunner->udp[0].handle,&stunner->udp[0].status);
   if((ret=aaNetStunClientStatus(stunner->stun.handle,&stunner->stun.status))!=YES) { oops; }
   if(stunner->stun.status.is_complete!=YES) { break; }
   aaNetAdrToString(&stunner->stun.status.local_adr,etc[0]);
   aaNetAdrToString(&stunner->stun.status.server_adr,etc[1]);
   aaNetAdrToString(&stunner->stun.status.other_adr,etc[2]);
   aaNetAdrToString(&stunner->stun.status.mapped_adr,etc[3]);
   aaNetAdrToString(&stunner->stun.status.remapped_adr,etc[4]);
   aaStringCopy(stunner->dot,etc[4]);
   aaStringFindChar(stunner->dot,0,&pos,':',YES,0,YES);;
   stunner->dot[pos]=0;
   //aaDebugf("stunner_dot=%s",stunner->dot);
   if(stunner->public_dot[0]!=NULL_CHAR)
    {
    //aaDebugf("public_dot=%s",stunner->public_dot);
    if(aaStringICompare(stunner->public_dot,stunner->dot,0)!=YES) { aaNote(0,"ip changed %s to %s",stunner->public_dot,stunner->dot); }
    }
   aaStringCopy(stunner->public_dot,stunner->dot);
   aaNetStunClientDestroy(stunner->stun.handle);
   stunner->stun.handle=0;
   if((ret=aaNetUdpDestroy(stunner->udp[0].handle))!=YES) { oops; }
   stunner->udp[0].handle=0;
   #if 0
   appLog("public_dot=[%s]  this_host=[%s]  naikapa_dot=[%s]",stunner->public_dot,stunner->this_host,stunner->naikapa_dot);
   //aaLog(-555,"public_dot=[%s]  this_host=[%s]  naikapa_dot=[%s]",stunner->public_dot,stunner->this_host,stunner->naikapa_dot);
   #endif
   if(aaStringICompare(stunner->public_dot,stunner->wanting_dot,0)!=YES)
    {
    if(0)
     {
     appLog("***** public_ip %s mismatch with wanting %s ",stunner->public_dot,stunner->wanting_dot);
     }
    }
   stunner->stage=230;
   break;

   case 230:
   case 330:
   aaNetDnsDestroy(stunner->dns.handle);
   stunner->dns.handle=0;
   stunner->is_finished=YES;
   stunner->ms=aaMsRunning();
   if(stunner->stage==230) { stunner->is_success=YES; stunner->stage=500; }
   else                    { stunner->is_failure=YES; stunner->stage=500; }
   if(0)
    {
    appLog("stunner , success=%i , failure=%i",stunner->is_success,stunner->is_failure);
    }
   break;

   case 500:
   if(aaHz(0.2))
    {
    el=aaMsRunning()-stunner->ms;
    if(el<app.kfg.stun_pause) { break; }
    }
   else {  break;   }
   stunner->stage=100;
   return YES;
   }
  }
 return RET_YES;
 }




//===================================
//===================================



 B httpInfoInit                        (_httpinfo*httpinfo)
 {
 if(httpinfo==NULL) { return RET_MISSINGPARM; }
 aaMemoryFill(httpinfo,sizeof(_httpinfo),0);
 httpinfo->magic=aaHPP(httpInfoInit);
 return RET_YES;
 }





 B httpInfoResultAdd                   (_httpinfo*httpinfo,_httpresult*httpresult)
 {
 if(httpinfo==NULL) { return RET_MISSINGPARM; }
 if(httpinfo->magic!=aaHPP(httpInfoInit)) { return RET_NOTINITIALIZED; }
 if(httpinfo->result_count>=1) { return RET_OVERFLOW; }
 if(httpresult==NULL) { return RET_MISSINGPARM; }
 if(httpinfo->is_finished==YES) { return RET_FINISHED; }
 aaMemoryCopy(&httpinfo->result,sizeof(_httpresult),httpresult);
 httpinfo->result_count++;
 return RET_YES;
 }




 B httpInfoHeaderAdd                   (_httpinfo*httpinfo,_httpheader*httpheader)
 {
 if(httpinfo==NULL) { return RET_MISSINGPARM; }
 if(httpinfo->magic!=aaHPP(httpInfoInit)) { return RET_NOTINITIALIZED; }
 if(httpinfo->header_count>=aaElementCount(httpinfo->header)) { return RET_OVERFLOW; }
 if(httpheader==NULL) { return RET_MISSINGPARM; }
 if(httpinfo->is_finished==YES) { return RET_FINISHED; }
 aaMemoryCopy(&httpinfo->header[httpinfo->header_count],sizeof(_httpheader),httpheader);
 httpinfo->header_count++;
 if(httpheader->field_code==aa_HTTPFIELD_BLANK) { httpinfo->is_finished=YES; }
 return RET_YES;
 }




//===================================
//===================================





 B msgpackNew                          (_msgpack*msgpack)
 {
 B ret;
 if(msgpack==NULL) { return RET_MISSINGPARM; }
 aaMemoryFill(msgpack,sizeof(_msgpack),0);
 msgpack->magic=aaHPP(msgpackNew);
 if((ret=aaMemoryUnitAllocate(&msgpack->mun,msgpack->mun.bytes+_4K))!=YES) { oops; }
 return RET_YES;
 }




 B msgpackDelete                       (_msgpack*msgpack)
 {
 if(msgpack==NULL) { return RET_MISSINGPARM; }
 if(msgpack->magic!=aaHPP(msgpackNew)) { return RET_NOTINITIALIZED; }
 aaMemoryUnitRelease(&msgpack->mun);
 aaMemoryFill(msgpack,sizeof(_msgpack),0);
 return RET_YES;
 }



 B msgpackReset                        (_msgpack*msgpack)
 {
 if(msgpack==NULL) { return RET_MISSINGPARM; }
 if(msgpack->magic!=aaHPP(msgpackNew)) { return RET_NOTINITIALIZED; }
 msgpack->mun.used=0;
 return RET_YES;
 }




 B msgpackReAlloc                      (_msgpack*msgpack,H thresh,H toadd)
 {
 B ret;
 H left;
 if(msgpack==NULL) { return RET_MISSINGPARM; }
 if(msgpack->magic!=aaHPP(msgpackNew)) { return RET_NOTINITIALIZED; }
 if(thresh) {}
 left=msgpack->mun.bytes-msgpack->mun.used;
 if(left<(toadd))
  {
  if((ret=aaMemoryUnitReAllocate(&msgpack->mun,msgpack->mun.bytes+toadd))!=YES) { oops; }
  left=msgpack->mun.bytes-msgpack->mun.used;
  }
 return RET_YES;
 }



 B msgpackAppend                       (_msgpack*msgpack,H bytes,VP buf)
 {
 B ret;
 BP bp;
 H i;
 if(msgpack==NULL) { return RET_MISSINGPARM; }
 if(msgpack->magic!=aaHPP(msgpackNew)) { return RET_NOTINITIALIZED; }
 if(bytes==0) { aaStringLen(buf,&bytes); }
 bp=(BP)buf;
 for(i=0;i<bytes;i++)
  {
  if((ret=msgpackReAlloc(msgpack,100,(msgpack->mun.bytes/4)+_4K))!=YES) { oops; }
  msgpack->mun.mem[msgpack->mun.used]=bp[i];
  msgpack->mun.used++;
  }
 return RET_YES;
 }



 B msgpackAppendByte                   (_msgpack*msgpack,B val)
 {
 return(msgpackAppend(msgpack,1,&val));
 }



 B msgpackAppendNil                    (_msgpack*msgpack)
 {
 return(msgpackAppendByte(msgpack,0xc0));
 }



 B msgpackAppendBool                   (_msgpack*msgpack,B val)
 {
 if(val) { return(msgpackAppendByte(msgpack,0xc3)); }
 else    { return(msgpackAppendByte(msgpack,0xc2)); }
 }



 B msgpackAppendInt                    (_msgpack*msgpack,H size,H val)
 {
 B ret;
 if(msgpack==NULL) { return RET_MISSINGPARM; }
 if(msgpack->magic!=aaHPP(msgpackNew)) { return RET_NOTINITIALIZED; }
 if((ret=msgpackAppendByte(msgpack,0xce))!=YES) { oops; return ret; }
 val=aaNumSwapDword(val);
 if((ret=msgpackAppend(msgpack,4,&val))!=YES) { oops; return ret; }
 if(size) {}
 return RET_YES;
 }




 B msgpackAppendBin                    (_msgpack*msgpack,H size,H bytes,VP buf)
 {
 B ret;
 BP bp;
 H i,len;
 if(msgpack==NULL) { return RET_MISSINGPARM; }
 if(msgpack->magic!=aaHPP(msgpackNew)) { return RET_NOTINITIALIZED; }
 switch(size)
  {
  default: oof;  return RET_FAILED;

  case 1: // bin8
  if((ret=msgpackAppendByte(msgpack,0xc4))!=YES) { oops; return ret; }
  len=bytes;
  if((ret=msgpackAppend(msgpack,size,&len))!=YES) { oops; return ret; }
  break;

  case 2: // bin16
  if((ret=msgpackAppendByte(msgpack,0xc5))!=YES) { oops; return ret; }
  len=aaNumSwapWord(bytes);
  if((ret=msgpackAppend(msgpack,size,&len))!=YES) { oops; return ret; }
  break;

  case 4: // bin32
  if((ret=msgpackAppendByte(msgpack,0xc6))!=YES) { oops; return ret; }
  len=aaNumSwapDword(bytes);
  if((ret=msgpackAppend(msgpack,size,&len))!=YES) { oops; return ret; }
  break;
  }
 bp=(BP)buf;
 for(i=0;i<bytes;i++)
  {
  if((ret=msgpackReAlloc(msgpack,100,(msgpack->mun.bytes/4)+_32K))!=YES) { oops; }
  msgpack->mun.mem[msgpack->mun.used]=bp[i];
  msgpack->mun.used++;
  }
 return RET_YES;
 }




 B msgpackAppendMap16                  (_msgpack*msgpack,H length)
 {
 B ret;
 W len;
 if(msgpack==NULL) { return RET_MISSINGPARM; }
 if(msgpack->magic!=aaHPP(msgpackNew)) { return RET_NOTINITIALIZED; }
 if((ret=msgpackAppendByte(msgpack,0xde))!=YES) { oops; }
 len=(W)length;
 len=aaNumSwapWord(len);
 if((ret=msgpackAppend(msgpack,2,&len))!=YES) { oops; }
 return RET_YES;
 }




 B msgpackAppendMap                    (_msgpack*msgpack,H count)
 {
 H mc;
 if(msgpack==NULL) { return RET_MISSINGPARM; }
 if(msgpack->magic!=aaHPP(msgpackNew)) { return RET_NOTINITIALIZED; }
 mc=0x80;
 mc+=count;
 return(msgpackAppendByte(msgpack,(B)mc));
 }



 B msgpackAppendArray                  (_msgpack*msgpack,H count)
 {
 H mc;
 if(msgpack==NULL) { return RET_MISSINGPARM; }
 if(msgpack->magic!=aaHPP(msgpackNew)) { return RET_NOTINITIALIZED; }
 mc=0x90;
 mc+=count;
 return(msgpackAppendByte(msgpack,(B)mc));
 }




 B msgpackAppendFixStrFixStr           (_msgpack*msgpack,VP key,VP fmt,...)
 {
 B ret;
 aaVargsf32K(fmt);
 if(msgpack==NULL) { return RET_MISSINGPARM; }
 if(msgpack->magic!=aaHPP(msgpackNew)) { return RET_NOTINITIALIZED; }
 if((ret=msgpackAppendFixStr(msgpack,"%s",key))!=YES) { return ret; }
 ret=msgpackAppendFixStr(msgpack,"%s",str32k.buf);
 return ret;
 }



 B msgpackAppendFixStrFloat            (_msgpack*msgpack,VP key,F val)
 {
 B ret;
 if(msgpack==NULL) { return RET_MISSINGPARM; }
 if(msgpack->magic!=aaHPP(msgpackNew)) { return RET_NOTINITIALIZED; }
 if((ret=msgpackAppendFixStr(msgpack,"%s",key))!=YES) { return ret; }
 ret=msgpackAppendFloat(msgpack,val);
 return ret;
 }




 B msgpackAppendFixStr                 (_msgpack*msgpack,VP fmt,...)
 {
 B ret;
 aaVargsf32K(fmt);
 if(msgpack==NULL) { return RET_MISSINGPARM; }
 if(msgpack->magic!=aaHPP(msgpackNew)) { return RET_NOTINITIALIZED; }
 if((ret=msgpackReAlloc(msgpack,(str32k.len+_1K),(str32k.len+_4K)))!=YES) { oops; }
 msgpack->mun.mem[msgpack->mun.used]=(0xa0+str32k.len);
 msgpack->mun.used++;
 aaMemoryCopy(&msgpack->mun.mem[msgpack->mun.used],str32k.len,str32k.buf);
 msgpack->mun.used+=str32k.len;
 return RET_YES;
 }




 B msgpackAppendStr8                   (_msgpack*msgpack,VP fmt,...)
 {
 B ret;
 aaVargsf32K(fmt);
 if(msgpack==NULL) { return RET_MISSINGPARM; }
 if(msgpack->magic!=aaHPP(msgpackNew)) { return RET_NOTINITIALIZED; }
 if((ret=msgpackReAlloc(msgpack,(str32k.len+_1K),(str32k.len+_4K)))!=YES) { oops; }
 msgpack->mun.mem[msgpack->mun.used]=(0xd9);
 msgpack->mun.used++;
 msgpack->mun.mem[msgpack->mun.used]=(B)str32k.len;
 msgpack->mun.used++;
 aaMemoryCopy(&msgpack->mun.mem[msgpack->mun.used],str32k.len,str32k.buf);
 msgpack->mun.used+=str32k.len;
 return RET_YES;
 }




 B msgpackAppendStr16                  (_msgpack*msgpack,VP fmt,...)
 {
 B ret;
 H len;
 aaVargsf32K(fmt);
 if(msgpack==NULL) { return RET_MISSINGPARM; }
 if(msgpack->magic!=aaHPP(msgpackNew)) { return RET_NOTINITIALIZED; }
 if((ret=msgpackReAlloc(msgpack,(str32k.len+_1K),(str32k.len+_4K)))!=YES) { oops; }
 msgpack->mun.mem[msgpack->mun.used]=(0xda);
 msgpack->mun.used++;
 len=aaNumSwapWord(str32k.len);
 if((ret=msgpackAppend(msgpack,2,&len))!=YES) { oops; return ret; }
 aaMemoryCopy(&msgpack->mun.mem[msgpack->mun.used],str32k.len,str32k.buf);
 msgpack->mun.used+=str32k.len;
 return RET_YES;
 }



 B msgpackAppendDouble                 (_msgpack*msgpack,D val)
 {
 B ret;
 Q temp_val;
 D result;
 if(msgpack==NULL) { return RET_MISSINGPARM; }
 if(msgpack->magic!=aaHPP(msgpackNew)) { return RET_NOTINITIALIZED; }
 memcpy(&temp_val,&val,sizeof(D));
 temp_val=((temp_val&0x00000000000000FFULL)<<56)|((temp_val&0x000000000000FF00ULL)<<40)|
          ((temp_val&0x0000000000FF0000ULL)<<24)|((temp_val&0x00000000FF000000ULL)<<8) |
          ((temp_val&0x000000FF00000000ULL)>>8) |((temp_val&0x0000FF0000000000ULL)>>24)|
          ((temp_val&0x00FF000000000000ULL)>>40)|((temp_val&0xFF00000000000000ULL)>>56);
 memcpy(&result,&temp_val,sizeof(D));
 if((ret=msgpackAppendByte(msgpack,0xcb))!=YES) { oops; return ret; }
 if((ret=msgpackAppend(msgpack,8,&result))!=YES) { oops; return ret; }
 return RET_YES;
 }




 B msgpackAppendFloat                  (_msgpack*msgpack,F val)
 {
 B ret;
 H temp_val;
 F result;
 if(msgpack==NULL) { return RET_MISSINGPARM; }
 if(msgpack->magic!=aaHPP(msgpackNew)) { return RET_NOTINITIALIZED; }
 memcpy(&temp_val,&val,sizeof(F));
 temp_val=((temp_val&0x000000FF)<<24)|((temp_val&0x0000FF00)<<8)|
          ((temp_val&0x00FF0000)>>8)|((temp_val&0xFF000000)>>24);
 memcpy(&result,&temp_val,sizeof(F));
 if((ret=msgpackAppendByte(msgpack,0xca))!=YES) { oops; return ret; }
 if((ret=msgpackAppend(msgpack,4,&result))!=YES) { oops; return ret; }
 return RET_YES;
 }





//===================================
//===================================








 B fishTtsVoiceListAdd                 (_fishtts*fishtts,VP id,VP name)
 {
 if(fishtts==NULL) { return RET_MISSINGPARM; }
 aaStringCopy(fishtts->voice[fishtts->voice_count].id,id);
 aaStringCopy(fishtts->voice[fishtts->voice_count].name,name);
 fishtts->voice_count++;
 return RET_YES;
 }



 B fishTtsNew                          (_fishtts*fishtts,VP key)
 {
 B ret;
 if(fishtts==NULL) { return RET_MISSINGPARM; }
 aaMemoryFill(fishtts,sizeof(_fishtts),0);
 fishtts->magic=aaHPP(fishTtsNew);
 fishTtsVoiceListAdd(fishtts,"d13f84b987ad4f22b56d2b47f4eb838e","scary voice");
 fishTtsVoiceListAdd(fishtts,"fdd99dfa9a6440e0b56665e9effa85ec","somebody1");
 fishTtsVoiceListAdd(fishtts,"6a948a5e34f8413aaf87386d9451a19e","somebody2");
 fishTtsVoiceListAdd(fishtts,"0d9f08bedd144aba96fd487aa614cc53","some girl");
 fishTtsVoiceListAdd(fishtts,"d13f84b987ad4f22b56d2b47f4eb838e","Mortal Kombat,Pedro");
 fishTtsVoiceListAdd(fishtts,"90e65eaaf50e4470b8e6d43ee6afd7d5","Super Smash Bros.");
 fishTtsVoiceListAdd(fishtts,"b4f55643a15944e499defe42964d2ebf","eric south park");
 fishTtsVoiceListAdd(fishtts,"9830641fbcd5492392caf02aad4b348d","kyle soutg park");
 fishTtsVoiceListAdd(fishtts,"61a8cdc3391f42829ca5cc066b0db9cd","shelly south park");
 fishTtsVoiceListAdd(fishtts,"9f269543d66d4e53aa74de8fdc23413d","bill burr");
 fishTtsVoiceListAdd(fishtts,"8e468a7c906648e3bb4cb7c08185b14a","angry indian");
 fishTtsVoiceListAdd(fishtts,"94a70b701598459592ac2f9f5fbbd661","drill sargeant");
 fishTtsVoiceListAdd(fishtts,"6461af367e71445a8ad8e69b78cacd35","australian barb");
 fishTtsVoiceListAdd(fishtts,"bb2efc2ca71c41bc96cbbb1f10f97015","netyahu");
 fishTtsVoiceListAdd(fishtts,"c76040e3b63d400c999d153c3b9141f3","armenian");
 fishTtsVoiceListAdd(fishtts,"2da039d5b3dd4a0bb9ebfd49180facae","cockney");
 fishTtsVoiceListAdd(fishtts,"4e407b98cb034f74b3863ec33c567c83","child");
 fishTtsVoiceListAdd(fishtts,"6d67b892daa74c3088524b8a92c5dff6","chinese man");
 fishTtsVoiceListAdd(fishtts,"d36061db5db44106a977a6ab9974fa10","ashod");
 fishTtsVoiceListAdd(fishtts,"9c30e1b9b3d546e6a452c722866741e8","amy");
 fishTtsVoiceListAdd(fishtts,"f0c09f2fbdef4a61b07ced6ee2adf605","bibi");
 fishTtsVoiceListAdd(fishtts,"4dab911a84414c41ae0438befe7f2e3c","donald");
 fishTtsVoiceListAdd(fishtts,"ec8ae38eb24e4da88697d751b769f7fd","duchen");
 fishTtsVoiceListAdd(fishtts,"141df7203ab3447280b42b030a8f2fd2","star-trek");
 fishTtsVoiceListAdd(fishtts,"de960f838fca4db6952947296b96d0fe","patric stewart");
 fishTtsVoiceListAdd(fishtts,"933563129e564b19a115bedd57b7406a","sarah");
 fishTtsVoiceListAdd(fishtts,"eb6b3c6b3a044c528212661833d6d7b6","tony montana");
 fishTtsVoiceListAdd(fishtts,"7767ce79a39e4793b7b62ba86b4571a4","louis ck");
 fishTtsVoiceListAdd(fishtts,"922505ae446943a49962333f2aa79cfc","chappelle");
 aaStringCopy(fishtts->key,key);
 msgpackNew(&fishtts->msgpack);
 if((ret=aaMemoryAllocate((VP)&fishtts->payload,_8MEG))!=YES) { oops; }

 aaMemoryNameSet(fishtts->payload,"fishpay");

 if((ret=aaMemoryAllocate((VP)&fishtts->sam,_8MEG*2))!=YES) { oops; }

 aaMemoryNameSet(fishtts->sam,"fishsam");

 aaQueCreate(&fishtts->que.handle);
 aaQueStatus(fishtts->que.handle,&fishtts->que.status);
 return RET_YES;
 }






 B fishTtsDelete                       (_fishtts*fishtts)
 {
 H i,done;
 if(fishtts==NULL) { return RET_MISSINGPARM; }
 if(fishtts->magic!=aaHPP(fishTtsNew)) { return RET_NOTINITIALIZED; }
 done=0;
 for(i=0;i<aaElementCount(fishtts->vox);i++)
  {
  if(fishtts->vox[i].magic!=aaHPP(fishTtsReference)) { continue; }
  if(fishtts->vox[i].is_audio==YES)
   {
   aaMemoryRelease((VP)fishtts->vox[i].audio_mem);
   }
  done++;
  }
 if(done!=fishtts->vox_count) oof;
 msgpackDelete(&fishtts->msgpack);
 aaMemoryRelease(fishtts->payload);
 aaMemoryRelease(fishtts->sam);
 aaNetWebsocketClientDelete(&fishtts->ws_cli);
 aaQueDestroy(fishtts->que.handle);
 aaMemoryFill(fishtts,sizeof(_fishtts),0);
 return RET_YES;
 }










 B fishTtsReference                    (_fishtts*fishtts,VP vid,H len,H lmx,VP mem,VP fmt,...)
 {
 B ret;
 H idx;
 B id[_1K];
 aaVargsf32K(fmt);

 if(fishtts==NULL) { return RET_MISSINGPARM; }
 if(fishtts->magic!=aaHPP(fishTtsNew)) { return RET_NOTINITIALIZED; }
 if(fishtts->stage<25) { oof; return RET_BADSTATE; }
 msgpackReset(&fishtts->msgpack);
 msgpackAppendMap16(&fishtts->msgpack,2);
 msgpackAppendFixStr(&fishtts->msgpack,"event");
 msgpackAppendFixStr(&fishtts->msgpack,"start");
 msgpackAppendFixStr(&fishtts->msgpack,"request");
 msgpackAppendMap(&fishtts->msgpack,9);
 msgpackAppendFixStr(&fishtts->msgpack,"text");
 msgpackAppendFixStr(&fishtts->msgpack,"");
 msgpackAppendFixStr(&fishtts->msgpack,"latency");
 msgpackAppendFixStr(&fishtts->msgpack,"balanced");
 msgpackAppendFixStr(&fishtts->msgpack,"format");
 msgpackAppendFixStr(&fishtts->msgpack,"pcm");
   msgpackAppendFixStr(&fishtts->msgpack,"condition_on_previous_chunks");
   msgpackAppendBool(&fishtts->msgpack,0);
 msgpackAppendFixStr(&fishtts->msgpack,"temperature");
  msgpackAppendDouble(&fishtts->msgpack,app.kfg.fish_defaults_temperature);
 msgpackAppendFixStr(&fishtts->msgpack,"model");
 msgpackAppendFixStr(&fishtts->msgpack,app.kfg.fish_defaults_model);//"s2-pro");
 msgpackAppendFixStr(&fishtts->msgpack,"chunk_length");
 msgpackAppendInt(&fishtts->msgpack,4,150);
 msgpackAppendFixStr(&fishtts->msgpack,"prosody");
 msgpackAppendMap(&fishtts->msgpack,3);
 msgpackAppendFixStr(&fishtts->msgpack,"speed");
 msgpackAppendDouble(&fishtts->msgpack,1.0);
 msgpackAppendFixStr(&fishtts->msgpack,"volume");
 msgpackAppendDouble(&fishtts->msgpack,0.0);
 msgpackAppendFixStr(&fishtts->msgpack,"normalize_loudness");
 msgpackAppendBool(&fishtts->msgpack,0);
 aaStringNull(id);
 if(vid!=NULL) { aaStringCopy(id,vid); }
 idx=0;
 if(id[0]==NULL_CHAR)
  {
  if(len>=lmx)
   {
   if(1) { appLog("quantizing clone waveform from %i to %i (q=%.2f%%)",len,lmx,aaNumPercentIs(lmx,len)); }
   len=lmx;
   }
  if(1) { appLog("voice being cloned from %i samples (%i bytes) of audio",len/2,len); }
  msgpackAppendFixStr(&fishtts->msgpack,"references");
  msgpackAppendArray(&fishtts->msgpack,1);
  msgpackAppendMap(&fishtts->msgpack,2);
  msgpackAppendFixStr(&fishtts->msgpack,"audio");
  msgpackAppendBin(&fishtts->msgpack,4,len,mem);
  msgpackAppendFixStr(&fishtts->msgpack,"text");
  msgpackAppendStr8(&fishtts->msgpack,"%s",str32k.buf);
  aaMemoryFill(&fishtts->vox[idx],sizeof(_fishttsvox),0);
  fishtts->vox[idx].magic=aaHPP(fishTtsReference);
  fishtts->vox[idx].is_audio=YES;
  fishtts->vox[idx].audio_len=len;
  if((ret=aaMemoryAllocate((VP)&fishtts->vox[idx].audio_mem,fishtts->vox[idx].audio_len))!=YES) { aaNote(0,"al=%i",fishtts->vox[idx].audio_len);  oops; }
  aaMemoryNameSet(fishtts->vox[idx].audio_mem,"voxay");
  aaMemoryCopy(fishtts->vox[idx].audio_mem,fishtts->vox[idx].audio_len,mem);
  aaStringCopyf(fishtts->vox[idx].text,"%s",str32k.buf);
  fishtts->vox_count++;
  }
 else
  {
  msgpackAppendFixStr(&fishtts->msgpack,"reference_id");
  msgpackAppendStr8(&fishtts->msgpack,"%s",id);//str32k.buf);
  aaMemoryFill(&fishtts->vox[idx],sizeof(_fishttsvox),0);
  fishtts->vox[idx].magic=aaHPP(fishTtsReference);
  fishtts->vox[idx].is_audio=NO;
  aaStringCopy(fishtts->vox[idx].voice_id,vid);
  aaStringCopyf(fishtts->vox[idx].text,"%s",str32k.buf);
  fishtts->vox_count++;
  }
 if((ret=aaNetWebsocketClientPktWrite(&fishtts->ws_cli,2,1,fishtts->msgpack.mun.used,fishtts->msgpack.mun.mem))!=YES) { oops; }
 fishtts->stage=30;
 return RET_YES;
 }





 B fishTtsWritef                       (_fishtts*fishtts,VP fmt,...)
 {
 B ret;
 B str[_32K];
 aaVargsf32K(fmt);
 if(fishtts==NULL) { return RET_MISSINGPARM; }
 if(fishtts->magic!=aaHPP(fishTtsNew)) { return RET_NOTINITIALIZED; }
 if(fishtts->stage!=30) { oof; return RET_BADSTATE; }
 fishtts->is_ready=NO;
 msgpackReset(&fishtts->msgpack);
 msgpackAppendMap(&fishtts->msgpack,2);
 msgpackAppendFixStr(&fishtts->msgpack,"event");
 msgpackAppendFixStr(&fishtts->msgpack,"text");
 msgpackAppendFixStr(&fishtts->msgpack,"text");
 aaStringCopyf(str,"%s",str32k.buf);
 aaStringUnQuote(str,0,0);
 msgpackAppendStr16(&fishtts->msgpack,"%s",str);
 if((ret=aaNetWebsocketClientPktWrite(&fishtts->ws_cli,2,1,fishtts->msgpack.mun.used,fishtts->msgpack.mun.mem))!=YES) { oops; }
 fishtts->stage=30;
 return RET_YES;
 }




 B fishTtsFlush                        (_fishtts*fishtts)
 {
 B ret;
 if(fishtts==NULL) { return RET_MISSINGPARM; }
 if(fishtts->magic!=aaHPP(fishTtsNew)) { return RET_NOTINITIALIZED; }
 if(fishtts->stage!=30) { oof; return RET_BADSTATE; }
 msgpackReset(&fishtts->msgpack);
 msgpackAppendMap(&fishtts->msgpack,1);
 msgpackAppendFixStr(&fishtts->msgpack,"event");
 msgpackAppendFixStr(&fishtts->msgpack,"flush");
 if((ret=aaNetWebsocketClientPktWrite(&fishtts->ws_cli,2,1,fishtts->msgpack.mun.used,fishtts->msgpack.mun.mem))!=YES) { oops; }
 return RET_YES;
 }







 B fishTtsYield                        (_fishtts*fishtts)
 {
 B ret;
 H go,to;
 B tok[_2K];
 H ib,pos,left,npos,as,vv;
 BP bp;
 Q temp_val;
 D result;
 H osamples;
 _fishttscode*fico;
 H fslen;
 G swp;

 if(fishtts==NULL) { return RET_MISSINGPARM; }
 if(fishtts->magic!=aaHPP(fishTtsNew)) { return RET_NOTINITIALIZED; }
 go=0;
 to=2;
 while(1)
  {
  if((go++)>=to)   {   break;   }

  switch(fishtts->stage)
   {
   case 0:
   fishtts->stage=10;
   break;

   case 10:
   aaStringCopyf(tok,"Bearer %s",fishtts->key);
   if((ret=aaNetWebsocketClientNew(&fishtts->ws_cli,0,0,app.kfg.fish_endpoint,0,443,1,tok,"/v1/tts/live"))!=YES) { oops; }
   fishtts->stage=20;
   break;

   case 20:
   if((ret=aaNetWebsocketClientYield(&fishtts->ws_cli))!=YES) { oops; }
   if(fishtts->ws_cli.cd->is_ready!=YES) { break; }
   fishtts->stage=30;
   break;


   case 30:
   if(go>1)
    {
    if((ret=aaNetWebsocketClientYield(&fishtts->ws_cli))!=YES) { oops; }
    }
   if(aaNetWebsocketClientPktRead(&fishtts->ws_cli,&fishtts->ws_hdr,fishtts->payload)!=YES) { break;  }
   ib=fishtts->ws_hdr.bytes;
   fishtts->payload[ib+0]=0;
   if((ib%2)!=0)    {    aaDebugf("ib=%i",ib);   break;    }
   fishtts->man_phaze=10;
   fishtts->man_pos=0;
   fishtts->man_ib=ib;
   left=fishtts->man_ib-fishtts->man_pos;
   fishtts->code_count=0;
   bp=(BP)&fishtts->payload[0];
   while(1)
    {
    if(fishtts->man_phaze==0)   { break; }
    left=fishtts->man_ib-fishtts->man_pos;
    if(left==0)    {     fishtts->is_ready=YES;     break;     }
    //---------------
    pos=fishtts->man_pos;
    fico=(_fishttscode*)&fishtts->code[0];
    fico+=fishtts->code_count;
    switch(fishtts->man_phaze)
     {
     case 10:
     fico->cat=0;
     fico->cmd=bp[pos];
     fico->pos=pos;
     fico->size=0;
     fico->plus=0;
     fico->more=0;
     fico->tl=0;
     fico->txt[0]=0;
     fico->dub=0;
     fico->ms=aaMsRunning();
     while(1)
      {
      fico->size=1;
      if(fico->cmd<=0x7f)
       {
       fico->cat=MPCAT_FIXINT;
       fico->plus=0;
       fico->more=0;
       npos=pos+(fico->size+fico->plus+fico->more);
       fishtts->code_count++;
       fishtts->man_pos=npos;
       break;
       }
      if(fico->cmd>=0x80&&fico->cmd<=0x8f)
       {
       fico->cat=MPCAT_FIXMAP;
       fico->plus=0;
       fico->more=fico->cmd-0x80;
       npos=pos+(fico->size+fico->plus);
       fishtts->code_count++;
       fishtts->man_pos=npos;
       break;
       }
      if(fico->cmd>=0x90&&fico->cmd<=0x9f)
       {
       fico->cat=MPCAT_FIXARRAY;
       fico->plus=0;
       fico->more=fico->cmd-0x90;
       npos=pos+(fico->size+fico->plus+fico->more);
       fishtts->code_count++;
       fishtts->man_pos=npos;
       break;
       }
      if(fico->cmd>=0xa0&&fico->cmd<=0xbf)
       {
       fico->cat=MPCAT_FIXSTR;
       fico->plus=0;
       fico->more=fico->cmd-0xa0;
       aaStringNCopy(fico->txt,&bp[pos+1],fico->more,YES);
       npos=pos+(fico->size+fico->plus+fico->more);
       fishtts->code_count++;
       fishtts->man_pos=npos;
       break;
       }
      if(fico->cmd==0xc0)
       {
       fico->cat=MPCAT_NIL;
       fico->plus=0;
       fico->more=0;
       npos=pos+(fico->size+fico->plus+fico->more);
       fishtts->code_count++;
       fishtts->man_pos=npos;
       break;
       }
      if(fico->cmd==0xc2||fico->cmd==0xc3)
       {
       fico->cat=MPCAT_BOOL;
       fico->plus=0;
       fico->more=0;
       npos=pos+(fico->size+fico->plus+fico->more);
       fishtts->code_count++;
       fishtts->man_pos=npos;
       break;
       }
      if(fico->cmd>=0xc4&&fico->cmd<=0xc6)
       {
       fico->cat=MPCAT_BIN;
       switch(fico->cmd)
        {
        case 0xc4:
        fico->plus=1;
        fico->more=bp[pos+1];
        as=pos+3;
        npos=pos+(fico->size+fico->plus+fico->more);
        break;

        case 0xc5:
        fico->plus=2;
        aaMemoryCopy(&vv,fico->plus,&bp[pos+1]);
        vv=aaNumSwapWord(vv);
        fico->more=vv;
        as=pos+3;
        npos=pos+(fico->size+fico->plus+fico->more);
        break;

        case 0xc6:
        fico->plus=4;
        aaMemoryCopy(&vv,fico->plus,&bp[pos+1]);
        vv=aaNumSwapDword(vv);
        fico->more=vv;
        as=pos+3;
        npos=pos+(fico->size+fico->plus+fico->more);
        break;
        }
       fslen=fico->more;
       if((ret=aaAudioConverterQuick(&am44100_16_1,fslen/2,&bp[as],1.0,&am16000_16_1,&osamples,fishtts->sam))!=YES) { oops; }
       if((ret=aaQueWrite(fishtts->que.handle,osamples*2,fishtts->sam))!=YES) { oops; }
       aaQueStatus(fishtts->que.handle,&fishtts->que.status);
       pos+=fslen;
       fishtts->code_count++;
       fishtts->man_pos=npos;
       break;
       }
      if(fico->cmd==0xca)
       {
       fico->cat=MPCAT_FLOAT;
       fico->plus=4;
       memcpy(&temp_val,&bp[pos],sizeof(F));
       temp_val=((temp_val&0x000000FF)<<24)|((temp_val&0x0000FF00)<<8)|
                ((temp_val&0x00FF0000)>>8)|((temp_val&0xFF000000)>>24);
       memcpy(&result,&temp_val,sizeof(F));
       fico->more=0;
       npos=pos+(fico->size+fico->plus+fico->more);
       fishtts->code_count++;
       fishtts->man_pos=npos;
       break;
       }
      if(fico->cmd==0xcb)
       {
       fico->plus=8;
       memcpy(&temp_val,&bp[pos],sizeof(D));
       memcpy(&result,&temp_val,sizeof(D));
       memcpy(&temp_val,&bp[pos],sizeof(D));
       swp=((temp_val&0xFF00000000000000ULL)>>56)|((temp_val&0x00FF000000000000ULL)>>40)|
           ((temp_val&0x0000FF0000000000ULL)>>24)|((temp_val&0x000000FF00000000ULL)>>8) |
           ((temp_val&0x00000000FF000000ULL)<<8) |((temp_val&0x0000000000FF0000ULL)<<24)|
           ((temp_val&0x000000000000FF00ULL)<<40)|((temp_val&0x00000000000000FFULL)<<56);
       temp_val=swp;
       memcpy(&result,&temp_val,sizeof(D));
       fico->more=0;
       npos=pos+(fico->size+fico->plus+fico->more);
       fishtts->code_count++;
       fishtts->man_pos=npos;
       break;
       }
      if(fico->cmd==0xd9)
       {
       fico->cat=MPCAT_STR;
       fico->plus=1;
       fico->more=bp[pos+1];
       aaStringNCopy(fico->txt,&bp[pos+1],fico->more,YES);
       npos=pos+(fico->size+fico->plus+fico->more);
       fishtts->code_count++;
       fishtts->man_pos=npos;
       break;
       }
      aaNote(0,"0x%02x",fico->cmd);
      }
     }
    }
   break;
   }
  }
 return RET_YES;
 }







//===================================
//===================================



 B claudeNew                           (_claude*claude,VP usruid)
 {
 aaMemoryFill(claude,sizeof(_claude),0);
 claude->magic=aaHPP(claudeNew);
 aaStringCopy(claude->usr_uid,usruid);
 claude->stage=1000;
 return RET_YES;
 }





 B claudeDelete                        (_claude*claude)
 {
 if(claude==NULL) { return RET_MISSINGPARM; }
 if(claude->magic!=aaHPP(claudeNew)) { return RET_NOTINITIALIZED; }
 aaDynbufDestroy(claude->debu.handle);
 if(claude->call.handle!=0)
  {
  aaNetTcpCallDestroy(claude->call.handle);
  }
 if(claude->sweets.handle!=0) { aaQueDestroy(claude->sweets.handle); }
 if(claude->sse.handle!=0) { aaQueDestroy(claude->sse.handle); }
 if(claude->answer.handle!=0) { aaQueDestroy(claude->answer.handle); }
 aaMemoryFill(claude,sizeof(_claude),0);
 return RET_YES;
 }







 B claudeDistill                       (_claude*claude)
 {
 B ret;
 H pos,num,i,len,nlen;
 H positions[30];
 H lengths[30];
 B blok[3][_32K];
 B answer_o[_64K];
 _textreader tre;
 H li;
 H chars;
 B txt[_32K];
 _str32k needle;
 B the_output[_32K]={0};

 if(claude==NULL) { return RET_MISSINGPARM; }
 if(claude->magic!=aaHPP(claudeNew)) { return RET_NOTINITIALIZED; }

 aaQueStatus(claude->sse.handle,&claude->sse.status);
 if(claude->sse.status.total_bytes_written==0) { return RET_YES; }



 appLog("line=%-5i SSE_QUE LEN=%i r=%I64d w=%I64d",__LINE__,claude->sse.status.bytes, claude->sse.status.total_bytes_read,claude->sse.status.total_bytes_written);
 num=0;
 positions[0]=0;
 while(1)
  {
  if((ret=aaQueFindByte(claude->sse.handle,0,claude->sse.status.bytes,&pos,0x0a,YES,num))!=RET_YES)  {  return RET_YES;   }
  positions[num+1]=pos;
  num++;
  if(num>=3) { break; }
  }
 appLog("NUM=%i",num);
 for(i=0;i<3;i++)
  {
  len=positions[i+1]-positions[i+0];
  lengths[i]=len;
  }
 //appLog("sse num=%i  positions=%i,%i,%i,%i  lengths=%i,%i,%i",num,positions[0],positions[1],positions[2],positions[3],lengths[0],lengths[1],lengths[2]);
 for(i=0;i<3;i++)
  {
  len=lengths[i];
  appLog("@@@@ i=%i/%i len=%i",i,lengths[i],len);
  if((ret=aaQueRead(claude->sse.handle,len,blok[i]))!=YES) { oops; }
  blok[i][len]=0;
  while(1)
   {
   if(blok[i][0]==0) { break; }
   if(aaCharIsVisible(blok[i][0])==YES) { break; }
   aaStringDeleteChars(blok[i],0,0,1);
   }
  //aaStringLastCharNonVisibleRemove(blok[i],0);
  aaStringLen(blok[i],&nlen);
  appLog("@#@## blobk i=%i nlen=%i",i,nlen);
  if(i==0)  { } // appLog(" "); }
  if(i!=1)  { } //appLog("%s",blok[i]); }
  if(i==1)
   {
   if(aaStringNICompare(blok[i],"data: ",6,0)!=YES) { oof; }
   aaStringReplaceString(&blok[i][6],0,"\\r",2,"\\\\r",3,1,answer_o);//
   aaStringCopy(&blok[i][6],answer_o);
   aaStringReplaceString(&blok[i][6],0,"\\n",2,"\\\\n",3,1,answer_o);//
   aaStringCopy(&blok[i][6],answer_o);
   appLog("a going to next reader %i",__LINE__);

   appProfiler(0,1,1);
   if((ret=aaJsonToTextReader(0,&blok[i][6],&tre))!=YES) { oops; }
   appLog("took %.5f",appProfiler(0,0,1));
   oof;

   //aaTextReaderDump(&tre,aaTextReaderProc);
   appLog("tre.line_count=%i line=%i",tre.line_count,__LINE__);
   appLog("@@@@@@!!!!!!!!!");
   for(li=0;li<tre.line_count;li++)
    {
    if((ret=aaTextReaderLineGet(&tre,li,&chars,txt))!=YES) { oops; break; }
    ///appLog("!!!!!!! li=%3i/%-3i chars=%-4i txt=%s",li,tre.line_count,chars,txt);
    if(li==0)
     {
     aaStringCopyfLen(needle.buf,&needle.len,"type:\"content_block_start\"");
     if(aaStringNICompare(txt,needle.buf,needle.len,0)==YES)
      {
      the_output[0]=0;
      }
     aaStringCopyfLen(needle.buf,&needle.len,"type:\"content_block_stop\"");
     if(aaStringNICompare(txt,needle.buf,needle.len,0)==YES) { oof; }
     }
    else
     {
     aaStringCopyfLen(needle.buf,&needle.len,"delta.text:");
     if(aaStringNICompare(txt,needle.buf,needle.len,0)==YES)
      {
      aaStringDeleteChars(txt,0,0,needle.len);
      aaStringUnQuote(txt,0,0);
      //aaStringAppendf(the_output,"%s",txt);
      aaStringAppend(the_output,txt);
      appLog("delta output=[%s]",the_output);
      }
     }
    }

   appLog("line=%i about to textreaderdump ",__LINE__);
   appLog("lile=%i",__LINE__);
   aaTextReaderDump(&tre,aaTextReaderProc);

   aaTextReaderDelete(&tre);
   }
  if(i==0)
   {
   //if((ret=aaQueDiscard(claude->sse.handle,1))!=YES) { oops; }
   }
  }
 if((ret=aaQueDiscard(claude->sse.handle,1))!=YES) { oops; }
 aaQueStatus(claude->sse.handle,&claude->sse.status);
 return RET_YES;
 }





 B claudeSet                           (_claude*claude,B isrdy,B issuc,H stage)
 {
 if(claude==NULL) { return RET_MISSINGPARM; }
 if(claude->magic!=aaHPP(claudeNew)) { return RET_NOTINITIALIZED; }
 claude->is_ready=isrdy;
 claude->is_success=issuc;
 claude->stage=stage;
 claude->response[0]=NULL_CHAR;
 return RET_YES;
 }





 B claudeRead                          (_claude*claude,HP chars,VP txt)
 {
 B ret;
 H cha;
 B answer[_64K];
 if(claude==NULL) { return RET_MISSINGPARM; }
 if(claude->magic!=aaHPP(claudeNew)) { return RET_NOTINITIALIZED; }
 if(chars) { *chars=0; }
 if(txt) { aaStringNull(txt); }

 if((ret=aaQueStringRead(claude->answer.handle,&cha,0,sizeof(answer),answer))!=YES) { return ret; }
 aaQueStatus(claude->answer.handle,&claude->answer.status);
 aaStringReplaceChar(answer,0,SQUOTE_CHAR,'`');
 aaStringReplaceChar(answer,0,DQUOTE_CHAR,'`');
 if(chars) { *chars=cha; }
 if(txt)   { aaMemoryCopy(txt,cha,answer); }
 return RET_YES;
 }





 B claudeYield                         (_claude*claude)
 {
 B ret;
 H go,to;
 N k;
 B smode;
 B cmd[_64K];
 B buf[_128K-_32K];
 H todo,left,chars,i;
 _httpresult hrs;
 _httpheader hdr;
 B str[_32K];
 _textreader tre;
 H ll,s,sl;
 B lin[_8K];
 B aft[_8K];
 B isok;
 B tetc[3][_64K];
 B answer_o[_64K];
 B cha;
 H fin,z;
 H msg_count;
 _textreader*atrp;
 _aisesh*asp;


 if(claude==NULL) { return RET_MISSINGPARM; }
 if(claude->magic!=aaHPP(claudeNew)) { return RET_NOTINITIALIZED; }
 go=0;
 to=3;

 while(1)
  {

  aa_user_line_executed=__LINE__;
  claudeDistill(claude);
  aa_user_line_executed=__LINE__;
  go++;
  if(go>to)
   {
   aa_user_line_executed=__LINE__;
   break;
   }
  aa_user_line_executed=__LINE__;

  asp=(_aisesh*)claude->aisesh_parent;
  atrp=(_textreader*)&asp->journal;

  //appLog("T%i %i",__LINE__,atrp->magic);


  switch(claude->stage)
   {
   case 1000:
   if(claude->usr_uid[0]==NULL_CHAR) { break; }
   appLog("UID!!!!!=%s",claude->usr_uid);
   aaStringCopyf(claude->vvvv[0],"%s",app.kfg.claude_defaults_model);
   aaStringCopyf(claude->vvvv[1],"%.1f",app.kfg.claude_defaults_temperature);
   aaStringCopyf(claude->vvvv[2],"%i",app.kfg.claude_defaults_max_tokens);
   aaStringCopyf(claude->vvvv[3],"%s",app.kfg.claude_defaults_system_prompt);

   fin=0;
   for(z=0;z<1000;z++)
    {
    if(aaTextReaderLineFind(atrp,fin,&ll,tetc[0],"\"role\":")!=YES) {  break; }    fin=ll+1;
    if(aaTextReaderLineFind(atrp,fin,&ll,tetc[1],"\"url\":")!=YES) { break; }      fin=ll+1;
    if(aaTextReaderLineFind(atrp,fin,&ll,tetc[2],"\"content\":")!=YES) { break; }  fin=ll+1;
    }
   claude->msg_count=z;
   claude->stage=1100;
   break;





   case 1100:
   if((ret=aaDynbufCreate(&claude->debu.handle))!=YES) { oops; }
   aaDynbufStatus(claude->debu.handle,&claude->debu.status);
   aaStringCopy(claude->host,app.kfg.claude_endpoint);
   claude->port=443;

   if((ret=aaQueCreate(&claude->sweets.handle))!=YES) { oops; }
   aaQueStatus(claude->sweets.handle,&claude->sweets.status);

   if((ret=aaQueCreate(&claude->sse.handle))!=YES) { oops; }
   aaQueStatus(claude->sse.handle,&claude->sse.status);

   if((ret=aaQueCreate(&claude->answer.handle))!=YES) { oops; }
   aaQueStatus(claude->answer.handle,&claude->answer.status);

   aa_user_line_executed=__LINE__;

   claude->stage=1200;
   break;





   case 1200:
   aa_user_line_executed=__LINE__;
   if((ret=aaNetTcpCallCreate(&claude->call.handle,0,0,claude->host,0,claude->port,1))!=YES) { oops; }
   aa_user_line_executed=__LINE__;
   claude->stage=1220;
   break;





   case 1220:
   aa_user_line_executed=__LINE__;
   aaNetTcpCallStatus(claude->call.handle,&claude->call.status);
   if(claude->call.status.is_connected!=YES) { break; }
   if(claude->call.status.is_ready!=YES) { break; }
   aa_user_line_executed=__LINE__;
   appLog("connected to %s port=%i, claude->stage=%i going to prompt",claude->host,claude->port,claude->stage);//iclaude is_ready claud->stage=%-5i  entering prompt",claude->stage);
   claudeSet(claude,YES,NO,CLAUDE_STAGE_PROMPT);
   break;




   case CLAUDE_STAGE_PROMPT:
   if(aaMathRand32(0,3)==0)
    {
    aaNetTcpCallStatus(claude->call.handle,&claude->call.status);
    //if(claude->call.status.is_ready==YES) { oof; }
    if(claude->call.status.is_ready==YES)
     {
     if(atrp->line_count==0) break;
     appLog("claude stage is prompt, now requesting trd line count=%i",atrp->line_count);
     claude->stage=CLAUDE_STAGE_REQUEST;
     }
    }
   break;




   case CLAUDE_STAGE_REQUEST: // send the request
   aaNetTcpCallStatus(claude->call.handle,&claude->call.status);
   if(claude->call.status.is_closed)
    {
    if(claude->call.handle!=0)
     {
     aaNetTcpCallDestroy(claude->call.handle);
     }
    appLog("reconnecting to claude connected!!!");
    if((ret=aaNetTcpCallCreate(&claude->call.handle,0,0,claude->host,0,claude->port,1))!=YES) { oops; }
    break;
    }
   if(claude->call.status.is_connected!=YES) { break; }
   if(claude->call.status.is_ready!=YES) { break; }

//      aaTextReaderDump(claude->trd,aaTextReaderProc);
   claude->is_ready=YES;
   claude->is_success=NO;

   aaDynbufReset(claude->debu.handle);
   aaDynbufAppendf(claude->debu.handle,"{");
   aaDynbufAppendf(claude->debu.handle,"\"model\":\"%s\",",claude->vvvv[0]);
   aaDynbufAppendf(claude->debu.handle,"\"temperature\":%s,",claude->vvvv[1]);
   aaDynbufAppendf(claude->debu.handle,"\"max_tokens\":%s,",claude->vvvv[2]);
   aaDynbufAppendf(claude->debu.handle,"\"stream\":true,");
   aaDynbufAppendf(claude->debu.handle,"\"system\":\"%s\",",claude->vvvv[3]);//tval);
   aaDynbufAppendf(claude->debu.handle,"\"messages\":");
   aaDynbufAppendf(claude->debu.handle,"[");

   aaTextReaderDump(atrp,aaTextReaderProc);
   k=0;
   fin=0;
   msg_count=0;
   while(1)
    {
    ///appLog("claude trd lc=%i",atrp->line_count);
    if(aaTextReaderLineFind(atrp,fin,&ll,tetc[0],"\"role\":")!=YES) { break; }
    fin=ll+1;
    if(aaTextReaderLineFind(atrp,fin,&ll,tetc[1],"\"url\":")!=YES) { appLog("not found %i %i",__LINE__,z); break; }
    fin=ll+1;
    if(aaTextReaderLineFind(atrp,fin,&ll,tetc[2],"\"content\":")!=YES) { appLog("not found %i %i",__LINE__,z); break; }
    fin=ll+1;

    aaStringReplaceString(tetc[2],0,"\"\"",2,"\"ok\"",4,0,answer_o);
    aaStringCopy(tetc[2],answer_o);
    aaStringReplaceString(tetc[2],0,"\\\"",2,"`",1,0,answer_o);
    aaStringCopy(tetc[2],answer_o);
    aaStringReplaceString(tetc[2],0,"\\\'",2,"`",1,0,answer_o);
    aaStringCopy(tetc[2],answer_o);
    aaStringLastCharDeleteIfChar(tetc[0],0,',');
    aaStringLastCharDeleteIfChar(tetc[1],0,',');
    aaStringLastCharDeleteIfChar(tetc[2],0,',');

    appLog("k=%i ll=%i [%s] [%s] [%s]",k,ll,tetc[0],tetc[1],tetc[2]);

    if(tetc[0][1]=='u')
     {
     if(tetc[1][0]>SPACE_CHAR&&aaStringNICompare(tetc[1],"null",4,0)!=YES)
      {
      aaDynbufAppendf(claude->debu.handle,"{");
      aaDynbufAppendf(claude->debu.handle,"\"role\":%s,",tetc[0]);
      aaDynbufAppendf(claude->debu.handle,"\"content\":");
      aaDynbufAppendf(claude->debu.handle,"[");
      aaDynbufAppendf(claude->debu.handle,"{");
      aaDynbufAppendf(claude->debu.handle,"\"type\":\"image\",");
      aaDynbufAppendf(claude->debu.handle,"\"source\":");
      aaDynbufAppendf(claude->debu.handle,"{");
      aaDynbufAppendf(claude->debu.handle,"\"type\":\"url\",");
      aaDynbufAppendf(claude->debu.handle,"\"url\":%s",tetc[1]);
      aaDynbufAppendf(claude->debu.handle,"}");
      aaDynbufAppendf(claude->debu.handle,"},");
      aaDynbufAppendf(claude->debu.handle,"{");
      aaDynbufAppendf(claude->debu.handle,"\"type\":\"text\",");
      aaDynbufAppendf(claude->debu.handle,"\"text\":%s",tetc[2]);
      aaDynbufAppendf(claude->debu.handle,"}");
      aaDynbufAppendf(claude->debu.handle,"]");
      aaDynbufAppendf(claude->debu.handle,"}");
      }
     else
      {
      aaDynbufAppendf(claude->debu.handle,"{");
      aaDynbufAppendf(claude->debu.handle,"\"role\":%s,",tetc[0]);
      aaDynbufAppendf(claude->debu.handle,"\"content\":");
      aaDynbufAppendf(claude->debu.handle,"[");
      aaDynbufAppendf(claude->debu.handle,"{");
      aaDynbufAppendf(claude->debu.handle,"\"type\":\"text\",");
      aaDynbufAppendf(claude->debu.handle,"\"text\":%s",tetc[2]);
      aaDynbufAppendf(claude->debu.handle,"}");
      aaDynbufAppendf(claude->debu.handle,"]");
      aaDynbufAppendf(claude->debu.handle,"}");
      //appLog("dynbuf append %s %s",tetc[0],tetc[2]);
      }
     }
    else
     {
     aaDynbufAppendf(claude->debu.handle,"{");
     aaDynbufAppendf(claude->debu.handle,"\"role\":%s,",tetc[0]);
     aaDynbufAppendf(claude->debu.handle,"\"content\":%s",tetc[2]);
     aaDynbufAppendf(claude->debu.handle,"}");
     }
    aaDynbufAppendf(claude->debu.handle,",");
    k++;
    msg_count++;
    }

   if(aaDynbufStatus(claude->debu.handle,&claude->debu.status)!=YES) oof;
   aaStringLastCharGet(claude->debu.status.mem,0,&cha);
   if(cha==',')
    {
    if(aaDynbufDeleteByte(claude->debu.handle)!=YES) oof;
    if(aaDynbufStatus(claude->debu.handle,&claude->debu.status)!=YES) oof;
    aaStringLastCharGet(claude->debu.status.mem,0,&cha);
    }

   aaDynbufAppendf(claude->debu.handle,"]");
   aaDynbufAppendf(claude->debu.handle,"}");
   aaDynbufStatus(claude->debu.handle,&claude->debu.status);
   claude->debu.status.mem[claude->debu.status.bytes_used]=NULL_CHAR;

   //aaStringReplaceString(claude->debu.status.mem,0,"\"",1,"\\\"",2,0,claude->debu.status.mem);
   //aaLog(-555,"%s",claude->debu.status.mem);
   if(msg_count==0) { oof; break; }

   aaStringNull(cmd);
   aaStringAppendf(cmd,"POST /v1/messages HTTP/1.1\r\n");
   aaStringAppendf(cmd,"Host: %s\r\n",claude->host);
   aaStringAppendf(cmd,"x-api-key: %s\r\n",app.kfg.claude_key);
   aaStringAppendf(cmd,"anthropic-version: 2023-06-01\r\n");
   aaStringAppendf(cmd,"content-type: application/json\r\n");
   aaStringAppendf(cmd,"content-length: %i\r\n",claude->debu.status.bytes_used);
   aaStringAppendf(cmd,"Accept: text/event-stream\r\n");
   aaStringAppendf(cmd,"connection: keep-alive\r\n");
   aaStringAppendf(cmd,"\r\n");
   aaNetTcpCallWritef(claude->call.handle,"%s",cmd);
   aaNetTcpCallWrite(claude->call.handle,claude->debu.status.bytes_used,claude->debu.status.mem);
   claude->debu.status.mem[claude->debu.status.bytes_used]=NULL_CHAR;

   aaNetTcpCallStatus(claude->call.handle,&claude->call.status);
   ///appLog("sent claude req, waiting for response");
   claude->stage=CLAUDE_STAGE_WAITRESPONSE;
   break;




   case CLAUDE_STAGE_WAITRESPONSE: // after we send request, we jump here for response
   aaNetTcpCallStatus(claude->call.handle,&claude->call.status);
   if(0&&claude->call.status.rcve_inactivity>=aaSecs(10)) { oof; }
   if(claude->call.status.is_closed)
    {
    app.do_restart=1;
    aaNote(0,"line=%i, do_restart=%i",__LINE__,app.do_restart);
    return RET_YES;
    }
   if(aaNetTcpCallStringRead(claude->call.handle,&chars,&smode,sizeof(buf),buf)!=YES) {  break; }
   buf[chars]=0;
   if(chars==0) { break; }
   if((ret=aaNetHttpResultReadFromString(&hrs,chars,buf))!=YES) { oops; }
   httpInfoInit(&claude->http_info);
   if((ret=httpInfoResultAdd(&claude->http_info,&hrs))!=YES) { oops; }
   if(claude->http_info.result.code!=200)
    {
    appLog("rRES: %i  %s",claude->http_info.result.code,buf);
    }
   claude->stage=2015;
   break;





   case 2015:
   aaNetTcpCallStatus(claude->call.handle,&claude->call.status);
   if(0&&claude->call.status.rcve_inactivity>=aaSecs(10)) { oof; }
   if(claude->call.status.is_closed)
    {
    aaNote(0,"line=%i closedbyloc=%i closedbyrem=%i",__LINE__,claude->call.status.is_closed_by_local,claude->call.status.is_closed_by_remote);
    }
   if(aaNetTcpCallStringRead(claude->call.handle,&chars,&smode,sizeof(buf),buf)!=YES) {  break; }
   if((ret=aaNetHttpHeaderReadFromString(&hdr,chars,buf))!=YES) { oops; }
   if((ret=httpInfoHeaderAdd(&claude->http_info,&hdr))!=YES) { oops; }
   if(chars!=0) { break; }
   ///appLog("claude checking %i http headers",claude->http_info.header_count);
   for(i=0;i<claude->http_info.header_count;i++)
    {
    if(claude->http_info.result.code!=200)
     {
     appLog("rHED: fc=%-3i %s=%s",claude->http_info.header[i].field_code,claude->http_info.header[i].field,claude->http_info.header[i].data);
     }
    if(claude->http_info.header[i].field_code==aa_HTTPFIELD_UNIMPLEMENTED) { continue; }
    // SEE mod_junk.c
    switch(claude->http_info.header[i].field_code)
     {
     case aa_HTTPFIELD_TRANSFERENCODING:     break;
     case aa_HTTPFIELD_CONTENTLENGTH:     break;
     case aa_HTTPFIELD_LOCATION:  aaStringCopy(claude->location,claude->http_info.header[i].data);   break;
     case aa_HTTPFIELD_CONTENTTYPE:   aaStringCopy(claude->content_type,claude->http_info.header[i].data);   break;
     }
    }
   claude->chunk_size=0;
   claude->stage=2025;
   break;




   case 2025:
   if(aaNetHttpChunkSizeRead(claude->call.handle,&claude->chunk_size)!=YES) { break; }
   claude->chunk_done=0;
   if(claude->chunk_size==0)  {  claude->stage=3000;   break;    }
   claude->chunk_done=0;
   claude->stage=2045;
   break;




   case 2040:
   if(aaNetHttpChunkSizeRead(claude->call.handle,&claude->chunk_size)!=YES) { break; }
   claude->chunk_done=0;
   //aaQueStatus(claude->builda.handle,&claude->builda.status);
   if(claude->chunk_size==0)
    {
    while(1)
     {
     aaQueStatus(claude->sweets.handle,&claude->sweets.status);
     if(aaQueStringRead(claude->sweets.handle,&chars,0,sizeof(str),str)==RET_YES)
      {
      if(str[0]=='d')
       {
       //appLog("reset line = %i",__LINE__);
       //resetkeith();
       if((ret=aaJsonToTextReader(0,&str[5],&tre))!=YES) { oops; }
       ///appLog("$$$$$$ line=%i jsontotr lc=%i",__LINE__,tre.line_count);
       ///aaTextReaderDump(&tre,aaTextReaderProc);
       if((ret=aaTextReaderLineGet(&tre,0,&chars,lin))!=YES) { oops; }
       while(1)
        {
        isok=0;
        if(aaStringICompare(lin,"type:\"content_block_start\"",0)==YES) { isok=1; break; }
        if(aaStringICompare(lin,"type:\"content_block_delta\"",0)==YES) { isok=2; break; }
        if(aaStringICompare(lin,"type:\"content_block_stop\"",0)==YES) { isok=3; break; }
        isok=0;
        break;
        }
       if(isok==1)
        {
        aaStringNull(claude->response);
        }
       else
       if(isok==2)
        {
        if(aaTextReaderLineFind(&tre,0,&ll,aft,"delta.text:",0)==YES)
         {
         aaStringUnQuote(aft,0,0);
         aaStringReplaceChar(aft,0,'`',DQUOTE_CHAR);
         aaStringAppend(claude->response,aft);
         }
        //aaTextReaderDump(&tre,aaTextReaderProc);
        }
       else
       if(isok==3)
        {
//        appLog("%s",claude->response);
        }
       aaTextReaderDelete(&tre);
       }
      continue;
      }
     break;
     }
    claude->stage=3000;
    break;
    }
   claude->chunk_done=0;
   claude->stage=2240;
   claude->stage=2045;
   break;



   case 2045:
   aaNetTcpCallStatus(claude->call.handle,&claude->call.status);
   if(0&&claude->call.status.rcve_inactivity>=aaSecs(10)) { oof; }
   if(claude->call.status.is_closed)
    {
    aaNote(0,"line=%i closedbyloc=%i closedbyrem=%i",__LINE__,claude->call.status.is_closed_by_local,claude->call.status.is_closed_by_remote);
    }
   todo=claude->chunk_size-claude->chunk_done;
   left=claude->chunk_size-claude->chunk_done;
   if(left==0) { oof; }
   todo=left;
   if(todo>claude->call.status.rcve_bytes)  {   todo=claude->call.status.rcve_bytes;  }
   if(todo==0) { break; }
   if((ret=aaNetTcpCallRead(claude->call.handle,(H)todo,buf))!=YES) { oops; }
   buf[(H)todo]=NULL_CHAR;
   if(claude->http_info.result.code!=200)
    {
    appLog("%s",buf);
    }
   aaQueWrite(claude->sweets.handle,todo,buf);
   aaQueStatus(claude->sweets.handle,&claude->sweets.status);
   claude->chunk_done+=(H)todo;
   left=claude->chunk_size-claude->chunk_done;
   if(left>0)  { oof;   }
   buf[claude->chunk_size]=NULL_CHAR;
   ///appLog("2045 chunk=%i",claude->chunk_size);
   //appLog("%s",buf);
   claude->response[0]=NULL_CHAR;
   claude->stage=2040;
   break;



   case 2090:
   for(i=0;i<claude->http_info.header_count;i++)
    {
    //appLog("i=%i fc=%i %s=%s",i,claude->http_info.header[i].field_code,claude->http_info.header[i].field,claude->http_info.header[i].data);
    switch(claude->http_info.header[i].field_code)
     {
     case aa_HTTPFIELD_CONTENTLENGTH:
     claude->is_content_length=YES;
     claude->is_chunked=NO;
     claude->content_length=claude->http_info.header[i].value[0];
     claude->content_done=0;
     break;
     case aa_HTTPFIELD_TRANSFERENCODING:
     claude->is_chunked=YES;
     claude->is_content_length=NO;
     claude->content_done=0;
     break;
     case aa_HTTPFIELD_LOCATION:
     aaStringCopy(claude->location,claude->http_info.header[i].data);
     break;
     case aa_HTTPFIELD_CONTENTTYPE:
     aaStringCopy(claude->content_type,claude->http_info.header[i].data);
     appLog("CT=%s",claude->content_type);
     break;
     }
    }
   if(1&&claude->is_chunked==YES)
    {
    claude->chunk_size=0;
    claude->chunk_done=0;
    claude->stage=2230;
    break;
    }
   if(1&&claude->is_content_length==YES)
    {
    claude->stage=2320;
    break;
    }
   appLog(">> nnr??");
   oof;
   claude->stage=2210;
   break;



   case 2222: // last crlf
   appLog("left=%i",claude->call.status.rcve_bytes);
   if(claude->call.status.rcve_bytes<2) { break; }
   if((ret=aaNetTcpCallStringRead(claude->call.handle,&chars,&smode,sizeof(buf),buf))!=YES)  {  oops;   break;    }
   ///appLog("last chunk crlf chars=%i smode=%i",chars,smode);
   claude->stage=3000;
   break;




   case 2230: // chunked
   //   aaQueStatus(claude->builda.handle,&claude->builda.status);
   aaNetTcpCallStatus(claude->call.handle,&claude->call.status);
   if(0&&claude->call.status.rcve_inactivity>=aaSecs(10)) { oof; }
   if(claude->call.status.is_closed)
    {
    aaNote(0,"line=%i closedbyloc=%i closedbyrem=%i",__LINE__,claude->call.status.is_closed_by_local,claude->call.status.is_closed_by_remote);
    }
   if(aaNetHttpChunkSizeRead(claude->call.handle,&claude->chunk_size)!=YES) { break; }
   claude->chunk_done=0;
   //   aaQueStatus(claude->builda.handle,&claude->builda.status);
   ///   appLog("######## 2230  zsschunk_size=%x",claude->chunk_size);
   if(claude->chunk_size==0)
    {
    ///appLog("2240, chunk_size==0");
    claude->stage=2222;
    break;
    }
   claude->chunk_done=0;
   claude->stage=2240;
   break;




   case 2240:
   aaNetTcpCallStatus(claude->call.handle,&claude->call.status);
   if(0&&claude->call.status.rcve_inactivity>=aaSecs(10)) { oof; }
   if(claude->call.status.is_closed)
    {
    aaNote(0,"line=%i closedbyloc=%i closedbyrem=%i",__LINE__,claude->call.status.is_closed_by_local,claude->call.status.is_closed_by_remote);
    }
   todo=claude->chunk_size-claude->chunk_done;
   left=claude->chunk_size-claude->chunk_done;
   if(left==0)
    {
    aaDebugf("todozereo  %s %-5i  secs=%.4f  ms=%.4f todo 0000",__func__,__LINE__,aaSecsRunning()/1.0,aaMsRunning()/1.0);
    claude->stage=2230;
    break;
    }
   todo=left;
   if(todo>claude->call.status.rcve_bytes)  {   todo=claude->call.status.rcve_bytes;  }
   if(todo==0) { break; }
   if((ret=aaNetTcpCallRead(claude->call.handle,(H)todo,buf))!=YES) { oops; }
   buf[(H)todo]=NULL_CHAR;
   aaQueWrite(claude->sweets.handle,todo,buf);
   aaQueStatus(claude->sweets.handle,&claude->sweets.status);
   claude->chunk_done+=(H)todo;
   left=claude->chunk_size-claude->chunk_done;
   if(left>0)  { oof;   }
   buf[claude->chunk_size]=NULL_CHAR;

   if((ret=aaQueWrite(claude->sse.handle,claude->chunk_size,buf))!=YES) { oops; }
   aaQueStatus(claude->sse.handle,&claude->sse.status);

   appLog("write sse [%s]",buf);
   claude->stage=2230;
   break;



   case 3000: // completed !!!
   if(aaStringICompare(claude->content_type,"text/event-stream; charset=utf-8",0)!=YES)
    {
    ////    aaNote(0,"claude->content_type=%s",claude->content_type);
    appLog("!!!!!!! content_type=%s",claude->content_type);
    }
   claude->stage=3007;
   break;




   case 3007:
   claude->response_preutf[0]=0;
   claude->response_preutf[1]=0;
   claude->stage=CLAUDE_STAGE_COMPLETED;
  // appLog("claude complete");
   break;





   case CLAUDE_STAGE_COMPLETED:
   aaStringLen(claude->response,&sl);
    /// appLog("!!! claude response sl=%i %c [%s]",sl,app.the_aisesh->whos_turn,claude->response);
      if((Z)sl!=UtfStrlen((CP)claude->response))
       {
       aaStringCopy(claude->response_preutf,(CP)claude->response);
 ///appLog("### claude->response=[%s]",claude->response);
       aaMemoryFill(str,sizeof(str),0);
       UtfEscape((CP)claude->response,(CP)str,sizeof(str));
       //appLog("claude response escaped=[%s]",str);
       aaStringCopy(claude->response,str);
       }

   for(s=0;s<sl;s++) { if(claude->response[s]<32||claude->response[s]>127) { claude->response[s]=32; } }

   //appLog("!! write answer ROLE=%c [%s]",app.the_aisesh->whos_turn,claude->response);
   appLog("!! write answer ROLE=%c [%s]",asp->whos_turn,claude->response);

   aaQueWritef(claude->answer.handle,"%s\n",claude->response);
   aaQueStatus(claude->answer.handle,&claude->answer.status);
   claude->stage=CLAUDE_STAGE_PROMPT;
   claude->response[0]=NULL_CHAR;
   //historyDump(&app.hihihi);
   //historySave(&app.hihihi,HIS_FILE);
   //appLog("re-entering claude prompt");
   break;
   }
  }
 aa_user_line_executed=__LINE__;
 return RET_YES;
 }






//===================================
//===================================




 B fluxSttNew                          (_fluxstt*fluxstt,VP key)
 {
 B ret;
 if(fluxstt==NULL) { return RET_MISSINGPARM; }
 aaMemoryFill(fluxstt,sizeof(_fluxstt),0);
 fluxstt->magic=aaHPP(fluxSttNew);
 aaStringCopy(fluxstt->key,key);
 fluxstt->keep_alive_ms=aaMsRunning();
 fluxstt->keep_alive_el=0;
 if((ret=aaMemoryUnitAllocate(&fluxstt->flux_memu,_256K))!=YES) { oops; }
 return RET_YES;
 }





 B fluxSttDelete                       (_fluxstt*fluxstt)
 {
 if(fluxstt==NULL) { return RET_MISSINGPARM; }
 if(fluxstt->magic!=aaHPP(fluxSttNew)) { return RET_NOTINITIALIZED; }
 if(fluxstt->flux_memu.bytes>0) { aaMemoryUnitRelease(&fluxstt->flux_memu); }
 aaNetWebsocketClientDelete(&fluxstt->ws_cli);
 aaMemoryFill(fluxstt,sizeof(_fluxstt),0);
 return RET_YES;
 }





 B fluxSttWrite                        (_fluxstt*fluxstt,H len,VP mem)
 {
 B ret;
 if(fluxstt==NULL) { return RET_MISSINGPARM; }
 if(fluxstt->magic!=aaHPP(fluxSttNew)) { return RET_NOTINITIALIZED; }
 if((ret=aaNetWebsocketClientPktWrite(&fluxstt->ws_cli,2,1,len,mem))!=YES) { oops; }
 fluxstt->keep_alive_ms=aaMsRunning();
 fluxstt->keep_alive_el=0;
 return RET_YES;
 }




 B fluxSttFlush                        (_fluxstt*fluxstt)
 {
 B ret;
 if(fluxstt==NULL) { return RET_MISSINGPARM; }
 if(fluxstt->magic!=aaHPP(fluxSttNew)) { return RET_NOTINITIALIZED; }
 if((ret=aaNetWebsocketClientPktWritef(&fluxstt->ws_cli,1,1,"{\"type\": \"Flush\"}"))!=YES) { oops; }
 return RET_YES;
 }






 B fluxSttForceEndTurn                 (_fluxstt*fluxstt)
 {
 B ret;
 if(fluxstt==NULL) { return RET_MISSINGPARM; }
 if(fluxstt->magic!=aaHPP(fluxSttNew)) { return RET_NOTINITIALIZED; }
 if((ret=aaNetWebsocketClientPktWritef(&fluxstt->ws_cli,1,1,"{\"type\": \"ForceEndTurn\"}"))!=YES) { oops; }
 return RET_YES;
 }




 B fluxSttEventProcess                 (_fluxstt*fluxstt,_fluxsttevent*fsev)
 {
 //B out[_4K];
 //H w;
 //_textreader*atrp;
 _aisesh*asp;


 if(fluxstt==NULL) { return RET_MISSINGPARM; }
 if(fluxstt->magic!=aaHPP(fluxSttNew)) { return RET_NOTINITIALIZED; }
 if(fsev==NULL) { return RET_MISSINGPARM; }

 asp=(_aisesh*)fluxstt->aisesh_parent;
// atrp=(_textreader*)&asp->journal;

 if(fsev->type_hash==flux_TurnInfo)
  {
  if(fsev->event_hash==flux_StartOfTurn||
     fsev->event_hash==flux_EagerEndOfTurn||
     fsev->event_hash==flux_EndOfTurn||
     fsev->event_hash==flux_TurnResumed||
     fsev->event_hash==flux_Update)
   {
   if(fsev->event_hash==flux_StartOfTurn) { appLog(" "); }

   if(strlen((CP)fsev->transcript)>=2)
    {

    if(fsev->event_hash==flux_EndOfTurn)
     {
//     asp=(_aisesh*)&app.the_aisesh;
     //appLog("save=%s",asp->save_full);
//     atrp=(_textreader*)&app.the_aisesh->journal;
     appLog("about to aadd user who=%c journal %s",asp->whos_turn,fsev->transcript);
//     appLog("T%i %i",__LINE__,atrp->magic);

     myseshListAppend(asp,"user",0,"%s",fsev->transcript);
     //appLog("%s",fsev->transcript);
     }
     //aaFileDelete(aisesh->save_full);
    //appLog("%-20s %s",fsev->event,fsev->transcript);
    return RET_YES;
    }
   }
  }

 return RET_YES;
 }














 B fluxSttEventDump                    (_fluxstt*fluxstt,_fluxsttevent*fsev)
 {
 B out[_4K];
 H w;
 //_textreader*atrp;
 //_aisesh*asp;


 if(fluxstt==NULL) { return RET_MISSINGPARM; }
 if(fluxstt->magic!=aaHPP(fluxSttNew)) { return RET_NOTINITIALIZED; }
 if(fsev==NULL) { return RET_MISSINGPARM; }

 //asp=(_aisesh*)fluxstt->aisesh_parent;
 //atrp=(_textreader*)&asp->journal;


 appLog(" ");
 aaStringNull(out);
 aaStringAppendf(out,"type=%s (0x%08x)",fsev->type,fsev->type_hash);
 if(fsev->event[0])
  {
  aaStringAppendf(out,"   ");
  aaStringAppendf(out,"event=%s (0x%08x)",fsev->event,fsev->event_hash);
  }
 if(fsev->trigger[0])
  {
  aaStringAppendf(out,"     ");
  aaStringAppendf(out,"trigger=%s",fsev->trigger);
  }
 if(fsev->req_id[0])
  {
  aaStringAppendf(out,"      ");
  aaStringAppendf(out,"request_id=%s",fsev->req_id);
  }
 appLog("%s",out);
 aaStringNull(out);
 aaStringAppendf(out,"turn_index=%i",fsev->turn_index);
 aaStringAppendf(out,"    ");
 aaStringAppendf(out,"sequence_id=%i",fsev->sequence_id);
 aaStringAppendf(out,"    ");
 aaStringAppendf(out,"fsev_counter=%i",fsev->fsev_counter);
 aaStringAppendf(out,"    ");

 if(fsev->audio_win[0]>0||fsev->audio_win[1]>0||fsev->eot_confidence>0)
  {
  aaStringAppendf(out,"   ");
  aaStringAppendf(out,"audio_win[0]=%.1f",fsev->audio_win[0]);
  aaStringAppendf(out,"  ");
  aaStringAppendf(out,"audio_win[1]=%.1f",fsev->audio_win[1]);
  aaStringAppendf(out,"   ");
  aaStringAppendf(out,"eot_confidence=%.1f",fsev->eot_confidence);
  }
 appLog("%s",out);
 if(fsev->word_count>0||fsev->languages_count>0||fsev->languages_hinted_count>0)
  {
  aaStringNull(out);
  aaStringAppendf(out,"languages_count=%i",fsev->languages_count);
  aaStringAppendf(out,"       ");
  aaStringAppendf(out,"languages_hinted_count=%i",fsev->languages_hinted_count);
  aaStringAppendf(out,"       ");
  aaStringAppendf(out,"word_count=%i",fsev->word_count);
  if(0) { appLog("%s",out); }
  }
 w=0;
 while(1)
  {
  if(w>=fsev->languages_count&&w>=fsev->languages_hinted_count) { break; }
  aaStringNull(out);
  if(fsev->languages_count>w)
   {
   aaStringAppendf(out,"languages[%i]=%s",w,fsev->languages[w]);
   aaStringAppendf(out,"       ");
   }
  if(fsev->languages_hinted_count>w)
   {
   aaStringAppendf(out,"languages_hinted[%i]=%s",w,fsev->languages_hinted[w]);
   }
  if(0) { appLog("%s",out); }
  w++;
  }

 for(w=0;w<fsev->word_count;w++)
  {
  aaStringNull(out);
  aaStringAppendf(out,"word[%-2i]  ",w);
  aaStringAppendf(out,"s=%-9.1f  ",fsev->word[w].start);
  aaStringAppendf(out,"e=%-9.1f  ",fsev->word[w].end);
  aaStringAppendf(out,"c=%-9.1f  ",fsev->word[w].confidence);
  aaStringAppendf(out,"w=%s ",fsev->word[w].word);
  if(0) { appLog("%s",out); }
  }

 if(strlen((CP)fsev->transcript)>2)
  {
  aaStringNull(out);
  aaStringAppendf(out,"transcript=%s",fsev->transcript);
  appLog("%s",out);
  }
 appLog(" ");

 return RET_YES;
 }






 B fluxSttYield                        (_fluxstt*fluxstt)
 {
 B ret;
 B etc[_8K];
 B tok[_32K];
 H ita,j,cnt;
 _str32k needle;
 _textreader trd;
 _textpair tpx[FLUX_STT_MAX_WORDS];
 _fluxsttevent fsev;
 _aisesh*asp;

 if(fluxstt==NULL) { return RET_MISSINGPARM; }
 if(fluxstt->magic!=aaHPP(fluxSttNew)) { return RET_NOTINITIALIZED; }


 asp=(_aisesh*)fluxstt->aisesh_parent;
  //atrp=(_textreader*)&asp->journal;

 //if(app.the_aisesh==NULL) { oof; }
 ita=3;
 while(ita--)
  {
  aa_user_line_executed=__LINE__;
  switch(fluxstt->stage)
   {
   case 0:
   fluxstt->stage=10;
   break;

   case 10:
   aaStringCopyf(tok,"Token %s",fluxstt->key);
   aaStringNull(etc);
   aaStringAppendf(etc,"model=flux-general-multi");
   aaStringAppendf(etc,"&language_hint=en");
   aaStringAppendf(etc,"&sample_rate=16000");
   aaStringAppendf(etc,"&eager_eot_threshold=0.5");
   aaStringAppendf(etc,"&eot_threshold=0.5");
   aaStringAppendf(etc,"&eot_timeout_ms=3000");
   if((ret=aaNetWebsocketClientNew(&fluxstt->ws_cli,0,0,app.kfg.deepgram_endpoint,0,443,1,tok,"/v2/listen?encoding=linear16&%s",etc))!=YES) { oops; }
   fluxstt->stage=20;
   break;


   case 20:
   if((ret=aaNetWebsocketClientYield(&fluxstt->ws_cli))!=YES) { oops; }
   if(fluxstt->ws_cli.cd->is_ready!=YES) { break; }
   appLog("connected to v2 url=%s listen wss ready",fluxstt->ws_cli.cd->url);
   fluxstt->stage=90;
   break;




   case 90:
   if((ret=aaNetWebsocketClientYield(&fluxstt->ws_cli))!=YES) { oops; }
   fluxstt->keep_alive_el=aaMsRunning()-fluxstt->keep_alive_ms;
   if(fluxstt->keep_alive_el>app.kfg.deepgram_keepalive)
    {
    if((ret=aaNetWebsocketClientPktWritef(&fluxstt->ws_cli,1,1,"{\"type\":\"KeepAlive\"}"))!=YES) { oops; }
    fluxstt->keep_alive_ms=aaMsRunning();
    fluxstt->keep_alive_el=0;
    fluxstt->keep_alive_trigs++;
    }

   if(aaNetWebsocketClientPktRead(&fluxstt->ws_cli,&fluxstt->ws_hdr,fluxstt->flux_memu.mem)!=YES) { break; }

   fluxstt->flux_memu.mem[fluxstt->ws_hdr.bytes]=NULL_CHAR;
   fluxstt->keep_alive_ms=aaMsRunning();
   fluxstt->keep_alive_el=0;
   if((ret=aaJsonToTextReader(fluxstt->ws_hdr.bytes,fluxstt->flux_memu.mem,&trd))!=YES) { oops; }
   //appLog("$$$$$$ line=%i jsontotr lc=%i",__LINE__,trd.line_count);
   //aaTextReaderDump(&trd,aaTextReaderProc);
   cnt=0;
   for(j=0;j<trd.line_count;j++)
    {
    if((ret=aaTextReaderPairGet(&trd,j,&tpx[j]))!=YES) { oops; break; }
    //if(j==0) appLog("----");
    //textpairLineLog(&tpx[j],123);//trd.line_count);
    cnt++;
    }



  if(trd.line_count>0)
   {
   aaMemoryFill(&fsev,sizeof(_fluxsttevent),0);
   j=0;
   while(1)
    {
    if(j>=trd.line_count) { break; }
    if(tpx[j].key_hash==flux_type)      {      fsev.type_hash=tpx[j].val_hash;      }
    if(tpx[j].key_hash==flux_event)      {      fsev.event_hash=tpx[j].val_hash;      }
    while(1)
     {
     if(tpx[j].key_hash==flux_type)           {      aaStringCopy(fsev.type,tpx[j].val);      break;      }
     if(tpx[j].key_hash==flux_request_id)     {      aaStringCopy(fsev.req_id,tpx[j].val);      break;      }
     if(tpx[j].key_hash==flux_event)          {      aaStringCopy(fsev.event,tpx[j].val);      break;      }
     if(tpx[j].key_hash==flux_turn_index)     {      fsev.turn_index=(H)tpx[j].gv; break; }
     if(tpx[j].key_hash==0x97025366)          {      fsev.audio_win[0]=(H)tpx[j].gv; break; }
     if(tpx[j].key_hash==0x45a6b270)          {      fsev.audio_win[1]=(H)tpx[j].gv; break; }
     if(tpx[j].key_hash==flux_transcript)     {      aaStringCopy(fsev.transcript,tpx[j].val);      break;      }
     if(tpx[j].key_hash==flux_eot_confidence) {      fsev.eot_confidence=tpx[j].dv;  break;      }
     if(tpx[j].key_hash==flux_sequence_id)    {      fsev.sequence_id=tpx[j].gv;  break;      }
     if(tpx[j].key_hash==0xc3afd061)          {      aaStringCopy(fsev.trigger,tpx[j].val);      break;      }

     if(tpx[j].key[0]=='w')
      {
      aaStringCopyfLen(needle.buf,&needle.len,"words[%i].word",fsev.word_count);
      if(aaStringNICompare(tpx[j].key,needle.buf,needle.len,0)==YES)
       {
       aaStringCopy(fsev.word[fsev.word_count].word,tpx[j].val);
       if(tpx[j+1].key[0]=='w')
        {
        aaStringCopyfLen(needle.buf,&needle.len,"words[%i].confidence",fsev.word_count);
        if(aaStringNICompare(tpx[j+1].key,needle.buf,needle.len,0)==YES)
         {
         fsev.word[fsev.word_count].confidence=tpx[j+1].dv;
         if(tpx[j+2].key[0]=='w')
          {
          aaStringCopyfLen(needle.buf,&needle.len,"words[%i].start",fsev.word_count);
          if(aaStringNICompare(tpx[j+2].key,needle.buf,needle.len,0)==YES)
           {
           fsev.word[fsev.word_count].start=tpx[j+2].dv;
           if(tpx[j+3].key[0]=='w')
            {
            aaStringCopyfLen(needle.buf,&needle.len,"words[%i].end",fsev.word_count);
            if(aaStringNICompare(tpx[j+3].key,needle.buf,needle.len,0)==YES)
             {
             fsev.word[fsev.word_count].end=tpx[j+3].dv;
             fsev.word_count++;
             }
            }
           }
          }
         }
        }
       break;
       }
      }

     aaStringCopyfLen(needle.buf,&needle.len,"languages[%i]",fsev.languages_count);
     if(aaStringNICompare(tpx[j].key,needle.buf,needle.len,0)==YES)
      {
      aaStringCopy(fsev.languages[fsev.languages_count],tpx[j].val);
      fsev.languages_count++;
      break;
      }
     aaStringCopyfLen(needle.buf,&needle.len,"languages_hinted[%i]",fsev.languages_hinted_count);
     if(aaStringNICompare(tpx[j].key,needle.buf,needle.len,0)==YES)
      {
      aaStringCopy(fsev.languages_hinted[fsev.languages_hinted_count],tpx[j].val);
      fsev.languages_hinted_count++;
      break;
      }

     break;
     }
    j++;
    }

   ///   fluxSttEventDump(fluxstt,&fsev);
   //appLog("line=%i sf=%s",__LINE__,asp->save_full);
   if((ret=myseshFsevQueWrite(asp,&fsev))!=YES) { oops; }
   }

   ///if((ret=myseshMsgQueWrite(app.the_aisesh,cnt,&tpx[0]))!=YES) { oops; }
   aaTextReaderDelete(&trd);
   break;
   }

  }
 return RET_YES;
 }





//===================================
//===================================



 B myseshNew                           (_aisesh*aisesh)
 {
 B ret;
 aaMemoryFill(aisesh,sizeof(_aisesh),0);
 aisesh->magic=1234;
 aisesh->stage=100;
 //if((ret=aaFileUnitLoad(&aisesh->filu,"amycar2.wav"))!=YES) { oops; }
 if((ret=aaFileUnitLoad(&aisesh->filu,"shiri1.wav"))!=YES) { oops; }

 aisesh->lo_lev=+9999;
 aisesh->hi_lev=-9999;
 aisesh->acum_lev=0;
 aisesh->acum_cnt=0;

 aaQueCreate(&aisesh->audio_out_que.handle);
 aaQueStatus(aisesh->audio_out_que.handle,&aisesh->audio_out_que.status);


 aaQueCreate(&aisesh->msg_que.handle);
 aaQueStatus(aisesh->msg_que.handle,&aisesh->msg_que.status);
 aaQueCreate(&aisesh->fsev_que.handle);
 aaQueStatus(aisesh->fsev_que.handle,&aisesh->fsev_que.status);

 //appLog("line=%i sf=%s",__LINE__,aisesh->save_full);

 //appLog("%s",__func__);
 return RET_YES;
 }







 B myseshDelete                        (_aisesh*aisesh)
 {
 B ret;
 H li,chars,done;
 B txt[_64K];
 _filestreamunit fu;

 aaFileUnitRelease(&aisesh->filu);

 if((ret=aaFileStreamCreateNewQuick(&fu.handle,aisesh->save_full))!=YES) { aaNote(0,"failed to create %s %s",arets,aisesh->save_full);  }
 done=0;
 for(li=0;li<aisesh->journal.line_count;li++)
  {
  if((ret=aaTextReaderLineGet(&aisesh->journal,li,&chars,txt))!=YES) { oops; return ret; }
  if(0) { appLog("%-5i life save %-3i [%s]",done,li,txt); }
  if((ret=aaFileStreamWritef(fu.handle,"%s\n",txt))!=YES) { oops; break; }
  if(chars==1&&txt[0]=='{')   {   done++;   }
  }
 aaFileStreamStatus(fu.handle,&fu.status);
 appLog(" ");
 appLog("wrote %i entries, file size= %I64d",done,fu.status.bytes);
 aaFileStreamDestroy(fu.handle);

 ret=aaQueDestroy(aisesh->audio_out_que.handle);
 if(ret!=YES) { oops; }

 claudeDelete(&aisesh->claude[0]);
 fishTtsDelete(&aisesh->fish[0]);
 fluxSttDelete(&aisesh->flux[0]);
// gootraDelete(&aisesh->goot[0]);
// phoneDelete(&aisesh->phone[0]);
 if(aisesh->msg_que.handle)    { aaQueDestroy(aisesh->msg_que.handle); }
 if(aisesh->fsev_que.handle)    { aaQueDestroy(aisesh->fsev_que.handle); }
 if((ret=aaTextReaderDelete(&aisesh->journal))!=YES) { oops; }
 aaMemoryFill(aisesh,sizeof(_aisesh),0);
// app.the_aisesh=NULL;
 return RET_YES;
 }







 B myseshStatus                        (_aisesh*aisesh)
 {
 B ret;
 H to,jo,so,ko;
 H vo,mo,left,sl,samples;
 I iyt[_32K];
 B str[_512K];
 H chars;
 _str32k needle;
 H pos;
 B etc[_64K];
 B path[_1K];
 B file[_1K];
 B full[_1K];
 Q el;
 B temp[_1K];
 _websockethdr wockhdr;
 B byt[_128K];
 H bof;
 D lev;
 #if DO_INPUT_STUFF==1
 _veekay vk;
 #endif
 H ax,axok;
 _fluxsttevent fsev;



 if(aisesh==NULL) { oof; }
 jo=0;
 to=3;
 *(HP)&aa_user_info_executed[0]=aisesh->stage;
 while(1)
  {
  jo++;
  if(jo>to) { break; }
  if(aisesh==NULL) { oof; }
  switch(aisesh->stage)
   {
   case 100:
   aisesh->stage=120;
   break;


   case 120:
   if((ret=serverPktRead(&wockhdr,str))==RET_YES)
    {
    chars=wockhdr.bytes;
    str[chars]=0;
    while(1)
     {
     aaStringCopyfLen(needle.buf,&needle.len,"\"ev\":\"hey\"");
     if(aaStringFindFirstIString(str,chars,needle.buf,needle.len,&pos)==RET_YES)
      {
      aaStringCopyfLen(needle.buf,&needle.len,"\"my_id\":\"");
      if(aaStringFindFirstIString(str,chars,needle.buf,needle.len,&pos)==RET_YES)
       {
       aaStringCopy(etc,&str[pos+needle.len]);
       aaStringLastCharSet(etc,0,0,YES);
       aaStringLastCharSet(etc,0,0,YES);
       aaStringCopy(aisesh->usr_uid,etc);
       aaStringRemoveChars(aisesh->usr_uid,0,'-');
       appLog("got uid");
       }
      break;
      }
     aaNote(0,"prepktget=%s",str);
     break;
     }
    }

   if(aisesh->usr_uid[0]==NULL_CHAR) { break; }
   for(ax=0;ax<6;ax++) {  aisesh->ready[ax]=NO; }
   aaStringCopy(temp,aisesh->usr_uid);
   aaStringCopyf(file,"%s_history",temp);
   aaStringCopyf(path,"%s/%c/%c",app.tree_dir,file[0],file[1]);
   aaStringReplaceChar(path,0,BSLASH_CHAR,FSLASH_CHAR);
   aaStringCopyf(full,"%s/%s",path,file);
   aaStringReplaceChar(full,0,BSLASH_CHAR,FSLASH_CHAR);
   aaStringAppendf(full,".txt");
   aaStringCopy(aisesh->save_path,path);
   aaStringCopy(aisesh->save_full,full);
   appLog("loading %s",aisesh->save_full);

   if(0) { aaFileDelete(aisesh->save_full); }


 retry:
   if((ret=aaTextReaderOpen(&aisesh->journal,aisesh->save_full,0,F32))==RET_YES)
    {
    if(aisesh->journal.line_count<6)
     {
     appLog("deleted %s as journal.line_count=%i",aisesh->save_full,aisesh->journal.line_count);
     aaTextReaderDelete(&aisesh->journal);
     aaFileDelete(aisesh->save_full);
     goto retry;
     }
    }
   else
    {
    if((ret=aaTextReaderNew(&aisesh->journal,0,0))!=YES) { oops; }
    }


   if((ret=claudeNew(&aisesh->claude[0],aisesh->usr_uid))!=YES) { oops; }
   aisesh->claude[0].aisesh_parent=aisesh;
   if((ret=fishTtsNew(&aisesh->fish[0],app.kfg.fish_key))!=YES) { oops; }
//   if((ret=gootraNew(&aisesh->goot[0]))!=YES) { oops; }
   if((ret=fluxSttNew(&aisesh->flux[0],app.kfg.deepgram_key))!=YES) { oops; }
   aisesh->flux[0].aisesh_parent=aisesh;
//   if((ret=fishTtsTrpSet(&aisesh->fish[0],&aisesh->journal))!=YES) { oops; }
   appLog("created new claude, journal=%i",aisesh->journal.line_count);

   aisesh->min_sl=98;
   aisesh->max_el=15000;
   aisesh->max_lmx=_1MEG;
   aisesh->frame_size=128;
   aisesh->stage=140;
   break;





   case 140:
   fishTtsYield(&aisesh->fish[0]);
   claudeYield(&aisesh->claude[0]);
//   gootraYield(&aisesh->goot[0]);
   fluxSttYield(&aisesh->flux[0]);
//   phoneYield(&aisesh->phone[0],10);
//   if(aisesh->goot[0].stage>90)                  {   if(aisesh->ready[1]==NO)   aisesh->ready[1]=YES; }
   if(aisesh->fish[0].ws_cli.cd->is_ready==YES)  {   if(aisesh->ready[1]==NO)   aisesh->ready[1]=YES;}
   if(aisesh->claude[0].is_ready==YES)           {   if(aisesh->ready[2]==NO)   aisesh->ready[2]=YES; }
   if(aisesh->flux[0].ws_cli.cd->is_ready==YES)  {   if(aisesh->ready[3]==NO)   aisesh->ready[3]=YES; }

   axok=YES;
   for(ax=1;ax<4;ax++)
    {
    if(aisesh->ready[ax]==NO) { axok=NO; break; }
    }
   if(axok!=YES) { break; }


   ///aisesh->journal_entries=aisesh->claude[0].msg_count;

   aisesh->voice_num=19;
   aaStringCopy(aisesh->voice_id,aisesh->fish[0].voice[aisesh->voice_num].id);
   aaStringCopy(aisesh->voice_name,aisesh->fish[0].voice[aisesh->voice_num].name);
   appLog("%i journal entries",aisesh->journal_entries);

   if(0) { if((ret=fishTtsReference(&aisesh->fish[0],aisesh->voice_id,0,0,0,""))!=YES) { oops; }    }
   else
    {
    //if((ret=fishTtsReference(&aisesh->fish[0],0,(H)aisesh->filu.bytes,aisesh->max_lmx,aisesh->filu.mem,0))!=YES) { oops; }
    if((ret=fishTtsReference(&aisesh->fish[0],0,(H)aisesh->filu.bytes,aisesh->max_lmx,aisesh->filu.mem,0))!=YES) { oops; }
    }

   aisesh->stage=160;
   break;





   case 160:
   fishTtsYield(&aisesh->fish[0]);
   if(aisesh->fish[0].vox[0].is_audio&&aisesh->fish[0].vox[0].text[0]==NULL_CHAR)
    {
    if(aisesh->min_sl>0)  {  aisesh->stage=200;     break;     }
    }
   aisesh->whos_turn='u';
   aisesh->start_ms=aaMsRunning();
   //aisesh->first_done=0;
   aisesh->stage=500;
   break;










                case 200:
                vo=0;
                while(1)
                 {
                 samples=128;
                 ///samples=aisesh->frame_size;

                 left=(H)aisesh->filu.bytes-aisesh->filu_off;
                 if(left<(samples*2)) { break; }
                 if(left==0)          { oof; }
                 if(left>(samples*2)) { left=samples*2; }
                 if((left%2)!=0)      { oof; }
                 aaMemoryCopy(iyt,left,&aisesh->filu.mem[aisesh->filu_off]);
                 if((ret=fluxSttWrite(&aisesh->flux[0],samples*2,iyt))!=YES) { oops; }
                 aisesh->filu_off+=left;
                 vo++;
                 if(vo<64) { continue; }
                 vo=0;
                 }
                aisesh->stage=220;
                if((ret=fluxSttFlush(&aisesh->flux[0]))!=YES) { oops; }
                fluxSttYield(&aisesh->flux[0]);
                aaStringNull(aisesh->filu_text);
                aisesh->filu_ms=aaMsRunning();
                break;





                case 220:
                vo=0;
                for(mo=0;mo<100;mo++)
                 {
                 el=aaMsRunning()-aisesh->filu_ms;
                 aaStringLen(aisesh->filu_text,&sl);
                 if(sl>aisesh->min_sl||el>aisesh->max_el) { vo=1; break; }
                 if(mo==0) { fluxSttYield(&aisesh->flux[0]); }

                 for(H po=0;po<10;po++)
                  {
                  if((ret=myseshFsevQueRead(aisesh,&fsev))==YES)
                   {
                   aaStringCopy(aisesh->filu_text,fsev.transcript);
                   appLog("%s",aisesh->filu_text);
                   }
                  else { break; }
                  }

                 aisesh->filu_ms=aaMsRunning();
                 }

                 //appLog("%s",aisesh->filu_text);
                ///if(mo>2) { appLog("mo=%i",mo); }
#if 0
             el=aaMsRunning()-aisesh->filu_ms;
                aaStringLen(aisesh->filu_text,&sl);
                fluxSttYield(&aisesh->flux[0]);

                appLog("sssssl=%i",sl);

                if(sl>128) vo=1;

     #endif
     //           //appLog("fsev=%i",aisesh->fsev_count);
                if(vo==0) { break; }

                fishTtsDelete(&aisesh->fish[0]);
                if((ret=fishTtsNew(&aisesh->fish[0],app.kfg.fish_key))!=YES) { oops; }
                aisesh->ready[1]=NO;
                if((ret=fluxSttDelete(&aisesh->flux[0]))!=YES) { oops; }
                if((ret=fluxSttNew(&aisesh->flux[0],app.kfg.deepgram_key))!=YES) { oops; }

                aisesh->flux[0].aisesh_parent=aisesh;

                aisesh->ready[3]=NO;
                aisesh->stage=240;
                //appLog("got to line %i",__LINE__);
                break;



                case 240:
                fluxSttYield(&aisesh->flux[0]);
                fishTtsYield(&aisesh->fish[0]);
                if(aisesh->flux[0].ws_cli.cd->is_ready==YES&&aisesh->ready[3]==NO)
                 {
                 aisesh->ready[3]=YES;
                 break;
                 }
                if(aisesh->fish[0].ws_cli.cd->is_ready==YES&&aisesh->ready[1]==NO)
                 {
                 aisesh->ready[1]=YES;
                 if((ret=fishTtsReference(&aisesh->fish[0],0,(H)aisesh->filu.bytes,aisesh->max_lmx,aisesh->filu.mem,"%s",aisesh->filu_text))!=YES) { oops; }
                 break;
                 }
                if(aisesh->fish[0].stage<30)  { break; }
                if(aisesh->ready[1]!=YES)     { break; }
                if(aisesh->ready[3]!=YES)     { break; }
                aisesh->start_ms=aaMsRunning();
                //ais->first_done=0;
                aisesh->whos_turn='u';
                appLog("NIC!!!");
                aisesh->stage=500;
                break;





   case 2001:
   case 2201:
   case 2401:
   oof;
   break;












   case 500:
   aisesh->frame_size=128;
   //aisesh->frame_size=256;

   aisesh->running_cycle=0;
   ///aisesh->cfg_auto_first_time=5300;
   appLog("aisesh->stage=500 changing to stage=700");
   //appLog("got to line %i",__LINE__);
   aisesh->needs_to_hear_ok=1;
   aisesh->stage=700;
   break;




   case 700:
   if(aisesh->change_voice_flag==1)
    {
    fishTtsDelete(&aisesh->fish[0]);
    if((ret=fishTtsNew(&aisesh->fish[0],app.kfg.fish_key))!=YES) { oops; }
    //if((ret=fishTtsTrpSet(&aisesh->fish[0],&aisesh->journal))!=YES) { oops; }
    aisesh->change_voice_flag=2;
    aisesh->ready[1]=NO;
    appLog("700: ttsNew");
    break;
    }

   fishTtsYield(&aisesh->fish[0]);
   //gootraYield(&aisesh->goot[0]);
   //appLog("ptr=%p %p",aisesh->flux[0].aisesh_parent,aisesh->claude[0].aisesh_parent);
   fluxSttYield(&aisesh->flux[0]);
   //fishTtsYield(&aisesh->fish[0]);
   claudeYield(&aisesh->claude[0]);
   if(aisesh->fish[0].ws_cli.cd->is_ready==YES&&aisesh->ready[1]==NO)    {    oof;    }
   if(aisesh->fish[0].stage<30)  { break; }

  if(aisesh->ready[1]!=YES)     { break; }
  if(aisesh->ready[2]!=YES)     { break; }
  if(aisesh->ready[3]!=YES)     { break; }


  if(aisesh->needs_to_hear_ok==1)
   {
   fishTtsWritef(&aisesh->fish[0],"fuck off ashman");
   fishTtsFlush(&aisesh->fish[0]);
   aisesh->needs_to_hear_ok=0;
   }




  so=0;

  #if 1
   while(1)
    {
    aaQueStatus(aisesh->audio_out_que.handle,&aisesh->audio_out_que.status);
    if(aisesh->audio_out_que.status.bytes==0) { break; }
    el=aaMsRunning()-aisesh->audio_out_ms;
    if(el<4) { break; } //16 app.kfg.cx[4]
    if((ret=aaQueStringRead(aisesh->audio_out_que.handle,&chars,0,sizeof(byt),byt))!=YES)  {  if(ret!=RET_NOTREADY) { appLog("%s",arets); }    break;     }
    byt[chars]=NULL_CHAR;
    if(0)  appLog("%s",byt);
    aaStringCopyfLen(needle.buf,&needle.len,"\"by\":[");
    if(aaStringFindFirstIString(byt,chars,needle.buf,needle.len,&pos)==RET_YES)
     {
     myseshStringToPcm(aisesh,&byt[pos+needle.len],&bof,iyt);
     odeoLevelGet(bof,iyt,&lev);
     lev+=111.0;
     lev=lev/111.0;
     lev=lev*100.0;
     if(lev>96) { lev=96; }
     voxlevPush(1,lev);
     }
    serverPktWritef(0x01,1,"%s",byt);
    aaQueStatus(aisesh->audio_out_que.handle,&aisesh->audio_out_que.status);
    so++;
    if(so>=8) { break; } // 3 app.kfg.cx[3]
    }
   #endif

   if(so>0)  {  aisesh->audio_out_ms=aaMsRunning();    }
   el=aaMsRunning()-aisesh->audio_out_ms;


//  gootraYield(&aisesh->goot[0]);
   fluxSttYield(&aisesh->flux[0]);
   fishTtsYield(&aisesh->fish[0]);
   claudeYield(&aisesh->claude[0]);


   if(aisesh->the_call_handle==0) { break; }
   aisesh->running_cycle++;
   aisesh->running_ms=aaMsRunning()-aisesh->start_ms;

  if(aisesh->fsev_count==0) { break; }

  if(aisesh->whos_turn!='u') break;
  if((ret=myseshFsevQueRead(aisesh,&fsev))!=YES) { oops; }


  while(1)
   {
   if(fsev.type_hash==flux_TurnInfo&&fsev.event_hash==flux_Update&&fsev.word_count==0)
    {
    if(strlen((CP)fsev.transcript)==2)  { break; }
    }
   if(fsev.type_hash==flux_TurnInfo&&fsev.event_hash==flux_StartOfTurn)
    {
    aaStringNull(aisesh->out);
    aisesh->word_index=0;
    aisesh->fsev_counter++;
    }
   fsev.fsev_counter=aisesh->fsev_counter;

   fluxSttEventProcess(&aisesh->flux[0],&fsev);
   ///fluxSttEventDump(&aisesh->flux[0],&fsev);

   if(fsev.type_hash==flux_TurnInfo&&fsev.event_hash==flux_EndOfTurn)
    {
    if(aisesh->whos_turn=='u')
     {
    // appLog("adding user journal [%s]",fsev.transcript);
     ///      atrp=(_textreader*)&app.the_aisesh->journal;
    //appLog("T%i %i",__LINE__,aisesh->journal.magic);
     appLog("about to aaddxx  who=%c journal %s",aisesh->whos_turn,fsev.transcript);
     myseshListAppend(aisesh,"user",0,"%s",fsev.transcript);
     }
    else
     {
     appLog("NOT YU");
     appLog("zzabout to aaddxx  who=%c journal %s",aisesh->whos_turn,fsev.transcript);
     myseshListAppend(aisesh,"assistant",0,"%s",fsev.transcript);

     }
    ///appLog("end of turn who=%c",aisesh->whos_turn);
    }
     ///myseshListAppend(&app.the_aisesh,"user",0,"%s",fsev->transcript);
   break;
   }

   myseshFishToClient(aisesh);     // read fish audio and send as pkt to client
   for(ko=0;ko<64;ko++)
    {
    if(myseshReadFromClient(aisesh)!=YES)  {    break;     }
    }
   myseshClaudeToFish(aisesh);    // read text from claude and give it to fish

   break;
   }
  }
 return RET_YES;
 }







 B myseshStringToPcm                   (_aisesh*aisesh,VP str,HP pcmdone,IP pcm)
 {
 B etc[_64K];
 H place,choff,bof,num;
 B isneg,ch;

 if(aisesh) {}
 aaStringCopy(etc,str);
 place=1;
 choff=bof=0;
 isneg=NO;
 num=0;
 while(1)
  {
  ch=etc[choff];
  if(ch==','||ch==']')
   {
   if(isneg==YES) { pcm[bof]=-num; }
   else           { pcm[bof]=+num; }
   bof++;
   place=1;
   choff++;
   isneg=NO;
   if(ch==']') { break; }
   continue;
   }
  if(ch=='-')
   {
   isneg=YES;
   choff++;
   continue;
   }
  if((ch>='0'&&ch<='9')&&place==1) {   num=0;    num+=(ch-'0');   choff++;   place++;  continue;  }
  if((ch>='0'&&ch<='9')&&place==2) {   num*=10;  num+=(ch-'0');   choff++;   place++;  continue;  }
  if((ch>='0'&&ch<='9')&&place==3) {   num*=10;  num+=(ch-'0');   choff++;   place++;  continue;  }
  if((ch>='0'&&ch<='9')&&place==4) {   num*=10;  num+=(ch-'0');   choff++;   place++;  continue;  }
  if((ch>='0'&&ch<='9')&&place==5) {   num*=10;  num+=(ch-'0');   choff++;   place++;  continue;  }
  aaNote(0,"num=%i choff=%i place=%i ch=%i ch=%c",num,choff,place,ch,ch);
  break;
  }
 *pcmdone=bof;
 return RET_YES;
 }






 B myseshReadFromClient                (_aisesh*aisesh)
 {
 B ret;
 B str[_128K];
 H chars,pos;
 _str32k needle;
 B etc[_128K];
 B rdig[_1K];
 B digs[_1K];
 B file[_1K];
 B full[_1K];
 B path[_1K];
 B byt[_128K];
 I iyt[_32K];
 H samples,bof;
 D lev;
 _websockethdr wockhdr;

 if((ret=serverPktRead(&wockhdr,str))!=YES) { return ret; }
 chars=wockhdr.bytes;
 str[chars]=0;

    while(1)
     {
     //appLog("%i %i",wockhdr.bytes,wockhdr.oc);

     aaStringCopyfLen(needle.buf,&needle.len,"\"ev\":\"hey\"");
     if(aaStringFindFirstIString(str,chars,needle.buf,needle.len,&pos)==RET_YES)
      {
      aaStringCopyfLen(needle.buf,&needle.len,"\"my_id\":\"");
      if(aaStringFindFirstIString(str,chars,needle.buf,needle.len,&pos)==RET_YES)
       {
       aaStringCopy(etc,&str[pos+needle.len]);
       aaStringLastCharSet(etc,0,0,YES);
       aaStringLastCharSet(etc,0,0,YES);
       aaStringCopy(aisesh->usr_uid,etc);
       appLog("usr_uid=%s",aisesh->usr_uid);
       }
      break;
      }
     //===========================
     //===========================
     //===========================
     aaStringCopyfLen(needle.buf,&needle.len,"\"ev\":\"pic\"");
     if(aaStringFindFirstIString(str,chars,needle.buf,needle.len,&pos)==RET_YES)
      {
      aaStringCopyfLen(needle.buf,&needle.len,"\"bb\":\"");
      if(aaStringFindFirstIString(str,chars,needle.buf,needle.len,&pos)==RET_YES)
       {
       appLog("got pic");
       aaStringCopy(etc,&str[pos+needle.len]);
       aaStringLastCharSet(etc,0,0,YES);
       aaStringLastCharSet(etc,0,0,YES);
       if(aaStringFindChar(etc,0,&pos,',',YES,0,YES)==YES) { aaStringDeleteChars(etc,0,0,pos+1);      }
       if(aaBase64Decode(etc,0,aisesh->decoded_buf,&aisesh->decoded_len)==RET_YES)
        {
        aaDigestQuick(aa_DIGESTTYPE_Sha256,rdig,digs,aisesh->decoded_len,aisesh->decoded_buf);
        aaStringCopy(file,digs);
        aaStringCopyf(path,"%s/%c/%c",app.tree_dir,file[0],file[1]);
        aaStringCopyf(full,"%s/%s",path,file);
        aaStringReplaceChar(full,0,BSLASH_CHAR,FSLASH_CHAR);
             ///=====================
              aaStringCopyf(byt,"{\"magic\":1234,\"ev\":\"fur\",\"url\":");
              aaStringAppendf(byt,"\"https://xueshen.online/c/tree/%c/%c/%s.jpg\"}",file[0],file[1],file);
              if(aisesh->next_url[0]==NULL_CHAR) {  aaStringCopyf(aisesh->next_url,"https://xueshen.online/c/tree/%c/%c/%s.jpg",file[0],file[1],file);  }
              ///=====================
        serverPktWritef(0x01,1,"%s",byt);
        aaStringAppendf(full,".jpg");
        if((ret=aaFileSaveFromMemory(full,aisesh->decoded_len,aisesh->decoded_buf))!=YES) { oops; }
        break;
        }
       }
      }
     //===========================
     //===========================
     //===========================
     aaStringCopyfLen(needle.buf,&needle.len,"\"ev\":\"aud\"");
     if(aaStringFindFirstIString(str,chars,needle.buf,needle.len,&pos)==RET_YES)
      {
      aaStringCopyfLen(needle.buf,&needle.len,"\"by\":[");
      if(aaStringFindFirstIString(str,chars,needle.buf,needle.len,&pos)==RET_YES)
       {
       myseshStringToPcm(aisesh,&str[pos+needle.len],&bof,iyt);
       samples=128;//aisesh->frame_size;
       if(samples!=bof) { aaNote(0,"bof and samples differ %i %i",samples,bof); }
       // PUSH 0 ,, read pkt containing raw pcm from client and convert to perent
       odeoLevelGet(samples,iyt,&lev);
       lev+=111.0;
       lev=lev/111.0;
       lev=lev*100.0;
       //aaLog(-555,"initial lev was %.3f , final lev=%.3f",was,lev);
       if(lev<10)     {     lev=0;     }
       if(lev>70)     {     aisesh->ms_since_noise=aaMsRunning();        }
       aisesh->acum_lev+=lev;
       aisesh->acum_cnt++;
       if(aisesh->acum_cnt>=50)
        {
        aisesh->acum_lev/=50.0;
        if(aisesh->acum_lev<aisesh->lo_lev) { aisesh->lo_lev=aisesh->acum_lev; }
        if(aisesh->acum_lev>aisesh->hi_lev) { aisesh->hi_lev=aisesh->acum_lev; }
        appLabel(2,"lo=%.5f hi=%.5f now=%.5f cu=%.5f",aisesh->lo_lev,aisesh->hi_lev,lev,aisesh->acum_lev);
        aisesh->acum_cnt=0;
        }
       voxlevPush(0,lev);
       //ec=aaElementCount(aisesh->audio_out_level)-1;
       //aaMemoryCopy(&aisesh->audio_out_level[0],sizeof(D)*ec,&aisesh->audio_out_level[1]);
       //aisesh->audio_out_level[ec]=lev;
       if((ret=fluxSttWrite(&aisesh->flux[0],samples*2,iyt))!=YES) { oops; }
       //ok=1;
       //if(ok==1&&0) { if((ret=deepSttFlush(&aisesh->deep[0]))!=YES) { oops; } }
       break;
       }
      }
     appLog("unhandled packet from js client");
     appLog("%s",str);
     break;
     }

 return RET_YES;
 }






 B myseshMsgQueRead                    (_aisesh*aisesh,HP count,_textpair*textpair)
 {
 H xcnt,xsiz,t;
 t=0;
 xcnt=xsiz=0;
 if(count) { *count=0; }

 while(1)
  {
  aaQueStatus(aisesh->msg_que.handle,&aisesh->msg_que.status);
    if(aaQuePeekDword(aisesh->msg_que.handle,0,&xcnt)==RET_YES)
     {
      if(aaQuePeekDword(aisesh->msg_que.handle,4,&xsiz)==RET_YES)
      {
      if(aaQuePeek(aisesh->msg_que.handle,8,xcnt*xsiz,&textpair[t])==RET_YES)
       {
       aaQueDiscard(aisesh->msg_que.handle,8+(xcnt*xsiz));
       aaQueStatus(aisesh->msg_que.handle,&aisesh->msg_que.status);;
//       appLog("T=%i xcnt=%i mc=%i",t,xcnt,aisesh->msg_count);
       t+=xcnt;
       aisesh->msg_count-=1;
       //aisesh->msg_count-=xcnt;
       break;
       continue;
       }
      }
     }
    break;
    }

 if(count) { *count=t; }

 return RET_YES;
 }






 B myseshMsgQueWrite                   (_aisesh*aisesh,H count,_textpair*textpair)
 {
 B ret;
   if((ret=aaQueWriteDword(aisesh->msg_que.handle,count))!=YES) { oops; }
   if((ret=aaQueWriteDword(aisesh->msg_que.handle,sizeof(_textpair)))!=YES) { oops; }
   if((ret=aaQueWrite(aisesh->msg_que.handle,count*sizeof(_textpair),textpair))!=YES) { oops; }
   aaQueStatus(aisesh->msg_que.handle,&aisesh->msg_que.status);
   aisesh->msg_count++;
 return RET_YES;
 }





 B myseshFsevQueRead                   (_aisesh*aisesh,_fluxsttevent*fsev)
 {
 if(aisesh==NULL) { return RET_BADPARM; }
 if(fsev==NULL) { return RET_BADPARM; }
 aaQueStatus(aisesh->fsev_que.handle,&aisesh->fsev_que.status);
 if(aaQuePeek(aisesh->fsev_que.handle,0,sizeof(_fluxsttevent),fsev)==RET_YES)
  {
  aaQueDiscard(aisesh->fsev_que.handle,sizeof(_fluxsttevent));
  aaQueStatus(aisesh->fsev_que.handle,&aisesh->fsev_que.status);
  aisesh->fsev_count-=1;
  return RET_YES;
  }
 return RET_FAILED;
 }






 B myseshFsevQueWrite                  (_aisesh*aisesh,_fluxsttevent*fsev)
 {
 B ret;
 if(aisesh==NULL) { return RET_BADPARM; }
 if(fsev==NULL) { return RET_BADPARM; }
 //appLog("sf=%s",aisesh->save_full);
 if((ret=aaQueWrite(aisesh->fsev_que.handle,sizeof(_fluxsttevent),fsev))!=YES) { appLog("SHJSIS"); oops; }
 aaQueStatus(aisesh->fsev_que.handle,&aisesh->fsev_que.status);
 aisesh->fsev_count++;
 return RET_YES;
 }







 B myseshListAppend                    (_aisesh*aisesh,VP role,VP url,VP fmt,...)
 {
 B ret;
 H mc;
 B etc[_64K];
 BP rle;
 _textreader*atrp;

 aaVargsf64K(fmt);
 mc=aisesh->journal_entries;//claude[0].msg_count;
 if(mc) {}
 rle=(BP)role;
 if(rle[0]==aisesh->journal_last_role) { oof; }

 aaStringReplaceChar(str64k.buf,0,'`',SQUOTE_CHAR);
 aaStringCopy(etc,str64k.buf);
 aaStringUnQuote(etc,0,0);

/// appLog("about to listappend trd=%i jc=%i",aisesh->journal.line_count,aisesh->journal_entries);

 if(aisesh->journal_entries==0) {} ///aaTextReaderAppend(&aisesh->journal,"\"history\":[");
 if(aisesh->journal_entries>0)  { ret=aaTextReaderAppend(&aisesh->journal,","); if(ret!=YES) oops; }
 ret=aaTextReaderAppend(&aisesh->journal,"{");
 if(ret!=YES)
  {
  oops;
  atrp=(_textreader*)&aisesh->journal;
  appLog("EET%i %i",__LINE__,atrp->magic);
  }
 ret=aaTextReaderAppend(&aisesh->journal,"\"role\":\"%s\",",role);
 if(ret!=YES) oops;
 if(url==NULL) {  ret=aaTextReaderAppend(&aisesh->journal,"\"url\":null,");     if(ret!=YES) oops;  }
 else          {  ret=aaTextReaderAppend(&aisesh->journal,"\"url\":\"%s\",",url); if(ret!=YES) oops; }

 //appLog("ETC=%s",etc);
 ret=aaTextReaderAppend(&aisesh->journal,"\"content\":\"%s\"",etc);
 if(ret!=YES) oops;
 ///aaTextReaderAppend(&aisesh->journal,"\"content\":\"%s\"",str64k.buf);

 ret=aaTextReaderAppend(&aisesh->journal,"}");
 if(ret!=YES) oops;
 aisesh->journal_entries++;
 //aisesh->first_done=2;
 //appLog("je=%i %i %s %s",aisesh->journal_entries,aisesh->journal.line_count,role,str64k.buf);
/// appLog("je=%i %i %s %s",aisesh->journal_entries,aisesh->journal.line_count,role,etc);
 aisesh->journal_last_role=rle[0];

 //appLog("whos_turn=%c ",aisesh->whos_turn);
 if(aisesh->journal_last_role=='u')
  {
  aisesh->whos_turn='a';
  }
 else
  {
  aisesh->whos_turn='u';
  }
//appLog("then whos_turn=%c ",aisesh->whos_turn);

 //appLog("ended listappend trd=%i jc=%i",aisesh->journal.line_count,aisesh->journal_entries);
 return RET_YES;
 }










 B myseshClaudeToFish                  (_aisesh*aisesh)
 {
 B ret;
 B answer[_64K];
 B answer_o[_64K];
 H chars;
 C str[_64K];

 //appLog("!!vf who=%c std=%i  qq=%i",aisesh->whos_turn,aisesh->claude[0].stage,aisesh->claude[0].answer.status.bytes);

 #if 0
 if(aaQueStringRead(aisesh->claude[0].answer.handle,&chars,0,sizeof(answer),answer)==RET_YES)
  {
  appLog("ANS=%s",answer);
  }
#endif

//if(aisesh->whos_turn=='a')appLog("!!vf who=%c std=%i  qq=%i",aisesh->whos_turn,aisesh->claude[0].stage,aisesh->claude[0].answer.status.bytes);

    if(aisesh->whos_turn=='a'&&aisesh->claude[0].stage==CLAUDE_STAGE_PROMPT)
     {
     appLog("vf who=%c @@@@@@@@@@@@",aisesh->whos_turn);
     if(aaQueStringRead(aisesh->claude[0].answer.handle,&chars,0,sizeof(answer),answer)==RET_YES)
      {
      appLog("ANS=%s",answer);
      #if 1
      aaQueStatus(aisesh->audio_out_que.handle,&aisesh->audio_out_que.status);
      if(aisesh->audio_out_que.status.bytes>_0K&&chars>0)
       {
       appLog("purged output due to interruption %i chars,  %i bytes",chars,aisesh->audio_out_que.status.bytes);
       if((ret=aaQueDiscard(aisesh->audio_out_que.handle,aisesh->audio_out_que.status.bytes))!=YES) { oops; }
       aaQueStatus(aisesh->audio_out_que.handle,&aisesh->audio_out_que.status);
       aisesh->audio_out_ms=aaMsRunning();
       }
      #endif
      aaStringReplaceChar(answer,0,SQUOTE_CHAR,'`');
      aaStringReplaceChar(answer,0,DQUOTE_CHAR,'`');
      aaStringReplaceString(answer,0,"Anthropic",0,"Ashod Apakian",0,0,answer_o);
      aaStringCopy(answer,answer_o);
      aaStringReplaceString(answer,0,"Claude",0,"Ash A.I",0,0,answer_o);
      aaStringCopy(answer,answer_o);
      appLog("          preans=[%s]",answer);
      aaMemoryFill(str,sizeof(str),0);
      UtfUnEscape((CP)answer,(CP)str);
      oof;
      myseshListAppend(aisesh,"assistant",0,"%s",str);

      ///if((ret=fishTtsWritef(&aisesh->fish[0],"%s",str))!=YES) { oops; }
      //fishTtsFlush(&aisesh->fish[0]);


//      aisesh->whos_turn='u';
      }
     }
 return RET_YES;
 }







 B myseshFishToClient                  (_aisesh*ais)
 {
 B ret;
 H go,samples,bof;
 IP pcm;
 I p;
 G pp;
 B byt[_128K];

    // READ AUDIO FROM FISH AND WRITE TO WEBSOCKET
    for(go=0;go<150;go++) // waas 100
     {
     samples=ais->frame_size;
     if((ret=aaQueRead(ais->fish[0].que.handle,samples*2,ais->fish[0].sam))!=YES) { break; }
     aaQueStatus(ais->fish[0].que.handle,&ais->fish[0].que.status);
     if(ais->the_call_handle==0) oof;
     if((ret=aaNetWebsocketServerYield(&app.the_server,ais->the_call_handle))!=YES) { oops; }
     while(1)
      {
                   aaStringCopyf(byt,"{\"magic\":1234,\"ev\":\"fis\",\"by\":[");
                   pcm=(IP)ais->fish[0].sam;
                   for(bof=0;bof<ais->frame_size;bof++)
                    {
                    pp=pcm[bof]*2;
                    if(pp>+32767) pp=+32767;
                    if(pp<-32767) pp=-32767;
                    p=(I)pp;
                    aaStringAppendf(byt,"%i,",p);
                    }
                   aaStringLastCharSet(byt,0,0,1);
                   aaStringAppend(byt,"]}");
      #if 1
      aaQueWritef(ais->audio_out_que.handle,"%s\n",byt);
      aaQueStatus(ais->audio_out_que.handle,&ais->audio_out_que.status);
      ais->audio_out_ms=aaMsRunning();
      //voxlevPush(1,lev);
      #else
      serverPktWritef(0x01,1,"%s",byt);
      #endif
      break;
      }
     }
 aaQueStatus(ais->fish[0].que.handle,&ais->fish[0].que.status);
 return RET_YES;
 }









//===================================
//===================================





 B serverPktWrite                      (B oc,B ff,H bytes,VP data)
 {
 B ret;
 if((ret=aaNetWebsocketServerPktWrite(&app.the_server,oc,ff,bytes,data))!=RET_YES) { oops; }
 return RET_YES;
 }





 B serverPktWritef                     (B oc,B ff,VP fmt,...)
 {
 aaVargsf256K(fmt);
 return(serverPktWrite(oc,ff,str256k.len,str256k.buf));
 }




 B serverPktRead                       (_websockethdr*wockhdr,VP wockdata)
 {
 B ret;
 BP bp;
 if((ret=aaNetWebsocketServerPktRead(&app.the_server,wockhdr,wockdata))!=RET_YES) { return ret; }
 //appLog("ww %i %i",wockhdr->bytes,wockhdr->oc);
 bp=(BP)wockdata;
 bp[wockhdr->bytes]=NULL_CHAR;
 return RET_YES;
 }





 B serverProcessor                     (V)
 {
 B ret;
 H ci;
 _servercalldata*tscd;
 Q el;
 _aisesh*aisp;
 ///_textreader*atrp;


 if((ret=aaNetWebsocketServerYield(&app.the_server,0))!=YES) {  return RET_NO;  }
 ci=app.the_server.call.status.index;
 tscd=(_servercalldata*)&app.server_calldata[ci];

 aisp=(_aisesh*)tscd->aisesh_ptr;
 //if(aisp==NULL) oof;


 if(app.the_server.scd->is_close!=0||app.the_server.scd->is_closing!=0)
  {
  aaNetTcpCallStatus(app.the_server.call.handle,&app.the_server.call.status);
  if(0) appLog("is_close=%i closing=%i closedbyloc=%i closedbyrem=%i",app.the_server.scd->is_close,app.the_server.scd->is_closing,app.the_server.call.status.is_closed_by_local,app.the_server.call.status.is_closed_by_remote);
  if(aisp!=NULL)
   {
   myseshDelete(aisp);
   if((ret=aaMemoryRelease(tscd->aisesh_ptr))!=YES) { oops; }
   tscd->aisesh_ptr=NULL;
   }

  aaMemoryFill(tscd,sizeof(_servercalldata),0);
  if(aaNetWebsocketServerCallClose(&app.the_server)!=YES) { oof; }
  appLog("server call close %i",__LINE__);
  return RET_NOTREADY;
  }



  switch(tscd->phaz)
   {
   case 0:
   if(app.the_server.scd->sys_flag!=1)
    {
    if(app.the_server.scd->wock.x_forwarded_for[0]==0) {  break; }
    aaNetWebsocketServerPktWritef(&app.the_server,0x01,YES,"{\"cmd\":\"xfwd\",\"val\":\"%s\"}",app.the_server.scd->wock.x_forwarded_for);
    app.the_server.scd->sys_flag=1;
    aaMemoryFill(tscd,sizeof(_servercalldata),0);
    tscd->call_handle=app.the_server.call.handle;
    tscd->call_index=ci;
    tscd->call_number=app.the_server.call.status.number;
    tscd->call_session=app.the_server.call.status.session;
    //aaStringCopyf(tscd->url,"%s",app.the_server.scd->wock.url);
    aaStringCopy(tscd->url,app.the_server.scd->wock.url);
    tscd->phaz=999;
    if(1)
     {
     appLog("new call ch=%i on %s xfwd=%s port=%i %i ",tscd->call_handle,app.the_server.scd->wock.url,app.the_server.scd->wock.x_forwarded_for,app.the_server.call.status.local_adr.port,app.the_server.call.status.remote_adr.port);
     appLog("allocating %i bytes for mysesh",sizeof(_aisesh));
     }



    aisp=(_aisesh*)tscd->aisesh_ptr;
    if(aisp==NULL)
     {
     if((ret=aaMemoryAllocate((VP)&tscd->aisesh_ptr,sizeof(_aisesh)))!=YES) { oops; }
     aaMemoryNameSet(tscd->aisesh_ptr,"aiseshptr");
     }
    aisp=(_aisesh*)tscd->aisesh_ptr;
    if(aisp==NULL)  { oof; }

    if(aisp->magic==0)
     {
     if((ret=myseshNew(aisp))!=YES) { oops; }
     }
    aisp=(_aisesh*)tscd->aisesh_ptr;
    aisp->the_call_handle=tscd->call_handle;
    aisp->the_call_index=ci;
//    app.the_aisesh=aisp;
    break;
    }
   break;


   case 60: aaDebugf("ph=%i",tscd->phaz); tscd->phaz++; break;
   case 61: tscd->phaz++; break;
   case 62: tscd->phaz++; break;
   case 63: tscd->phaz++; break;
   case 64: tscd->phaz++; break;
   case 65: tscd->phaz++; break;
   case 66:
   if(aaNetWebsocketServerCallClose(&app.the_server)!=YES) { oof; }
   appLog("server call close %i",__LINE__);
   break;

   case 70:
   el=aaMsRunning()-app.the_server.scd->ums;
   if(el>=3000) { appLog("ustage 70 el=%I64d",el); tscd->phaz=60;   }
   break;

   case 999:
   if(aaStringICompare(tscd->url,"/",0)==YES) {  tscd->phaz=1000;  break;    }
   tscd->phaz=1500;
   break;

   case 1000:
   if(tscd->aisesh_ptr==NULL) oof;
   aisp=(_aisesh*)tscd->aisesh_ptr;
   if(aisp==NULL) oof;
   aisp->the_call_handle=tscd->call_handle;
   aisp->the_call_index=ci;
   if(aisp==NULL) oof;
  // app.the_aisesh=aisp;
   //appLog("about to sesh ");

   ///atrp=(_textreader*)&aisp->journal;

   //appLog("mafgi=%i lc=%i",atrp->magic,atrp->line_count);
   myseshStatus(aisp);
///   app.the_aisesh=NULL;
   break;

   case 1500:
   break;
   }
 return RET_YES;
 }





//===================================
//===================================



 B appStart                            (V)
 {
 B ret;
 _size s1;
 _rect r1;
 N fs,fi;

 aaMemoryFill(&app,sizeof(_app),0);
 app.magic=aaHPP(appStart);

 aaStringCopy(app.c_time,__TIMESTAMP__);
 aaStringReplaceChar(app.c_time,0,SPACE_CHAR,'_');

 aaFocusToChrome(1);
 aaDebugfPrefix(0);
 aaDebugfLogWriteSet(NO);
 if(1) { aaFocusToDbg(1); }

 if((ret=aaInfoGet(&app.info,F32))!=YES)     { oops; }
 while(1)
  {
  app.i_am=0;
  if(aaStringICompare(app.info.sys_info.fqdn_name,"Acer@DESKTOP-BVG2LE9",0)==YES) { app.i_am=1; break; }
  if(aaStringICompare(app.info.sys_info.fqdn_name,"Administrator@EC2AMAZ-PIG79LA",0)==YES) { app.i_am=2; break; }
  break;
  }
 aaStringCopyf(app.tree_dir,"%stree",app.info.sys_path.current_dir);
 if(0)
  {
  if(1)
   {
   aaNote(0,"deleting %s",app.tree_dir);
   if((ret=aaFileFolderTreeDelete(app.tree_dir,2,16,YES))!=YES) { oops; }
   }

  if(1)
   {
   aaNote(0,"creating %s",app.tree_dir);
   if((ret=aaFileFolderTreeCreate(app.tree_dir,2,16))!=YES) { oops; }
   }
  aaQuit();
  return RET_YES;
  }
 app.border=8;
 app.tray_icon_ms=aaMsRunning();
 aaSizeSet(&s1,DEF_APP_WID,DEF_APP_HIT);
 if((ret=aaSurfaceCreate(&app.canvas.handle,&s1))!=YES) { oops; }
 if((ret=aaSurfaceVisualize(app.canvas.handle,YES-1,0))!=YES) { oops; }
 if((ret=aaSurfaceIconSetUsingResource(app.canvas.handle,1000,0))!=YES) { }
 aaSurfaceStatus(app.canvas.handle,&app.canvas.status);

 fi=0; fs=36;
 if((ret=aaFontCreate(&app.font[fi].handle,"consolas",0,fs,158,0,0,1,0))!=YES) { oops; }
 aaFontStatus(app.font[fi].handle,&app.font[fi].status);
 fi=1; fs=30;
 if((ret=aaFontCreate(&app.font[fi].handle,"consolas",0,fs,198,0,0,5,0))!=YES) { oops; }
 aaFontStatus(app.font[fi].handle,&app.font[fi].status);
 fi=2; fs=26;
 if((ret=aaFontCreate(&app.font[fi].handle,"consolas",0,fs,198,0,0,5,0))!=YES) { oops; }
 aaFontStatus(app.font[fi].handle,&app.font[fi].status);
 fi=3; fs=22;
 if((ret=aaFontCreate(&app.font[fi].handle,"consolas",0,fs,172,0,0,5,0))!=YES) { oops; }
 aaFontStatus(app.font[fi].handle,&app.font[fi].status);
 fi=4; fs=16;
 if((ret=aaFontCreate(&app.font[fi].handle,"consolas",0,fs,172,0,0,5,0))!=YES) { oops; }
 aaFontStatus(app.font[fi].handle,&app.font[fi].status);

 aaRectSet(&r1,240,100,app.canvas.status.size.w,app.canvas.status.size.h);
 aaRectSet(&r1,app.info.display_info.desktop_rect.w-r1.w-24,app.info.display_info.desktop_rect.h-r1.h-24,r1.w,r1.h);
 aaRectAdjust(&r1,-10,-30,0,0);

 aaRectSet(&r1,88,88,r1.w,r1.h);

 if((ret=aaSurfaceTraySet(app.canvas.handle,1000+(app.tray_icon_index%2),"%s %s",app.canvas.status.title,DEV_VERSION))!=YES) { oops; }
 aaSurfaceTitleSet(app.canvas.handle,"%s",app.info.sys_info.product_name);
 aaSurfaceRectSet(app.canvas.handle,&r1);
 aaSurfaceFillFrame(app.canvas.handle,0,2,&col_cyan[21],&col_pastelblue[28]);
 aaSurfaceFocus(app.canvas.handle);
 if(0)  {  aaSurfaceTransparencySet(app.canvas.handle,128,0);  }
 aaSurfaceOnTop(app.canvas.handle,0);
 aaSurfaceShow(app.canvas.handle,YES);
 aaSurfaceOnTop(app.canvas.handle,1);
 aaSurfaceStatus(app.canvas.handle,&app.canvas.status);
 aaSurfaceOnTop(app.canvas.handle,0);
 aaSurfaceStatus(app.canvas.handle,&app.canvas.status);
 aaRectSet(&app.draw_rect,app.border,app.border,app.canvas.status.size.w-(app.border*2),app.canvas.status.size.h-(app.border*2));
 aaMemoryStatus(&app.mem_status);
 aaNetStatus(&app.ns);

 #if DO_INPUT_STUFF==YES
 aaQueCreate(&app.vk_que.handle);
 aaQueStatus(app.vk_que.handle,&app.vk_que.status);
 #endif

 if((ret=appKonfig("confy.txt"))!=YES) { oops; }

 if(app.kfg.server_max_calls>=SERVER_MAX_CALLS) { app.kfg.server_max_calls=SERVER_MAX_CALLS; }
 if(app.kfg.server_max_calls==0) { app.kfg.server_max_calls=1; }
 if((ret=aaNetWebsocketServerNew(&app.the_server,0,app.kfg.server_port,app.kfg.server_max_calls))!=YES) { oops; aaQuit(); }

 stunnerNew(&app.stunner,app.kfg.stun_match);//STUN_THIS_HOST);
 app.load_msel[0]=aaMsRunning();

 //appLog("tp=%i",sizeof(_textpair));

 aaFocusToChrome(1);

 return RET_YES;
 }





 B appStop                             (V)
 {
 H ii;
 if(app.magic!=aaHPP(appStart)) { return RET_NOTINITIALIZED; }
 if(app.canvas.handle)          { aaSurfaceDestroy(app.canvas.handle); }
 for(ii=0;ii<aaElementCount(app.font);ii++)
  {
  if(app.font[ii].handle)         { aaFontDestroy(app.font[ii].handle); }
  }
 #if DO_INPUT_STUFF==YES
 if(app.vk_que.handle)          { aaQueDestroy(app.vk_que.handle); }
 #endif
 if(app.the_server.magic)       { aaNetWebsocketServerDelete(&app.the_server); }
 //if(app.server_chat_io.magic)   { aaIoqueDelete(&app.server_chat_io); }
 if(app.stunner.magic)          { stunnerDelete(&app.stunner); }
 if(app.kfg.magic)              { aaTextReaderDelete(&app.kfg.tre); }
 aaFocusToCodeBlocks();
 return RET_YES;
 }



 B appQuit                             (V)
 {
 if(app.magic!=aaHPP(appStart)) { return RET_NOTINITIALIZED; }
 if(app.quit_stage==0) { app.quit_stage=1; }
 return RET_YES;
 }



 B appDraw                             (V)
 {
 aaSurfaceUpdateAreaAdd(app.canvas.handle,&app.draw_rect,1);
 aaSurfaceStatus(app.canvas.handle,&app.canvas.status);
 return RET_YES;
 }




 B appLabel                            (H line,VP fmt,...)
 {
 N fi;
 H fs,maxl;
 _cord c1;
 _rect r1;
 aaVargsf32K(fmt);
 fi=1;
 fs=app.font[fi].status.size.h;
 maxl=app.canvas.status.size.h/fs;
 if(line>=maxl) { return RET_YES; }
 aaCordSet(&c1,0,140+(line*fs));
 //aaRectSet(&r1,(app.border>>1),c1.y+(app.border>>1),app.canvas.status.size.w-(app.border*1)-160,fs);//-(app.border>>1));
 aaRectSet(&r1,(app.border>>1)+10,c1.y+10+(app.border>>1),app.canvas.status.size.w-(app.border*1)-220,fs);//-(app.border>>1));
 aaCordAdjust(&c1,r1.x,r1.y+(app.border>>1));//app.border,(app.border>>1));
 //aaCordAdjust(&c1,app.border,(app.border>>1));
 aaRectSet(&r1,10,(line*fs)+(app.border<<0)+140,app.canvas.status.size.w-40,fs);
 aaCordSet(&c1,r1.x+5,r1.y);
 aaSurfaceFill(app.canvas.handle,&r1,&col_gray[24+((line%2)*4)]);
 aaSurfacePrintf(app.canvas.handle,&c1,app.font[fi].handle,&col_gray[3],0,"%s",str32k.buf);
 aaSurfaceUpdateAreaAdd(app.canvas.handle,&r1,0);
 return RET_YES;
 }




 B appLog                              (VP fmt,...)
 {
 N fi;
 _rect r1;
 aaVargsf32K(fmt);
 fi=3;
 aaRectSet(&r1,app.draw_rect.x,app.draw_rect.y+350,app.draw_rect.w,app.draw_rect.h-350-30);
 aaSurfaceLog(app.canvas.handle,&r1,&col_blue[20],app.font[fi].handle,&col_yellow[29],"%-13.3f %s",aaSecsRunning(),str32k.buf);
 aaLog(-555,"%-12I64d %s",aaMsRunning(),str32k.buf);
 return RET_YES;
 }




 D appProfiler                         (H index,B init,B mode)
 {
 B ret;
 G nano;
 if(index>=aaElementCount(app.profiler)) { return -1.0; }
 if(init)
  {
  if((ret=aaTimerProfilerGet(&app.profiler[index]))!=YES) { return -1.0;  }
  app.profelap[index]=0;
  }
 if((ret=aaTimerProfilerElapsed(app.profiler[index],0,0,&nano,0))!=YES) { return -1.0;  }
 while(1)
  {
  if(mode==0) { app.profelap[index]=nano/1000000.0; break; }// in ms
  if(mode==2) { app.profelap[index]=nano/1.0; break; }// in nano
  app.profelap[index]=nano/1000.0; // in micro
  break;
  }
 return app.profelap[index];
 }





 #if DO_INPUT_STUFF==YES
 V appVkeyYield                        (V)
 {
 H vk;
 _veekay veekay;

 if(app.is_using_vk!=YES) { return; }
 if(aaInputStateGet(&app.is)!=YES) { return; }
 for(vk=0;vk<256;vk++)
  {
  if((app.is.vkey_state[vk]!=app.prev_vk_state[vk])&&(app.is.vkey_state[vk]!=0))
   {
   veekay.vk=vk;
   veekay.state=app.is.vkey_state[vk];
   if(veekay.state==1)  {  app.held_vk_ms[vk]=aaMsRunning();    }
   aaMemoryCopy(&veekay.is,sizeof(app.is),&app.is);
   aaQueWrite(app.vk_que.handle,sizeof(veekay),&veekay);
   aaQueStatus(app.vk_que.handle,&app.vk_que.status);
   }
  app.prev_vk_state[vk]=app.is.vkey_state[vk];
  }
 }



 B appVkeyGet                          (_veekay*veek)
 {
 B ret;
 app.is_using_vk=YES;
 if((ret=aaQueRead(app.vk_que.handle,sizeof(_veekay),veek))!=YES) { return ret; }
 aaQueStatus(app.vk_que.handle,&app.vk_que.status);
 veek->ms=aaMsRunning()-app.held_vk_ms[veek->vk];
 return RET_YES;
 }
 #endif






 B appCpuViz                           (V)
 {
 H ec,x,z,y,fi;
 _rect mr,r1;
 _cord c1,c2;
 N perc;
 _rgba pn[4];

 ec=aaElementCount(app.load_timeline[0]);
 if(app.load_counter_prev!=app.load_counter&&1)
  {
  aaRectSet(&mr,app.canvas.status.size.w-130,30,ec+10,110);
  aaRectSet(&mr,12,20,ec+10,110);
  aaSurfaceFill(app.canvas.handle,&mr,&col_pastelblue[13]);
  aaRectCopy(&r1,&app.draw_rect);
  aaRectSet(&r1,r1.w-10-ec,r1.y+10,ec,100);
  r1.x=mr.x+((mr.w-ec)>>1);
  r1.y=mr.y+((mr.h-ec)>>1);
  aaSurfaceFill(app.canvas.handle,&r1,&col_pastelblue[16]);
  aaRgbaCopy(&pn[0],&col_pastelblue[31]);
  aaRgbaCopy(&pn[1],&col_gray[5]);
  aaRgbaCopy(&pn[2],&col_pastelred[31]);
  aaRgbaCopy(&pn[3],&col_gray[11]);
  pn[0].a=255;
  pn[1].a=255;
  pn[2].a=128;
  pn[3].a=192;
  for(y=10;y<100;y+=10)
   {
   aaCordsSet(&c1,&c2,r1.x+5,(r1.y+y),(r1.x+r1.w)-6,(r1.y+y));
   aaSurfaceLine(app.canvas.handle,&c1,&c2,&col_gray[15]);
   }
  for(x=0;x<(ec);x++)
   {
   for(z=0;z<2;z++)
    {
    perc=(N)app.load_timeline[z][x]*1;
    aaCordsSet(&c1,&c2,r1.x+x,(r1.y+100)-perc,r1.x+x,r1.y+100);
    aaSurfaceLine(app.canvas.handle,&c1,&c2,&pn[(z*2)+0]);
    aaSurfacePixelPut(app.canvas.handle,&c1,&pn[(z*2)+1]);
    }
   }




  fi=2;
  aaCordSet(&c1,mr.x+13,mr.y+5);
  aaRgbaSet(&pn[0],40,40,40,128);
  aaSurfacePrintf(app.canvas.handle,&c1,app.font[fi].handle,&pn[0],0,"%.1f",aa_curcpuload);
  aaCordAdjust(&c1,-3,-3);
  aaRgbaSet(&pn[0],240,240,40,188);
  aaSurfacePrintf(app.canvas.handle,&c1,app.font[fi].handle,&pn[0],0,"%.1f",aa_curcpuload);

  fi=3;
  aaCordSet(&c1,mr.x+13,mr.y+30);
  aaRgbaSet(&pn[0],40,40,40,128);
  aaSurfacePrintf(app.canvas.handle,&c1,app.font[fi].handle,&pn[0],0,"%.1f",aa_curproload);
  aaCordAdjust(&c1,-3,-3);
  aaRgbaSet(&pn[0],40,240,240,228);
  aaSurfacePrintf(app.canvas.handle,&c1,app.font[fi].handle,&pn[0],0,"%.1f",aa_curproload);


  aaSurfaceUpdateAreaAdd(app.canvas.handle,&mr,0);
  //appLog("lc=%i plc=%i",app.load_counter,app.load_counter_prev);
  app.load_counter_prev=app.load_counter;
  return RET_YES;
  }
 return RET_NO;
 }





 B appYield                            (V)
 {
 B ret;
 _size s1;
 _rect r1;
 Q el;
 H i,ec;
 B ir;

 if(app.magic!=aaHPP(appStart)) { return RET_NOTINITIALIZED; }
 if(aa_cycle==30)
  {
  aaSurfaceFocus(app.canvas.handle);
  aaSurfaceStatus(app.canvas.handle,&app.canvas.status);
  aaFocusToChrome(0);
  aaFocusToDbg(0);
  }

 switch(app.quit_stage)
  {
  case 0: if(1&&aa_is_esc)  { appQuit(); }  break;
  case 1: app.quit_stage=2;  break;
  case 2: return RET_NO;
  }

 if(aaYield(app.kfg.app_speed)!=YES) {  return RET_NO;  }

 for(i=0;i<1;i++)
  {
  if(serverProcessor()!=YES) { break; }
  }
 if(1&&aaHz(0.3))  {  aaNetStatus(&app.ns);  }
 if(1&&aaHz(0.4))  {  aaMemoryStatus(&app.mem_status); }

 aaSurfaceStatus(app.canvas.handle,&app.canvas.status);

 if(app.canvas.status.is_systray)
  {
  if((el=aa_msrunning-app.tray_icon_ms)>=400)
   {
   app.tray_icon_index++;
   if((ret=aaSurfaceTraySet(app.canvas.handle,1000+(app.tray_icon_index%2),"%s %s",app.canvas.status.title,DEV_VERSION))!=YES) { oops; }
   app.tray_icon_ms=aa_msrunning;
   if(aa_display_change_counter)
    {
    if((ret=aaInfoGet(&app.info,F32))!=YES) { oops; }
    aaSizeSet(&s1,app.canvas.status.size.w,app.canvas.status.size.h);
    aaRectSet(&r1,app.info.display_info.tray_rect.x-s1.w-24,app.info.display_info.tray_rect.y-s1.h-24,s1.w,s1.h);
    aaSurfaceRectSet(app.canvas.handle,&r1);
    aaSurfaceStatus(app.canvas.handle,&app.canvas.status);
    aa_display_change_counter=0;
    }
   }
  if(aaSurfaceIsTrayClicked(app.canvas.handle,0,&ir)==RET_YES)
   {
   if((ret=aaSurfaceTrayClickClear(app.canvas.handle))!=YES) { oops; }
   if(ir)
    {
    aaSurfaceOnTop(app.canvas.handle,(app.canvas.status.is_top^1));
    }
   else
    {
    aaSurfaceShow(app.canvas.handle,(B)(app.canvas.status.is_shown^1));
    aaSurfaceFocus(app.canvas.handle);
    }
   aaSurfaceStatus(app.canvas.handle,&app.canvas.status);
   }
  }
 if(app.canvas.status.is_focus!=app.prev_focus)
  {
  app.prev_focus^=1;
  if(app.canvas.status.is_focus) { aaSurfaceFillFrame(app.canvas.handle,0,4,&col_cyan[23],0); }
  else                           { aaSurfaceFillFrame(app.canvas.handle,0,4,&col_red[31],0); }
  aaSurfaceUpdateAreaAdd(app.canvas.handle,0,0);
  }
 aaSurfaceUpdate(app.canvas.handle);
 aaSurfaceStatus(app.canvas.handle,&app.canvas.status);

 #if DO_INPUT_STUFF==YES
 appVkeyYield();
 #endif

 stunnerYield(&app.stunner,1);

 app.load_msel[1]=aaMsRunning()-app.load_msel[0];
 if(app.load_msel[1]>=100)
  {
  ec=aaElementCount(app.load_timeline[0])-1;
  for(i=0;i<2;i++) { aaMemoryCopy(&app.load_timeline[i][0],sizeof(D)*ec,&app.load_timeline[i][1]);  }
  app.load_timeline[0][ec]=aa_curcpuload;
  app.load_timeline[1][ec]=aa_curproload;
  app.load_msel[0]=aaMsRunning();
  app.load_counter++;
  }

 ///appLabel(10,"%I64d",aaMsRunning());

 return RET_YES;
 }











 B voxlevPaint                         (H ix,H xx,H yy)
 {
 H ec,x;
 _rect mr,r1;
 _cord c1,c2;
 D sqs;
 N perc;
 H count[130];
 D bia;

 bia=111.0;
 //aisesh->bia=111.0;
 //if(aisesh->bia==0.0) { return RET_YES; }

  ec=aaElementCount(app.voxlev_timeline[ix]);
  aaRectSet(&mr,xx,yy,(ec)+10,(121*1)+10);
  aaSurfaceFill(app.canvas.handle,&mr,col_map[121+(ix*27)]);
  aaRectSet(&r1,mr.x,mr.y,mr.w,mr.h);
  aaSurfaceFill(app.canvas.handle,&r1,col_map[((16+ix)*32)+31]);

  if(ix==0)   { aaSurfaceFillFrame(app.canvas.handle,&r1,4,&col_gray[10],&col_pastelgreen[29]); }
  else
  if(ix==1)   { aaSurfaceFillFrame(app.canvas.handle,&r1,4,&col_gray[10],&col_pastelblue[29]);  }

  // voxlev main painter
  aaMemoryFill(count,sizeof(count),0);
  for(x=0;x<(ec);x++)
   {
   sqs=app.voxlev_timeline[ix][ec-x-1]*1.0;
                if(0)
                 {
                 sqs+=bia;//aisesh->bia;
                 sqs=sqs/bia;//aisesh->bia;
                 sqs=sqs*100.0;
                 }
   perc=(N)sqs;
   if(perc>10&&perc<100)
    {
    if(aaMathRand32(0,200)==0)     {     }
    }
   if(perc<0||perc>99)    {    aaNote(0,"perc=%i",perc);    }
   count[perc]++;
   aaCordsSet(&c1,&c2,r1.x+x+5,(r1.y+120+4)-perc,r1.x+x+5,r1.y+120+4);
   aaSurfaceLine(app.canvas.handle,&c1,&c2,col_map[((ix+8)*32)+21]);
   }
 aaSurfaceUpdateAreaAdd(app.canvas.handle,&mr,0);
 app.voxlev_counter_prev[ix]=app.voxlev_counter[ix];
 return RET_YES;
 }




 B voxlevPush                          (H ix,D lev)
 {
 H ec=aaElementCount(app.voxlev_timeline[ix])-1;
 aaMemoryCopy(&app.voxlev_timeline[ix][0],sizeof(D)*ec,&app.voxlev_timeline[ix][1]);
 app.voxlev_timeline[ix][ec]=lev;
 app.voxlev_counter[ix]++;
 return RET_YES;
 }




 V UtfEscape                           (CP src,CP dest,Z dest_sz)
 {
 Z i,j,code;
 B c;
 i=j=0;
 while(src[i]!=NULL_CHAR&&j<dest_sz-1)
  {
  c=src[i];
  if(c<0x80)
   {
   if(j+1<dest_sz) dest[j++]=src[i++];
   }
  else
  if((c&0xE0)==0xC0&&src[i+1]!=NULL_CHAR)
   {
   code=((c&0x1F)<<6)|(src[i+1]&0x3F);
   if(j+6<dest_sz)
    {
    j+=snprintf(&dest[j],dest_sz-j,"\\u%04X",code);
    i+=2;
    }
   else break;
   }
  else
  if((c&0xF0)==0xE0&&src[i+1]!=NULL_CHAR&&src[i+2]!=NULL_CHAR)
   {
   code=((c&0x0F)<<12)|((src[i+1]&0x3F)<<6)|(src[i+2]&0x3F);
   if(j+6<dest_sz)
    {
    j+=snprintf(&dest[j],dest_sz-j,"\\u%04X",code);
    i+=3;
    }
   else break;
   }
  else
   {
   i++; // Skip or handle 4-byte surrogate pairs if necessary
   }
  }
 dest[j]=NULL_CHAR;
 }






 V UtfUnEscape                         (CP src,CP dest)
 {
 Y code;
 while (*src)
  {
  if(*src=='\\'&&*(src+1)=='u')
   {
   sscanf(src+2,"%04x",&code);
   if(code<=0x7F)
    {
    *dest++=(char)code;
    }
   else
   if(code<=0x7FF)
    {
    *dest++=(char)(0xC0|((code>>6)&0x1F));
    *dest++=(char)(0x80|(code&0x3F));
    }
   else
    {
    *dest++=(char)(0xE0|((code>>12)&0x0F));
    *dest++=(char)(0x80|((code>>6)&0x3F));
    *dest++=(char)(0x80|(code&0x3F));
    }
   src+=6; // Move past "\uXXXX"
   }
  else
   {
   *dest++=*src++;
   }
  }
 *dest=NULL_CHAR;
 }





 Z UtfStrlen                           (CP src)
 {
 Z count;
 count=0;
 while (*src)
  {
  if((*src&0xC0)!=0x80) {  count++;    }
  src++;
  }
 return count;
 }



 B textpairLineLog                     (_textpair*textpair,H lines)
 {
 B out[_128K];
 aaStringNull(out);
 aaStringAppendf(out,"%-4i/%-4i 0x%08x %-25s 0x%08x %s",textpair->line,lines,textpair->key_hash,textpair->key,textpair->val_hash,textpair->val);
 appLog("> %s",out);
 return RET_YES;
 }




 B aaTextReaderProc                    (_textreader*textreader,H li,H chars,VP txt)
 {
 H pos;
 B tkey[513];
 B tval[_32K];
 B tokn[_64K];
 BP bp;

 if(chars) {}
 if(textreader) { }

 if(li==0)
  {
  //appLog(" ");
  }
  appLog("%4i/%-4i %s",li,textreader->line_count,txt);
 ///aaLog(-555,"got here b");
 if(aaStringNICompare(txt,"channel.alternatives[0].transcript:",F32,0)==YES)
  {
  //appLog("trd11 %-4i %s",li,txt);
  }
 #if 0
 aaStringReplaceString(txt,0,"\r",1,"\\r",2,1,txt);
 aaStringReplaceString(txt,0,"\n",1,"\\n",2,1,txt);
 #endif
 if(aaStringFindChar(txt,0,&pos,':',YES,0,YES)!=YES)
  {
  //appLog("BAD  %4i/%-4i %s",li,textreader->line_count,txt);
  return RET_YES;
  }
 bp=(BP)txt;
 aaStringNCopy(tkey,bp,pos,YES);
 aaStringCopy(tval,&bp[pos+1]);
 //aaStringCopyf(tokn,"%s",tkey);
 aaStringCopy(tokn,tkey);
 return RET_YES;
 }


