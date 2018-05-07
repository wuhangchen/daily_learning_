## how to mount and unmount an iso image in linux

>this problem brothering me a some time ,but i usually forget it .

an iso image or .iso file is an archive file that contains a disk amage called iso9660 file system format.
sometime it happens that we need to access files and view content from these  iso message,but without wasting disk space and in burning them on to  cd/dvd.

this article describes how to mount and unmount an iso image on a linux operating system to access and list the content of files..

```shell
    mkdir /mnt/iso
#or
    sudo mkdir /mnt/iso
```

```shell
    mount -t iso9660 -o  loop ./filename.iso /mnt/iso
#or
    sudo mount -t iso9660 -o  loop ./filename.iso /mnt/iso
```

therefore,we can complete the knowledge,a good advice to see man mount.

#### how to unmount an iso image

simply run the following command from the terminal either "root" or "sudo "to unmount an mount iso image.

```shell
    umount /mnt/iso
#or
    sudo umount /mnt/iso
```


#### where option

- -t:this argument is used to indicate the given filesystem type.
- -iso9660 :it describes standard and default filesystem structure to be used on cd/dvd roms;
- -o  :options are necessary with a followed by a sseparated comma string of  options.
- -loop :the loop device is a pseudo-device that often used for mounting cd/cdvd iso image and makes those files accessible as a block device.  





#### other choice 
we can using the mount directly to mount the filesystem where destination .


```shell 
    mount /dev/cdrom   /mnt/iso
```
by default ,we know that mounted fileststem it mount the /dev/cdrom .
