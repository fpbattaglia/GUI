#!/bin/bash


#export CANOPY_PREFIX=/home/fpbatta/Enthought
export CANOPY_INCLUDES=/usr/include/python2.7
#export CANOPY_LIBS=${CANOPY_PREFIX}/Canopy_64bit/User/lib
#export CANOPY_ROOTPATH=`ls -d ${CANOPY_PREFIX}/Canopy/appdata/*/lib`
#export CANOPY_PATH=`ls -d ${CANOPY_PREFIX}/Canopy/appdata/*/lib/python2.7`
#export CANOPY_VENV=/Canopy_64bit/User/lib/python2.7/site-packages
#export CANOPY_FULLPATH=${CANOPY_PATH}:${CANOPY_ROOTPATH}/python27.zip:${CANOPY_PATH}/plat-linux2:${CANOPY_PATH}/lib-tk:${CANOPY_PATH}/lib-old:${CANOPY_PATH}/lib-dynload:${CANOPY_PATH}/site-packages:${CANOPY_PREFIX}/Canopy_64bit/User/lib/python2.7/site-packages
#export CANOPY_HOME=`ls -d ${CANOPY_PREFIX}/Canopy/appdata/*`
#export CANOPY_RUNLIBS=`pwd`/python_libs
#export CANOPY_LIBS=$CANOPY_RUNLIBS
#export LIBPYTHON=`ls ${CANOPY_PREFIX}/Canopy/lib/libpython2.7*`
#mkdir -p $CANOPY_RUNLIBS
#echo on
#ln -sf ${LIBPYTHON} $CANOPY_RUNLIBS/libpython2.7.so
#ln -sf ${LIBPYTHON} $CANOPY_RUNLIBS/libpython2.7.so.1.0
#echo off

echo $CANOPY_PREFIX
echo $CANOPY_INCLUDES
echo $CANOPY_LIBS


#cat <<FINE >run_open_ephys
##!/bin/bash
#
#CANOPY_PREFIX=/home/fpbatta
#
#export LD_LIBRARY_PATH=/lib/x86_64-linux-gnu:${CANOPY_RUNLIBS}:/usr/lib/x86_64-linux-gnu/
#export PYTHONPATH=${CANOPY_FULLPATH}
#export PYTHONHOME=${CANOPY_HOME}
#`pwd`/Builds/Linux/build/open-ephys

#FINE


#chmod +x run_open_ephys

make


