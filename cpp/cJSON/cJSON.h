//
// Created by zhangliujie on 2020/4/15.
//

#ifndef CJSON_H
#define CJSON_H

#define cJSON_False 0
#define cJSON_True 1
#define cJSON_NULL 2
#define cJSON_Number 3
#define cJSON_String 4
#define cJSON_Array 5
#define cJSON_Object 6

#define cJSON_IsReference 256
#define cJSON_StringIsConst 512


typedef struct cJSON {
    struct cJSON *next, *prev;
    struct cJSON *child;

    int type;

    char *valuestring;
    int vauleint;
    double valuedouble;

    char *string;
} cJSON;

extern cJSON *cJSON_Parse(const char *value);

extern cJSON *cJSON_ParseWithOpts(const char *value, const char **return_parse_end, int require_null_terminated);

extern cJSON *cJSON_New_Item();

/* Delete a cJSON entity and all subentities. */
extern void cJSON_Delete(cJSON *c);


#endif //CJSON_H
