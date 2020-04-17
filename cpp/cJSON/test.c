//
// Created by zhangliujie on 2020/4/15.
//
#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"


void doit(const char *text) {
    char *out;
    cJSON *json;
    json = cJSON_Parse(text);
    if (!json) {
        printf("Error before: [%s]\n", cJSON_GetErrorPtr());
    } else {
        out = cJSON_Print(json);
        /*
         * json是通过cJSON_New_Item创建的，
         * 打印结束后，需调用此接口释放。
         * TODO: 如果不显式地释放会有什么后果呢？
         */
        cJSON_Delete(json);
        printf("%s\n", out);
        /*
         * 此处如果不显式地释放，会有什么后果呢？
         */
        free(out);
    }
}

int main(int argc, const char *argv[]) {
    char text1[] = "{\n\"name\": \"Jack (\\\"Bee\\\") Nimble\", \n\"format\": {\"type\":       \"rect\", \n\"width\":      1920, \n\"height\":     1080, \n\"interlace\":  false,\"frame rate\": 24\n}\n}";
    doit(text1);
}