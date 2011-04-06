#include "FileEnumeration.h"

list<string> GetDirectories(string BaseDir)
{
    list<string> str_lst;

#ifdef LINUX
    struct stat DirInfo;
    struct dirent * File;
    DIR * Dir;
    struct stat FileInfo;

    lstat( BaseDir.c_str(), &DirInfo);
    
    if (!S_ISDIR(DirInfo.st_mode))
        return lst;
        
    if ((Dir = opendir( BaseDir.c_str())) == NULL)
    {
        return lst;
    }
    
    while (( File = readdir(Dir)) != NULL)
    {
        string Name = BaseDir + "/" + File->d_name;

        lstat(Name.c_str(), &FileInfo);

        if (S_ISDIR(FileInfo.st_mode))
        {
            if(strcmp(File->d_name, ".") != 0 && strcmp(File->d_name, "..") != 0)
                lst.push_back(Name);
        }
    }  // end while
    closedir(Dir);
#endif

#ifdef WINDOWS

#endif

QDir dir = QDir((QString)BaseDir.c_str());

QStringList lst = dir.entryList(QDir::Dirs);

for(QStringList::iterator it = lst.begin(); it != lst.end(); it++)
{
    if(*it != "." && *it != "..")
        str_lst.push_back(dir.filePath(*it).toStdString());
}

return str_lst;
}

list<string> GetFiles(string BaseDir)
{
    list<string> str_lst;

#ifdef LINUX
    struct stat DirInfo;
    struct dirent * File;
    DIR * Dir;
    struct stat FileInfo;
    short int mode;

    lstat( BaseDir.c_str(), &DirInfo);
    
    if (!S_ISDIR(DirInfo.st_mode))
        return lst;
        
    if ((Dir = opendir( BaseDir.c_str())) == NULL)
    {
        return lst;
    }
    
    while (( File = readdir(Dir)) != NULL)
    {
        string Name = BaseDir + "/" + File->d_name;

        lstat(Name.c_str(), &FileInfo);

        if (!S_ISDIR(FileInfo.st_mode))
        {
            lst.push_back(Name);
        }
    }  // end while
    closedir(Dir);
#endif

#ifdef WINDOWS

#endif

QDir fDir = QDir((QString)BaseDir.c_str());

QStringList fLst = fDir.entryList(QDir::Files);

for(QStringList::iterator it3 = fLst.begin(); it3 != fLst.end(); it3++)
{
    str_lst.push_back(fDir.filePath(*it3).toStdString());
}

return str_lst;
}
