ofxSerialTouchPad
=====================================

An OpenFrameworks addon to receive multitouch event notifications from generic, custom made input devices.
As the name suggests, it uses serial communication (@9600 baud), so it can work with devices connected via USB, bluetooth, etc…

I originally created this addon to work with input devices built around the MPR121 sensor; if you want a quick and easy way to create your own, [here](https://github.com/naus3a/touchPad#protocol)'s a compatible firmware.

Protocol
--------
The addon uses a simple and compact 1 byte protocol: if you're making your own hardware and firmware, just follow these guidelines.

Every received byte is considered a separate touch event, formatted this way:

```
bit index:  1  2  3  4  5  6  7  8
use:       [P][P][P][P][P][P][T][T]
```

The 6 most significant bits are used to store the address of the pin that generated the event. This means the protocol allows 64 available addresses.

The 2 least significant bits store the event type:
0 means "touch down"
1 means "touch up"

Since 2 bits are used and only 2 event types are implemented, there's free space in this field: this is because I will probably need to implement more event types for a project I'm working on.

Licence
-------
The code in this repository is available under the [MIT License](https://secure.wikimedia.org/wikipedia/en/wiki/Mit_license).  
Copyright (c) 2015 Enrico<naus3a>Viola
naus3a@gmail.com

Installation
------------
Copy to your openFrameworks/addons folder.

Compatibility
------------
openFrameworks 008.x 



Known issues
------------
none

Version history
------------
