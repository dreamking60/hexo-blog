---
title: GDB Script Basics and Examples
date: 2025-09-08 01:11:00
categories: Debugging
tags:
  - GDB
  - Debugging
  - Reverse Engineering
  - pwn.college
description: Quick guide to writing .gdb scripts with breakpoints, commands, register access, and printf; includes a practical pwn.college-style example.
---

Maybe some student may be confused about .gdb script file. I will give something here to help you understand it.

<!-- more -->

From the sample code in pwn.colledge. Here the gdb script will trigger anytime the program run at main+42.

And at this location, it will define a variable called $local_variable and then store the value ($rbp-0x32) pointer to as long long value.
And then printf out it.
```gdb
start
break *main+42
commands
  silent
  set $local_variable = *(unsigned long long*)($rbp-0x32)
  printf "Current value: %llx\n", $local_variable
  continue
end
continue
```

In the pwn.college Debugging Refresher Level5, you can use `disass` command which will show you the assembly code of the program to help you understand the program logic.

And then you will find that this is similar with the Level4. It will set random value and ask you to input it.
So there is a sample .gdb script here.
```gdb
start
breakpint1
    silence
    set $your_local_var = $some_register_in_code_1
    continue
end
breakpoint2
    silence
    set $some_register_in_code_2 = $your_local_var
    continue
end
```
