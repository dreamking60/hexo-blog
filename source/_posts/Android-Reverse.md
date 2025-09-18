---
title: Android-Reverse
date: 2025-03-11 23:18:07
categories: Android
tags:
    - Android
    - Smali
    - Reverse Engineering
---
## 环境准备
安卓模拟器+Magisk安装
安卓模拟器：Nox模拟器
Magisk：根据52pj的教程进行安装
## 认识apk

| 文件                    | 含义                                        |
| --------------------- | ----------------------------------------- |
| assets目录              | 存放apk的一些静态资源文件，比如video, audio and picture |
| lib目录                 | 一些app运行需要的库，例如c++的一些动态链接库.so              |
| META-INF目录            | 签名信息的文件                                   |
| res目录                 | 资源文件，包括图片和字符串                             |
| AndroidMainfest.xml文件 | APK的应用清单信息，它描述了应用的名字，成本，权限，引用的库文件等等信息     |
| classes.dex文件         | classes.dex是java源码编译后生成的java字节码文件         |
| resources.arsc文件      | 编译后的二进制资源文件，映射表                           |

### 双开APK

| 原理          | 解释                                                                                          |
| ----------- | ------------------------------------------------------------------------------------------- |
| 修改包名        | 让手机系统认为这是两个app，就产生了2个数据存储目录，多开相当于打开两个互不干扰apk                                                |
| 修改Framework | 对于有系统修改权限的厂商，可以修改Framework来实现双开，例如小米                                                        |
| 通过虚拟化技术     | 虚拟Framework层、虚拟文件系统、模拟Android对组件的管理、虚拟应用的进程管理等虚拟化技术，将apk在虚拟空间中运行                            |
| 以插件机制运行     | 利用反射替换，动态代理，hook了系统的大部分与system-server进程通讯的函数，以此欺骗系统以为只有一个apk在运行，瞒过插件让其以为自己已经安装，例如VirtualAPP |
### 汉化apk
汉化使显示为中文
软件汉化和游戏汉化
查壳 -> 反编译 ->修改代码 -> 回编译签名 
反编译汉化
- Arsc汉化
- xml汉化
- Dex汉化
汉化手段
	使用MT管理器，进行搜索需要替换的字符串，然后找到目标文件改写保存即可。
	Arsc，xml，Dex在不同的区域会被搜索到，但核心都差不太多。
	使用翻译插件进行汉化

AndroidManifest.xml文件是整个应用程序的信息描述文件，定义了应用程序中包含的Activity,Service,Content provider和BroadcastReceiver组件信息。每个应用程序在Root目录下必须包含一个AndroidManifest.xml文件，且文件名不能修改。它描述了package中暴露的组件，他们各自的实现类，各种能被处理的数据和启动位置。

| 属性                                 | 定义                                         |
| ---------------------------------- | ------------------------------------------ |
| versionCode                        | 版本号，主要用来更新，例如:12                           |
| versionName                        | 版本名，给用户看的，例如:1.2                           |
| package                            | 包名，例如：com.zj.52pj.demo                     |
| uses-permission android:name=""    | 应用权限，例如：android.permission.INTERNET 代表网络权限 |
| android:label="@string/app_name"   | 应用名称                                       |
| android:icon="@mipmap/ic_launcher" | 应用图标路径                                     |
| android:debuggable="true"          | 应用是否开启debug权限                              |
修改软件名称：在arsc文件中查找。
修改软件图标：图标名称一般为ic_launcher.jpg，一般在assets或res文件夹里查找皆可。
修改软件名称和图标：在AndroidMainfest.xml中找到对应的字段名，在arsc中搜索到对应的位置。
查询到多张图片：SD, U3, JY, D2，分别对应的不同的dpi缩放比。
可以使用反资源混淆的功能，来恢复正常资源文件夹。
找到对应ic_launcher.jpg的文件，替换为我们自己的ic_launcher.jpg即可。

## smali认识
JVM：java虚拟机
Dalvik：Android应用虚拟机，文件格式是dex
Art：Dalvik升级版

smali是Dalvik寄存器语言。

逆向的关键点：
	快速定位
		搜索关键字
		抓取按钮id
	修改方法
		修改判断
		强制跳转
		修改寄存器的值

## 广告和弹窗处理
核心破解插件，可以禁用签名较检
## 安卓四大组件

| 组件                        | 描述                                                                                                                                          |
| ------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------- |
| Activity(活动)              | 在应用中的一个Activity可以用来表示一个界面，意思可以理解为“活动”，即一个活动开始，代表 Activity组件启动，活动结束，代表一个Activity的生命周期结束。一个Android应用必须通过Activity来运行和启动，Activity的生命周期交给系统统一管理。 |
| Service(服务)               | Service它可以在后台执行长时间运行操作而没有用户界面的应用组件，不依赖任何用户界面，例如后台播放音乐，后台下载文件等。                                                                              |
| Broadcast Receiver(广播接收器) | 一个用于接收广播信息，并做出对应处理的组件。比如我们常见的系统广播：通知时区改变、电量低、用户改变了语言选项等。                                                                                    |
| Content Provider(内容提供者)   | 作为应用程序之间唯一的共享数据的途径，Content Provider主要的功能就是存储并检索数据以及向其他应用程序提供访问数据的接口。Android内置的许多数据都是使用Content Provider形式，供开发者调用的（如视频，音频，图片，通讯录等）            |
去广告：
1. 直接修改源代码跳过某些特定的广告代码
2. 找到广告资源对应的xml，增加android:visibility="gone"来隐藏图片
3. 使用MT管理器Activity监听，找到广告对应的进程

## 动态调试
软件获得debug权限
1. 修改debug权限
	AndroidMainfest.xml文件，android:debuggable="true"
2. XappDebug模块hook对应的app
3. Magisk命令
	```shell
	adb shell #adb turn into terminal mode
	su #change to super user
	magisk resetprop ro.debuggable
	stop;start; #reboot
	```
4. 刷入MagiskHide Props Config模块

安卓机要开启开发者模式[[adb]]权限。

使用jeb去动态调试源码。
分析代码找到某个合理的位置，ctrl+b下断点。
```
adb shell am start -D -n <包名/类名>
```
这里是com.zj.wuaipojie/.ui.MainActivity
然后在jeb中点击，debug开始，就可以看到右边显示的内部变量。
F6：进入函数
F7：next
根据id输入，会生成不同的密钥。
这里观察内部变量，可以拿到一个string值，这个string就是flag{}中间部分的内容。

日志插桩
将日志插桩.dex移入apk中，改名为classes2.dex
然后在需要的值下方加入smali语句：
```
invoke-static {<Reg>},  Lcom/mtools/LogUtils;->v(Ljava/lang/Object;)V
```

## APK校验
校验方式：签名校验、dexcrc校验、apk完整性校验、路径文件校验
### APK签名
APK签名，开发者证明对Apk的所有权和控制权，可用于安装和更新应用，在Android设备上的安装Apk，如果是一个没有被签名的Apk，则会拒绝安装，在安装Apk时，软件包管理器也会验证Apk是否已经被正确签名，并且通过签名证书和数据摘要验证是否合法没有被篡改。
作用：
	1. 证明Apk所有者
	2. 允许Android市场和设备校验Apk的正确性
签名方案：
	v1：基于JAR签名
		META-INF目录下三个文件：
			Mainfest.mf
				摘要文件，程序遍历Apk所有文件，对非文件夹非签名文件的文件，逐个用SHA1生成digest，再用Base64进行编码。
			Android.sf
				对摘要的签名文件，对Mainfest.mf使用SHA1-RSA，用开发者私钥进行签名，安装时只能使用公钥才能解密他，解密之后，再将它与未加密的摘要信息（即，Mainfest.mf文件）进行对比。
			Android.rsa
				保存了公钥和加密算法信息。
	v2：AnD7引入
		将Apk视为blob，对整个文件进行签名检查，对Apk进行任何修改都会使Apk签名作废。这种形式的Apk验证不仅速度要快得多，而且能够发现更多种未授权的修改。
	v3：AnD9引入
	v4：AnD11引入
判断是否存在签名校验：
	直接对应用进行签名再进行安装，若无法正常安装或启动，便存在签名校验。
三角校验：复杂难搞的校验。
普通获取签名校验代码：

```java
private boolean SignCheck() {
    String trueSignMD5 = "d0add9987c7c84aeb7198c3ff26ca152";
    String nowSignMD5 = "";
    try {
        // 得到签名的MD5
        PackageInfo packageInfo = getPackageManager().getPackageInfo(getPackageName(),PackageManager.GET_SIGNATURES);
        Signature[] signs = packageInfo.signatures;
        String signBase64 = Base64Util.encodeToString(signs[0].toByteArray());
        nowSignMD5 = MD5Utils.MD5(signBase64);
    } catch (PackageManager.NameNotFoundException e) {
        e.printStackTrace();
    }
    return trueSignMD5.equals(nowSignMD5);
}
```

系统将应用的签名信息封装在 PackageInfo 中，调用 PackageManager 的 getPackageInfo(String packageName, int flags) 即可获取指定包名的签名信息。

签名校验的对抗：
1. 核心破解插件，不签名安装应用
2. 一键过签名工具，例如MT的去签名校验功能
3. 具体分析签名校验逻辑
4. io重定向

### io重定向
什么是IO重定向？
[平头哥的核心代码](https://github.com/virjarRatel/ratel-core) 
[Virtual Engine for Android(Support 12.0 in business version)](https://github.com/asLody/VirtualApp)

IO重定向可以干嘛？
1. 可以让文件只读，不可写
2. 禁止访问文件
3. 路径替换
具体实现： 
过签名检测(读取原包) 
风控对抗(例:一个文件记录App启动的次数) 
过Root检测
Xposed检测(文件不可取)


## Kali Frida
```
sudo apt update
sudo apt install vim leafpad
sudo apt install xfonts-intl-chinese
sudo apt install ttf-wqy-microhei
```

代理配置：
```
export https_proxy=http://192.168.92.1:7890
export http_proxy=http://192.168.92.1:7890
export all_proxy=socks5://192.168.92.1:7890

```
