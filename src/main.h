//
// Created by Kazeya on 2023/3/9.
//
#ifndef BUAA_ASE_WORDLIST_MAIN_H
#define BUAA_ASE_WORDLIST_MAIN_H
const int PARAM_CONFLICT =  -1; // 参数不兼容
const int PARAM_LACK =      -2; // 单独出现-h -t -j -r
const int WORD_CIRCLE =     -3; // 存在单词环
const int PARAM_FORMAT =    -4; // 指定-h -t -j时，没有给定字母(缺失或给的是数字、符号)
const int PARAM_UNDEFINED = -5; // 参数未定义
const int FILE_TYPE_WRONG = -6; // 文件非.txt
const int FILE_NOT_EXIST =  -7; // 文件不存在
const int FILE_DUPLICATE =  -8; // 重复选择文件
const int FILE_NOT_GIVEN =  -9; // 未选择文件
const int PARAM_DUPLICATE = -10; // 重复指定-h -t -j
const int RESULT_TOO_LONG = -11;

int test_main(int argc,char*argv[]);

#endif //BUAA_ASE_WORDLIST_ERRORS_H
