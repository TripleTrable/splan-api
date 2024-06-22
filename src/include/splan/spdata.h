/*! @file spdata.h
 *  @brief Header file for the starplanner handling
 *
 *  This file contains the data structures which are used
 *  to interact and parse the Starplanner output
 */

#ifndef SPDATA_H
#define SPDATA_H

#include <stdint.h>
#include <stdlib.h>

/**
 *  @brief Struct contains configuration to pass into the context of microhttpd callback handlder
 * */
typedef struct {
    char *server_api_endpoint;
} server_user_config;

extern server_user_config _server_config; /*!< Global struct to pass the configuration into the context of the callback handler from microhttpd*/

/** @brief struct containing a university
 * */
typedef struct {
    uint64_t id; /*!< id of the university JSON object */
    char *shortname; /*!< shortname of the university JSON object */
    char *name; /*!< name of the university JSON object */
} loc;

/** @brief free the university struct
 * @param data struct to free
 * */
void loc_free(loc *data);

/** @brief free list of university struct
 * @param data list of structs to free
 * @param size number of struct in data
 * */
void loc_free_all(loc *data, size_t size);

/** @brief struct containing a semester
 * */
typedef struct {
    uint64_t id; /*!< id of the semester JSON object */
    char *shortname; /*!< shortname of the semester JSON object */
    char *name; /*!< name of the semester JSON object */
    char *startdate;   /*!< startdata of the semester JSON object */ // potential change to sruct tm
    char *enddate;  /*!< enddate of the semester JSON object */ // potential change to sruct tm
    uint8_t dateasdefault; /*!< dateasdefault of the semester JSON object */
    loc *defaultloc; /*!< defaultloc of the semester JSON object */
    uint8_t visibleonweb; /*!< visibleonweb of the semester JSON object */
} pu;

/** @brief free the semester struct
 * @param data struct to free
 * */
void pu_free(pu *data);

/** @brief free list of semester struct
 * @param data list of structs to free
 * @param size number of struct in data
 * */
void pu_free_all(pu *data, size_t size);


/** @brief struct containing a faculty
 * */
typedef struct {
    uint64_t id; /*!< id of the university JSON object */
    char *shortname; /*!< shortname of the university JSON object */
    char *name; /*!< name of the university JSON object */
} og;

/** @brief free the faculty struct
 * @param data struct to free
 * */
void og_free(og *data);

/** @brief free list of faculty struct
 * @param data list of structs to free
 * @param size number of struct in data
 * */
void og_free_all(og *data, size_t size);


/** @brief struct containing a lecture
 * */
typedef struct {
    uint64_t id; /*!< id of the lecture JSON object */
    char *shortname; /*!< shortname of the lecture JSON object */
    char *name; /*!< name of the lecture JSON object */
    uint64_t pgid; /*!< pgid of the lecture JSON object */
} lecture;

/** @brief free the lecture struct
 * @param data struct to free
 * */
void lecture_free(lecture *data);

/** @brief free list of lecture struct
 * @param data list of structs to free
 * @param size number of struct in data
 * */
void lecture_free_all(lecture *data, size_t size);

/** @brief struct containing a module
 * */
typedef struct {
    uint64_t id; /*!< id of the module JSON object */
    char *shortname; /*!< shortname of the module JSON object */
    char *name; /*!< name of the module JSON object */
    lecture *lectures; /*!< lecture of the module JSON object */
    size_t lecture_count; /*!< lecture_count of the module JSON object */
} pgsext;

/** @brief free the module struct
 * @param data struct to free
 * */
void pgsext_free(pgsext *data);

/** @brief free list of module struct
 * @param data list of structs to free
 * @param size number of struct in data
 * */
void pgsext_free_all(pgsext *data, size_t size);

/**
 * Initializes the config and Splan API related structs.
 * @param   config struct containing SPlan server data.
 *          This struct is copied inside splan_init.
 * @return  0 on success. -1 on failure and errno is set.
 */
int splan_init(server_user_config *config);

#endif // !SPDATA_H
