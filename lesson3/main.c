#include "main.h"

void my_opn(int ws){
  printf("@@@@@@@@my_opn(%d)\n",ws);
  wsend(ws,"HELLO");
}
void my_msg(int ws,char*msg){
  printf("@@@@@@@@my_msg(%d)[%s]\n",ws,msg);
  if(!strcmp(msg,"HELLO")){
    printf(" $$ HELLO\n");
    wsend(ws, "HOWZIT");
  }else if(!strcmp(msg,"HOWZIT")){
    printf(" $$ HOWZIT\n");
    wsend(ws, "GREAT");
  }else if(!strcmp(msg,"GREAT")){
    printf(" $$ GREAT\n");
    wclose(ws);
  }else if(!strcmp(msg,"")){
    printf(" $$ BLANK\n");
  }else{
    printf(" $$ DUNNO\n");
  }
}
void my_cls(int ws){
  printf("@@@@@@@@my_cls(%d)\n",ws);
}

int main(){
  printf("hello from main\n");
  eleven();
  wsox(my_opn, my_msg, my_cls);
  int ws = wconn("wss://echo.websocket.org");
  printf("ws = %d\n", ws);
}
