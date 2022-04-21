#include <dirent.h>
// #include <conio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void director(const char* name) 
   {
   #ifdef __linux__
        // int check;
    //   check= 
      mkdir(name, 0777);
    //   if(!check) printf("directtory created"); 
   #else
       _mkdir(name);
   #endif
   }