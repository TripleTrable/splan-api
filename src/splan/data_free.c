#include "splan/spdata.h"

void loc_free(loc *data)
{
    if (!data)
        return;

    free(data->shortname);
    free(data->name);
    free(data);
}

void loc_free_all(loc *data, size_t size)
{
    if (!data || size == 0)
        return;
    for (int i = 0; i < size; i++) {
        free(data[i].shortname);
        free(data[i].name);
    }
    free(data);
}

void pu_free(pu *data)
{
    if (!data)
        return;

    free(data->shortname);
    free(data->name);
    free(data->startdate);
    free(data->enddate);
    loc_free(data->defaultloc);
    free(data);
}

void pu_free_all(pu *data, size_t size)
{
    if (!data || size == 0)
        return;
    for (int i = 0; i < size; i++) {
        free(data[i].shortname);
        free(data[i].name);
        free(data[i].startdate);
        free(data[i].enddate);
        loc_free(data[i].defaultloc);
    }
    free(data);
}

void og_free(og *data)
{
    if (!data)
        return;

    free(data->shortname);
    free(data->name);
    free(data);
}

void og_free_all(og *data, size_t size)
{
    if (!data || size == 0)
        return;
    for (int i = 0; i < size; i++) {
        free(data[i].shortname);
        free(data[i].name);
    }
    free(data);
}
