#!/bin/bash


export SOURCE_DIR=`pwd`
export PYTHON_LIBS=$SOURCE_DIR/python-libs
export CONDA_HOME=`which python | sed "s/\/bin\/python//"`
echo $CONDA_HOME

mkdir $PYTHON_LIBS
ln -sf $CONDA_HOME/lib/libpython2.7.so $PYTHON_LIBS/libpython2.7.so
ln -sf $CONDA_HOME/lib/libpython2.7.so.1.0 $PYTHON_LIBS/libpython2.7.so.1.0

cd Builds/Linux/
make 


