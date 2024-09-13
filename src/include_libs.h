//-*-C++-*-

#include <set>
#include <map>
#include <vector>
#include <assert.h>
#include <filesystem>
#include <iostream>
#ifdef _WIN32
    #include <io.h>
    #define stat _stat
    #define S_ISREG(m) (((m) & _S_IFMT) == _S_IFREG)
#else
    #include <unistd.h>
    #define stat lstat
#endif