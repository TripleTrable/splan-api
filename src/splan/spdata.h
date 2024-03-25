#ifndef SPDATA_H
#define SPDATA_H

#include <stdint.h>

typedef struct {
    char* server_api_endpoint;
} server_user_config;

extern server_user_config _server_config;
/*
2. "getlocs" (get list of universities):
    GET https://splan.th-rosenheim.de/splan/json?m=getlocs
    RESPONSE: [[{"id":3,"shortname":"*RO","name":"Rosenheim (Hochschule)"},{"id":6,"shortname":"AÖ","name":"Altötting (Berufliche Oberschule Inn-Salzach)"},{"id":8,"shortname":"BGL","name":"Ainring (Akademie Berchtesgadener Land)"},{"id":7,"shortname":"Bgh","name":"cb - Hochschulinstitut Burghausen"},{"id":9,"shortname":"CC","name":"Campus Chiemgau Traunstein"},{"id":4,"shortname":"MÜ","name":"Mühldorf (Haus der Wirtschaft)"},{"id":5,"shortname":"WS","name":"Wasserburg (RoMed Klinik)"}]]
*/
typedef struct {
    uint64_t id;
    char* shortname;
    char* name;
} loc;

/**
 * Initializes the config and Splan API related structs.
 * @param   config struct containing SPlan server data.
 *          This struct is copied inside splan_init.
 * @return  0 on success. -1 on failure and errno is set.
 */
int splan_init(server_user_config* config);

#endif // !SPDATA_H
