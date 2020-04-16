//
// Created by zhangliujie on 2020/4/15.
//
#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"

int main(int argc, const char *argv[]){
    char text1[] = "{\n\"name\": \"Jack (\\\"Bee\\\") Nimble\", \n\"format\": {\"type\":       \"rect\", \n\"width\":      1920, \n\"height\":     1080, \n\"interlace\":  false,\"frame rate\": 24\n}\n}";
    printf("%s", text1);
}