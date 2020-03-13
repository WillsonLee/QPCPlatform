#!/bin/bash
if [$1 -eq ""];then
    prefix=~/QPCPlatform
else
    prefix=$1
fi
echo "installation prefix:"$prefix
if [ ! -d $prefix ];then
    mkdir $prefix
fi
cp -r ./configure $prefix/configure
cp -r ./images $prefix/images
cp -r ./include $prefix/include
cp -r ./lib $prefix/lib
cp -r ./plugins $prefix/plugins
cp -r ./templates $prefix/templates
mkdir $prefix/bin
if [ -d ./Release ];then
    cp ./Release/QPCPlatform $prefix/bin/
elif [ -d ./Debug ];then
    cp ./Debug/QPCPlatform $prefix/bin/
else
    echo "cannot find QPCPlatform,please compile QPCPlatform first!"
fi
touch /etc/ld.so.conf.d/qpcplatform.conf
echo $prefix/lib >> /etc/ld.so.conf.d/qpcplatform.conf
ldconfig
# create desktop icon
touch $prefix/QPCPlatform.desktop
echo "[Desktop Entry]" >> $prefix/QPCPlatform.desktop
echo "Encoding=UTF-8" >> $prefix/QPCPlatform.desktop
echo "Name=QPCPlatform" >> $prefix/QPCPlatform.desktop
echo "Comment=Plugin platform based on Qt" >> $prefix/QPCPlatform.desktop
echo "Exec=cd "$prefix"/bin && "$prefix"/bin/QPCPlatform" >> $prefix/QPCPlatform.desktop
echo "Icon="$prefix"/images/Icon.xpm" >> $prefix/QPCPlatform.desktop
echo "Terminal=false" >> $prefix/QPCPlatform.desktop
echo "StartupNotify=true" >> $prefix/QPCPlatform.desktop
echo "Type=Application" >> $prefix/QPCPlatform.desktop
echo "Categories=Application;Development;" >> $prefix/QPCPlatform.desktop
chmod -R 777 $prefix
cp $prefix/QPCPlatform.desktop /usr/share/applications/
