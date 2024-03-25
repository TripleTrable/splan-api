#include <locale.h>
#include <stdio.h>
#include "splan/spdata.h"
#include "splan/json/spapi.h"

int main(void)
{
    if (!setlocale(LC_ALL, "de_DE.UTF-8"))
        perror("could not set german locale");
    server_user_config user_config;
    user_config.server_api_endpoint =
        "https://splan.th-rosenheim.de/splan/json";

    splan_init(&user_config);

    splan_get_locs();
    printf("Hello World");
}
