# MySQL Cheat Sheet

## 基础命令

**登录**：`mysql -uroot -p[密码]`

**退出**：`exit`、`quit`

**查看数据库列表**：`show databases;`

**使用某个数据库**：`use [数据库名];`

**查看当前使用的数据库名**：`select database();`

**创建数据库**：`create database [数据库名];`

**删除数据库：**`drop database [数据库名];`

**查看数据库表名**：`show tables;`

**执行SQL脚本**：use 某个数据库时`source [不带中文的路径]`，Windows可能要用两个反斜杠

**查看表所有数据**：`select * from [表名];`

**查看表结构**：`desc [表名];`

**查看 MySQL 版本**：`select version();`

>   **Windows中打开服务**：`net start mysql80`
>
>   **Windows中关闭服务**：`net stop mysql80`
>
>   注意这两个命令是在cmd里面输入的，mysql80是安装MySQL在windows服务界面配置的服务名，默认mysql80
>
>   除了命令行，还可以通过Windows的`服务`手动打开和关闭

## 其他命令

- `SHOW STATUS;` 显示广泛服务器状态信息
- `SHOW GRANTS;` 显示授权用户的安全权限
- `SHOW ERRORS;`服务器错误信息
- `SHOW WARNINGS;`服务器警告信息
- `show engines \G`查看存储引擎
- `show create table [表名];`查看创建语句：

**导出数据（退出MySQL到命令行）：**

```bash
mysqldump [数据库名] > [路径] -uroot -p[密码];
```

**例子：**

```bash
mysqldump bj > ~/Desktop/bj.sql -uroot -p[密码]
```

```bash
mysqldump --single-transaction -u［用户名］ -p［密码］［数据库名］ >［导出文件名］.sql
```

--single-transaction选项： 该选项适用于 InnoDB 引擎的表，可以在导出时启动一个事务，从而避免锁表。使用该选项，mysqldump 会在导出过程中保持数据的一致性，而不需要锁定表，这样其他进程仍然可以对数据库进行读写操作

在目标服务器上，使用 mysql 客户端来导入数据库。首先需要创建数据库（如果它还不存在），然后导入

```bash
mysql -u username -p -e "CREATE DATABASE IF NOT EXISTS database_name"
mysql -u username -p database_name < database_dump.sql
```

## Select

### 简单查询

**查询多个字段**：`select [字段名],[字段名]... from [表名];`

**查询所有字段**：`select * from [表名];`

**列起别名**：

`select [字段名] as [别名] from [表名];`

`select [字段名] [别名] from [表名];`

`select [字段名] ‘[别名]’ from [表名];`（别名是中文或带空格的方案）

**字段可以带有数学表达式**，例如：`select ENAME, SAL*12 'YEAR SALE' from emp;`

### 条件查询

**格式**：

```sql
select
	[字段名1], [字段名2], [字段名3]...
from
	[表名]
where
	[条件];
```

**例子**：

```sql
 select empno, ename from emp where sal = 800;
 
 select ename, sal, deptno from emp where sal > 2000 and (deptno = 10 or deptno = 20);
 
 select ename, job from emp where job in ('manager', 'salesman');
 
 select ename from emp where ename like '%o%';
```

**条件**：

- 大小关系：`=, !=, <, >, <>`

- 两个值之间（包含）：`between [值1] and [值2]`

- 判断为空：`is null`和`is not null`

- 并且：`and`

- 或：`or` （and 优先级比 or 高，加括号改变优先级）

- 是否包含：`in ([值1], [值2]...)`和`not in ([值1], [值2]...)`

- 模糊查询：`like [值]`（% 代表 0 到任意多个字符， _ 代表任意一个字符，注意 \ 转义）

### 多情况讨论

**格式：**

```sql
select
	[字段名1], [字段名2], [字段名3]...
	
case [目标字段名]
    when
        [值1]
    then 
        [对应处理]
    when
        [值2]
    then 
        [对应处理]
    else
        [对应处理]
end

from
	[表名];
```

**例子：**

```sql
select ename, job, sal oldsal, (case job when 'manager' then sal * 1.1 when 'salesman' then sal * 1.3 else sal end) as newsal from emp;
```

### 子查询

**语法：**

在 `select`, `from`, `where` 子句中嵌套查询

**例子：**

```sql
select ename, sal 
from emp 
where sal > (
    select min(sal) 
    from emp
);
```

```sql
select t.job, t.avgsal, s.grade
from (select job, avg(sal) avgsal from emp group by job) t
join salgrade s
on t.avgsal between s.losal and s.hisal;
```

```sql
select e.ename, (select d.dname from dept d where e.deptno = d.deptno) dname from emp e;
```

### 正则表达式

```sql
SELECT prod_name
FROM products
WHERE prod_name REGEXP '\\([0-9] sticks?\\)';
```

```
+----------------+
| prod_name      |
+----------------+
| TNT (1 stick)  |
| TNT (5 sticks) |
+----------------+
```

- \\\\ 代表转义
- [0-9] 匹配 0～9 的任意一个字符
- ? 代表其前一个字符出现1次或0次

```sql
SELECT prod_name
FROM products
WHERE prod_name REGEXP '^[0-9\\.]';
```

```
+--------------+
| prod_name    |
+--------------+
| .5 ton anvil |
| 1 ton anvil  |
| 2 ton anvil  |
+--------------+
```

- 此处 ^ 代表匹配串的开始

### union 

**语法：**

```sql
[查询语句]
union
[查询语句]
```

*注：合理运用 union, 查询次数可以优于 join （例如多表连接）*

*注：要求结果的列数和数据类型相同*

**例子：**

```sql
select ename , job from emp where job = 'manager'
union
select ename , job from emp where job = 'salesman';
```

- UNION 自动去除重复的行，使用 UNION ALL 包含重复的行
- UNION 中若要排序，只允许出现一次，放在最后的 SELECT 语句后

### 单行处理函数

- 转大小写：`lower(字段名)`和`upper(字段名)`
- 提取子串：`substr(字段名, 起始下标, 截取长度)`    *注：起始下标从 1 开始*
- 拼接成字符串：`concat(字段名1, 字段名2)`
- 长度：`length(字段名)`
- 去空格：`trim(字段名)`
- 四舍五入：`round(字段名, 小数位)`
- 生成随机数：`rand()`
- 处理 NULL：`ifnull(字段名, 被当做的值)`
- 条件表达式：`if(条件，为真的值，为假的值)`
- `ABS()`: 返回一个数的绝对值。
- `CEILING()`: 返回大于或等于给定数值的最小整数。
- `FLOOR()`: 返回小于或等于给定数值的最大整数。
- `ROUND()`: 四舍五入到指定的小数位数。
- `MOD()`: 返回除法操作的余数。
- `FORMAT()`: 格式化数字为格式化的字符串，通常用于货币显示。

**例子：**

```sql
select lower(ename) as ename from emp;

select concat(upper(substr(ename, 1, 1)), lower(substr(ename, 2, length(ename) - 1))) as name from emp;

select ename from emp where ename = trim('  KING ');

select round(rand() * 1000, -1) as num from emp;

select ename, (sal + ifnull(comm, 0)) * 12 yearsal from emp;
```

###  限制结果条数

**语法：**

```sql
[其他查询语句]
limit [起始下标], [长度];
```

**例子：**偏移量是从 0 开始的，即第一条记录的偏移量是 0；如果想从第 3 条记录开始，偏移量就应该是 2。

```sql
SELECT * FROM table_name LIMIT 2, 8;
```

## 排序

**格式**：

```sql
select
	[字段名1], [字段名2], [字段名3]...
from
	[表名]
order by
	[规则];
```

**例子：**

```sql
select ename, sal from emp order by sal asc, ename asc;

select ename, sal from emp order by 2;

select ename, sal from emp where sal between 1000 and 2000 order by sal;
```

**规则：**

- 默认升序：`[字段名]`
- 指定降序：`[字段名] desc`
- 指定升序：`[字段名] asc`
- 多个字段排序：`[字段名1] [排序方式], [字段名2] [排序方式]...`（靠前的规则优先）
- 根据查询结果的字段位置排序：`[数字]`

## 分组

**格式：**

```sql
select
	[分组字段名1], [分组字段名2] ... [分组函数1], [分组函数2]...
from
	[表名]
where
	[不带分组函数的条件]
group by
	[分组字段名1], [分组字段名2]...
having
	[带分组函数的条件]
order by
	[规则];
```

**例子：**

```sql
select job, sum(sal) from emp group by job;

select job, deptno, max(sal) from emp group by job, deptno;

select deptno, max(sal) from emp group by deptno having max(sal) > 2000 order by max(sal);

select deptno, count(distinct job) from emp group by deptno;
```

**分组函数（多行处理函数）：**

- 最大最小：`max(字段名)`和`min(字段名)`
- 求和：`sum(字段名)`，可以加入判断例如 `sum(a.id<10)`
- 平均：`avg(字段名)`
- 数量：`count(字段名)` 计算不为 null 的数量，`count(*)` 包括 null 的数量

> 对于判断，例如 `a.id<10`，返回的是0或1，对于 count，因为不为 null 都计数，所以`count(a.id<10)`没有意义，无论0或者1都计数，对于sum函数可以累加返回1的个数

**关键字补充**

- 去重：`distinct`（放在所有字段前，后面字段联合去重）
- WITH ROLLUP 在分组中使用，获得汇总值

```sql
SELECT vend_id, COUNT(*) AS num 
FROM products 
GROUP BY vend_id WITH ROLLUP;
```

```
+---------+-----+
| vend_id | num |
+---------+-----+
|    1001 |   3 |
|    1002 |   2 |
|    1003 |   7 |
|    1005 |   2 |
|    NULL |  14 |
+---------+-----+
```

## join

### 内连接

**SQL99语法：**

```sql
select
	[字段名1], [字段名2]...
from
	[表名A]
inner join
	[表名B]
on
	[表连接条件];
```

*注：A B 两表没有主次关系，只看表连接条件，inner 可省略*

**例子：**

```sql
select e.ename, d.dname from emp e, dept d where e.deptno = d.deptno;

select e.ename, d.dname from emp e inner join dept d on e.deptno = d.deptno;
 
select e.ename, e.sal, s.grade from emp e join salgrade s on e.sal between s.losal and s.hisal;

select a.ename employee, b.ename employer from emp a join emp b on a.mgr = b.empno;
```

### 外连接

**语法：**

```sql
select
	[字段名1], [字段名2]...
from
	[表名A]
right outer join  -- left outer join
	[表名B]
on
	[表连接条件];
```

*注：right 意思是表 B 为主表，left 意思是表 A 为主表，outer 可省略*

**例子：**

```sql
select e.ename, d.dname from emp e right join dept d on e.deptno = d.deptno;

select a.ename employee, b.ename employer from emp a left join emp b on a.mgr = b.empno;
```

### 自联结

**例：寻找与 prod_id = 'DTNTR' 产品相同供应商的产品**

```sql
SELECT p1.prod_id, p1.prod_name
FROM products p1
join products p2
on p2.prod_id = 'DTNTR' AND p1.vend_id = p2.vend_id; 
```

### 自然连接

不重要的概念，指联结后不出现重复的列

```sql
SELECT c.cust_id, c.cust_name, o.order_num, oi.prod_id
FROM customers AS c
JOIN orders AS o
ON c.cust_id = o.cust_id
JOIN orderitems AS oi
ON oi.order_num = o.order_num AND oi.prod_id = 'FB';
```

```
+---------+-------------+-----------+---------+
| cust_id | cust_name   | order_num | prod_id |
+---------+-------------+-----------+---------+
|   10001 | Coyote Inc. |     20005 | FB      |
|   10001 | Coyote Inc. |     20009 | FB      |
+---------+-------------+-----------+---------+
```

##  DQL 语句总结

**格式：**

```sql
select
	[分组字段名1], [分组字段名2] ... [分组函数1], [分组函数2]...
from
	[表名]
where
	[不带分组函数的条件]
group by
	[分组字段名1], [分组字段名2]...
having
	[带分组函数的条件]
order by
	[规则]
limit 
	[起始下标], [长度];
```

**执行顺序：**

1. from
2. where
3. group by
4. having
5. select
6. order by
7. limit

**例子：每个部门工资最多的人**

```sql
select e.ename, t.*
from emp e
join (select max(sal) maxsal, deptno from emp group by deptno) t
on e.sal = t.maxsal and e.deptno = t.deptno;
```

```
+-------+---------+--------+
| ename | maxsal  | deptno |
+-------+---------+--------+
| BLAKE | 2850.00 |     30 |
| SCOTT | 3000.00 |     20 |
| KING  | 5000.00 |     10 |
| FORD  | 3000.00 |     20 |
+-------+---------+--------+
```

## 修改表结构

创建表

```sql
create table [表名](
  [字段名1] [数据类型] default [默认值],
  [字段名2] [数据类型] ...,
  [字段名3] [数据类型] ...,
  ......
);
```
*注：default [默认值] 可省略*

删表

```sql
drop table [表名];

drop table if exists [表名];
```

**数据类型：**

- varchar		可变长度字符串（最长255）
- char			定长字符串（最长255）
- int				
- bigint		长整型
- float
- double		短日期
- datetime	长日期，年月日时分秒
- date			短日期，年月日
- clob			字符大对象，可存 4G 字符串
- blob			二进制大对象，例如媒体数据

**例子：**

```sql
create table t_student(
	nob int,
  name varchar(32),
  sex char(1) default 'm',
  age int(4),
  email varchar(255)
);

create table emp2 as select ename, job from emp where job = 'manager';
```

**添加列：**

```sql
ALTER TABLE vendors
ADD vend_phone CHAR(20);
```

**删除列：**

```sql
ALTER TABLE vendors
DROP COLUMN vend_phone;
```

**添加约束：**

```sql
# 来自 create.sql

ALTER TABLE orderitems 
ADD CONSTRAINT fk_orderitems_orders 
FOREIGN KEY (order_num) REFERENCES orders (order_num);
```

**重命名表**

```sql
RENAME TABLE [旧表] TO [新表名];
```

### 约束

- 非空约束 ：`not null`
- 唯一性约束（NULL不算）： `unique`
- 联合唯一：`unique([字段名1],[字段名2]...)`
- 主键约束（非空，唯一）：`primary key`
- 复合主键（不建议使用）：`primary key([字段名1],[字段名2]...)`
- 设置自然主键：`auto_increment`
- 外键约束：`foreign key([子表字段名]) references [父表名]([父表unique字段名])`

**例子：**

```sql
create table t_vip (
	id int primary key auto_increment,
	name varchar(32) not null,
	email varchar(255),f
	unique(name, email)
);
```

```sql
create table t_class (
	classno int primary key,
  classname varchar(255)
);

create table t_student(
	id int primary key auto_increment,
  name varchar(255),
  classno int,
  foreign key(classno) references t_class(classno)
);

insert into t_class values (100, 'class one'), (101, 'class two');

insert into t_student(name, classno) 
values ('jk', 100), ('jjkk', 101), ('ab', 100), ('cd', 101), ('ps', 100), ('ed', 101);

select s.*, t.classname from t_student s join t_class t where s.classno = t.classno;
```

### 隔离

**查看隔离级别：**

```sql
select @@transaction_isolation;
```

**改变隔离级别：**

```sql
set global transaction isolation level [隔离级别];
```

**隔离级别：**

- `read uncommitted`：可以查到未提交的数据
- `read committed`：查已提交的数据
- `repeatable read`：只要另一方开启事务就不会查到对应数据
- `serializable`：非并行，排队

### 索引

**查看索引：**

```sql
explain [查询语句]
```

**添加索引：**

```sql
create index [索引名] on [表名]([字段名], [字段名]...);
```

*注：主键与 unique 自动添加索引*

**删除索引：**

```sql
drop index [索引名] on [表名];
```

*注：索引可以缩短查询时间，但模糊查询，类型转换，or条件，索引字段参与运算或函数等等情况会使其失效*

## insert 插入数据

**格式：**

```sql
insert into 
	[表名]([字段名1], [字段名2], [字段名3]...) 
values 
	([数据], [数据], [数据]...),
	([数据], [数据], [数据]...),
	([数据], [数据], [数据]...)
	...;
```

*注：([字段名1], [字段名2], [字段名3]...) 可省略，values 要填写全部信息*

**例子：**

```sql
insert into t_student(nob, name, sex, age, email) 
values (1, 'jk', 'f', 18, 'jk@666.com');

insert into t_student(name, nob) values ('Abe', 2);

insert into t_student values (3, 'jjkk', 'f', 19, 'jjkk@666.com');

insert into t_student(nob, name) values (4, 'a'), (5, 'b'), (6, 'c');

insert into emp2 select ename, job from emp where job = 'salesman';
```

## 日期操作

**字符串转date：**

```sql
str_to_date([字符串日期], [日期格式])
```

*注：如果日期格式为'%Y-%m-%d'，不用函数也能将字符串转date*

**date转字符串：**

```sql
date_format([日期], [格式])
```
*注：默认日期格式为'%Y-%m-%d'*
*注：如果是datetime，默认日期格式为'%Y-%m-%d %h:%i:%s'*

**获取当前时间：**

```sql
now()
```

| %Y   | %m   | %d   | %h   | %i   | %s   |
| ---- | ---- | ---- | ---- | ---- | ---- |
| 年   | 月   | 日   | 时   | 分   | 秒   |


**例子：**

```sql
create table t_user(
	id int(11),
  name varchar(32),
  birth date,
  create_time datetime
);

insert into t_user(id, name, birth)
values (1, 'jk',str_to_date('2000-12-03', '%Y-%m-%d'),now());

insert into t_user values (2, 'jjkk','2002-09-12','2022-07-28 13:13:13');

select name, date_format(birth, '%d\%m\%Y') birth from t_user;
```

| CurDate()    | CurTime()    | Now()              |
| ------------ | ------------ | ------------------ |
| 返回当前日期 | 返回当前时间 | 返回当前日期和时间 |

| Date()       | Time()       | Year()     | Month() | Day() | Hour() | Minute() | Second() |
| ------------ | ------------ | ---------- | ------- | ----- | ------ | -------- | -------- |
| 返回日期部分 | 返回时间部分 | 返回年部分 | 类比    | 类比  | 类比   | 类比     | 类比     |

**例子：**

```sql
SELECT order_num, order_date
FROM orders
WHERE Date(order_date) BETWEEN '2005-09-01' AND '2005-09-30';

SELECT order_num, order_date
FROM orders
WHERE Year(order_date) = 2005 AND Month(order_date) = 9;
```

## update 修改数据

**格式：**

```sql
update 
	[表名]
set
	[字段名1] = [数据],
	[字段名2] = [数据],
	[字段名3] = [数据],
	......
where
	[条件];
```

**例子：**

```sql
update t_user set name = 'Abe' where id = 2;
```

## 删除表中数据

**格式：**

```sql
delete from [表名] where [条件]; 
```

```sql
truncate table [表名];
```

*注：delete支持回滚，速度慢。truncate 物理删除，速度快*

**例子：**

```sql
delete from t_user where id = 2; 

truncate table t_user;
```

| 区别     | delete                                   | truncate                       | drop                                               |
| -------- | ---------------------------------------- | ------------------------------ | -------------------------------------------------- |
| 类型     | 属于 DML                                 | 属于 DDL                       | 属于 DDL                                           |
| 回滚     | 可回滚                                   | 不可回滚                       | 不可回滚                                           |
| 删除内容 | 表结构还在，删除表的全部或者一部分数据行 | 表结构还在，删除表中的所有数据 | 从数据库中删除表，所有数据行，索引和权限也会被删除 |
| 删除速度 | 删除速度慢，需要逐行删除                 | 删除速度快                     | 删除速度最快                                       |

因此，在不再需要一张表的时候，用 drop；在想删除部分数据行时候，用 delete；在保留表而删除所有数据的时候用 truncate

## 视图

**创建视图：**

```sql
create view [视图名] as [查询语句];
```

**删除视图：**

```sql
drop view [视图名]
```

*注：对视图的增删改查格式不变，对视图的改变会影响原表*

**例子：**

```sql
create view emp_dept_view as
select e.ename, e.sal, d.dname
from emp e
join dept d
on e.deptno = d.deptno;
```

## 全文本搜索

开启全文本搜索支持

```sql
# 来自 create.sql

CREATE TABLE productnotes
(
  note_id    int           NOT NULL AUTO_INCREMENT,
  prod_id    char(10)      NOT NULL,
  note_date datetime       NOT NULL,
  note_text  text          NULL ,
  PRIMARY KEY(note_id),
  FULLTEXT(note_text)
) ENGINE=MyISAM;
```

全文本搜索为每一条数据给出一个匹配值，最匹配d的记录优先

```sql
SELECT note_text
FROM productnotes
WHERE Match(note_text) Against('rabbit');
```

使用查询扩展，即找出与搜索结果再相关的其他行

```sql
SELECT note_text
FROM productnotes
WHERE Match(note_text) Against('anvils' WITH QUERY EXPANSION);
```

布尔文本搜索不需要建立 FULLTEXT 索引，更慢

**例子:**

```sql
SELECT note_text
FROM productnotes
WHERE Match(note_text) Against('heavy -rope*' IN BOOLEAN MODE);
```

- `-`代表排除后面这个词
- `*`代表词尾通配符

```sql
WHERE Match(note_text) Against('"rabbit bait"' IN BOOLEAN MODE);
```

- `""`将双引号内部的词视为一整个短语

```sql
WHERE Match(note_text) Against('+safe +(<combination)' IN BOOLEAN MODE);
```

- `+`代表一定有这个词
- `()`包含一个子表达式
- `<`降低这个词的等级

## 存储过程

- 存储过程可以封装一系列复杂的操作
- 有输入输出
- 形式类似于函数

创建存储过程

**例子1：**

```sql
DELIMITER //

CREATE PROCEDURE productpricing()
BEGIN
    SELECT Avg(prod_price) AS priceaverage
    FROM products;
END //

DELIMITER ;
```

- `DELIMITER`重新定义语句分隔符
- `BEGIN`, `END` 包含存储过程体
- 存储过程名为 `productpricing()`，这个例子没有参数

**例子2:**

```sql
DELIMITER //

CREATE PROCEDURE productpricing2 (
    OUT pl DECIMAL(8, 2),
    OUT ph DECIMAL(8, 2),
    OUT pa DECIMAL(8, 2)
)
BEGIN
    SELECT Min(prod_price)
    INTO pl
    FROM products;
    SELECT Max(prod_price)
    INTO ph
    FROM products;
    SELECT Avg(prod_price)
    INTO pa
    FROM products;
END //

DELIMITER ;
```

- 这个存储过程有三个函数
- `OUT`代表可以从存储过程传出
- `pl`等等为形参名
- `DECIMAL`是一种数据类型，精度可变的浮点值

**例子3:**

```sql
DELIMITER //

CREATE PROCEDURE ordertotal(
    IN  onumber INT,
    OUT ototal DECIMAL(8, 2)
)
BEGIN
    SELECT Sum(item_price * quantity)
    FROM orderitems
    WHERE onumber = order_num
    INTO ototal;
END //

DELIMITER ;
```

- `IN` 代表传入参数

**例子4:**

```sql
DELIMITER //

-- Name : ordertotal2
-- Parameters : onumber = order number
--              taxable = 0 if not taxable, 1 if taxable
--              ototal = order total if variable

CREATE PROCEDURE ordertotal2(
    IN onumber INT,
    IN taxable BOOLEAN,
    OUT ototal DECIMAL(8, 2)
) COMMENT 'Obtain order total, optionally add tax'
BEGIN
    
    DECLARE total DECIMAL(8, 2);
    DECLARE taxrate INT DEFAULT 6;

    SELECT Sum(item_price * quantity)
    FROM orderitems
    WHERE onumber = order_num
    INTO total;
    
    IF taxable THEN
        SELECT total + (total / 100 * taxrate) INTO total;
    END IF;
    
    SELECT total INTO ototal;
    
END //

DELIMITER ;
```

- `--`表示注释
- `DECLARE`声明变量
- `IF`,`END IF`包含分支语句
- `COMMENT`内容非必要，将在`SHOW PROCEDURE STATUS`展示

使用存储过程

**例子1：**

```sql
CALL productpricing();
```

```
+--------------+
| priceaverage |
+--------------+
|    16.133571 |
+--------------+
```

**例子2:**

```sql
CALL productpricing2(
    @pricelow,
    @pricehigh,
    @priceaverage
);

SELECT @pricelow, @pricehigh, @priceaverage;
```

```
+-----------+------------+---------------+
| @pricelow | @pricehigh | @priceaverage |
+-----------+------------+---------------+
|      2.50 |      55.00 |         16.13 |
+-----------+------------+---------------+
```

- MySQL 变量名由`@`开始

**例子3:**

```sql
CALL ordertotal(20005, @total);

SELECT @total;
```

```
+--------+
| @total |
+--------+
| 149.87 |
+--------+
```

**例子4:**

```sql
CALL ordertotal2(20005, 1, @total);

SELECT @total;
```

```
+--------+
| @total |
+--------+
| 158.86 |
+--------+
```

删除存储过程

```sql
DROP PROCEDURE productpricing;
```

检查存储过程

```sql
SHOW CREATE PROCEDURE ordertotal;

SHOW PROCEDURE STATUS;

SHOW PROCEDURE STATUS LIKE 'ordertotal2';
```

## 游标

------

- 通常在存储过程中使用
- 表示一个`SELECT`语句，一次取一条数据，可用于遍历

```sql
DELIMITER //

CREATE PROCEDURE processorders()
BEGIN
    
    DECLARE done BOOLEAN DEFAULT 0; -- 遍历结束条件
    DECLARE o INT;
    DECLARE t DECIMAL(8, 2);
    
    -- 定义游标
    DECLARE ordernumbers CURSOR
    FOR
    SELECT order_num FROM orders;
    
    -- 遍历结束条件,出现SQLSTATE为'02000'时,即未找到,done = 1
    DECLARE CONTINUE HANDLER FOR SQLSTATE '02000' SET done = 1;
    
    DROP TABLE IF EXISTS ordertotals;
    -- 存结果的表
    CREATE TABLE IF NOT EXISTS ordertotals(
        order_num INT,
        total DECIMAL(8, 2)
    );
    
    -- 打开游标才能使用
    OPEN ordernumbers;
    
    -- 循环体，开始
    REPEAT
        FETCH ordernumbers INTO o;-- 取一条记录
        CALL ordertotal2(o, 1, t);
        INSERT INTO ordertotals(order_num, total) VALUES(o, t);
    UNTIL done END REPEAT;
    -- 循环体，结束
    
    -- 关闭游标，释放资源
    CLOSE ordernumbers;
    
END //

DELIMITER ;
```

```sql
CALL processorders();
SELECT * FROM ordertotals;
```

```
+-----------+---------+
| order_num | total   |
+-----------+---------+
|     20005 |  158.86 |
|     20009 |   40.78 |
|     20006 |   58.30 |
|     20007 | 1060.00 |
|     20008 |  132.50 |
|     20008 |  132.50 |
+-----------+---------+
```

## 触发器

------

- 在对表内容修改前或后自动触发一些操作
- 支持语句`INSERT`,`DELETE`,`UPDATE`
- 使用`BEFORE`,`AFTER`来表示修改后或修改前
- `BEFORE`可以用于验证数据
- 如果触发器或语句出错，后续语句和触发器不会执行
- 合理运用触发器，可以保证数据一致性，追踪保留更改

INSERT 触发器

```sql
# 书上例子
# 执行报错：ERROR 1415 (0A000): Not allowed to return a result set from a trigger
# 新版本不支持这种写法。触发器不允许出现SELECT *的形式
CREATE TRIGGER neworder AFTER INSERT ON orders
FOR EACH ROW SELECT NEW.order_num;

# 修改版
# 结果放进变量
CREATE TRIGGER neworder AFTER INSERT ON orders
FOR EACH ROW SELECT NEW.order_num INTO @ordernumber;
```

- 创建了名为`neworder`的触发器
- 在 `INSERT  orders`之后触发
- `FOR EACH ROW`代表每一行都触发
- `NEW`是一个虚拟表，可以获取新插入的内容

```sql
INSERT INTO orders(order_date, cust_id)
VALUES (Now(), 10001);

SELECT @ordernumber;
```

```
+--------------+
| @ordernumber |
+--------------+
|        20010 |
+--------------+
```

DELETE 触发器

```sql
CREATE TABLE archive_orders # 存档表
(
  order_num  int      NOT NULL AUTO_INCREMENT,
  order_date datetime NOT NULL ,
  cust_id    int      NOT NULL ,
  PRIMARY KEY (order_num)
) ENGINE=InnoDB;


DELIMITER //

CREATE TRIGGER deleteorder BEFORE DELETE ON orders
FOR EACH ROW
BEGIN
    INSERT INTO archive_orders(order_num, order_date, cust_id)
    VALUES(OLD.order_num, OLD.order_date, OLD.cust_id);
END //

DELIMITER ;
```

- `OLD`是一个虚拟表，可以访问要删除的信息
- `OLD`只读

```sql
DELETE FROM orders WHERE order_num = 20010;

SELECT * FROM archive_orders;
```

```
+-----------+---------------------+---------+
| order_num | order_date          | cust_id |
+-----------+---------------------+---------+
|     20010 | 2022-08-03 15:32:25 |   10001 |
+-----------+---------------------+---------+
```

UPDATE 触发器

```sql
CREATE TRIGGER updatevendor BEFORE UPDATE ON vendors
FOR EACH ROW SET NEW.vend_state = Upper(NEW.vend_state);
```

- `NEW`虚拟表可以修改，也修改即将更新的内容
- `OLD`只读

删除触发器

```sql
DROP TRIGGER updatevendor;
```

## 事务

**关闭自动提交机制：**`start transaction;`

**回滚：**`rollback;`

**提交：**`commit;`

保留点：

- 保留点在实务中设置
- 如果不显式释放保留点，则在事务完成后自动释放

**创建保留点**

```sql
SAVEPOINT delete1;
```

**退回到保留点**

```sql
ROLLBACK TO delete1;
```

**释放保留点**

```sql
RELEASE SAVEPOINT delete1;
```

**不自动提交更改**

```sql
SET autocommit = 0; # 针对链接而不是服务器
```

## 用户管理

创建用户

```sql
CREATE USER ben IDENTIFIED BY 'p@$$word';
```

更改口令

```sql
SET PASSWORD FOR ben = 'n3w p@$$word';

SET PASSWORD = 'n3w p@$$word'; # 更改自己口令
```

查看用户

```sql
USE mysql;
SELECT user FROM user;
```

```
+------------------+
| user             |
+------------------+
| ben              |
| mysql.infoschema |
| mysql.session    |
| mysql.sys        |
| root             |
+------------------+
```

重命名用户

```sql
RENAME USER ben TO QMS;
```

删除用户

```sql
DROP USER QMS;
```

查看权限

```sql
SHOW GRANTS FOR ben;
```

```
+---------------------------------+
| Grants for ben@%                |
+---------------------------------+
| GRANT USAGE ON *.* TO `ben`@`%` |
+---------------------------------+
```

- `USAGE`代表没有权限

授予权限

```sql
GRANT [权限] ON [数据库名].[表名] TO [用户名];
```

- 具体到权限表见书

**例子：**

```sql
GRANT SELECT ON cc.* TO ben; # cc 就是 crashcourse
```

```
mysql> SHOW GRANTS FOR ben;
+-------------------------------------+
| Grants for ben@%                    |
+-------------------------------------+
| GRANT USAGE ON *.* TO `ben`@`%`     |
| GRANT SELECT ON `cc`.* TO `ben`@`%` |
+-------------------------------------+
```

撤销权限

```sql
REVOKE SELECT ON cc.* FROM ben;
```





