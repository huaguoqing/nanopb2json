# nanopb2json

#### 介绍
实现nanopb的c结构与json串的互相转换； 找遍github发现都是使用protobuf-c转json,显然在嵌入式系统上不合适。而nanopb没有保存变量名，即无法实现反射功能。

目前nanopb转json我只增加完成了反射表的定义，增加了保存变量名信息，还没有实现与json的互转逻辑。
不过，我将cson(https://gitee.com/sunchb/cson)放在这个工程下，以便能使用json库和利用它的json互转能力，目前cson可以对接cJSON和jassion两种库。
我对cson也作了改进，支持了通过注解方式生成反射表。这样在内存非常有限的嵌入设备上， 可以不使用nanopb转json,而是直接使用cson的json与c结构的转换能力。

我建议在内存非常吃紧的系统中，使用cson来与json配置文件互转。
只有内存较多时，再打开nanopb的反射表功能，使用nanopb转json.毕竟所有message都保存反射信息，会增加固件体积和内存的开销。

#### 软件架构
软件架构说明


#### 安装教程

1.  xxxx
2.  xxxx
3.  xxxx

#### 使用说明

1.  xxxx
2.  xxxx
3.  xxxx

#### 参与贡献

1.  Fork 本仓库
2.  新建 Feat_xxx 分支
3.  提交代码
4.  新建 Pull Request


#### 特技

1.  使用 Readme\_XXX.md 来支持不同的语言，例如 Readme\_en.md, Readme\_zh.md
2.  Gitee 官方博客 [blog.gitee.com](https://blog.gitee.com)
3.  你可以 [https://gitee.com/explore](https://gitee.com/explore) 这个地址来了解 Gitee 上的优秀开源项目
4.  [GVP](https://gitee.com/gvp) 全称是 Gitee 最有价值开源项目，是综合评定出的优秀开源项目
5.  Gitee 官方提供的使用手册 [https://gitee.com/help](https://gitee.com/help)
6.  Gitee 封面人物是一档用来展示 Gitee 会员风采的栏目 [https://gitee.com/gitee-stars/](https://gitee.com/gitee-stars/)
