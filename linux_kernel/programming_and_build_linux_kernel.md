
#### 必要的过程对于重新编译内核

首先从kernel.org下载所需要内核版本。不出意外，下载的压缩文件为`.tar.xz`格式。我们需要将压缩文件解压成正常的文件。
```shell 
    tar -xvJf file.tar.xz
```
当然也可以先解压成`tar`包格式。 
```shell 
    xz -d file.tar.xz
    tar -xvf file.tar
```

1)`make menuconfig`
    在`/usr/src/linux`中进入对应的源代码中，然后运行这条命令，会出现一个可选的编译进内核的选项界面。

2)`make` 
    当然可以开处理器的个数*2的线程来加快速度。
3)`make modules`

4)`make modules_install`

5)`make install`
