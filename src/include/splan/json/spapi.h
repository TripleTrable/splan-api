#ifndef SPAPI_H
#define SPAPI_H
#include "../spdata.h"
#include <cjson/cJSON.h>

/*
2. "getlocs" (get list of universities):
    GET https://splan.th-rosenheim.de/splan/json?m=getlocs
    RESPONSE: [[{"id":3,"shortname":"*RO","name":"Rosenheim (Hochschule)"},{"id":6,"shortname":"AÖ","name":"Altötting (Berufliche Oberschule Inn-Salzach)"},{"id":8,"shortname":"BGL","name":"Ainring (Akademie Berchtesgadener Land)"},{"id":7,"shortname":"Bgh","name":"cb - Hochschulinstitut Burghausen"},{"id":9,"shortname":"CC","name":"Campus Chiemgau Traunstein"},{"id":4,"shortname":"MÜ","name":"Mühldorf (Haus der Wirtschaft)"},{"id":5,"shortname":"WS","name":"Wasserburg (RoMed Klinik)"}]]

3. "getpus" (get list of semesters):
    GET https://splan.th-rosenheim.de/splan/json?m=getpus
    RESPONSE: [[{"id":37,"shortname":"2024 SoSe","name":"Sommersemester 2024","startdate":"2024-03-15","enddate":"2024-09-30","dateasdefault":true,"defaultloc":null,"visibleonweb":true},{"id":34,"shortname":"2023 WS","name":"Wintersemester 2023/24","startdate":"2023-10-01","enddate":"2024-03-14","dateasdefault":true,"defaultloc":null,"visibleonweb":true},{"id":33,"shortname":"2023 SoSe","name":"Sommersemester 2023","startdate":"2023-03-15","enddate":"2023-09-30","dateasdefault":true,"defaultloc":null,"visibleonweb":true},{"id":24,"shortname":"2022 WS","name":"Wintersemester 2022/23","startdate":"2022-10-01","enddate":"2023-03-14","dateasdefault":true,"defaultloc":null,"visibleonweb":true},{"id":23,"shortname":"2022 SS","name":"Sommersemester 2022","startdate":"2022-03-15","enddate":"2022-09-30","dateasdefault":true,"defaultloc":null,"visibleonweb":true}]]
*/

loc *splan_get_locs(void);
pu *splan_get_pus(void);
og *splan_get_ogs(const pu *semseter);
pgsext *splan_get_pgsext(const og *faculty, const pu *semester);
timetable *splan_get_timetable(pu *semeseter, lecture *lectures,
                               size_t lectures_count);

char *splan_get_pus_json(void);
char *splan_get_locs_json(void);

//local
loc *locs_parse_json(const char *data);
pu *pus_parse_json(const char *_data);
og *ogs_parse_json(const char *_data);
pgsext *pgsext_parse_json(const char *_data);
timetable *tt_parse_json(const char *_data);

lecture *lecture_parse(const cJSON *_data, size_t *size);

lecture *sort_lectures_partition(lecture *left, lecture *right);
void sort_lectures_ascending(lecture *left, lecture *right);
char *encode_lectures(lecture *lectures, size_t lectures_count);

char *iso8859_1_to_utf_8(const char *iso);

#endif // !SPAPI_H
