#include "main.h"
static FN1 _opn = 0, _cls = 0;
static FN2 _msg = 0;
#include <emscripten.h>
void wopn(int ws){         _opn(ws);}
void wmsg(int ws,char* d){ _msg(ws, d);}
void wcls(int ws){         _cls(ws);}
void wsox(FN1 opnfn, FN2 msgfn, FN1 clsfn){
  _opn = opnfn; _msg = msgfn; _cls = clsfn;
  EM_ASM({
      try{
	console.log(WebSocket);
      }catch(e){
	WebSocket = require("ws");
      }
      WSARR = [];
      wopn = Module._wopn;
      wmsg = Module.cwrap("wmsg","void",["number","string"]);
      wcls = Module._wcls;
    });}

void wsend(int ws, char* data){
  return EM_ASM({ WSARR[$0 - 2000].send(UTF8ToString($1)); }, ws, data);}
void wclose(int ws){
  return EM_ASM({ WSARR[$0 - 2000].close(); }, ws);}
int wconn(char* url){
  return EM_ASM_INT({
      var dest = UTF8ToString($0);
      var ws = new WebSocket(dest);
      ws.onopen=function(){	wopn(ws.id);      };
      ws.onmessage=function(e){	wmsg(ws.id, e.data);};
      ws.onclose=function(){	wcls(ws.id);      };
      return ws.id = (WSARR.push(ws)-1+2000);
    }, url);}

