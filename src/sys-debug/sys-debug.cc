#include <releax>
#include <iostream>

using namespace std;

int main_func(releax::cli &app) {

}

int genlog_func(releax::cli &app) {

}

int main(int ac, char** av) {

    releax::cli app;

    app.name("sys-debug")
       .version(0.1)
       .release('a')
       .description("releax os system debugger")

       .author("Manjeet Singh", "itsmanjeet@releax.in", "-")

       .main(main_func)

       .sub("gen-log", "To Generate log file", "command", genlog_func);

    
    return app.execute(ac, av);
}