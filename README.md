# :mag: GameOffsetDumper

![header](https://user-images.githubusercontent.com/33578715/93803078-e8c84180-fc76-11ea-8fd4-dce048825479.PNG)

Leave a **:star:star** if you find this helpful :)

**GameOffsetDumper** is a tool that finds offsets of various games by pattern scanning the entire module according to the signature you specify. This is a substitute for hazedumper not gonna lie, but this tool adopted toml file instead of json for config file.

Basically this would help game hackers yet sadly if you guys don't know how to reverse games and stuff, this is gonna be a trash for you. However, I'll be always ok to answer whatever you will ask, so create issue if you're wondering something.

:warning:Do not use this to the game running with a modern anti-cheat. Or launch option `-insecure` will help you when you try this tool on the game under VAC protection.

# :fire: Get started

Go to [**Release**](https://github.com/s3pt3mb3r/GameOffsetDumper/releases) and download latest version of GameOffsetDumper.

If you hate to download binary from someone else, then build from source by yourself. It'll work as well

Firstly, prepare config.toml file in the same directory as GameOffsetDumper.exe and fill it up properly.

This is the format of config.toml.
(We also have [**a sample of config.toml**](https://github.com/s3pt3mb3r/GameOffsetDumper/blob/master/config.toml) :ok_hand:.)

```toml
game = "left4dead2.exe"  #specify the name of the target game

[[targets]]
name = "dwLocalPlayer"   #You can name whatever you want.
signature = "8Bxxxxxxxxxxxx85xx74xx8Bxx8Bxxxxxxxxxx8BxxFFxx85xx74xx8Bxx"  #The signature you've got
module = "client.dll"   #name of the module that the address belongs to
offset = 3  #Read up below
extra = 0

[[targets]]
name = "BaseOfHandgun"
signature = "0Dxxxxxxxxxxxx0FB7xx03xx03xx03xx8Bxxxx"
module = "server.dll"
offset = 1
extra = 0

#so on and so forth
```

We also have [**a sample of config.toml**](https://github.com/s3pt3mb3r/GameOffsetDumper/blob/master/config.toml) :ok_hand:.

**I'm currently working on making a complete guide of this tool for those who don't understand what signature, offset and extra is. Wait for it.** Alternatively, you can find them [Here](https://guidedhacking.com/resources/download-hazedumper-csgo-offset-dumper.24/) as well.

Then run GameOffsetDumper.exe and every offset will be searched through whole module and written to GameOffset.hpp which will create at the same directory.


# :notes: Background

The purpose of this project for me is reinventing the wheel and to use for my personal hacking activity in the future.
