# Guide

All configurable options are set and explained in the `lindbergh.conf` file, and should be resonably easy to understand. This document further explains some of those setup options.

## Libraries

Additional libraries that you might need to install to get all games running are listed here:

```
sudo apt install build-essential freeglut3:i386 freeglut3-dev:i386 libglew-dev xorg-dev libopenal1:i386 libopenal-dev:i386 libxmu6:i386 libstdc++5:i386 libsdl2-dev:i386 libfaudio0:i386 libfaudio-dev:i386 libncurses5:i386 libasound2-dev:i386 alsa-utils:i386 libasound2-plugins:i386
```

## Game Issues

### Let's Go Jungle Rev A

- The game must be run in export mode to have the stereo sound option.

## Controller Setup

There are 2 modes for the controller setup in the emulator, these are set using the `INPUT_MODE` flag in the configuration file.

### Input Mode 0

In this input mode, both input mode 1 and input mode 2 are active.

### Input Mode 1

In the first input mode, the keys on the keyboard are used to control the game play. If playing a light gun game, the mouse pointer in the window is used as the player 1 light gun. There are no configurable options in this mode.

### Input Mode 2

In the second input mode, inputs are taken directly from the evdev library in linux and so you can configure additional devices such as light guns, controllers and steering wheels.

To list the available inputs you should type:

```
./lindbergh --lits-inputs
```

From there you will be able to see the controllers and all of the inputs support. Then in the config file you should map an arcade input to a controller input as follows.

```
PLAYER_1_BUTTON_UP XBOX_CONTROLLER_BTN_UP
ANALOGUE_1 XBOX_CONTROLLER_ABS_X
```

You can map digital controls to analogue controls. The analogue value will be set to the digital value, such that if the button isn't pressed it will be set to 0, and if the button is pressed it will be set to MAX. This is useful if your controller doesn't have analogue accelerator or break buttons.

```
ANALOGUE_0 XBOX_CONTROLLER_BUTTON_BR
```

You can map analogue controls to digital controls too. For each analogue input, there are 2 more inputs created ending in _MAX and _MIN. These are digital controls that will be triggered when the analogue input is either at the minimum or maximum value. This can be useful if you'd like to use an analogue stick to control a fighting game for example.

```
PLAYER_1_BUTTON_UP XBOX_CONTROLLER_ABS_Y_MAX
PLAYER_1_BUTTON_DOWN XBOX_CONTROLLER_ABS_Y_MIN
PLAYER_1_BUTTON_LEFT XBOX_CONTROLLER_ABS_X_MIN
PLAYER_1_BUTTON_RIGHT XBOX_CONTROLLER_ABS_X_MAX
```

## Audio

There are currently no audio options that you can set. If you have a stereo sound card installed then the audio will be downmixed to stereo. If you have a 5.1 sound card installed and the game supports surround sound, each surround channel should be passed through properly and should play sound as it was originally intended.

## Supported Games

The follow list of games are supported. It is worth noting that there are multiple releases of these games, and some specific releases may not be supported.

| Game Name                       | Game ID | DVP      | NVidia | Intel (Mesa) | AMD (Mesa) | AMD (proprietary) |
| ------------------------------- | ------- | -------- | ------ | ------------ | ---------- | ----------------- |
| 2 Spicy                         | SBMV    | DVP-0027 | ✓      | ✓            | ✓          | ✓                 |
| After Burner Climax             | SBLR    | DVP-0009 | ✓      | ✓            | ✓          |                   |
| Ghost Squad Evolution           | SBNJ    | DVP-0029 | ✓      | ✓            | ✓          | ✓                 |
| Harley Davidson                 | SBRG    | DVP-5007 | ✓      | ✓            | ✓          | ✓                 |
| Hummer Extreme                  | SBST    | DVP-0079 | ✓      | ✓            | ✓          | ✓                 |
| Hummer                          | SBQN    | DVP-0057 | ✓      | ✓            | ✓          | ✓                 |
| Let's Go Jungle                 | SBLU    | DVP-0011 | ✓      | ✓            | ✓          |                   |
| Let's Go Jungle Special         | SBNR    | DVP-0036 | ✓      | ✓            | ✓          |                   |
| Outrun 2 SP SDX                 | SBMB    | DVP-0015 | ✓      | ✓            | ✓          | ✓                 |
| R-Tuned                         | SBQW    | DVP-0060 | ✓      | ✓            | ✓          | ✓                 |
| Race TV                         | SBPF    | DVP-0044 | ✓      | ✓            | ✓          | ✓                 |
| Rambo                           | SBQL    | DVP-0069 | ✓      | ✓            | ✓          | ✓                 |
| The House of the Dead 4         | SBLC    | DVP-0003 | ✓      | ✓            | ✓          | ✓                 |
| The House of the Dead 4 Special | SBLS    | DVP-0010 | ✓      | ✓            | ✓          | ✓                 |
| The House of the Dead Ex        | SBRC    | DVP-0063 | ✓      | ✓            | ✓          | ✓                 |
| Virtua Fighter 5                | SBLM    | DVP-0008 | ✓      | ✓            | ✓          | ✓                 |
| Virtua Fighter 5 R              | SBQU    | DVP-5004 | ✓      | ✓            | ✓          | ✓                 |
| Virtua Fighter 5 FS             | SBUV    | DVP-5019 | ✓      | ✓            | ✓          | ✓                 |
| Initial D 4                     | SBNK    | DVP-0030 | ✓      | ✓            | ✓          | ✓                 |
| Initial D 5                     | SBTS    | DVP-0075 | ✓      | ✓            | ✓          |                   |
| Virtua Tennis 3                 | SBKX    | DVP-0005 | ✓      | ✓            | ✓          | ✓                 |
| Primeval Hunt                   | SBPP    | DVP-0048 | ✓      | ✓            | ✓          | ✓                 |
