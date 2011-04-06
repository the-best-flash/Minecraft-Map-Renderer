#ifndef _FILE_ENUMERATION_H_
#define _FILE_ENUMERATION_H_

#include <string>
#include <list>
#include <cstring>
using namespace std;

#include <QDir>

#ifdef LINUX
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/param.h>
#endif

#ifdef WINDOWS

#endif

list<string> GetDirectories(string BaseDir);
list<string> GetFiles(string BaseDir);

#endif 
