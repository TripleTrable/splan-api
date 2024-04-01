#include <locale.h>
#include <stdio.h>
#include "splan/spdata.h"
#include "splan/json/spapi.h"

int main(void)
{
    server_user_config user_config;
    user_config.server_api_endpoint =
        "https://splan.th-rosenheim.de/splan/json";

    splan_init(&user_config);

    splan_get_locs();

    splan_get_pus();
    printf("Hello World");
}
