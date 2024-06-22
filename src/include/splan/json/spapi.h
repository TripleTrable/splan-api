/*! @file spapi.h
 *  @brief Header file for the starplanner handling
 *
 *  This file contains the function declarations which are used
 *  to interact and parse the Starplanner output
 */
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

/** @brief request all universities from StarPlanner
 *
 *  This function makes a HTTP-2.0 GET request to the StarPlanner API and
 *  converts the request result into a list of university structs
 *
 *  @returns list of universities
 * */
loc *splan_get_locs(void);

/** @brief request all semesters from StarPlanner
 *
 *  This function makes a HTTP-2.0 GET request to the StarPlanner API and
 *  converts the request result into a list of semester structs
 *
 *  @returns list of semesters
 * */
pu *splan_get_pus(void);

/** @brief request all faculties from StarPlanner
 *
 *  This function makes a HTTP-2.0 GET request to the StarPlanner API and
 *  converts the request result into a list of faculty structs
 *
 *  @param semester semester to filter for the faculties.
 *  @returns list of faculties
 * */
og *splan_get_ogs(const pu *semseter);

/** @brief request  modules from StarPlanner
 *
 *  This function makes a HTTP-2.0 GET request to the StarPlanner API and
 *  converts the request result into a list of module structs for the given filtering
 *
 *  @param faculty faculty to filter for the modules.
 *  @param semester semester to filter for the modules.
 *  @returns list of modules of the selected combinations.
 * */
pgsext *splan_get_pgsext(const og *faculty, const pu *semester);



/** @brief request all universities from StarPlanner
 *
 *  This function makes a HTTP-2.0 GET request to the StarPlanner API and
 *  converts the request result into a list of university structs
 *
 *  @returns string json object from the StarPlanner API
 * */
char *splan_get_locs_json(void);

/** @brief request all semesters from StarPlanner
 *
 *  This function makes a HTTP-2.0 GET request to the StarPlanner API and
 *  converts the request result into a list of semester structs
 *
 *  @returns string json object from the StarPlanner API
 * */
char *splan_get_pus_json(void);

//local

/** @brief convert JSON string contating universities into C-Struct list
 *
 *  @param data JSON-String from the StarPlanner API
 *  @return list of univiersity structs
 * */
loc *locs_parse_json(const char *data);

/** @brief convert JSON string contating semesters into C-Struct list
 *
 *  @param _data JSON-String from the StarPlanner API
 *  @return list of semester structs
 * */
pu *pus_parse_json(const char *_data);

/** @brief convert JSON string contating faculties into C-Struct list
 *
 *  @param _data JSON-String from the StarPlanner API
 *  @return list of faculty structs
 * */
og *ogs_parse_json(const char *_data);

/** @brief convert JSON string contating modules into C-Struct list
 *
 *  @param _data JSON-String from the StarPlanner API
 *  @return list of modules structs
 * */
pgsext *pgsext_parse_json(const char *_data);


/** @brief convert JSON string contating lectures into C-Struct list
 *
 *  @param _data JSON-String from the StarPlanner API
 *  @return list of lectures structs
 * */
lecture *lecture_parse(const cJSON *_data, size_t *size);

/** @brief convert iso8859_1 to utf8 string
 *
 *  @param iso  iso string to convert
 *  @return converted iso string
 * */
char *iso8859_1_to_utf_8(const char *iso);

#endif // !SPAPI_H
