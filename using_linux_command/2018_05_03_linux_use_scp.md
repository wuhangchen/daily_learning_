## using_linux_command_scp  

>scp — secure copy (remote file copy program)

#### how to use it sent some data to service 

```shell 
    sudo scp ./source_file_name  name@service_id: ./destine_file_name_or_dir 
```

#### how to use it download some data from service  

```shell 
    sudo scp name_host@service_id: ./service_file_name  ./local_file_name_or_dir 
``` 


#### some parameter need to summary 
    if the service have the firewall ,therefor the client have to set the port ,we need to 
use -P choice to set the port number .  
```shell 
   sudo  scp -P 4588 remote@www.runoob.com:/usr/local/sin.sh /home/administrator
``` 
    of cource have the -r choice to represent the recurive.
