# SFML Hello World example

From: http://www.sfml-dev.org/documentation/2.5.1/

## Screenshot
![Screenshot](http://opentechschool-zurich.github.io/cpp-co-learning/topics/graphics/richard/SfmlHelloWorld/SfmlHelloWorld.png)

## Description:
This short program creates a Window, loads a jpg image and displays it.

It loads a font and uses it to render a text.

It loads a ogg sound file and plays the sound in a loop.

## Build and run
```bash
mkdir build
cd build
cmake ..
make
./LearnSfml
```

## CPACK packaging to create rpm etc.

```bash
cd build
make package
make package_source
```

## Testing the package on a openSUSE leap Docker container

see: (https://medium.com/@SaravSun/running-gui-applications-inside-docker-containers-83d65c0db110)
and (http://somatorio.org/en/post/running-gui-apps-with-docker/)

```bash
docker run -it --net=host --env="DISPLAY" --volume="$HOME/.Xauthority:/root/.Xauthority:rw" --device /dev/dri --device /dev/snd --device /dev/input --rm opensuse/leap 
docker run -it --net=host --env="DISPLAY" -v /tmp/.X11-unix:/tmp/.X11-unix --device /dev/dri --device /dev/snd --device /dev/input --rm opensuse/leap

# on a different terminal find the container it
docker ps
# copy the package to the docker container
docker cp ..whereever/LearnSfml/build/LearnSfml-1.x86_64.rpm <<container>>:/
# in the docker container:
zypper in LearnSfml-1.x86_64.rpm
```

##Copyright information:
Picture of Davos, taken by Richard Eigenmann in December 2016, is hereby contributed to the public domain

The sound file comes from https://www.freesound.org/people/club%20sound/sounds/107330/
It is licensed under the creative commons attribution- Non Commercial license.
See here: https://creativecommons.org/licenses/by-nc/3.0/
The sound was created by a user called "club sound": https://www.freesound.org/people/club%20sound/

The Font was taken from http://www.1001freefonts.com/changa_one.font
It is in the public domain and licenced under OFL and GPL
Designer was Eduardo Tunni http://www.1001freefonts.com/search.php?d=1&q=Eduardo+Tunni
