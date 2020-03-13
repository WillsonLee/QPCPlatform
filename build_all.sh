#!/bin/bash
function compile(){
    if [ ! -d ./Release ];then
       mkdir Release
    fi
    cd Release
    qmake ../*.pro
    make -j8
    cd ..
}
# compile Reflex,IPlugin,QtPCLViewer and TypeDataPeeker
cd ./dependency/Reflex
compile
cd ../IPlugin
compile
cd ../QtPCLViewer
compile
cd ../TypeDataPeeker
compile
cd ../../Plugins
# compile all plugins
for i in `ls .`;do
    if [ -d $i ];then
        cd $i
        compile
        cd ..
    fi
done
# compile main program
cd ..
compile
