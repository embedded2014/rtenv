/*uer program begins at 0x00008000 = 32k*/

/*#include "stm32f10x.h"*/

int test_main(){
  const char *p = "this is a user program";
  
  /*
  while(*p){
     while(USART_GetFlagStatus(USART2,USART_FLAG_TXE) == RSET);
     USART_SendData(USART2,*p);
     p++;    
  }
  */
  return 1;
}
