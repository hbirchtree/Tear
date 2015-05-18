# Tear
A redux of QStreamSuite, this time with a better name.
Also, this time it is better written, with C++11 features in use and a structure that is easy to understand.

# The goal of Tear
The goal of Tear is to be able to play games on a desktop, wirelessly with a tablet or phone.
This combined with gyroscopic input can be used for virtual reality as well, which is a nice side-effect.
To make this happen, it is necessary to have low-latency input and low-latency video,
 and perhaps audio at some point. (If we are really going wireless)
 
 # Progress so far
  - Input system and networking is done
  - QML client is almost done, missing the virtual buttons however.
  - Screen is captured through Qt's own QScreen method to a QImage, then compressed as JPG
  - Video is broken at this point. The network connection becomes constipated and stops working (18.05.15)
  - I want to add audio support at some point
