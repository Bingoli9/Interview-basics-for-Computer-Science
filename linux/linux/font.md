sudo mkdir -p /usr/share/fonts/custom  
sudo mv Monaco.ttf /usr/share/fonts/custom  
sudo chmod 744 /usr/share/fonts/custom/Monaco.ttf  

sudo mkfontscale  #生成核心字体信息  
sudo mkfontdir  
sudo fc-cache -fv  