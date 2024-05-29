# 下载到当前目录并安装
wget https://golang.org/dl/go1.18.1.linux-amd64.tar.gz  
sudo tar -C /usr/local -xzf go1.18.1.linux-amd64.tar.gz

# 设置Go环境变量
echo 'export PATH=$PATH:/usr/local/go/bin' >> ~/.bashrc
source ~/.bashrc

# 验证Go安装
go version

# 安装pprof
echo 'installing pprof'
go install github.com/google/pprof@latest

# 将 GOPATH/bin 添加到PATH
echo 'export PATH=$PATH:$(go env GOPATH)/bin' >> ~/.bashrc
source ~/.bashrc

# 验证 pprof 安装
pprof -h

# 如果要运行该文件
# chmod +x go_install.sh
# ./go_install.sh