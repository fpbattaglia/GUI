- INSTALL CANOPY 
get an academic license and download from the website http://www.enthought.com
IMPORTANT: if you have previous installations of canopy, please make sure you wipe them out before doing anything else. Do not upgrade Canopy if a previosu installation exists on the system
Install with 

sudo bash canopy-1.4.1-full-rh5-64.sh

When prompted about the installation directory enter something like 
/home/user/Enthought/Canopy
where user is your username 
Use defaults for all other questions.
Start Canopy once with 
/home/user/Enthought/Canopy/canopy
this will set up the environment. 
When asked whether to make Canopy the default python distribution, say yes

You can now close the canopy GUI. 

- INSTALL OPEN EPHYS
open a new terminal window (or a new shell anyway) so that all the new environment settings will be taken into account.
install the modified version of open ephys:
download the most recent version by 
git clone https://github.com/fpbattaglia/GUI.git
(install git if you don't have it already)
cd GUI (or wherever you've cloned the repository)
in a text editor, edit the file build.sh
only one line needs to be modified, 
export CANOPY_PREFIX=/home/user/Enthought
(that is, this is set to the installation folder that you gave for Canopy, but *without* the last Canopy folder)
exit the editor
build open ephys with the command
./build.sh 
(or bash build.sh if the first one doesn't work)
this command, in addition to building open ephys, will generate the script run_open_ephys with the proper runtime environment configuration 

- COMPILE THE PLUGIN 
again make sure that your environment is set up: type
which python 
and this should point to the canopy python binary.
go to the plugin folder, type 
make

- RUN OPEN EPHYS
go back to the root directory of the repository (the one named 'GUI') and type 
./run_open_ephys
the program should start 



