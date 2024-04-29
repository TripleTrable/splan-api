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
    RESPONSE: [[{"id":3,"shortname":"*RO","name":"Rosenheim (Hochschule)"},{"id":6,"shortname":"AÖ","name":"Altötting (Berufliche Oberschule Inn-Salzach)"}]]
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
    RESPONSE: [[{"id":37,"shortname":"2024 SoSe","name":"Sommersemester 2024","startdate":"2024-03-15","enddate":"2024-09-30","dateasdefault":true,"defaultloc":null,"visibleonweb":true},{"id":34,"shortname":"2023 WS","name":"Wintersemester 2023/24","startdate":"2023-10-01","enddate":"2024-03-14","dateasdefault":true,"defaultloc":null,"visibleonweb":true}]]
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

/*
  4. "getogs&pu=<getpus[i].id>" (get faculties):
    GET https://splan.th-rosenheim.de/splan/json?m=getogs&pu=37
    RESPONSE: [[{"id":105,"shortname":"AAI-B","name":"Bachelorstudiengang Applied Artificial Intelligence"},{"id":41,"shortname":"AFE-M","name":"Masterstudiengang Angewandte Forschung & Entwicklung in den Ingenieurwissenschaften"}]]
*/

typedef struct {
    uint64_t id;
    char *shortname;
    char *name;
} og;

void og_free(og *data);

void og_free_all(og *data, size_t size);

/**
 * Initializes the config and Splan API related structs.
 * @param   config struct containing SPlan server data.
 *          This struct is copied inside splan_init.
 * @return  0 on success. -1 on failure and errno is set.
 */
int splan_init(server_user_config *config);

#endif // !SPDATA_H
