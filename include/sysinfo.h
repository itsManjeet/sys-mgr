#ifndef __SYSINFO__
#define __SYSINFO__

#include <releax>
#include <fstream>
#include <streambuf>

#define DEBUG

using namespace std;

#define OS_RELEASE "/etc/os-release"
#define LSB_RELEASE "/etc/lsb_release"
#define RELEAX_RELEASE "/etc/releax-release"

namespace releax {

namespace sysinfo {

    string osver();
    string osrel();
    string codename();

    int apps_count(bool inc_sys_apps = false);
    string parse_osrel(string var);

    string dmi(string i);

    string parse_sys_files(string f_path, string var, string del = ":");
    string getout(const char* cmd);
}

}

#endif