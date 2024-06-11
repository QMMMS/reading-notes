# 环境和介绍

java从5开始就是Java5，java6，java7，java8这样命名，java5之前都是java1，java1.2，java1.3，java1.4这样命名，我们口中说的Java8、JDK8、JDK1.8都是一个东西。

JDK：java development kit （java开发工具） 

JRE：java runtime environment （java运行时环境）

JVM：Java Virtual Machine （java虚拟机）

- Java 技术 = Java 语言 + Java 平台
- Java 平台 = JVM + JDK
- Java SE = JDK 根基
- Java EE，JavaSE，JavaFX 是 Java SE 的扩展

## JDK

开发环境（核心）

Java development kit的缩写，意思是Java开发工具，里面包含运行时环境（JRE）和其他 Java 开发所需的工具，比如说解释器（java）、编译器（javac）、文档生成器（javadoc）等等。

jdk主要包含三个部分：

1. Java运行时环境，JVM
2. Java的基础类库，这个类库的数量还是相当可观的
3. Java的开发工具，它们都是辅助你更好地使用Java的利器jre--运行环境

## JRE

运行环境，如果只想运行 Java 程序而不需要开发 Java 程序的话，只需要安装 JRE 就可以了。

jdk中包含的jre，在jre的bin目录里有个jvm.dll，既然JRE是运行时环境，那么运行在哪？肯定是JVM虚拟机上了。另，jre的lib目录中放的是一些JAVA类库的class文件，已经打包成jar文件。

## JVM

Java Virtual Machine （java虚拟机）的缩写。一次编译，随处运行的功臣。

Java的程序也就是我们编译的代码都会编译为class文件，class文件就是在jvm上运行的文件，只有JVM还不能完全支持class的执行，因为在解释class的时候JVM需要调用解释所需要的类库lib，而jre包含lib类库。

JVM屏蔽了与具体操作系统平台相关的信息，使得Java程序只需生成在Java虚拟机上运行的目标代码（字节码），就可以在多种平台上不加修改的运行。

![](./img/jdkre.jpg)

## 三大版本

**简单点说**
Java SE 是做电脑上运行的软件。
Java EE 是用来做网站的（我们常见的JSP技术）
Java ME 是做手机软件的。

> JSP的全称是Java Server Pages，即Java的服务器页面，JSP的主要作用是代替Servlet程序回传HTML页面的数据

- Java SE 全称（Java Platform，Standard Edition）以前称为 J2SE。它允许开发和部署在桌面、服务器、嵌入式环境和实时环境中使用的 Java 应用程序，包含了支持 Java Web 服务开发的类，为（Java EE）提供基础。
- Java EE 全称（Java Platform，Enterprise Edition）这个版本以前称为 J2EE。企业版帮助开发和部署可移植、健壮、可伸缩且安全的服务器端 Java 应用程序。Java EE 是在 Java SE 的基础上构建的，它提供 Web 服务、组件模型、管理和通信 API，可以用来实现企业级的面向服务体系结构（service-oriented architecture，SOA）和 Web 2.0 应用程序。
- Java ME 全称（Java Platform，Micro Edition）这个版本以前称为 J2ME。为在移动设备和嵌入式设备（比如手机、PDA、电视机顶盒和打印机）上运行的应用程序提供一个健壮且灵活的环境。包括灵活的用户界面、健壮的安全模型、许多内置的网络协议以及对可以动态下载的连网和离线应用程序的丰富支持。基于 Java ME 规范的应用程序只需编写一次，就可以用于许多设备，而且可以利用每个设备的本机功能。

Java EE 是开发 WEB 应用的！例如网站，网页等，Java EE 包含Java SE，要想学好Java EE，除了Java SE 精通外，你还要学一些其他的框架以及知识，例如Spring、SpringMVC、MyBatis 等一些框架。Java 最厉害，用的最多的地方就是做 WEB 应用！当然 WEB 应用大体也可分为 前端开发 和 后端开发（服务器开发）两类！但是不管怎么样，Java SE 是基础，是必须要好好学的。

Java EE 相比于Java SE 来说，除了多出包（Package）以外，还多了若干 Java 容器，如 Tomcat、GlassFish、IBM WebSphere 等。

Java SE 是 Java EE 的基础所开发的东西也不一样，如果想找一份好的工作还是把 Java SE 学好学精可以找一个几千块的工作，如果把 Java EE 学精那么相信你的工资很快就会超过 20k。

> 补充：
>
> JavaFX是用于构建富互联网应用程序的Java库。 使用此库编写的应用程序可以跨多个平台一致运行。
>
> 使用JavaFX开发的应用程序可以在各种设备上运行，如台式计算机，手机，电视，平板电脑等。
> 要使用Java编程语言开发GUI应用程序，程序员依赖于诸如高级窗口工具包(AWT)和Swings之类的库。
>
> 在JavaFX出现之后，这些Java程序开发就可以有效地利用丰富的类库来开发GUI应用程序。

## 编译流程

在编写好Welcome.java之后，编译与运行的命令（包名为空）：

```sh
javac Welcome.java;  # 将源代码文件编译为 Welcome.class 字节码文件
java Welcome;  # 运行字节码
```

有包名的情况下：

```java
package com.example;

public class Main{
    public static void main(String[] args){
        System.out.println("Hello World");
    }
}
```

这个java文件放在 `/test/com/example` 文件夹下，需要在该文件夹下编译后，回到`/test`文件夹，运行：

```bash
java com.example.Main
```

