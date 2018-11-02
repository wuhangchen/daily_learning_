### how to use the find and grep 

by default ,we can use the find and redirection and grep to finish many thing .
```shell 
    find ./ -name "file" 
```  
    of cource ,find command combine * command have a great power,at the some time ,combine 
redirection also finish many things. 
```shell 
    find ./ -name "file*" | grep file 
``` 
at the end,there are many choice about the find .such as : 
- d  represent the directory . 
- l  the symbol link  
- f  some nurual file  


### how to use the grep   

the grep comman is a very great power power.it conected to the regular expression . 
```shell 
    grep file 
``` 

the other choice: 
- r represent recursive 
- v represent reversal 
 




