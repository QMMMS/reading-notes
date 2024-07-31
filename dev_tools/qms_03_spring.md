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

假设已经使用Maven注入好依赖，我们有一个类`com.atguigu.spring6.User`

![](./img/springstr.png)

在resources目录创建一个 Spring 配置文件 beans.xml（配置文件名称可随意命名），配置HelloWorld所对应的bean，即将HelloWorld的对象交给Spring的IOC容器管理 通过bean标签配置IOC容器所管理的bean

> 我们将由 IoC 容器管理的 Java 对象称为 Spring Bean，不过它与使用关键字 new 创建的 Java 对象没有任何区别。

```xml
 <bean id="user" class="com.atguigu.spring6.User"></bean>
```

我们不再使用传统的 new 对象，而是：

```java
ApplicationContext ac = new ClassPathXmlApplicationContext("beans.xml");
User user = (User) ac.getBean("user");
```

## 基本分析

上面的示例代码中，调用了无参数构造方法。可以看作是反射的一种实现方式。

> 传统的反射代码：
>
> ```java
> // 通过反射机制调用无参数构造方法创建对象
> Class clazz = Class.forName("com.atguigu.spring6.User");
> //Object obj = clazz.newInstance();
> Object object = clazz.getDeclaredConstructor().newInstance();
> ```

创建好的bean对象最终存储在spring容器中，在spring源码底层就是一个map集合，存储bean的map在**DefaultListableBeanFactory**类中：

```java
private final Map<String, BeanDefinition> beanDefinitionMap = new ConcurrentHashMap<>(256);
```

Spring容器加载到Bean类时 , 会把这个类的描述信息, 以包名加类名的方式存到beanDefinitionMap 中 , 其中 String是Key , 默认是类名首字母小写 , BeanDefinition是类的定义(描述信息) , 我们通常叫BeanDefinition接口为 bean的定义对象。

还有一个问题，上面的代码中，`ApplicationContext`是什么？在创建 bean 之前，首先需要创建IoC 容器。Spring 提供了IoC 容器的两种实现方式：

- BeanFactory：是 IoC 容器的基本实现，是 Spring 内部使用的接口。面向 Spring 本身，不提供给开发人员使用。
- ApplicationContext：BeanFactory 的子接口，提供了更多高级特性。面向 Spring 的使用者，几乎所有场合都使用 ApplicationContext 而不是底层的 BeanFactory。主要实现类包括：

| 类型名                          | 简介                                                         |
| ------------------------------- | ------------------------------------------------------------ |
| ClassPathXmlApplicationContext  | 通过读取类路径下的 XML 格式的配置文件创建 IOC 容器对象       |
| FileSystemXmlApplicationContext | 通过文件系统路径读取 XML 格式的配置文件创建 IOC 容器对象     |
| ConfigurableApplicationContext  | ApplicationContext 的子接口，包含一些扩展方法 refresh() 和 close() ，让 ApplicationContext 具有启动、关闭和刷新上下文的能力。 |
| WebApplicationContext           | 专门为 Web 应用准备，基于 Web 环境创建 IOC 容器对象，并将对象引入存入 ServletContext 域中。 |

## 容器：IoC

IoC 容器是 Spring 框架中最重要的核心组件之一，Spring 通过 IoC 容器来管理所有 Java 对象的实例化和初始化，控制对象与对象之间的依赖关系。

控制反转（IoC）是一种思想。是为了降低程序耦合度，提高程序扩展力。

反转的是什么？

- 将对象的创建权利交出去，交给第三方容器负责。
- 将对象和对象之间关系的维护权交出去，交给第三方容器负责。

IOC 就是一种控制反转的思想， 而 DI（Dependency Injection）依赖注入是对IoC的一种具体实现。

依赖注入指Spring创建对象的过程中，将对象依赖属性通过配置进行注入，依赖注入常见的实现方式包括两种：set注入和构造注入

## bean生命周期

- bean对象创建（调用无参构造器）

- 给bean对象设置属性（注入）

- bean的后置处理器（初始化之前）

- bean对象初始化（需在配置bean时指定初始化方法）

- bean的后置处理器（初始化之后）

- bean对象就绪可以使用

- bean对象销毁（需在配置bean时指定销毁方法）

- IOC容器关闭

注意创建对象的时机，配置bean标签的scope属性来指定，各取值含义参加下表：

| 取值              | 含义                                    | 创建对象的时机  |
| ----------------- | --------------------------------------- | --------------- |
| singleton（默认） | 在IOC容器中，这个bean的对象始终为单实例 | IOC容器初始化时 |
| prototype         | 这个bean在IOC容器中有多个实例           | 获取bean时      |

## 自动装配

即根据指定的策略，在IOC容器中匹配某一个bean，自动为指定的bean中所依赖的类类型或接口类型属性赋值

例子展示：一般开发中调用关系如下：

![](./img/auto1.png)

如果不使用spring，那么常规方法就是在 controller 中先 new 一个 service，同理 service 中也要 new 一个 dao，再调用相关方法。

![](./img/auto2.png)

如果使用 spring 呢？例如 controller 代码可以这么写：

```java
package com.atguigu.spring6.autowire.controller
public class UserController {
    private UserService userService;
    public void setUserService(UserService userService) {
        this.userService = userService;
    }
    public void saveUser(){
        userService.saveUser();  // 调用 service 中相关方法
    }
}
```

配置bean的`autowire-xml.xml`如下：

```xml
<bean id="userController" class="com.atguigu.spring6.autowire.controller.UserController" autowire="byType"></bean>

<bean id="userService" class="com.atguigu.spring6.autowire.service.impl.UserServiceImpl" autowire="byType"></bean>

<bean id="userDao" class="com.atguigu.spring6.autowire.dao.impl.UserDaoImpl"></bean>
```

可以实现根据类型自动匹配和赋值：

```java
ApplicationContext ac = new ClassPathXmlApplicationContext("autowire-xml.xml");
UserController userController = ac.getBean(UserController.class);
userController.saveUser();
```

## 基于注解管理Bean

我们可以使用注解来实现自动装配，简化 Spring 的 XML 配置。在开发中更常用。

> 复习一下，注解（Annotation）是代码中的一种特殊标记，可以在编译、类加载和运行时被读取，执行相应的处理。开发人员可以通过注解在不改变原有代码和逻辑的情况下，在源代码中嵌入补充信息。

简单来说，就是直接把注解可以标注在 Java 类上，将它们定义成 Spring Bean。

```java
@Component(value="user")  // 对应 xml 中的 id，默认是类名首字母小写
public class User{
}
```

| 注解        | 说明                                                         |
| ----------- | ------------------------------------------------------------ |
| @Component  | 该注解用于描述 Spring 中的 Bean，它是一个泛化的概念，仅仅表示容器中的一个组件（Bean），并且可以作用在应用的任何层次，例如 Service 层、Dao 层等。  使用时只需将该注解标注在相应类上即可。 |
| @Repository | 该注解用于将数据访问层（Dao 层）的类标识为 Spring 中的 Bean，其功能与 @Component 相同。 |
| @Service    | 该注解通常作用在业务层（Service 层），用于将业务层的类标识为 Spring 中的 Bean，其功能与 @Component 相同。 |
| @Controller | 该注解通常作用在控制层（如SpringMVC 的 Controller），用于将控制层的类标识为 Spring 中的 Bean，其功能与 @Component 相同。 |

那么如何注入？使用 Autowired，类似上面的自动装配一节，根据类型装配：

> 思考一下底层如何实现？当发现一个带有 `@Autowired` 注解的属性时，就使用反射机制为其赋值，赋什么值呢？当然是从 管理所有Bean 的`Map<String, BeanDefinition>`里面找名字或者类型符合的 Bean

```java
@Controller
public class UserController {
    @Autowired
    private UserService userService;

    public void out() {
        userService.out();  // 调用 service 相关方法
    }
}
```

但是这些注解在哪里被处理？我们需要让 Spring 扫描组件！具体来说，我们写一个配置类来代替 xml 配置文件

```java
package com.atguigu.spring6.config;
// import...
@Configuration  // 配置类
@ComponentScan("com.atguigu.spring6")  // 扫描包的路径
public class Spring6Config {
}
```

测试类不再读取 xml 文件，而是配置类：

```java
ApplicationContext context = new AnnotationConfigApplicationContext(Spring6Config.class);
UserController userController = context.getBean("userController", UserController.class);
userController.out();
```

## 面向切面（AOP）实例

假设我们实现了一个四则计算工具（业务代码），想加上日志功能（非业务代码），如何实现？

显然把业务代码和非业务代码混在一起不是一个明智的选择，我们可以使用**代理模式**：

![](./img/prox1.png)

> 二十三种设计模式中的一种，属于结构型模式。它的作用就是通过提供一个代理类，让我们在调用目标方法的时候，不再是直接对目标方法进行调用，而是通过代理类**间接**调用。让不属于目标方法核心逻辑的代码从目标方法中剥离出来——**解耦**。调用目标方法时先调用代理对象的方法，减少对目标方法的调用和打扰，同时让附加功能能够集中在一起也有利于统一维护。

Spring 使用了**动态代理**来实现AOP，还是那我们上面的例子来画图：

![](./img/dypro.png)

```java
// 测试类：
ProxyFactory factory = new ProxyFactory(new CalculatorLogImpl());
Calculator proxy = (Calculator) factory.getProxy();
proxy.div(1,0);

// 代理内部：
System.out.println("[动态代理][日志] "+method.getName()+"，参数："+ Arrays.toString(args));
result = method.invoke(target, args);  // 业务代码
System.out.println("[动态代理][日志] "+method.getName()+"，结果："+ result);
```

## AOP基本概念

AOP（Aspect Oriented Programming）是一种设计思想，是面向对象编程的一种补充和完善，它以通过预编译方式和运行期动态代理方式实现，在不修改源代码的情况下，给程序动态统一添加额外功能的一种技术。利用AOP可以对业务逻辑的各个部分进行隔离，从而使得业务逻辑各部分之间的耦合度降低，提高程序的可重用性，同时提高了开发的效率。

作用：

- 简化代码：把方法中固定位置的重复的代码**抽取**出来，让被抽取的方法更专注于自己的核心功能，提高内聚性。

- 代码增强：把特定的功能封装到切面类中，看哪里有需要，就往上套，被**套用**了切面逻辑的方法就被切面给增强了。

相关术语：

- 横切关注点：分散在每个各个模块中解决同一样的问题，如用户验证、日志管理、事务处理、数据缓存都属于横切关注点。
- 通知（增强）：通俗说，就是你想要增强的功能，比如 安全，事务，日志等。每一个横切关注点上要做的事情都需要写一个方法来实现，这样的方法就叫通知方法。
  - 前置通知：在被代理的目标方法**前**执行
  - 返回通知：在被代理的目标方法**成功结束**后执行（**寿终正寝**）
  - 异常通知：在被代理的目标方法**异常结束**后执行（**死于非命**）
  - 后置通知：在被代理的目标方法**最终结束**后执行（**盖棺定论**）
  - 环绕通知：使用try...catch...finally结构围绕**整个**被代理的目标方法，包括上面四种通知对应的所有位置
- 切面：封装通知方法的类。
- 连接点：把方法排成一排，每一个横切位置看成x轴方向，把方法从上到下执行的顺序看成y轴，x轴和y轴的交叉点就是连接点。**通俗说，就是spring允许你使用通知的地方**
- 切入点：定位连接点的方式。Spring 的 AOP 技术可以通过切入点定位到特定的连接点。通俗说，要实际去增强的方法。

![](./img/aop1.png)

![](./img/aop2.png)

## 基于注解的AOP

在添加好依赖和在 xml 文件中配置后，核心代码为：

```java
@Aspect  // 表示这个类是一个切面类
@Component  //保证这个切面类能够放入IOC容器
public class LogAspect {
    
    // 前置通知
    @Before("execution(public int com.atguigu.aop.annotation.CalculatorImpl.*(..))")
    public void beforeMethod(JoinPoint joinPoint){
        String methodName = joinPoint.getSignature().getName();
        String args = Arrays.toString(joinPoint.getArgs());
        System.out.println("Logger-->前置通知，方法名："+methodName+"，参数："+args);
    }
}
```

其中，切入点表达式语法为：

![](./img/aopg.png)

这样，在完全不用修改 `CalculatorImpl` 类的情况下，就可以通过切入点表达式语法找到连接点，增强功能。

## SpringBoot

Spring Boot是Spring提供的一个子项目，用于快速构建Spring应用程序。

传统方式构建spring应用程序比较繁琐

- 导入maven依赖繁琐
- 项目xml配置繁琐

SpringBoot特性包括

- 起步依赖：使用一个Maven坐标，整合了完成需要的所有Maven坐标

  ```
  <dependency>    
  	<groupId>org.springframework.boot</groupId>
  	<artifactId>spring-boot-starter-web</artifactId>
  </dependency>
  ```

- 自动配置：遵循约定大约配置的原则，在boot程序启动后，一些bean对象会自动注入到ioc容器，不需要手动声明，简化开发

- 其他特性：内嵌的Tomcat、Jetty（无需部署WAR文件）；外部化配置；不需要XML配置(properties/yml)

SpringBoot的启动流程：

> SpringBoot启动，其本质就是加载各种配置信息，然后初始化IOC容器，在run方法中会真正的实例化容器，并创建容器中需要的Bean实例，最终返回

在启动类执行SpringApplication.run这行代码的时候，在它的方法内部其实会做两个事情

```java
@SpringBootApplication
public class App {    
    public static void main(String[] args) {        
        ConfigurableApplicationContext context = SpringApplication.run(App.class, args);    
    }
}
```

1. 创建SpringApplication对象；
   - 确认web应用的类型，一般情况下是Servlet类型，这种类型的应用，将来会自动启动一个tomcat。
   - 从spring.factories配置文件中，加载默认的ApplicationContextInitializer和ApplicationListener
   - 记录当前应用的主启动类，将来做包扫描使用
2. 执行run方法。
   - 准备Environment对象，它里面会封装一些当前应用运行环境的参数，比如环境变量等等
   - 实例化容器，这里仅仅是创建ApplicationContext对象
   - 容器创建好了以后，会为容器做一些准备工作，比如为容器设置Environment、BeanFactoryPostProcessor后置处理器，并且加载主类对应的Definition
   - 刷新容器，就是我们常说的referesh，在这里会真正的创建Bean实例

IOC容器的初始化，核心工作是在AbstractApplicationContext.refresh方法中完成的

1. 准备BeanFactory，在这一块需要给BeanFacory设置很多属性，比如类加载器、Environment等
2.  执行BeanFactory后置处理器，这一阶段会扫描要放入到容器中的Bean信息，得到对应的BeanDefinition（注意，这里只扫描，不创建）
3. 是注册BeanPostProcesor，我们自定义的BeanPostProcessor就是在这一个阶段被加载的, 将来Bean对象实例化好后需要用到
4. 启动tomcat
5. 实例化容器中实例化非懒加载的单例Bean, 这里需要说的是，多例Bean和懒加载的Bean不会在这个阶段实例化，将来用到的时候再创建
6. 当容器初始化完毕后，再做一些扫尾工作，比如清除缓存等 
