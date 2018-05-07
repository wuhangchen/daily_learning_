## docker_command summury 


#### install docker 
```shell
    -sudo apt-get update 

    "Install packages to allow apt to use a repository over HTTPS: 
    -sudo apt-get install \
    apt-transport-https \
    ca-certificates \
    curl \
    software-properties-common
    
    "Add Docker’s official GPG key:
    -curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add - 
    
    "Verify that you now have the key with the fingerprint 9DC8 5822 9FC7 DD38 854A E2D8 8D81 803C 0EBF CD88, by searching for the last 8 characters of the fingerprint.
    -sudo apt-key fingerprint 0EBFCD88 

    "Use the following command to set up the stable repository. You always need the stable repository, even if you want to install builds from the edge or test repositories as well. To add the edge or test repository, add the word edge or test (or both) after the word stable in the commands below. 
    -sudo add-apt-repository \
     "deb [arch=amd64] https://download.docker.com/linux/ubuntu \
     $(lsb_release -cs) \
     stable"

```
