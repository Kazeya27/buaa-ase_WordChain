# 结对项目-最长英语单词链

> 作业要求传送门：[结对项目-最长英语单词链-CSDN社区](https://bbs.csdn.net/topics/613883108)

### 项目结构

```
WordListProject
├── bin                                       // 可执行文件以及动态链接库
│   ├── Wordlist.exe
│   ├── core.dll 
├── guibin                                    // gui可执行文件
│   ├── main.exe
├── guisrc                                    // gui源码
│   ├── main.py
│   ├── ....
├── src                                       // 计算核心源码
│   └── main.cpp
│   └── ...
├── test                                      // 单元测试源码及数据
│   └── CliTests
│   └── CoreTests
│   └── gtest.cpp
├── CMakeLists.txt                            // CMake配置文件
└── README.md
```

### 使用方法

可支持参数如[结对项目-最长英语单词链-CSDN社区](https://bbs.csdn.net/topics/613883108)中要求。

- cli使用方法

```bash
git clone git@github.com:Kazeya27/buaa-ase_WordChain.git
cd buaa-ase_WordChain/bin
Wordlist.exe -w -r -h s -j b testfile.txt
```

- gui使用方法

```bash
git clone git@github.com:Kazeya27/buaa-ase_WordChain.git
cd buaa-ase_WordChain/guibin
main.exe
```

