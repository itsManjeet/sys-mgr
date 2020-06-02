#include <releax.hh>

using namespace std;

int enableCoreDump(App* app);

int 
main(int ac, char** av)
{

    auto app = new App();
    app->name("sys-coredump")
       ->version(0.1)
       ->release('a')
       ->desc("System core dump managment tool")
       ->author("Manjeet Singh", "itsmanjeet@releax.in", "-")

       ->sub("enable","To enable kernel core dump", "", enableCoreDump);
    
    auto status = app->execute(ac, av);

    delete app;
    return status;
}


int
enableCoreDump(App* app)
{
    bool withSUID = false,
         now      = false;

    for(auto a: app->args) {
        if (a == "-with-suid")  {
            withSUID = true;
        } else if (a == "now") {
            now = true;
        }
    }


    string dir_path = "/etc/sysctl.d/";
    string file_name = "50-coredump.conf";

    if (!filesys::exist(dir_path)) filesys::makedir(dir_path,0755);

    string core_pattern = "kernel.core_pattern = /var/crash/%e.core-%u-%p\n";
    if (withSUID) {
        core_pattern += "kernel.suid_dumpable = 2\n";
    }

    if (!filesys::exist("/var/crash")) filesys::makedir("/var/crash",0644);

    filesys::touchFile(dir_path + '/' + file_name,
    core_pattern, 0644, false);


    if (now) {
        int status = sys::exec("/sbin/sysctl -p");
        if (status != 0) {
            cout << "error while enable core dump" << endl;
        }
    }

    return 0;
}


