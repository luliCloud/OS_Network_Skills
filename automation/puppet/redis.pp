# define Redis install, config and server
node 'redisserver.example.com' {
    # install Redis package
    package { 'redis-server':
        ensure => installed,
    }
    
    # manage Redis config files
    file { '/etc/redis/redis.conf':
        ensure  => file,
        source  => 'puppet:///modules/redis/redis.comf', # suppoer in Puppet server module
        mode    => '0644',
        require => Package['redis-server'], # ensure install Redis before configure
    }

    # ensure Redis server is running
    service { 'redis-server':
        ensure     => running,
        enable     => true, # ensure service start when system start
        hasstatus  => true,
        hasrestart => true,
        require    => File['/etc/redis/redis.conf'], # ensure config file applied first
    }
}

# 步骤说明：
# 安装 Redis: package { 'redis-server': ensure => installed, } 确保安装 Redis 包。如果 Redis 尚未安装，Puppet 会自动安装它。管理 Redis 配置文件:

# 使用 file 资源来管理 /etc/redis/redis.conf 文件。这个配置文件会从 Puppet 服务器的 modules/redis/files/redis.conf 中提取（你需要提前将文件放在 Puppet 服务器的指定路径）。
# 管理 Redis 服务:

# service { 'redis-server': ... } 确保 Redis 服务始终在运行，并且配置为开机自启动。hasstatus 和 hasrestart 表示 Puppet 可以检查和重新启动 Redis 服务。

# ensure Redis config is under Puppet Master right path
# like puppet/modules/redis/files/redis.conf
# mkdir -p /etc/puppetlabs/code/environments/production/modules/redis/files
# cp /path/to/your/redis.conf /etc/puppetlabs/code/environments/production/modules/redis/files/

# apply redis.pp to Puppet server or puppet agent, then apply cmd
# puppet apply redis.pp
# 这将确保Redis已经安装，配置文件已更新，服务已经启动并在运行中