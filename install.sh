#!/bin/bash
# installation location
if [ -z $1 ];then
    prefix=~/QPCPlatform
else
    prefix=$1
fi
echo "installation prefix:"$prefix
if [ ! -d $prefix ];then
    mkdir $prefix
else
    echo "installation location already exist.installation terminated."
    exit
fi
# copy files
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
# create launcher
touch $prefix/bin/startup.sh
echo "cd "$prefix"/bin" >> $prefix/bin/startup.sh
echo "export LD_LIBRARY_PATH=../lib" >> $prefix/bin/startup.sh
echo "./QPCPlatform" >> $prefix/bin/startup.sh
chmod a+x $prefix/bin/startup.sh
# create shortcut
touch $prefix/QPCPlatform.desktop
echo "[Desktop Entry]" >> $prefix/QPCPlatform.desktop
echo "Encoding=UTF-8" >> $prefix/QPCPlatform.desktop
echo "Name=QPCPlatform" >> $prefix/QPCPlatform.desktop
echo "Comment=Plugin platform based on Qt" >> $prefix/QPCPlatform.desktop
echo "Exec=\"/home/lyx/QPCPlatform/bin/startup.sh\"" >> $prefix/QPCPlatform.desktop
echo "Icon="$prefix"/images/Icon.xpm" >> $prefix/QPCPlatform.desktop
echo "Terminal=false" >> $prefix/QPCPlatform.desktop
echo "StartupNotify=true" >> $prefix/QPCPlatform.desktop
echo "Type=Application" >> $prefix/QPCPlatform.desktop
echo "Categories=Application;Development;" >> $prefix/QPCPlatform.desktop
cp $prefix/QPCPlatform.desktop ~/.local/share/applications/
chmod a+x $prefix/QPCPlatform.desktop
