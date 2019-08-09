# SFML Hello World example

## Screenshot

![Screenshot](http://richardeigenmann.github.io/LearnSfml/LearnSfml.png)

## Description

This short program creates a Window, loads a jpg image and displays it while playing a sound file. The user can move the text with the cursor keys. It was created as a starter project for SFML experiments.

Successful Experiments include:

* Using cmake as a build system with C++ 17
* Creating a .rpm package for openSUSE using CPACK
* Creating a .deb package for Debian using CPACK
* Testing the .rpm and .deb packages on a Docker  container running openSUSE or Debian
* Creating and running a Flatpak
* Including getopt to turn on verboseness with -v

## Build and run

```bash
mkdir build
cd build
cmake ..
make
./LearnSfml
```

## CPACK packaging to create .rpm and .deb

```bash
cd build
make package
make package_source
```

The packages are to be found in the build subdirectory.

## Testing the package on a openSUSE leap Docker container

see: (https://medium.com/@SaravSun/running-gui-applications-inside-docker-containers-83d65c0db110)
and (http://somatorio.org/en/post/running-gui-apps-with-docker/)

```bash
xhost +  # allow other computers to use your DISPLAY
docker run -it --gpu --net=host --env="DISPLAY" --volume="$HOME/.Xauthority:/root/.Xauthority:rw" --volume /tmp/.X11-unix:/tmp/.X11-unix --volume /etc/localtime:/etc/localtime --device /dev/dri --device /dev/snd --device /dev/input --rm opensuse/leap

# on a different terminal find the container it
docker ps
# copy the package to the docker container
docker cp ..whereever/LearnSfml/build/LearnSfml-1.x86_64.rpm <<container>>:/
# in the docker container:
zypper in LearnSfml-1.x86_64.rpm
zypper in Mesa
```

## Compiling and running with Flatpak

```bash
git submodule add -f https://github.com/flathub/shared-modules.git
flatpak-builder build-dir --force-clean org.richinet.LearnSfml.json
flatpak-builder --run build-dir org.richinet.LearnSfml.json LearnSfml
flatpak-builder --repo=repo --force-clean build-dir org.richinet.LearnSfml.json
flatpak --user remote-add --no-gpg-verify --if-not-exists tutorial-repo repo
flatpak --user install tutorial-repo org.richinet.LearnSfml
flatpak run org.richinet.LearnSfml
flatpak remove org.richinet.LearnSfml
```

## Copyright information

Picture of Davos, taken by Richard Eigenmann in December 2016, is hereby contributed to the public domain

The sound file comes from https://www.freesound.org/people/club%20sound/sounds/107330/
It is licensed under the creative commons attribution- Non Commercial license.
See here: https://creativecommons.org/licenses/by-nc/3.0/

The sound was created by a user called "club sound" or nowadays "chimerical": https://freesound.org/search/?q=Countdown+News+Intro It is licenced under the Creative Commons Attribution Non-Commerical licence

The Font was taken from http://www.1001freefonts.com/changa_one.font
It is in the public domain and licenced under OFL and GPL
Designer was Eduardo Tunni http://www.1001freefonts.com/search.php?d=1&q=Eduardo+Tunni
