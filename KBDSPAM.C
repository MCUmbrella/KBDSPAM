#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#define max 126
#define min 32
int main(int argc, char **argv)
{
  if(argc==1){puts("[X] TOO FEW OPTIONS");return(-1);};
  if(argc==2 && (strcmp(argv[1],"--help")==0 || strcmp(argv[1],"--HELP")==0)){puts("[i] KBDSPAM V1.0");puts("[i] (C)2019 UMBRELLA STUDIO");puts("[i] KBDSPAM.EXC <NUMBER O\' CHARACTERS> [--NOSPACE] [--NONUMBER] [--NO$] [--NOUPPER] [--ALLUPPER]");return(0);};
  short nospace=0;
  short nonumber=0;
  short no$=0;
  short noupper=0;
  short allupper=0;
  short aa=0;
  unsigned int aaa=atoi(argv[1]);
  unsigned char a=32;
  struct timeval tv;
  unsigned int num;
  unsigned int aaaa=0;
  short ccc=0;

  void c(char cc[]){
  if(strcmp(cc,"--NOSPACE")==0){nospace=1;}
  else if(strcmp(cc,"--NONUMBER")==0){nonumber=1;}
  else if(strcmp(cc,"--NO$")==0){no$=1;}
  else if(strcmp(cc,"--NOUPPER")==0){noupper=1;}
  else if(strcmp(cc,"--ALLUPPER")==0){allupper=1;}
  else{ccc=1;};
  }
  for(short i=2;i<argc;i++){c(argv[i]);};
  if(ccc==1){puts("[!] AT LEAST 1 INVALID OPTION DETECTED IN COMMAND");};
  if(aaa<=1){puts("[X] NUMBER NOT ACCEPTABLE");return(-1);};
  if(argc>=7){puts("[X] TOO MANY OPTIONS");return(-1);};
  printf("[i] ");while(aa<argc){printf("%s ",argv[aa]);aa++;};printf("PROCESSING\n");
  gettimeofday(&tv,NULL);
  srand(tv.tv_sec*1000000);

  while(aaaa<aaa)
  {
  r:
  num=rand()%(max-min)+min;
  a=num;
  if(nospace==1 && num==32){goto r;};
  if(nonumber==1 && num>=48 && num<=57){goto r;};
  if(no$==1 && ((num>=33 && num<=47) || (num>=58 && num<=64) || (num>=91 && num<=96) || (num>=123 && num<=126))){goto r;};
  if(noupper==1 && num>=65 && num<=90){goto r;};
  if(allupper==1 && num>=97 && num<=122){goto r;};
  printf("%c",a);
  aaaa++;
  }

  printf("\n[i] %d CHARACTERS DONE\n",aaa);
  return aaa;
}
