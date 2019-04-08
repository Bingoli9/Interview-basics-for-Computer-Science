## Launchctl

launchctl是任务管理器，可用设置开机启动或是定时任务

#### .plist

开机启动任务列表，例如sshd开机启动

launchctl load -w /System/Library/LaunchDaemons/ssh.plist

- launchctl list
- launchctl start (service)
- launchctl stop (service)
- launchctl kill (service)