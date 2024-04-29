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

/*
10."getPgsExt" (on list expansion using getogs[i].id and getpus[i].id to get module stuff):
    GET https://splan.th-rosenheim.de/splan/json?m=getPgsExt&pu=37&og=35
    RESPONSE: [[{"id":14119,"shortname":"INF-M/FWPM","name":"Masterstudiengang Informatik - fachwissenschaftliche Wahlpflichtmodule","lectures":[{"id":4721,"shortname":"DL","name":"Deep Learning","pgid":14119},{"id":4166,"shortname":"DSP","name":"Digital Signal Processing and Machine Learning","pgid":14119},{"id":4167,"shortname":"DSP P","name":"Digital Signal Processing and Machine Learning Praktikum","pgid":14119},{"id":4357,"shortname":"EEZS","name":"Embedded Echtzeitsysteme","pgid":14119},{"id":6537,"shortname":"ExModSim","name":"Experimental Modelling and Simulation","pgid":14119},{"id":3210,"shortname":"Fachschaft INF","name":"Fachschaft INF","pgid":13796},{"id":6302,"shortname":"FINS","name":"Finance with SAP","pgid":14119},{"id":6539,"shortname":"IntercultCom","name":"Intercultural communication - working in international groups","pgid":14119},{"id":3752,"shortname":"KS","name":"Kognitive Systeme","pgid":14119},{"id":4392,"shortname":"KVM","name":"Konfliktmanagement, Verhandlungs- und Moderationstechnik","pgid":14119},{"id":2960,"shortname":"ML","name":"Maschinelles Lernen","pgid":14119},{"id":6538,"shortname":"PsyfF","name":"Psychologie für Führungskräfte","pgid":14119},{"id":1026,"shortname":"RE","name":"Requirements Engineering","pgid":14119},{"id":1038,"shortname":"SQS","name":"Software Qualitätssicherung","pgid":14119},{"id":3753,"shortname":"xDB","name":"Erweiterte Datenbanksysteme","pgid":14119},{"id":3754,"shortname":"xITS","name":"Vertiefung der IT-Sicherheit","pgid":14119},{"id":4345,"shortname":"xRN","name":"Vertiefung Rechnernetze","pgid":14119}]},{"id":13815,"shortname":"INF-M/Pflicht","name":"Masterstudiengang Informatik - Pflichtmodule","lectures":[{"id":3210,"shortname":"Fachschaft INF","name":"Fachschaft INF","pgid":13796},{"id":1072,"shortname":"MVI","name":"Mathematische Verfahren der Informatik","pgid":13815},{"id":1073,"shortname":"MVI Ü","name":"Übungen zu Mathematische Verfahren der Informatik","pgid":13815},{"id":6303,"shortname":"SBAS","name":"SAP Basiskonzepte, Entwicklung und Systemarchitektur","pgid":13815},{"id":1070,"shortname":"STI","name":"Seminar theoretische Informatik","pgid":13815},{"id":4346,"shortname":"SwArb","name":"Seminar wissenschaftliches Arbeiten","pgid":13815},{"id":4347,"shortname":"SwArb Koll","name":"Seminar wissenschaftliches Arbeiten - Kolloquium","pgid":13815}]}]]

 lecture: {"id":4721,"shortname":"DL","name":"Deep Learning","pgid":14119}
*/
typedef struct {
    uint64_t id;
    char *shortname;
    char *name;
    uint64_t pgid;
} lecture;

void lecture_free(lecture *data);

void lecture_free_all(lecture *data, size_t size);

typedef struct {
    uint64_t id;
    char *shortname;
    char *name;
    lecture *lectures;
    size_t lecture_count;
} pgsext;

void pgsext_free(pgsext *data);

void pgsext_free_all(pgsext *data, size_t size);

/**
 * Initializes the config and Splan API related structs.
 * @param   config struct containing SPlan server data.
 *          This struct is copied inside splan_init.
 * @return  0 on success. -1 on failure and errno is set.
 */
int splan_init(server_user_config *config);

#endif // !SPDATA_H
