#include "../../include/sysinfo.h"
#include <releax-cc/ui>
#include <vector>
#include <utility>

#define UI_FILE "data/sys-info.glade"

// int
// mainFunc(releax::cli& app)
// {
    
//     cout << releax::sysinfo::parse_osrel("PRETTY_NAME") << endl
//          << "version         :  " <<  << endl
//          << "release         :  " << releax::sysinfo::osrel() << endl
//          << "id              :  " <<  << endl
//          << "code name       :  " << releax::sysinfo::parse_osrel("VERSION_CODENAME") << endl
//          << "Hardware        :  " <<  << endl
//          << "Memory          :  " <<  << endl
//          << "Cpu             :  " <<  << endl
//          << "apps count      :  " << releax::sysinfo::apps_count() << "|" << releax::sysinfo::apps_count(true) - releax::sysinfo::apps_count() << endl
//          << "kernel version  :  " <<  << endl;
//     return 0;
// }

int 
main(int ac, char** av)
{
    releax::ui app;
    app.name("sys-info")
       .version(0.1)
       .release('a')
       .description("System Information")
       .author("Manjeet Singh", "itsmanjeet@releax.in","-");

    app.setup_gtk(ac, av, UI_FILE, "in.releax.sys.info");

    Gtk::Label *ver_label, *rel_label, *id_label, *hard_label, *mem_label, *cpu_label, *kernel_label, *osname_label;
    Gtk::LinkButton *home_linklabel, *help_linklabel, *comm_linklabel;

    app.builder->get_widget("ver_label",  ver_label);  ver_label->set_text(releax::sysinfo::osver());
    app.builder->get_widget("rel_label",  rel_label);  rel_label->set_text(releax::sysinfo::osrel());
    app.builder->get_widget("id_label",   id_label);   id_label->set_text(releax::sysinfo::parse_osrel("ID"));
    app.builder->get_widget("mem_label",  mem_label);  mem_label->set_text(releax::sysinfo::getout("free -h | head -n2 | tail -n1 | awk '{print $2}'"));
    app.builder->get_widget("hard_label", hard_label); hard_label->set_text(releax::sysinfo::dmi("product_name") + " " + releax::sysinfo::dmi("chassis_vendor"));
    app.builder->get_widget("cpu_label",  cpu_label);  cpu_label->set_text(releax::sysinfo::parse_sys_files("/proc/cpuinfo","model name"," : "));
    app.builder->get_widget("kernel_label", kernel_label);  kernel_label->set_text(releax::sysinfo::getout("uname -r"));

    app.builder->get_widget("osname_label", osname_label); osname_label->set_text(releax::sysinfo::parse_osrel("PRETTY_NAME"));
    app.builder->get_widget("home_linklabel", home_linklabel); home_linklabel->set_uri(releax::sysinfo::parse_osrel("HOME_URL"));
    app.builder->get_widget("help_linklabel", help_linklabel); help_linklabel->set_uri(releax::sysinfo::parse_osrel("DOCUMENTATION_URL"));
    app.builder->get_widget("comm_linklabel", comm_linklabel); comm_linklabel->set_uri(releax::sysinfo::parse_osrel("SUPPORT_URL"));


    return app.execute(ac, av);
}



