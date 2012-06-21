WarBots Development Setup Instructions
======================================

1.0 Download Ubuntu 11.10 (Oneiric Ocelot) 32-bit (IMPORTANT, 32 BIT, note that x86 is 32 bit)  
    http://mirror.anl.gov/pub/ubuntu-iso/DVDs/ubuntu/11.10/release/

1.1 Setup GitHub account, follow instructions:  
    www.github.com  
    https://help.github.com  
    https://help.github.com/articles/generating-ssh-keys

1.2 Open terminal (Ctrl+Alt+T), it will be your best friend

2.0 install simspark related packages, in terminal

    sudo apt-add-repository ppa:gnurubuntu/rubuntu
    sudo apt-get update
    
Either use Synaptic Package Manager (install from Ubuntu Software Center)

        search "rcss", excluding quotes, and install these packages:
            rcssmonitor
            rcssmonitor-dev
            rcsslogplayer
            rcsslogplayer-dev
            rcsoccersim
            rcssserver
            rcssserver-dev
            rcssserver3d
            rcssserver3d-dev
            
Or run this in terminal:

        sudo apt-get install rcssmonitor rcssmonitor-dev rcsslogplayer rcsslogplayer-dev rcsoccersim rcssserver rcssserver-dev rcssserver3d rcssserver3d-dev
    
3.0 Clone this repository, if you haven't yet  
To clone, run the following in terminal: 
        cd ~
        git clone git@github.com:uWaterloo-IEEE-StudentBranch/IEEE-SB-SETUP.git
        
Open synpatic, install search for following packages:

        libxml++2.6-2
        libxml++2.6-dev
        libeigen2-dev
        doxygen
        
Or run this in terminal:

        sudo apt-get install libxml++2.6-2 libxml++2.6-dev libeigen2-dev doxygen
        
Follow the README file in each of the four subfolders under the WarBots folder
    
*\*Note\** if configure gives errors on missing libraries, install them with synpatic and retry  
*\*Note\** sudo make install is only for the libraries (libbats and librcsc)  
*\*Note\** agent2d is dependent on librcsc, so install librcsc first
        
Generally, you run the following commands in each folder:

    ./configure
    make
    sudo make install
    
4.0 To test a few things, run terminal (use chmod to change permission if needed):

    <man chmod to see help for chmod>
    
Sim2D:

    rcsoccersim
    [agent2d source folder]/src/start.sh
    
Sim3D:

    rcsoccersim3d
    [libbats souce folder]/examples/helloworld/helloworld

5.1 Go to our official [repository](https://github.com/uWaterloo-IEEE-StudentBranch/WarBots-CodeRepo), and happy hacking.