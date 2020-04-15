//
// Created by zhangliujie on 2020/4/15.
//

#include <string>
#include <cstdio>
#include <cmath>
#include <cfloat>
#include <cctype>
#include <climits>
#include "cJSON.h"

/*
 * 静态变量可以声明于function中， 其lifetime从第一次调用此函数开始，一直到program结束；
 * 静态变量只执行一次初始化，并保存在heap中，发生修改就保存。
 *
 * 当为类的成员变量时，必须在类外初始化，不能在类内初始化
 */

static const char *ep;

/* Parse the input text into an unescaped cstring, and populate item. */
static const unsigned char firstByteMask[7] = {0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC};

/* malloc和new的区别:
 * 1. new可以自动计算申请内存的大小, malloc需指定size; 如 int *p = new int[10]
 * 2. new返回指定类型的指针, malloc返回void*
 * 3. malloc只管分配内存，不负责初始化，其内存中的值是随机的
 *
 * malloc()其实就是在内存中找到一片指定大小的空间, 然后将空间的首地址返回给一个指针变量,
 * 这里的指针变量可以是一个单独的指针，也可以是一个数组的首地址
*/

/*
 * 函数指针, 将malloc函数绑定到了cJSON_malloc
 * 高阶用法:
 * void func(int e, int d, int(*f)(int a, int b)){
 *  // 此处传入了一个int类型，双参数，返回值为int的函数
 *  std::cout << f(e, d) << std::endl;
 * }
 */
static void *(*cJSON_malloc)(size_t sz) = malloc;

/*
 * new/delete和malloc/free的区别：
 * 本质区别：
 *  1. new/delete通常来说是操作符，类似"+"/"-"一样；(C++里才有的)
 *      - new是构造一个对象，并调用对象的构造函数初始化对象，分两步：①申请内存 ②调用构造函数
 *      - delete：①调用析构函数 ② 销毁heap内存
 *  2. malloc/free是C/C++语言的标准库函数
 *      - 调用malloc后需要显式进行类型转换
 *      - malloc不关心要为什么类型申请内存，只关心内存的总字节数
 *      - 如果p是空指针，对p执行多次free不会出问题；若p不是空指针，对p连续两次free会导致程序运行错误（悬浮指针和空指针区别）
 *
 *  二者的详细区别，参考：https://blog.csdn.net/u013630349/article/details/44947255
 */
static void (*cJSON_free)(void *ptr) = free;

// skip whitespace and cr/lf
static const char *skip(const char *in){
    while(in && *in && (unsigned char) *in <= 32) in ++;
    return in;
}

static const char* parse_string(cJSON *item, const char *str){
    // 忽略前面的"
    const char *ptr = str + 1;
    char *ptr2;
    char *out;
    int len = 0;
    // 等价于unsigned int，int是隐含的
    unsigned uc, uc2;
    if(*str != '\"'){
        ep = str;
        return nullptr; // not a string
    }
    while(*ptr != '\"' && *ptr && ++len){
        if(*ptr++ == '\\') ptr ++; // skip escaped quota
    }

    out = (char *) cJSON_malloc(len+1);
    if(!out) return nullptr;

    ptr = str + 1;
    ptr2 = out;
    while(*ptr != '\"' && *ptr) {
        if(*ptr != '\\') *ptr2++ = *ptr++;
        else{
            ptr++;
            switch(*ptr){
                case 'b':
                    *ptr2++ = '\b';
                    break;
                case 'f':
                    *ptr2++ = '\f';
                    break;
                case 'n':
                    *ptr2++ = '\n';
                    break;
                case 'r':
                    *ptr2++ = '\r';
                    break;
                case 't':
                    *ptr2++ = '\t';
                    break;
                case 'u':
                    // TODO: to utf-8
                    uc = parse_hex4(ptr+1);
                    ptr+= 4;
                    // check for valid
                    if((uc >=0xDC00 && uc <= 0xDFFF) || uc ==0) break;
                    if((uc >=0xD800 && uc <= 0xDBFF)){
                        /* missing second-half of surrogate.	*/
                        if (ptr[1] != '\\' || ptr[2] !='u') break;
                        uc2 = parse_hex4(ptr+3);
                        ptr+=6;
                        if(uc >=0xDC00 && uc <= 0xDFFF) break;
                        uc = 0x10000 + (((uc &0x3FF)<<10) | (uc2 & 0x3FF));
                    }
                    len = 4;
                    if(uc < 0x80) len = 1;
                    else if(uc < 0x800) len = 2;
                    else if(uc < 0x10000) len = 3;

                    ptr += len;

                    switch(len){
                        case 4:
                            *--ptr2 = ((uc | 0x80) & 0xBF);
                            uc >>=6;
                        case 3:
                            *--ptr2 = ((uc | 0x80) & 0xBF);
                            uc >> 6;
                        case 2:
                            *--ptr2 = ((uc | 0x80) & 0xBF);
                            uc >> 6;
                        case 1:
                            *--ptr2 = (uc | fisrtByteMark[len]);
                    }
                    ptr2 += len;
                    break;
                default:
                    *ptr2++ = *ptr;
                    break;
            }
            ptr++;
        }
    }
    *ptr2 = 0;
    if(*ptr == '\"') ptr ++;
    item->valuestring = out;
    item->type = cJSON_String;
    return ptr;
}

static const char *parse_value(cJSON *item, const char *value){
    if(!value)  return nullptr;
    /* 若前n个字符相同，则返回0
     * C++中 单引号是字符型(实际代表一个整数)，双引号是字符串型(指向吴明数组起始字符的指针)
     * 'a' 表示一个字符，"a"相当于'a' + '\0'
     */
    if(!strncmp(value, "null", 4)){
        item->type = cJSON_NULL;
        return value + 4;
    }

    if(!strncmp(value, "false", 5)){
        item->type = cJSON_False;
        return value + 5;
    }

    if(!strncmp(value, "true", 4)){
        item->type = cJSON_True;
        item->vauleint = 1;
        return value + 4;
    }
    // TODO: add parse function
    if(*value == '\"') {return parse_string(item, value);}
    if(*value == '-' || (*value >= '0' && *value <= '9')) {return parse_number(item, value);}
    if(*value == '[') {return parse_array(item, value);}
    if(*value == '{') {return parse_object(item, value);}

    ep = value;
    return nullptr; //fail
}

cJSON *cJSON_Parse(const char *value){
    return cJSON_ParseWithOpts(value, nullptr, 0);
}

void cJSON_Delete(cJSON *c){
    cJSON *next;
    while(c){
        next = c->next;
        if(!(c->type && cJSON_IsReference) && c->child) cJSON_Delete(c->child);
        if(!(c->type && cJSON_IsReference) && c->valuestring) cJSON_free(c->valuestring);
        if(!(c->type && cJSON_StringIsConst) && c->string) cJSON_free(c->string);
        cJSON_free(c);
        c = next;
    }
}

cJSON *cJSON_ParseWithOpts(const char *value, const char **return_parse_end, int require_null_terminated) {
    const char *end = nullptr;
    cJSON *c = cJSON_New_Item();
    ep = nullptr;
    if(!c) return nullptr;  // memory fail

    // return pointer pointing the end of char* value
    end = parse_value(c, skip(value));

    if(!end){
        // TODO: add defination
        cJSON_Delete(c);
        return nullptr; // parse failure, ep is set
    }

    if(require_null_terminated){
        end = skip(end);
        if(*end){
            cJSON_Delete(c);
            ep = end;
            return nullptr;
        }
    }
    if(return_parse_end) *return_parse_end = end;
    return c;
}


cJSON *cJSON_New_Item(){
    // 通过函数指针，实际调用的是malloc(sizeof(cJSON))
    cJSON *node = (cJSON *) cJSON_malloc(sizeof(cJSON));
    // 结构体常见的初始化方式
    if(node) memset(node, 0, sizeof(cJSON));
    return node;
}



