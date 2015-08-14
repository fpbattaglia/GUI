#!/bin/bash


export SOURCE_DIR=`pwd`
export PYTHON_LIBS=$SOURCE_DIR/python-libs
export CONDA_HOME=/home/fpbatta/anaconda

mkdir $PYTHON_LIBS
ln -sf $CONDA_HOME/lib/libpython2.7.so $PYTHON_LIBS/libpython2.7.so
ln -sf $CONDA_HOME/lib/libpython2.7.so.1.0 $PYTHON_LIBS/libpython2.7.so.1.0



cat <<FINE >run_open_ephys
#!/bin/bash

export PYTHONHOME=${CONDA_HOME}
`pwd`/Builds/Linux/build/open-ephys

FINE


chmod +x run_open_ephys

cd Builds/Linux/
make 


