//
// Created by Kazeya on 2023/3/11.
//
#include "gtest/gtest.h"
#include "../src/core.h"
#include <string>
#include <fstream>
#include <iostream>
#include <unordered_set>
#include "main.h"

using namespace std;


void chain_test(char*result[], int len) {
    for (int i = 0;i<len-1;i++) {
        int len1 = strlen(result[i]);
        ASSERT_EQ(result[i][len1-1],result[i+1][0]);
    }
}

void chain_test_all(char*result[], int len) {
    for (int i = 0;i<len;i++) {
        char* s = result[i];
        int len1 = strlen(s);
        for (int j = 0;j<len1;j++) {
            for (int k = j+1;k<len1;k++) {
                if (s[k] == ' ') {
                    ASSERT_EQ(s[k-1],s[k+1]);
                    j = k + 1;
                    break;
                }
            }
        }
    }
}

void head_tail_ban_test(char*result[],char head,char tail,char banned,int len) {
    if (len > 0) {
        if (head != '\0')
            ASSERT_EQ(result[0][0],head);
        if (tail != '\0') {
            int str_len = strlen(result[len - 1]);
            ASSERT_EQ(result[len-1][str_len - 1],tail);
        }
        if (banned != '\0') {
            for (int i = 0;i<len;i++) {
                ASSERT_NE(result[i][0],banned);
            }
        }
    }
}

void answer_test(int index, char*words[], char*result[], int* rtn) {
    int model;
    char head = '\0',tail = '\0',banned = '\0';
    bool enable_loop = false;
    string fileName = "../test/CoreTests/testfile" + to_string(index) + ".txt";
    ifstream ifile;
    ifile.open(fileName,ios::in);
    if (!ifile.is_open()) {
        cout << fileName + " open file failed" << endl;
        return;
    }
    string line;
    vector<char*> buffer;
    while (getline(ifile, line))
    {
        if (!line.empty())
        {
            char* ptr = new char[line.length() + 1];
            strcpy_s(ptr, line.length() + 1, line.c_str());
            switch (ptr[0]) {
                case 'n':
                    model = 0;
                    break;
                case 'w':
                    model = 1;
                    break;
                case 'c':
                    model = 2;
                    break;
                case 'h':
                    head = ptr[2];
                    break;
                case 't':
                    tail = ptr[2];
                    break;
                case 'j':
                    banned = ptr[2];
                    break;
                case 'r':
                    enable_loop = true;
                    break;
            }
        }
        else
            break;
    }
    while (getline(ifile, line))
    {
        if (!line.empty())
        {
            char* ptr = new char[line.length() + 1];
            strcpy_s(ptr, line.length() + 1, line.c_str());
//            for (int i = 0; i < line.length(); i++)
//            {
//                ptr[i] += ('A' <= ptr[i] && ptr[i] <= 'Z') ? 'a' - 'A' : 0;
//            }
            buffer.push_back(ptr);
        }
    }
    int len = (int)buffer.size() - 1;
    for (int i = 0; i < len; i++)
    {
        words[i] = buffer[i];
    }
    int realRtn = stoi(buffer[len]);
    int tmp = -1;
//    cout << head << " " << tail << " " << banned << endl;
    switch (model) {
        case 0:
            tmp = gen_chains_all(words,len,result);
            break;
        case 1:
            tmp = gen_chain_word(words,len,result,head,tail,banned,enable_loop);
            break;
        case 2:
            tmp = gen_chain_char(words,len,result,head,tail,banned,enable_loop);
            break;
        default:
            break;
    }
    *rtn = tmp;
//    for (int i = 0;i<tmp;i++)
//        cout << result[i] << endl;
    ASSERT_EQ(tmp,realRtn);
    if (model == 0) {
        chain_test_all(result,*rtn);
    }
    else {
        chain_test(result,*rtn);
        head_tail_ban_test(result,head,tail,banned,*rtn);
    }
}

void unique_test(char*result[],int len) {
    unordered_set<string> unique;
    for (int i = 0;i<len;i++) {
        ASSERT_TRUE(unique.find(result[i]) == unique.end());
        unique.insert(result[i]);
    }
}

void cli_test(int index) {
    char* argv[15];
    int argc = 0;
    string fileName = "../test/CliTests/config" + to_string(index) + ".txt";
    ifstream ifile;
    ifile.open(fileName,ios::in);
    string line;
    getline(ifile,line);
    int realRtn = stoi(line);
    getline(ifile,line);
    char*path = new char[line.length() + 20];
    strcpy_s(path,18,"../test/CliTests/");
//    cout << path << endl;
    path = strcat(path,line.c_str());
//    cout << path << endl;
    argv[argc++] = (char*)"Wordlist.exe";
    while (getline(ifile, line))
    {
        if (!line.empty())
        {
            char* ptr = new char[line.length() + 1];
            strcpy_s(ptr, line.length() + 1, line.c_str());
            argv[argc++] = ptr;
        }
    }
    argv[argc++] = path;
//    cout << argc << endl;
//    for (int i = 0;i<argc;i++)
//        cout << argv[i] << endl;
    int rtn = test_main(argc,argv);
    delete []path;
    ASSERT_EQ(rtn, realRtn);
}
static char* result[20002];
static char* words[20002];
TEST(TestCase,AllNorm){

    int rtn;
    answer_test(1, words, result, &rtn);
    unique_test(result,rtn);
}

TEST(TestCase,AllEmpty){
    int rtn;
    answer_test(2, words, result, &rtn);
    unique_test(result,rtn);
}

TEST(TestCase,WordNorm){
    int rtn;
    answer_test(3, words, result, &rtn);
    unique_test(result,rtn);
}

TEST(TestCase,WordEmpty){
    int rtn;
    answer_test(4, words, result, &rtn);
    unique_test(result,rtn);
}

TEST(TestCase,WordHead){
    int rtn;
    answer_test(5, words, result, &rtn);
    unique_test(result,rtn);
}

TEST(TestCase,WordTail){
    int rtn;
    answer_test(6, words, result, &rtn);
    unique_test(result,rtn);
}

TEST(TestCase,WordBan){
    int rtn;
    answer_test(7, words, result, &rtn);
    unique_test(result,rtn);
}

TEST(TestCase,LetterNorm){
    int rtn;
    answer_test(8, words, result, &rtn);
    unique_test(result,rtn);
}

TEST(TestCase,LetterEmpty){
    int rtn;
    answer_test(25, words, result, &rtn);
    unique_test(result,rtn);
}

TEST(TestCase,LetterHead){
    int rtn;
    answer_test(9, words, result, &rtn);
    unique_test(result,rtn);
}

TEST(TestCase,LetterTail){
    int rtn;
    answer_test(10, words, result, &rtn);
    unique_test(result,rtn);
}

TEST(TestCase,LetterBan){
    int rtn;
    answer_test(11, words, result, &rtn);
    unique_test(result,rtn);
}

TEST(TestCase,WordNormR){
    int rtn;
    answer_test(12, words, result, &rtn);
    unique_test(result,rtn);
}

TEST(TestCase,WordHeadR){
    int rtn;
    answer_test(14, words, result, &rtn);
    unique_test(result,rtn);
}

TEST(TestCase,WordTailR){
    int rtn;
    answer_test(15, words, result, &rtn);
    unique_test(result,rtn);
}

TEST(TestCase,WordBanR){
    int rtn;
    answer_test(16, words, result, &rtn);
    unique_test(result,rtn);
}

TEST(TestCase,LetterNormR){
    int rtn;
    answer_test(17, words, result, &rtn);
    unique_test(result,rtn);
}

TEST(TestCase,LetterHeadR){
    int rtn;
    answer_test(19, words, result, &rtn);
    unique_test(result,rtn);
}

TEST(TestCase,LetterTailR){
    int rtn;
    answer_test(20, words, result, &rtn);
    unique_test(result,rtn);
}

TEST(TestCase,LetterBanR){
    int rtn;
    answer_test(21, words, result, &rtn);
    unique_test(result,rtn);
}

TEST(TestCase,ALLNormCircle){
    int rtn;
    answer_test(22, words, result, &rtn);
    unique_test(result,rtn);
}

TEST(TestCase,WordNormCircle){
    int rtn;
    answer_test(23, words, result, &rtn);
    unique_test(result,rtn);
}

TEST(TestCase,LetterNormCircle){
    int rtn;
    answer_test(24, words, result, &rtn);
    unique_test(result,rtn);
}

TEST(TestCase,LetterHeadCircle){
    int rtn;
    answer_test(27, words, result, &rtn);
    unique_test(result,rtn);
}

TEST(TestCase,Circle){
    int rtn;
    answer_test(26, words, result, &rtn);
    unique_test(result,rtn);
}

TEST(TestCase,LetterEmptyR){
    int rtn;
    answer_test(18, words, result, &rtn);
    unique_test(result,rtn);
}

TEST(TestCase,WordEmptyR){
    int rtn;
    answer_test(13, words, result, &rtn);
    unique_test(result,rtn);
}

TEST(TestCase,LetterSet){
    int rtn;
    answer_test(28, words, result, &rtn);
    unique_test(result,rtn);
}

TEST(TestCase,Circle2){
    int rtn;
    answer_test(29, words, result, &rtn);
    unique_test(result,rtn);
}

TEST(TestCase,Random1){
    int rtn;
    answer_test(30, words, result, &rtn);
    unique_test(result,rtn);
}

TEST(TestCase,Random2){
    int rtn;
    answer_test(31, words, result, &rtn);
    unique_test(result,rtn);
}

TEST(TestCase,Random3){
    int rtn;
    answer_test(32, words, result, &rtn);
    unique_test(result,rtn);
}

TEST(TestCase,Random4){
    int rtn;
    answer_test(33, words, result, &rtn);
    unique_test(result,rtn);
}

TEST(TestCase,Random5){
    int rtn;
    answer_test(34, words, result, &rtn);
    unique_test(result,rtn);
}

TEST(TestCase,WordNormCli){
    cli_test(2);
}

TEST(TestCase,AllNormCli){
    cli_test(1);
}

TEST(TestCase,LetterNormCli){
    cli_test(3);
}

TEST(TestCase,BanNormCli){
    cli_test(12);
}

TEST(TestCase,ConflictA){
    cli_test(4);
}

TEST(TestCase,ConflictB){
    cli_test(5);
}

TEST(TestCase,ConflictC){
    cli_test(6);
}

TEST(TestCase,ConflictD){
    cli_test(10);
}

TEST(TestCase,ConflictE){
    cli_test(25);
}

TEST(TestCase,ConflictF){
    cli_test(26);
}

TEST(TestCase,ConflictG){
    cli_test(27);
}

TEST(TestCase,ConflictH){
    cli_test(28);
}

//TEST(TestCase,ConflictI){
//    cli_test(29);
//}

TEST(TestCase,ParamLackA){
    cli_test(7);
}

TEST(TestCase,ParamLackB){
    cli_test(8);
}

TEST(TestCase,ParamLackC){
    cli_test(9);
}

TEST(TestCase,ParamLackD){
    cli_test(11);
}

TEST(TestCase,AllCircle){
    cli_test(13);
}

TEST(TestCase,WordCircle){
    cli_test(14);
}

TEST(TestCase,LetterCircle){
    cli_test(15);
}


TEST(TestCase,HeadFormatError){
    cli_test(16);
}

TEST(TestCase,BanFormatError){
    cli_test(17);
}

TEST(TestCase,TailFormatError){
    cli_test(18);
}

TEST(TestCase,ParamUndefined){
    cli_test(19);
}

TEST(TestCase,FileType){
    cli_test(20);
}

TEST(TestCase,FileNotSelected){
    char* argv[15];
    int argc = 0;
    argv[argc++] = (char*)"Wordlist.exe";
    argv[argc++] = (char*)"-w";
    argv[argc++] = (char*)"-h";
    argv[argc++] = (char*)"a";
    ASSERT_EQ(test_main(argc,argv), -9);
}

TEST(TestCase,FileNotExist){
    cli_test(21);
}

TEST(TestCase,ParamDuplicateH){
    cli_test(22);
}

TEST(TestCase,ParamDuplicateT){
    cli_test(23);
}

TEST(TestCase,ParamDuplicateJ){
    cli_test(24);
}

TEST(TestCase,LongN){
    cli_test(30);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();  // //RUN_ALL_TESTS()运行所有测试案例
}