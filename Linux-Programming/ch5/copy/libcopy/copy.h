#ifndef __COPY_H
#define __COPY_H
#include <sys/stat.h>
/*
* copy file from source file to destination.
@param	src		source file
@param	dest	destination file
@param	mode	mode.
*/
int cp_file(char* src, char* dest, __mode_t mode);

/*
* copy directory from source to destination.
@param	src		source dir
@param	dest	destination dir
*/
int cp_dir(const char* src, const char* dest);

#endif
