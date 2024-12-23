[![Actions Status](https://github.com/dkeruza-neo/lindbergh-loader/actions/workflows/ci.yml/badge.svg)](https://github.com/dkeruza-neo/lindbergh-loader/actions)

# SEGA Lindbergh Emulator

This project emulates the SEGA Lindbergh, allowing games to run on modern Linux computers to be used as replacement hardware for broken Lindbergh systems in physical arcade machines. It supports both Intel and AMD CPUs as well as Intel, NVIDIA and AMD GPUs, surround sound audio, networking and JVS pass through.

## Building & Running

First you will need to install the following dependencies.

```shell
sudo dpkg --add-architecture i386
sudo apt update
sudo apt install git build-essential gcc-multilib freeglut3-dev:i386 libsdl2-dev:i386 libfaudio-dev:i386
```

This emulator will need access to the input devices and serial devices on your computer. You should add your user account to the following groups and then _restart your computer_.

```shell
sudo usermod -a -G dialout,input $USER
```

Then you should clone the repository, change directory into it and run make.

```shell
git clone git@github.com:dkeruza-neo/lindbergh-loader.git
cd lindbergh-loader
make
```

You should then copy the contents of the build directory to your game directory and run `./lindbergh` for the game, or `./lindbergh -t` for test mode.

```shell
cp -a build/* /home/games/the-house-of-the-dead-4/disk0/elf/.
cd /home/games/the-house-of-the-dead-4/disk0/elf/.
./lindbergh
```

If you'd like to change game settings copy the default configuration file from the repository to your game directory.

```shell
cp build/docs/lindbergh.conf /home/games/the-house-of-the-dead-4/disk0/elf/.
nano lindbergh.conf
```

Configuration options and supported games are explained in the [guide](docs/guide.md).

## License

<p xmlns:cc="http://creativecommons.org/ns#" xmlns:dct="http://purl.org/dc/terms/"><a property="dct:title" rel="cc:attributionURL" href="https://github.com/lindbergh-loader/">Lindbergh Loader</a> by <a rel="cc:attributionURL dct:creator" property="cc:attributionName" href="https://github.com/lindbergh-loader/">Lindbergh Loader Development Team</a> is licensed under <a href="https://creativecommons.org/licenses/by-nc-sa/4.0/?ref=chooser-v1" target="_blank" rel="license noopener noreferrer" style="display:inline-block;">Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International<img style="height:22px!important;margin-left:3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/cc.svg?ref=chooser-v1" alt=""><img style="height:22px!important;margin-left:3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/by.svg?ref=chooser-v1" alt=""><img style="height:22px!important;margin-left:3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/nc.svg?ref=chooser-v1" alt=""><img style="height:22px!important;margin-left:3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/sa.svg?ref=chooser-v1" alt=""></a></p>

Our project is open source, and our primary goal is to preserve and maintain Lindbergh arcade machines, ensuring they continue to operate in arcades. We encourage individuals to use the information provided for their own open source projects and contribute to the development of the loader to improve it for the benefit of the community. However, we do not permit the use of any of our code in commercial ventures without prior consent from the Lindbergh Loader Development Team. If we become aware of any such use, we reserve the right to take legal action.

## Thanks

This project has been built by referencing various earlier projects and would like to extend it's thanks to everyone that has contributed to the Lindbergh scene.

## Takedown Notices

The Lindbergh Loader Development Team respects intellectual property rights and is committed to ensuring that no copyrighted material is shared without proper authorization. If you believe that we are infringing on your intellectual property or have any concerns regarding our activities, please email us at bobby [at] dilley [dot] uk. We are more than happy to address any issues and discuss them further.
