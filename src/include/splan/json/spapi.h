#ifndef SPAPI_H
#define SPAPI_H
#include "../spdata.h"

/*
2. "getlocs" (get list of universities):
    GET https://splan.th-rosenheim.de/splan/json?m=getlocs
    RESPONSE: [[{"id":3,"shortname":"*RO","name":"Rosenheim (Hochschule)"},{"id":6,"shortname":"AÖ","name":"Altötting (Berufliche Oberschule Inn-Salzach)"},{"id":8,"shortname":"BGL","name":"Ainring (Akademie Berchtesgadener Land)"},{"id":7,"shortname":"Bgh","name":"cb - Hochschulinstitut Burghausen"},{"id":9,"shortname":"CC","name":"Campus Chiemgau Traunstein"},{"id":4,"shortname":"MÜ","name":"Mühldorf (Haus der Wirtschaft)"},{"id":5,"shortname":"WS","name":"Wasserburg (RoMed Klinik)"}]]
*/

loc *splan_get_locs(void);

//local
loc *locs_parse_json(const char *data);
char *iso8859_1_to_utf_8(char *iso);

#endif // !SPAPI_H
