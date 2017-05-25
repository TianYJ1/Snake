#include "LibraryMerger.h"
ArrayElement *memArr = NULL;
FILE *saverFile = NULL;

char *getUnformatted(char *key, ...)
{
   char buf[DEFAULT_LENGTH_STR] = { 0 };
   va_list vl;
   va_start(vl, key);
   vsnprintf(buf, sizeof(buf), key, vl);
   va_end(vl);
   char *ret = malloc(sizeof(buf));
   sprintf(ret, "%s", buf);
   return ret;
}
char* getMem(char *key)
{
   ArrayElement *cur = memArr;
   while (cur)
   {
      MemEntry *memEl = (MemEntry *)cur->container;
      ArrayElement *next = cur->linkToNext;
      if (strcmp(memEl->key,key) == 0)
         return memEl->data;
      if (!next)
         break;
      cur = next;
   }
   return "";
}
void putMem(char *key, char *data)
{
   ArrayElement *cur = memArr;
   if (cur != NULL)
   {
      int i = 0;
      while (cur != NULL)
      {
         MemEntry *memEl = (MemEntry *)cur->container;
         ArrayElement *next = cur->linkToNext;
         if (cur && memEl->key && strcmp(memEl->key, key) == 0)
         {
            memEl->data = data;
            set(memArr, i, (byte *)memEl, sizeof(memEl));
            return;
         }
         if (!next)
            break;
         cur = next;
         i++;
      }
   }
   MemEntry newEntry;
   newEntry.data = data;
   newEntry.key = key;
   add(&memArr, (byte *)&newEntry, sizeof(newEntry));
}
void loadMem()
{
   saverFile = fopen(DATA_SAVE_FILE, "a+");
   if (!saverFile)
   {
      Log_e(__func__, "opening saving data file error");
      return;
   }
   char str[DEFAULT_LENGTH_STR] = { 0 };
   while (fgets(str, sizeof(str), saverFile) != NULL)
   {
      char *eq = strstr(str, "=");
      if (eq)
      {
         char *data = malloc(sizeof(str)), *key = malloc(sizeof(str));
         memset(data, 0, sizeof(&data));
         memset(key, 0, sizeof(&key));
         memcpy(key, str, eq - str);
         key[eq - str] = 0;
         memcpy(data, eq + 1, str + sizeof(str) - eq);
         data[str + sizeof(str) - eq] = 0;
         //Log_i(__func__, "Loaded: %s=%s", key, data);
         putMem(key, data);
      }
   }
}
void saveMem()
{
   fclose(saverFile);
   saverFile = fopen(DATA_SAVE_FILE, "w+");
   if (!saverFile)
   {
      Log_e(__func__, "opening saving data file error");
      return;
   }
   ArrayElement *cur = memArr;
   while (cur)
   {
      MemEntry *memEl = (MemEntry *)cur->container;
      ArrayElement *next = cur->linkToNext;
      fprintf(saverFile, "%s=%s", memEl->key, memEl->data);
      Log_i(__func__, "Saved: %s=%s", memEl->key, memEl->data);
      if (!next)
         break;
      cur = next;
   }
   fclose(saverFile);
   saverFile = fopen("saves.data", "r+");

}
