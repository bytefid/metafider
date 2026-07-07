#include <print>
#include "metafider_app/MetafiderApp.h"

int main() {
    MetafiderApp main_app;
    if (!main_app.Init()) {
        return 1;
    }

    if (!main_app.Load("meta_raw.dat")) {
        return 1;
    }

    main_app.Parse();

    main_app.PrintData();

    return 0;
}