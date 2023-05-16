#!/bin/bash
~/projects/GacUI/Release/Tools/GacGen/Bin/GacGen /C64 Resource.xml
sed -i 's/GetIdx() = 0/GetIdx()const = 0/g' Source/GacfredPartialClasses.h 
sed -i 's/GetType() = 0/GetType()const = 0/g' Source/GacfredPartialClasses.h 
sed -i 's/GetContent() = 0/GetContent()const = 0/g' Source/GacfredPartialClasses.h 
sed -i 's/GetCtime() = 0/GetCtime()const = 0/g' Source/GacfredPartialClasses.h 

