from  : https://github.com/Jhuster/AudioDemo
audio recode and play demo

from  https://audioprograming.wordpress.com/2012/03/03/android-audio-streaming-with-opensl-es-and-the-ndk/
opnesl_io 集成  封装 OpenSL ES     very nice

假设某音频信号是采样率为8kHz、双通道、位宽为16bit，20ms一帧，则一帧音频数据的大小为：
int size = 8000 x 2 x 16bit x 0.02s = 5120 bit = 640 byte