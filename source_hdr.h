/*-----------------------------------------------------------------------*/
 #pragma once
 #ifndef INC_SOURCE_HDR_H
 #define INC_SOURCE_HDR_H
 #define PUB                           extern
 #ifdef __cplusplus
 PUB "C" {
 #endif
/*-----------------------------------------------------------------------*/
 #include "aa.h"
/*-----------------------------------------------------------------------*/
 #define DEV_VERSION                   "3.34"
 #define SERVER_MAX_CALLS              24
 #define DO_INPUT_STUFF                0
/*-----------------------------------------------------------------------*/
 #define DEF_APP_WID                   1600
 #define DEF_APP_HIT                   888
/*-----------------------------------------------------------------------*/

 #if DO_INPUT_STUFF==YES

 structure
 {
 H vk;
 C state;
 Q ms;
 _inputstate is;
 }
 _veekay;

 #endif

/*-----------------------------------------------------------------------*/


 structure
 {
 H magic;
 _textreader tre;
 H app_speed;
 D app_version;
 B stun_host[129];
 B stun_match[129];
 H stun_pause;
 B twilio_sip_host[129];
 B twilio_sip_domain[129];
 B twilio_sip_user[129];
 B twilio_sip_pass[129];
 B twilio_sip_agent[129];
 B translate_host[129];
 B deepgram_key[129];
 B deepgram_endpoint[129];
 H deepgram_keepalive;
 B deepgram_defaults_model[129];
 B inworld_key[129];
 B fish_key[129];
 B fish_endpoint[129];
 B fish_defaults_model[129];
 D fish_defaults_temperature;
 B fish_defaults_voiceid[129];
 B claude_key[129];
 B claude_endpoint[129];
 B claude_defaults_model[129];
 D claude_defaults_temperature;
 H claude_defaults_max_tokens;
 B claude_defaults_system_prompt[129];
 H server_max_calls;
 W server_port;
 H voip_delay;
 H voip_frame_size;
 B voip_codec[129];
 H cx[10];
 }
 _konfig;


/*-----------------------------------------------------------------------*/

 B odeoAmplify                         (H samples,IP pcm,D gain);
 D odeoMinDbForSamples                 (Z samples);
 B odeoLevelDerive                     (Z samples,IP pcm,DP lev,DP nor,DP bias);
 B odeoLevelGet                        (H samples,IP pcm,DP lev);
 B odeoComfort                         (IP out,H num_samples,D target_rms,D smoothing,DP state);

/*-----------------------------------------------------------------------*/


 structure
 {
 H magic;
 H stage;
 B is_finished;
 B is_success;
 B is_failure;
 B this_host[129];
 _udpunit udp[1];
 _dnsunit dns;
 H dns_index;
 _stununit stun;
 B dot[129];
 Q ms;
 B public_dot[129];
 B wanting_dot[129];
 }
 _stunner;


 B stunnerNew                          (_stunner*stunner,VP thishost);
 B stunnerDelete                       (_stunner*stunner);
 B stunnerYield                        (_stunner*stunner,H ita);


/*-----------------------------------------------------------------------*/

 structure
 {
 H magic;
 B is_finished;
 H result_count;
 H header_count;
 _httpresult result;
 _httpheader header[90];
 }
 _httpinfo;


 B httpInfoInit                        (_httpinfo*httpinfo);
 B httpInfoResultAdd                   (_httpinfo*httpinfo,_httpresult*httpresult);
 B httpInfoHeaderAdd                   (_httpinfo*httpinfo,_httpheader*httpheader);


/*-----------------------------------------------------------------------*/


 E{
 MPCAT_FIXINT=0x01, MPCAT_FIXMAP, MPCAT_FIXARRAY, MPCAT_FIXSTR,
 MPCAT_NIL, MPCAT_BOOL, MPCAT_BIN, MPCAT_EXT, MPCAT_FLOAT,
 MPCAT_UINT, MPCAT_INT, MPCAT_FIXEXT, MPCAT_STR, MPCAT_ARRAY,
 MPCAT_MAP, MPCAT_NEGFIXINT
 };


 structure
 {
 H magic;
 _memoryunit mun;
 }
 _msgpack;


 B msgpackNew                          (_msgpack*msgpack);
 B msgpackDelete                       (_msgpack*msgpack);
 B msgpackReset                        (_msgpack*msgpack);
 B msgpackReAlloc                      (_msgpack*msgpack,H thresh,H toadd);
 B msgpackAppend                       (_msgpack*msgpack,H bytes,VP buf);
 B msgpackAppendByte                   (_msgpack*msgpack,B val);
 B msgpackAppendNil                    (_msgpack*msgpack);
 B msgpackAppendBool                   (_msgpack*msgpack,B val);
 B msgpackAppendInt                    (_msgpack*msgpack,H size,H val);
 B msgpackAppendBin                    (_msgpack*msgpack,H size,H bytes,VP buf);
 B msgpackAppendMap                    (_msgpack*msgpack,H count);
 B msgpackAppendMap16                  (_msgpack*msgpack,H length);
 B msgpackAppendArray                  (_msgpack*msgpack,H count);
 B msgpackAppendFixStrFixStr           (_msgpack*msgpack,VP key,VP fmt,...);
 B msgpackAppendFixStrFloat            (_msgpack*msgpack,VP key,F val);
 B msgpackAppendFixStr                 (_msgpack*msgpack,VP fmt,...);
 B msgpackAppendStr8                   (_msgpack*msgpack,VP fmt,...);
 B msgpackAppendStr16                  (_msgpack*msgpack,VP fmt,...);
 B msgpackAppendDouble                 (_msgpack*msgpack,D val);
 B msgpackAppendFloat                  (_msgpack*msgpack,F val);


/*-----------------------------------------------------------------------*/

 structure
 {
 B id[65];
 B name[65];
 }
 _fishttsvoice;


 structure
 {
 H cat;
 H cmd;
 H pos;
 H size;
 H plus;
 H more;
 H tl;
 B txt[257];
 D dub;
 Q ms;
 }
 _fishttscode;


 structure
 {
 H magic;
 B is_audio;
 B voice_id[129];
 H audio_len;
 BP audio_mem;
 B text[_1K];
 }
 _fishttsvox;



 structure
 {
 H magic;
 H stage;
 B key[129];
 _websocketclient ws_cli;
 _websockethdr ws_hdr;
 _msgpack msgpack;
 BP payload;
 IP sam;
 _queunit que;
 H man_phaze;
 H man_pos;
 H man_ib;
 _fishttscode code[100];
 H code_count;
 B is_ready;
 H vox_count;
 _fishttsvox vox[1];
 H voice_count;
 _fishttsvoice voice[64];
 }
 _fishtts;



 B fishTtsVoiceListAdd                 (_fishtts*fishtts,VP id,VP name);
 B fishTtsNew                          (_fishtts*fishtts,VP key);
 B fishTtsDelete                       (_fishtts*fishtts);
 B fishTtsReference                    (_fishtts*fishtts,VP vid,H len,H lmx,VP mem,VP fmt,...);
 B fishTtsWritef                       (_fishtts*fishtts,VP fmt,...);
 B fishTtsFlush                        (_fishtts*fishtts);
 B fishTtsYield                        (_fishtts*fishtts);



/*-----------------------------------------------------------------------*/

 E{
 CLAUDE_STAGE_PROMPT=1300,
 CLAUDE_STAGE_REQUEST=1400,
 CLAUDE_STAGE_WAITRESPONSE=2000,
 CLAUDE_STAGE_COMPLETED=3010,
 };




 structure
 {
 H magic;
 H stage;
 B is_ready;
 B is_success;
 B is_complete;
 H phaze;
 B host[129];
 W port;
 _tcpcallunit call;
 _httpinfo http_info;
 B is_chunked;
 B is_content_length;
 B content_type[129];
 B location[_2K];
 H chunk_size;
 H chunk_done;
 N content_length;
 N content_done;
 _queunit sweets;
 _queunit sse;
 _dynbufunit debu;
 _queunit answer;
 B response_preutf[_8K];
 B response[_2K];
 H msg_count;
 B usr_uid[129];
 B vvvv[32][_1K];
 VP aisesh_parent;
 }
 _claude;


 B claudeNew                           (_claude*claude,VP usruid);
 B claudeDelete                        (_claude*claude);
 B claudeDistill                       (_claude*claude);
 B claudeSet                           (_claude*claude,B isrdy,B issuc,H stage);
 B claudeRead                          (_claude*claude,HP chars,VP txt);
 B claudeYield                         (_claude*claude);




/*-----------------------------------------------------------------------*/

 #define FLUX_STT_MAX_WORDS            160

 #define flux_Connected                0x4427e748
 #define flux_EagerEndOfTurn           0x6e4c2861
 #define flux_EndOfTurn                0x2d81927d
 #define flux_eot_confidence           0x3556f7dd
 #define flux_event                    0xadcaccd6
 #define flux_request_id               0x94467a2d
 #define flux_sequence_id              0x4e6ca545
 #define flux_StartOfTurn              0x5934b5a0
 #define flux_transcript               0x1a95bfa5
 #define flux_turn_index               0x5bb5404b
 #define flux_TurnInfo                 0xb9d36fb9
 #define flux_TurnResumed              0x9f5bcb4d
 #define flux_type                     0x3165b05d
 #define flux_Update                   0x532399cb



 structure
 {
 B word[65];
 D confidence;
 D start;
 D end;
 }
 _fluxsttword;



 structure
 {
 B type[65];
 B event[65];
 H type_hash;
 H event_hash;
 B req_id[65];
 H turn_index;
 D audio_win[2];
 B transcript[513];
 D eot_confidence;
 H fsev_counter;
 H sequence_id;
 H word_count;
 _fluxsttword word[FLUX_STT_MAX_WORDS];
 B trigger[65];
 H languages_count;
 B languages[32][3];
 H languages_hinted_count;
 B languages_hinted[32][3];
 }
 _fluxsttevent;



 structure
 {
 H magic;
 H stage;
 B key[129];
 _websocketclient ws_cli;
 _websockethdr ws_hdr;
 Q keep_alive_ms;
 Q keep_alive_el;
 H keep_alive_trigs;
 _memoryunit flux_memu;
 _fluxsttevent the_event;
 VP aisesh_parent;
 }
 _fluxstt;


 B fluxSttNew                          (_fluxstt*fluxstt,VP key);
 B fluxSttDelete                       (_fluxstt*fluxstt);
 B fluxSttWrite                        (_fluxstt*fluxstt,H len,VP mem);
 B fluxSttFlush                        (_fluxstt*fluxstt);
 B fluxSttForceEndTurn                 (_fluxstt*fluxstt);
 B fluxSttEventProcess                 (_fluxstt*fluxstt,_fluxsttevent*fsev);
 B fluxSttEventDump                    (_fluxstt*fluxstt,_fluxsttevent*fsev);
 B fluxSttYield                        (_fluxstt*fluxstt);


/*-----------------------------------------------------------------------*/


 structure
 {
 H magic;
 H stage;
 _fishtts fish[1];
 _claude  claude[1];
 _fluxstt flux[1];
// _gootra  goot[1];
// _phone phone[1];
 B ready[256];
 B usr_uid[129];
 H the_call_handle;
 H the_call_index;
 _fileunit filu;
 H filu_off;
 Q filu_ms;
 B filu_text[_8K];
 H min_sl;
 Q max_el;
 H max_lmx;
 D lo_lev;
 D hi_lev;
 D acum_lev;
 H acum_cnt;
 _queunit audio_out_que;
 Q audio_out_ms;
 B save_full[_1K];
 B save_path[_1K];
 B save_file[_1K];
 _textreader journal;
 H journal_entries;
 B journal_last_role;
 H frame_size;
 B decoded_buf[_256K];
 H decoded_len;
 B next_url[_1K];
 Q ms_since_noise;
 H voice_num;
 B voice_id[129];
 B voice_name[65];
 B whos_turn;
 Q start_ms;
 Q running_ms;
 H running_cycle;
 B change_voice_flag;
 B needs_to_hear_ok;
 _queunit msg_que;
 H msg_count;
 B out[_64K];
 _queunit fsev_que;
 H fsev_count;
 H fsev_counter;
 H word_index;
 }
 _aisesh;


 B myseshNew                           (_aisesh*aisesh);
 B myseshDelete                        (_aisesh*aisesh);
 B myseshStatus                        (_aisesh*aisesh);
 B myseshStringToPcm                   (_aisesh*aisesh,VP str,HP pcmdone,IP pcm);
 B myseshReadFromClient                (_aisesh*aisesh);

 B myseshMsgQueRead                    (_aisesh*aisesh,HP count,_textpair*textpair);
 B myseshMsgQueWrite                   (_aisesh*aisesh,H count,_textpair*textpair);

 B myseshFsevQueRead                   (_aisesh*aisesh,_fluxsttevent*fsev);
 B myseshFsevQueWrite                  (_aisesh*aisesh,_fluxsttevent*fsev);

 B myseshListAppend                    (_aisesh*aisesh,VP role,VP url,VP fmt,...);


 B myseshFishToClient                  (_aisesh*ais);
 B myseshClaudeToFish                  (_aisesh*aisesh);

/*-----------------------------------------------------------------------*/


 structure
 {
 H call_handle;
 N call_index;
 H call_number;
 H call_session;
 H phaz;
 H chat_stage;
 B url[129];
 VP aisesh_ptr;
 }
 _servercalldata;


 B serverPktWrite                      (B oc,B ff,H bytes,VP data);
 B serverPktWritef                     (B oc,B ff,VP fmt,...);
 B serverPktRead                       (_websockethdr*wockhdr,VP wockdata);
 B serverProcessor                     (V);



/*-----------------------------------------------------------------------*/



 structure
 {
 H magic;
 H quit_stage;
 N i_am;
 B c_time[65];
 _info info;
 B tree_dir[513];
 H border;
 _surfaceunit canvas;
 B prev_focus;
 H tray_icon_index;
 Q tray_icon_ms;
 _fontunit font[5];
 _rect draw_rect;
 _memorystatus mem_status;
 _netstatus ns;
 Q profiler[64];
 D profelap[64];
 #if DO_INPUT_STUFF==YES
 _queunit vk_que;
 B is_using_vk;
 _inputstate is;
 Q held_vk_ms[256];
 C prev_vk_state[256];
 #endif
 _konfig kfg;
 Q load_msel[2];
 D load_timeline[2][100];
 H load_counter;
 H load_counter_prev;
 D voxlev_timeline[2][300];
 H voxlev_counter[2];
 H voxlev_counter_prev[2];
 B do_restart;
 _websocketserver the_server;
 _servercalldata server_calldata[SERVER_MAX_CALLS];
 _stunner stunner;
 }
 _app;


 B appKonfig                           (VP filename);
 B appKonfigGet                        (H index,VP key,VP val,DP dub);
 B appKonfigFind                       (H index,HP found,VP key,VP val,DP dub,B partial,VP fmt,...);

 B appStart                            (V);
 B appStop                             (V);
 B appQuit                             (V);
 B appDraw                             (V);
 B appLabel                            (H line,VP fmt,...);
 B appLog                              (VP fmt,...);
 D appProfiler                         (H index,B init,B mode);
 #if DO_INPUT_STUFF==YES
 V appVkeyYield                        (V);
 B appVkeyGet                          (_veekay*veek);
 #endif
 B appCpuViz                           (V);
 B appYield                            (V);

 B voxlevPaint                         (H ix,H xx,H yy);
 B voxlevPush                          (H ix,D lev);

 V UtfEscape                           (CP src,CP dest,Z dest_sz);
 V UtfUnEscape                         (CP src,CP dest);
 Z UtfStrlen                           (CP src);

 B textpairLineLog                     (_textpair*textpair,H lines);

 B aaTextReaderProc                    (_textreader*textreader,H li,H chars,VP txt);


/*-----------------------------------------------------------------------*/
 PUB _app                              app;
/*-----------------------------------------------------------------------*/
 #endif
/*-----------------------------------------------------------------------*/
 #ifdef __cplusplus
 }
 #endif

