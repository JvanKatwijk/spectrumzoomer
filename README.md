
A simple spectrumviewer

---------------------------------------------------------------------


Since most of modern sdr devices can handle signals with a substantial 
bandwidth, it is desirable to be able to show such spectra.

*spectrumzoomer*  is a program to show such a wide band. However,
since showing a band of e.g. 10 Mhz on a screen with a picture width
of e.g. 500 dots, hides lots of details. After all, in this case
a single dot on the screen would represent 20 KHz, and many details
of signals will be lost.

The spectrumzoomer therefore is built such that one might zoom in
on the signal, up to a factor of 128,such that a single dot on the
screen will stand for less than 200 Hz.

The two picture show different zooming factors, the first one showing the
full 10 Mhz, the second showing a width of 200 Khz.

![spectrumviewer](/spectrumzoomer_1.png?raw=true)

![spectrumviewer](/spectrumzoomer_2.png?raw=true)

It shows that an FM signal has a width - as we all knew - of over 200 KHz.

The ultimate goal is to create a "zooming" factor such that one
can zoom in to see the signal width a width of only a few Hz.

The supported devices (currently Linux only) are

a) the "good old" rtlsdr based dabsticks, the bandwidth is set to 2.5 Mhz,
b) the airspy, the bandwidth is set to 10 MHz,
c) the Hackrf, the bandwidth is set to 10 MHz,
d) the SDRplay, the bandwidth is set to 8 or to 10 Mhz, depending on the version,
e) the limeSDR, the bandwidth is set to 10 Mhz.

On start up of the program, it will detect the device connected to the
computer where the software is running.

The software is under development

------------------------------------------------------------------------

To construct the spectrumviewer adapt the ".pro" file to your needs
For the devices included (by uncommenting the appropriate lines
in the ".pro" file) you need to install the appropriate libraries

--------------------------------------------------------------------------



