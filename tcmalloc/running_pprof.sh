#!/bin/sh

# 设置内存剖析文件的路径
PROFILE_PATH="memory_profile"

# 导出 HEAPPROFILE 环境变量
export HEAPPROFILE="${PROFILE_PATH}"

# compile and running one of your program
g++ -o supervise.out supervise_mallocextension.cpp -ltcmalloc
./supervise.out

# running this program
# chmod +x running_pprof.sh
# ./running_pprof.sh  
# noting in real case, we cannot always check .0001.heap as the number will increase auto