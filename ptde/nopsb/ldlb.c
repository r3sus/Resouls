#include <dirent.h>

// load from given directory DLLs whose name contains given string
void loadDLLs(char *dirN, char *flt)
{
char *tgt;
struct dirent *dp;
DIR *dir0 = opendir(dirN);
DEBUG_PRINT("dir %s ", dirN);
if (!dir0) {DEBUG_PRINT("not found; "); return;}
if (strcmp(dirN,".") != 0 ) SetDllDirectory(dirN);
while( dp = readdir(dir0) )
 {
 tgt = dp->d_name; 
 if (!strstr(tgt, ".dll") || !strstr(tgt, flt) ) continue;
 DEBUG_PRINT("%s ", tgt);
 LoadLibraryA(tgt);
 }
}
