#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#define MAX_CHAR_RANGE 126
#define MIN_CHAR_RANGE 32

short noSpace = 0;
short noNumber = 0;
short noSpecial = 0;
short noUpper = 0;
short allUpper = 0;
short debug = 0;
short noNewLine = 0;
short unknownArgument = 0;
unsigned char converted = 32;
struct timeval tv;
unsigned int generated;

void parseArgument(char arg[])
{
  if (!strcmp(arg, "--nospace") || !strcmp(arg, "-s"))
    noSpace = 1;
  else if (!strcmp(arg, "--nonumber") || !strcmp(arg, "-n"))
    noNumber = 1;
  else if (!strcmp(arg, "--nospecial") || !strcmp(arg, "-$"))
    noSpecial = 1;
  else if (!strcmp(arg, "--noupper") || !strcmp(arg, "-u"))
    noUpper = 1;
  else if (!strcmp(arg, "--allupper") || !strcmp(arg, "-a"))
    allUpper = 1;
  else if (!strcmp(arg, "--nonewline") || !strcmp(arg, "-r"))
    noNewLine = 1;
  else if (!strcmp(arg, "--debug") || !strcmp(arg, "-d"))
    debug = 1;
  else
    unknownArgument = 1;
}

void toLowerString(char str[])
{
  int i = 0;
  char c;
  while (str[i])
  {
    c = str[i];
    if (c >= 65 && c <= 90)
      str[i] = c + 32;
    i++;
  }
}

int main(int argc, char **argv)
{
  unsigned int amount = atoi(argv[1]);
  gettimeofday(&tv, NULL);
  srand(tv.tv_usec);
  if (argc == 1)
  {
    puts("[X] TOO FEW OPTIONS");
    return (-1);
  };
  for (int a = 0; a != argc; a++)
    toLowerString(argv[a]);
  if (argc == 2 && ((!strcmp(argv[1], "--help")) || !strcmp(argv[1], "-h")))
  {
    puts("[i] KBDSPAM V1.3\n    (C)2019-2021 UMBRELLA STUDIO\n    Usage: kbdspam <character amount> [--noSpace || -s] [--noNumber || -n] [--noSpecial || -$]\n                  [(--noUpper || -u) || (--allUpper || -a)] [--noNewLine || -r] [--debug || -d]");
    return (0);
  };
  if (strchr(argv[1], '-'))
  {
    puts("[X] NUMBER NOT ACCEPTABLE");
    return (-1);
  };

  for (short i = 2; i < argc; i++)
    parseArgument(argv[i]);
  if (debug && unknownArgument)
    puts("[!] UNKNOWN ARGUMENT FOUND IN COMMAND");
  if (amount < 1)
  {
    puts("[X] NUMBER NOT ACCEPTABLE");
    return (-1);
  }
  if (noSpace && noNumber && noSpecial && noUpper && allUpper)
  {
    puts("[X] TOO MANY OPTIONS");
    return (-1);
  }
  if (debug)
  {
    printf("[D] ");
    for (int a = 0; a < argc; a++)
      printf("%s ", argv[a]);
    printf("PROCESSING\n");
  }

  for (unsigned int genCount = 0; genCount < amount; genCount++)
  {
    generated = rand() % (MAX_CHAR_RANGE - MIN_CHAR_RANGE) + MIN_CHAR_RANGE;
    converted = generated;
    if (noSpace && generated == 32)// ignore ' '
    {
      genCount--;
      continue;
    }
    if (noNumber && generated >= 48 && generated <= 57)// ignore '0-9'
    {
      genCount--;
      continue;
    }
    if (noSpecial && ((generated >= 33 && generated <= 47) || (generated >= 58 && generated <= 64) || (generated >= 91 && generated <= 96) || (generated >= 123 && generated <= 126)))// ignore special characters
    {
      genCount--;
      continue;
    }
    if (noUpper && generated >= 65 && generated <= 90)// ignore 'A-Z'
    {
      genCount--;
      continue;
    }
    if (allUpper && generated >= 97 && generated <= 122)// ignore 'a-z'
    {
      genCount--;
      continue;
    }
    printf("%c", converted);
    gettimeofday(&tv, NULL);
  }
  if (!noNewLine)
    puts("");
  if (debug)
    printf("[D] %d CHARS GENERATED\n", amount);
  return amount;
}
