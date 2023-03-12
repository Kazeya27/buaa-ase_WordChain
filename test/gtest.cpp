//
// Created by Kazeya on 2023/3/11.
//
#include "gtest/gtest.h"
#include "../src/core.h"
#include <string>
#include <fstream>
#include <iostream>
#include <unordered_set>

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
    string fileName = "../test/testfiles/testfile" + to_string(index) + ".txt";
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

TEST(TestCase,AllNorm){
    char* result[2002];
    char* words[2002];
    int rtn;
    answer_test(1, words, result, &rtn);
    unique_test(result,rtn);
}

TEST(TestCase,AllEmpty){
    char* result[2002];
    char* words[2002];
    int rtn;
    answer_test(2, words, result, &rtn);
    unique_test(result,rtn);
}

TEST(TestCase,WordNorm){
    char* result[2002];
    char* words[2002];
    int rtn;
    answer_test(3, words, result, &rtn);
    unique_test(result,rtn);
}

TEST(TestCase,WordEmpty){
    char* result[2002];
    char* words[2002];
    int rtn;
    answer_test(4, words, result, &rtn);
    unique_test(result,rtn);
}

TEST(TestCase,WordHead){
    char* result[2002];
    char* words[2002];
    int rtn;
    answer_test(5, words, result, &rtn);
    unique_test(result,rtn);
}

TEST(TestCase,WordTail){
    char* result[2002];
    char* words[2002];
    int rtn;
    answer_test(6, words, result, &rtn);
    unique_test(result,rtn);
}

TEST(TestCase,WordBan){
    char* result[2002];
    char* words[2002];
    int rtn;
    answer_test(7, words, result, &rtn);
    unique_test(result,rtn);
}

TEST(TestCase,LetterNorm){
    char* result[2002];
    char* words[2002];
    int rtn;
    answer_test(8, words, result, &rtn);
    unique_test(result,rtn);
}

TEST(TestCase,LetterHead){
    char* result[2002];
    char* words[2002];
    int rtn;
    answer_test(9, words, result, &rtn);
    unique_test(result,rtn);
}

TEST(TestCase,LetterTail){
    char* result[2002];
    char* words[2002];
    int rtn;
    answer_test(10, words, result, &rtn);
    unique_test(result,rtn);
}

TEST(TestCase,LetterBan){
    char* result[2002];
    char* words[2002];
    int rtn;
    answer_test(11, words, result, &rtn);
    unique_test(result,rtn);
}

TEST(TestCase,WordNormR){
    char* result[2002];
    char* words[2002];
    int rtn;
    answer_test(12, words, result, &rtn);
    unique_test(result,rtn);
}

TEST(TestCase,WordHeadR){
    char* result[2002];
    char* words[2002];
    int rtn;
    answer_test(14, words, result, &rtn);
    unique_test(result,rtn);
}

TEST(TestCase,WordTailR){
    char* result[2002];
    char* words[2002];
    int rtn;
    answer_test(15, words, result, &rtn);
    unique_test(result,rtn);
}

TEST(TestCase,WordBanR){
    char* result[2002];
    char* words[2002];
    int rtn;
    answer_test(16, words, result, &rtn);
    unique_test(result,rtn);
}

TEST(TestCase,LetterNormR){
    char* result[2002];
    char* words[2002];
    int rtn;
    answer_test(17, words, result, &rtn);
    unique_test(result,rtn);
}

TEST(TestCase,LetterHeadR){
    char* result[2002];
    char* words[2002];
    int rtn;
    answer_test(19, words, result, &rtn);
    unique_test(result,rtn);
}

TEST(TestCase,LetterTailR){
    char* result[2002];
    char* words[2002];
    int rtn;
    answer_test(20, words, result, &rtn);
    unique_test(result,rtn);
}

TEST(TestCase,LetterBanR){
    char* result[2002];
    char* words[2002];
    int rtn;
    answer_test(21, words, result, &rtn);
    unique_test(result,rtn);
}

TEST(TestCase,ALLNormCircle){
    char* result[2002];
    char* words[2002];
    int rtn;
    answer_test(22, words, result, &rtn);
    unique_test(result,rtn);
}

TEST(TestCase,WordNormCircle){
    char* result[2002];
    char* words[2002];
    int rtn;
    answer_test(23, words, result, &rtn);
    unique_test(result,rtn);
}

TEST(TestCase,LetterNormCircle){
    char* result[2002];
    char* words[2002];
    int rtn;
    answer_test(24, words, result, &rtn);
    unique_test(result,rtn);
}

//TEST(TestCase,LetterEmptyR){
//    char* result[2002];
//    char* words[2002];
//    int rtn;
//    answer_test(18, words, result, &rtn);
//    unique_test(result,rtn);
//}
//
//TEST(TestCase,WordEmptyR){
//    char* result[2002];
//    char* words[2002];
//    int rtn;
//    answer_test(13, words, result, &rtn);
//    unique_test(result,rtn);
//}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();  // //RUN_ALL_TESTS()运行所有测试案例
}