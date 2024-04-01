#ifndef SPDATA_H
#define SPDATA_H

#include <stdint.h>
#include <stdlib.h>

typedef struct {
    char *server_api_endpoint;
} server_user_config;

extern server_user_config _server_config;
/*
2. "getlocs" (get list of universities):
    GET https://splan.th-rosenheim.de/splan/json?m=getlocs
    RESPONSE: [[{"id":3,"shortname":"*RO","name":"Rosenheim (Hochschule)"},{"id":6,"shortname":"AÖ","name":"Altötting (Berufliche Oberschule Inn-Salzach)"},{"id":8,"shortname":"BGL","name":"Ainring (Akademie Berchtesgadener Land)"},{"id":7,"shortname":"Bgh","name":"cb - Hochschulinstitut Burghausen"},{"id":9,"shortname":"CC","name":"Campus Chiemgau Traunstein"},{"id":4,"shortname":"MÜ","name":"Mühldorf (Haus der Wirtschaft)"},{"id":5,"shortname":"WS","name":"Wasserburg (RoMed Klinik)"}]]
*/
typedef struct {
    uint64_t id;
    char *shortname;
    char *name;
} loc;

void loc_free(loc *data);

void loc_free_all(loc *data, size_t size);

/*
3. "getpus" (get list of semesters):
    GET https://splan.th-rosenheim.de/splan/json?m=getpus
    RESPONSE: [[{"id":37,"shortname":"2024 SoSe","name":"Sommersemester 2024","startdate":"2024-03-15","enddate":"2024-09-30","dateasdefault":true,"defaultloc":null,"visibleonweb":true},{"id":34,"shortname":"2023 WS","name":"Wintersemester 2023/24","startdate":"2023-10-01","enddate":"2024-03-14","dateasdefault":true,"defaultloc":null,"visibleonweb":true},{"id":33,"shortname":"2023 SoSe","name":"Sommersemester 2023","startdate":"2023-03-15","enddate":"2023-09-30","dateasdefault":true,"defaultloc":null,"visibleonweb":true},{"id":24,"shortname":"2022 WS","name":"Wintersemester 2022/23","startdate":"2022-10-01","enddate":"2023-03-14","dateasdefault":true,"defaultloc":null,"visibleonweb":true},{"id":23,"shortname":"2022 SS","name":"Sommersemester 2022","startdate":"2022-03-15","enddate":"2022-09-30","dateasdefault":true,"defaultloc":null,"visibleonweb":true}]]
 * */

typedef struct {
    uint64_t id;
    char *shortname;
    char *name;
    char *startdate; // potential change to sruct tm
    char *enddate; // potential change to sruct tm
    uint8_t dateasdefault;
    loc *defaultloc;
    uint8_t visibleonweb;
} pu;

void pu_free(pu *data);

void pu_free_all(pu *data, size_t size);

/**
 * Initializes the config and Splan API related structs.
 * @param   config struct containing SPlan server data.
 *          This struct is copied inside splan_init.
 * @return  0 on success. -1 on failure and errno is set.
 */
int splan_init(server_user_config *config);

#endif // !SPDATA_H
