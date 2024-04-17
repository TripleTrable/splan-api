#include <signal.h>
#include <stdio.h>
#include "splan/spdata.h"
#include "splan/json/spapi.h"
#include "rest/default_route.h"
#include <microhttpd.h>

void sig_handler(int signum)
{
    exit(0);
}

int main(void)
{
    signal(SIGTERM, sig_handler);
    signal(SIGINT, sig_handler);
    server_user_config user_config;
    user_config.server_api_endpoint =
        "https://splan.th-rosenheim.de/splan/json";

    splan_init(&user_config);

    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_THREAD_PER_CONNECTION, 8080, NULL, NULL,
                              &default_handler, NULL, MHD_OPTION_END);

    if (!daemon)
        return -1;

    while (1)
        sleep(1);

    MHD_stop_daemon(daemon);
    printf("Hello World");
}
