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
    int valueint;
    double valuedouble;

    char *string;
} cJSON;

/*
 * C语言中，利用extern，
 *    1. 可以在一个文件中引用另一个文件定义的变量和函数
 *    2. 该行只是声明，并没有分配内存
 *    3. 场景：一个c文件需要调用另一个c文件中的变量和函数
 * 参考：
 *   1. https://blog.csdn.net/xingjiarong/article/details/47656339
 *   2. http://www.uml.org.cn/c%2B%2B/201908011.asp
 */
extern cJSON *cJSON_Parse(const char *value);

extern cJSON *cJSON_ParseWithOpts(const char *value, const char **return_parse_end, int require_null_terminated);

extern cJSON *cJSON_New_Item();

/* Delete a cJSON entity and all subentities. */
extern void cJSON_Delete(cJSON *c);

extern const char *cJSON_GetErrorPtr(void);

extern char *cJSON_Print(cJSON *item);


#endif //CJSON_H
