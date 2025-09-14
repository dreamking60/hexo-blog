---
title: Hexo Blog Build
date: 2025-03-11 11:20:24
categories: WebDev
tags:
    - hexo
    - blog
    - ubuntu
---

# Nodejs 
Install nodejs for running hexo blog framework.
First make sure you have curl, because we need to install nodejs through [nodesource](https://github.com/nodesource/distributions?tab=readme-ov-file#ubuntu-versions).
```bash
sudo apt-get install -y curl
```
curl to download the setup shell script and then run the script.
```bash
curl -fsSL https://deb.nodesource.com/setup_22.x -o nodesource_setup.sh
sudo -E bash nodesource_setup.sh
```
And then install nodejs.
```bash
sudo apt-get install -y nodejs
```
Use the following command to check if your nodejs install correctly.
```bash
node -v
```
# Hexo 
We need to install hexo-cli, but for the people who is super familar with hexo, they also can only install hexo.
```bash
npm install -g hexo-cli
npm install hexo
```
If you find the following warning, it means that you run with a normal user, but npm install need a root user, so please use `sudo`.
```bash
npm error The operation was rejected by your operating system.
npm error It is likely you do not have the permissions to access this file as the current user
npm error
npm error If you believe this might be a permissions issue, please double-check the
npm error permissions of the file and its containing directories, or try running
npm error the command again as root/Administrator.
```
For easily run command with in linux, we can add npm node_modules to environment variable.
```bash
echo 'PATH="$PATH:./node_modules/.bin"' >> ~/.profile
```
After install hexo, we can init the basic files in our blog directory. And then install the blog.
```bash
hexo init dreamking60-blog
cd dreamking60-blog
npm install
```
The target blog directory file may be as following, this is using the [[tree]] command.
```bash
├── _config.landscape.yml
├── _config.yml
├── node_modules
├── package-lock.json
├── package.json
├── scaffolds
├── source
└── themes
```

# Stellar
Go into our blog directory and then install the theme.
Install hexo-theme-steller by the following command.
```bash
npm i hexo-theme-stellar
```
And then modfiy the \_config.yam file. Change the `theme` to `stellar`
```bash
theme: stellar
```

According to the [hexo offical document](https://hexo.io/zh-cn/docs/configuration) to configure the blog website.

# Running
Running the server can along the hexo server command.
```bash
hexo server -p 80
```
If we want to make it continue to run on our server. We should use the pm2 to manage the server.
```bash
npm install -g pm2
pm2 start "hexo server -p 20" --name hexo
```
And also remember to add the following command for futher configuration.
```bash
pm2 startup
pm2 save
```

# Add Comment System
In the `_config.stellar.yml` configure file, 

# Blog Update
Anytime you update the settings of the blog. Restart the pm2 to enable the new setting.
```bash
sudo pm2 restart hexo
```
