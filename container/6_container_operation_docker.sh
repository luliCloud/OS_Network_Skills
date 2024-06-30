# pull an image from the docker hub registry to the local repo, 
# to start exploring container operations supported by docker. 
docker image pull alpine
docker image ls

# create a container from the image available in the local repo. This comamnd does not start the
# container, it only creates it. Since we are not providing a name for the container, the
# runtime will assign a random name
docker container create -it alpine sh
# 2dc79913e575757dcad3b26b745bdc15926f922a143e259bd568161607ff3b57

# start the created container, using a partial container ID. The container will start the sh
# program, as we provided as a COMMAND argument.
docker container start 2dc

docker container ls
# CONTAINER ID   IMAGE          COMMAND                  CREATED              STATUS         PORTS                                       NAMES
# 2dc79913e575   alpine         "sh"                     About a minute ago   Up 6 seconds                                               intelligent_burnell

# Running a container instead of creating & starting. The -t option allocates a pseudo-TTY,
# and the -i option keep the STDIN open in interactive mode. Both -i and -t options can be 
# combined into a -it or -ti notation. all with the same effect. The --name option allow the 
# myapline name to be assigned to the running container, instead of allowing the runtime to 
# pick a random name for it
docker container run -it --name myalpine alpine sh

# Detaching from a running container ensures the container remains running. By pressing the 
# Ctrl + p + Ctrl + q key combination in the terminal of running container. 
# but vscode does not support this method. 
# instead, we can type 
exit # to exit the whole container but not just detach the container (detach means the
# container keep running in the back)

# another way to run the container, name it, and make it running in the back
docker container run -itd --name myapline alpine sh
# db705cb657c06aa5aeeff595dd8e99b5746dd2a92988e7120b9d64535c082305
docker container ls
#CONTAINER ID   IMAGE          COMMAND                  CREATED          STATUS          PORTS                                       NAMES
#db705cb657c0   alpine         "sh"                     12 seconds ago   Up 11 seconds                                               myapline
#2dc79913e575   alpine         "sh"                     18 minutes ago   Up 17 minutes                                               intelligent_burnell

# we can attach a running container 
docker start db7
docker container attach myalpine
# output: / # 

# we can run a container in the background with -d option. in which case we receive an output
# with the container ID. this example will run an infinite while-loop inside the container. 
docker container run -d alpine sh -c 'while [ 1 ]; do echo "hello world from container"; \
sleep 1; done'
# ad7beeac52a370e1fccdbf30050020d1d1484cd8ddd7d358f96cf9be6da95dad

# display container logs
docker container logs ad7
# hello world from conttainer
# hello world from conttainer
# hello world from conttainer 
# ...

# stop a running container
docker container stop ad7
# list all containers (ruuuning and stopped)
docker container ls -a  # up to indicating this container still running
# so we can check all container using this command and stop any running container

# start a stopped container
docker container start ad7

# restaring a container. This command !!!stops!!! a container first and then starts it again.
docker container restart ad7

# pausing and resuming a container
docker container pause ad7
docker container ls -a 
docker container unpause ad7
docker container ls -a




