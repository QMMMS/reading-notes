# Spring 基本原理

Spring 是一款主流的 Java EE 轻量级开源框架 。

广义上的 Spring 泛指以 Spring Framework 为核心的 Spring 技术栈。例如 Spring Framework、Spring MVC、SpringBoot、Spring Cloud、 Spring Data、Spring Security 等，其中 Spring Framework 是其他子项目的基础。

Spring 有两个最核心模块，其中 IoC 是Inverse of Control 的简写，译为“控制反转”，指把创建对象过程交给 Spring 进行管理。 

另外一个最核心模块是 AOP，Aspect Oriented Programming 的简写，译为“面向切面编程”。AOP 用来封装多个类的公共行 为，将那些与业务无关，却为业务模块所共同调用的逻辑封装起来，减少系统的重复代码，降低模块间 的耦合度。另外，AOP 还解决一些系统层面上的问题，比如日志、事务、权限等。

Spring Framework特点：

- 非侵入式：使用 Spring Framework 开发应用程序时，Spring 对应用程序本身的结构影响非常小。 对领域模型可以做到零污染；对功能性组件也只需要使用几个简单的注解进行标记，完全不会破坏 原有结构，反而能将组件结构进一步简化。这就使得基于 Spring Framework 开发应用程序时结构 清晰、简洁优雅。 
- 控制反转：IoC，翻转资源获取方向。把自己创建资源、向环境索取资源 变成环境将资源准备好，我们享受资源注入。 
- 面向切面编程：AOP，在不修改源代码的基础上增强代码功能。 
- 容器：Spring IoC 是一个容器，因为它包含并且管理组件对象的生命周期。组件享受到了容器化的 管理，替程序员屏蔽了组件创建过程中的大量细节，极大的降低了使用门槛，大幅度提高了开发效 率。
-  组件化：Spring 实现了使用简单的组件配置组合成一个复杂的应用。在 Spring 中可以使用 XML 和 Java 注解组合这些对象。这使得我们可以基于一个个功能明确、边界清晰的组件有条不紊的搭建超 大型复杂应用系统。 
- 一站式：在 IoC 和 AOP 的基础上可以整合各种企业应用的开源框架和优秀的第三方类库。而且 Spring 旗下的项目已经覆盖了广泛领域，很多方面的功能性需求可以在 Spring Framework 的基础 上全部使用 Spring 来实现。

## 基础使用

假设已经使用Maven注入好依赖，我们有一个类

```java
package com.atguigu.spring6.bean;
public class HelloWorld {
    public void sayHello(){
    	System.out.println("helloworld");
    }
}
```

在resources目录创建一个 Spring 配置文件 beans.xml（配置文件名称可随意命名），配置HelloWorld所对应的bean，即将HelloWorld的对象交给Spring的IOC容器管理 通过bean标签配置IOC容器所管理的bean

```xml
<bean id="helloWorld" class="com.atguigu.spring6.bean.HelloWorld"></bean>
```

