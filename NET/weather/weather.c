#include "weather.h"
#include "usart.h"
#include "jsmn.h"

#include <stdio.h>
#include <string.h>
#include "malloc.h"


unsigned char* name;
char cloud[6];
char code[6];
char temperature[6];

void copyStr(const char *souces, char *to,int length)
{
    if (souces == NULL || to == NULL)   return;
    while (length--)
    {
        *to++ = *souces++;
    }
}

static int jsoneq(const char *json, jsmntok_t *tok, const char *s) 
{
  if (tok->type == JSMN_STRING && (int)strlen(s) == tok->end - tok->start &&
      strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
    return 0;
  }
  return -1;
}

int Parse_Weather(char str[400])
{
    int i;
    int r;
		char utf8str[6];
    jsmn_parser p;
    jsmntok_t t[128] ; /* We expect no more than 128 tokens */
		char JSON_STRING[400] = "{";
	
		strcat(JSON_STRING,str);
		UsartPrintf(USART_DEBUG,"%s\r\n",JSON_STRING);
    jsmn_init(&p);
    r = jsmn_parse(&p, JSON_STRING, strlen(JSON_STRING), t,sizeof(t) / sizeof(t[0]));
    if (r < 0) {
        UsartPrintf(USART_DEBUG,"Failed to parse JSON: %d\n", r);
        return 1;
    }

    /* Assume the top-level element is an object */
    if (r < 1 || t[0].type != JSMN_OBJECT) {
        UsartPrintf(USART_DEBUG,"Object expected\n");
        return 1;
    }

    for (i = 1; i < r; i++) {
    if (jsoneq(JSON_STRING, &t[i], "name") == 0) {
      /* We may use strndup() to fetch string value */
      copyStr(JSON_STRING + t[i + 1].start,utf8str,t[i + 1].end - t[i + 1].start);
      UsartPrintf(USART_DEBUG,"- name: %s\n",name);
      //UsartPrintf("- name: %.*s\n",t[i + 1].end - t[i + 1].start,JSON_STRING + t[i + 1].start);
      i++;
    } else if (jsoneq(JSON_STRING, &t[i], "text") == 0) {
      /* We may additionally check if the value is either "true" or "false" */
      copyStr(JSON_STRING + t[i + 1].start,cloud,t[i + 1].end - t[i + 1].start);
      UsartPrintf(USART_DEBUG,"- text: %s\n",cloud);
      // UsartPrintf("- text: %.*s\n", t[i + 1].end - t[i + 1].start,JSON_STRING + t[i + 1].start);
      i++;
    } else if (jsoneq(JSON_STRING, &t[i], "code") == 0) {
      /* We may want to do strtol() here to get numeric value */
      copyStr(JSON_STRING + t[i + 1].start,code,t[i + 1].end - t[i + 1].start);
      UsartPrintf(USART_DEBUG,"- code: %s\n",code);
      // UsartPrintf("- code: %.*s\n", t[i + 1].end - t[i + 1].start,JSON_STRING + t[i + 1].start);
      i++;
    } else if (jsoneq(JSON_STRING, &t[i], "temperature") == 0) {
      /* We may want to do strtol() here to get numeric value */
      copyStr(JSON_STRING + t[i + 1].start,temperature,t[i + 1].end - t[i + 1].start);
      UsartPrintf(USART_DEBUG,"- temperature: %s\n",temperature);
      // UsartPrintf("- temperature: %.*s\n", t[i + 1].end - t[i + 1].start,JSON_STRING + t[i + 1].start);
      i++;
    } else {
      //UsartPrintf("Unexpected key: %.*s\n", t[i].end - t[i].start,JSON_STRING + t[i].start);
    }
  }


    return 0;
}

