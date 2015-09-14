#!/bin/bash


export SOURCE_DIR=`pwd`
export PYTHON_LIBS=$SOURCE_DIR/python-libs
export CONDA_HOME=`which python | sed "s/\/bin\/python//"`
echo $CONDA_HOME

rm -rf $PYTHON_LIBS
mkdir $PYTHON_LIBS
ln -sf $CONDA_HOME/lib/libpython3.4m.so $PYTHON_LIBS/libpython3.4m.so
ln -sf $CONDA_HOME/lib/libpython3.4m.so.1.0 $PYTHON_LIBS/libpython3.4m.so.1.0

cd Builds/Linux/
make 


