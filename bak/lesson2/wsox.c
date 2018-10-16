#include "main.h"
static FN1 _opn = 0, _cls = 0;
static FN2 _msg = 0;
#include <emscripten.h>

void wsend(int ws, char* data){
  printf("hello from wsend(%d,\"%s\"\n", ws, data);
  return EM_ASM({ WSARR[$0 - 2000].send(UTF8ToString($1)); }, ws, data);}
void wclose(int ws){
  printf("hello from wclose(%d)\n", ws);
  return EM_ASM({ WSARR[$0 - 2000].close(); }, ws);}
int wconn(char* url){
  printf("hello from wconn\n");
  return EM_ASM_INT({
      var dest = UTF8ToString($0);
      console.log("CONNECT TO", dest);
      var ws = new WebSocket(dest);
      ws.onopen=function(){
	console.log("  ON OPEN");
	wopn(ws.id);
      };
      ws.onmessage=function(e){
	console.log("  ON MSG"+e.data);
	wmsg(ws.id, e.data);
      };
      ws.onclose=function(){
	console.log("  ON CLOSE");
	wcls(ws.id);
      };
      return ws.id = (WSARR.push(ws)-1+2000);
    }, url);}

void wopn(int ws){
  //printf("@@@@@@@@ wopn %d\n", ws);
  _opn(ws);}
void wmsg(int ws,char* d){
  //printf("@@@@@@@@ wmsg %d [%s]\n", ws, d);
  _msg(ws, d);}
void wcls(int ws){
  //printf("@@@@@@@@ wcls %d\n", ws);
  _cls(ws);}
void wsox(FN1 opnfn, FN2 msgfn, FN1 clsfn){
  printf("hello from wsox\n");
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
