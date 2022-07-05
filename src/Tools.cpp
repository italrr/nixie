#include <chrono>
#include <thread>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdarg.h>
#include <dirent.h>
#include <random>
#include <cmath>
#include <mutex>

#include "Tools.hpp"


bool nx::File::exists(const std::string &path){
    struct stat tt;
    stat(path.c_str(), &tt);
    return S_ISREG(tt.st_mode);	
}
