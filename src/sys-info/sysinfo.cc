#include "../../include/sysinfo.h"
#include <algorithm>

void rm_nl(string &s) {
    for (int p = s.find("\n"); p != (int) string::npos; p = s.find("\n"))
    s.erase(p,1);
}

string
releax::sysinfo::osver()
{
    return parse_osrel("VERSION_ID");
}

string
releax::sysinfo::osrel()
{
    string verdata = parse_osrel("VERSION");
    if (verdata.find("(") != string::npos) {
        int start = verdata.find("(") + 1;
        int end = verdata.find(")") - start;
        return verdata.substr(start, end);
    }
    return "UNKNOWN";
}

string
releax::sysinfo::parse_osrel(string var)
{
    if (is_exist(OS_RELEASE)) {
        ifstream fptr(OS_RELEASE);
        if (fptr.good()) {
            string line;
            while(getline(fptr, line)) {

                int eqloc = line.find("=");
                string v = line.substr(0, eqloc);
                string vl = line.substr(eqloc + 1);

                if (v == var) {
                    fptr.close();
                    if (vl.find("\"") != string::npos) {
                        vl = vl.substr(1, vl.size() - 2);
                    }
                    return vl;
                }
            }
        }

        fptr.close();
    }
    throw "unknow option";
}

int
releax::sysinfo::apps_count(bool inc_sys_apps)
{
    if (releax::is_exist("/var/lib/app/")) {
        auto f = releax::list_all("/var/lib/app");
        if (!inc_sys_apps) {
            auto a = releax::list_all("/apps/");
            return a.size() - 3;
        }
        return f.size();
    }
    return 0;
}

string
releax::sysinfo::dmi(string d)
{
    string fp = "/sys/devices/virtual/dmi/id/" + d;
    ifstream fptr(fp);
    if (fptr.good()) {
        string line;
        getline(fptr, line);
        
        fptr.close();
        return line;
    }

    return  "UNKNOWN";
}

string 
releax::sysinfo::parse_sys_files(string f_path, string var, string del)
{
    ifstream fptr(f_path);
    if (fptr.good()) {
        string line;
        getline(fptr, line);
        if (line.find(var + del) != string::npos) {
            int start = line.find(del) + 1;
            int end   = line.size() - start;
            return config::trim(line.substr(start, end));
        }
    }

    return "UNKNOWN";
}

string 
releax::sysinfo::getout(const char* cmd) {
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    rm_nl(result);
    return result;
}